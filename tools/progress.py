"""Build a progress report in the decompilati.onl format (https://decompilati.onl/docs/report-format).

The report only contains numbers (byte counts) and format names: no game data. It needs your own
disc image, so it is generated locally and committed as progress/report.json.

What is measured:
- code: the boot executable named in SYSTEM.CNF. "total" is its code size (the .text section
  if it has one, else an estimate up to the last `jr $ra`). "matching" / "non_matching" come
  from MATCHED_CODE below until a real build/objdiff report replaces them.
- data: every file on the disc except the executable, SYSTEM.CNF and IOP modules, grouped by
  extension. A format counts as "done" when it is fully documented in docs/formats and readable
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
from iso_list import list_image, read_file  # noqa: E402

# Extension (upper case, without the dot) -> ("done" | "todo", description).
# Keep in sync with docs/formats/README.md.
FORMAT_STATUS = {}

MATCHED_CODE = {"matching": 0, "non_matching": 0}

SKIP_EXTENSIONS = {"IRX", "IMG", "CNF"}


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
    for name, _, size in list_image(image)[2]:
        base = os.path.basename(name)
        ext = base.rsplit(".", 1)[-1].upper() if "." in base else "(none)"
        if base.upper() == exe.upper() or ext in SKIP_EXTENSIONS:
            continue
        sizes[ext] += size

    areas = []
    for ext, size in sorted(sizes.items(), key=lambda kv: -kv[1]):
        status, description = FORMAT_STATUS.get(ext, ("todo", "Not studied yet"))
        areas.append({"name": f".{ext}", "description": description,
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
