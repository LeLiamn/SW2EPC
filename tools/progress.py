"""Build a progress report in the decompilati.onl format (https://decompilati.onl/docs/report-format).

The report only contains numbers (byte counts) and format names: no game data. It needs your own
disc image, so it is generated locally and committed as progress/report.json.

What is measured:
- code: the boot executable named in SYSTEM.CNF. "total" is its code size (the .text section
  if it has one, else an estimate up to the last `jr $ra`). "matching" / "non_matching" come
  from MATCHED_CODE below until a real build/objdiff report replaces them.
- data: every file on the disc except the executable, SYSTEM.CNF and IOP modules. LINKDATA
  containers and the packs inside them are opened (see tools/pack.py) and their leaves grouped by
  real format (signature); the container structure itself (tables, padding) counts as "Containers". Other files are grouped
  by extension. A format counts as "done" when it is fully documented in docs/formats and readable
  by the tools. Statuses live in FORMAT_STATUS below.

Usage:
  py tools/progress.py image.iso            write progress/report.json
  py tools/progress.py image.iso --stdout   print it instead
"""
import json
import os
import sys
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import elf_info  # noqa: E402
from disc_info import system_cnf  # noqa: E402
from iso_list import SECTOR, list_image, read_file  # noqa: E402
import linkdata  # noqa: E402
import pack  # noqa: E402

# Format -> ("done" | "todo", description). Keep in sync with docs/formats/README.md.
FORMAT_STATUS = {
    "Containers": ("done", "LINKDATA and pack tables, padding"),
    "TIM2": ("done", "Textures (Sony TIM2), convertible to PNG"),
    "MPEG2": ("todo", "Movies (MPEG-2 program streams)"),
    "ANS stream": ("todo", "Audio streams (music?)"),
    "PS2": ("todo", "Files starting with 'PS2 '"),
    "tm3": ("todo", "Files starting with 'tm3 '"),
    "TMD2": ("todo", "Files starting with 'TMD2'"),
    "IPU": ("todo", "IPU images (ipu2)"),
    "PAC0": ("todo", "PAC0 files"),
    "Unidentified": ("todo", "Leaves without a known signature (models, motions, scripts...)"),
}

MATCHED_CODE = {"matching": 0, "non_matching": 0}

SKIP_EXTENSIONS = {"IRX", "IMG", "CNF"}
CONTAINER_KIND = {"ANS": "ANS stream", "CNS": "MPEG2"}
LEAF_KIND = {"tm2": "TIM2", "tm3": "tm3", "tmd2": "TMD2", "ps2": "PS2", "pac": "PAC0",
             "ipu": "IPU", "pss": "MPEG2", "bin": "Unidentified"}


def count_container(data, sizes, forced_kind=None):
    """Add a LINKDATA container's bytes to `sizes`, by leaf format (opening nested packs)."""
    used = 0
    if forced_kind:
        for e in linkdata.parse_header(data)["entries"]:
            sizes[forced_kind] += e["size"]
            used += e["size"]
    else:
        for _, leaf in pack.iter_leaves(data):
            sizes[LEAF_KIND[pack.kind_of(leaf)]] += len(leaf)
            used += len(leaf)
    sizes["Containers"] += len(data) - used


def code_total(elf):
    text = next((s for s in elf["sections"] if s["name"] == ".text"), None)
    if text:
        return text["size"]
    start, end, _ = elf_info.estimate_code(elf)
    return end - start


def build_report(image):
    _, exe = system_cnf(image)
    elf = elf_info.parse(read_file(image, exe))
    total = code_total(elf)

    sizes = defaultdict(int)
    disc = open(image, "rb")
    for name, lba, size in list_image(image)[2]:
        base = os.path.basename(name)
        ext = base.rsplit(".", 1)[-1].upper() if "." in base else "(none)"
        if base.upper() == exe.upper() or ext in SKIP_EXTENSIONS or "/MODULES/" in name.upper():
            continue
        if base.upper().startswith("LINKDATA."):
            disc.seek(lba * SECTOR)
            count_container(disc.read(size), sizes, CONTAINER_KIND.get(ext))
        else:
            sizes[ext] += size
    disc.close()

    areas = []
    for kind, size in sorted(sizes.items(), key=lambda kv: -kv[1]):
        status, description = FORMAT_STATUS.get(kind, ("todo", "Not studied yet"))
        areas.append({"name": kind, "description": description,
                      "data": {"total": size, "done": size if status == "done" else 0}})

    code = {"total": total, **MATCHED_CODE}
    return {
        "unit": "bytes",
        "code": code,
        "data": {"total": sum(a["data"]["total"] for a in areas),
                 "done": sum(a["data"]["done"] for a in areas)},
        "layout": "treemap",
        "areas": [
            {"name": "Executable", "description": f"{exe} code", "code": code},
            {"name": "Game data", "description": "Files on the disc, by format",
             "weight": total, "children": areas},
        ],
    }


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    report = build_report(sys.argv[1])
    text = json.dumps(report, indent=2) + "\n"
    if "--stdout" in sys.argv:
        print(text, end="")
        return
    out = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                       "progress", "report.json")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(text)
    print(f"Wrote {out}: code {report['code']['matching']}/{report['code']['total']} bytes, "
          f"data {report['data']['done']}/{report['data']['total']} bytes")


if __name__ == "__main__":
    main()
