"""Build a progress report in the decompilati.onl format (https://decompilati.onl/docs/report-format).

The report only contains numbers (byte counts) and format names: no game data. It needs your own
disc image, so it is generated locally and committed as progress/report.json.

What is measured:
- code: the boot executable named in SYSTEM.CNF. "total" is its code size (the .text section
  if it has one, else an estimate up to the last `jr $ra`). "non_matching" = the original size of the
  functions decompiled in src/ (each tagged '/* 0xADDRESS, SIZE bytes'); "matching" = those whose
  tag goes on with ', matching' (proven byte-identical with the original compiler on decomp.me, the
  scratch link follows the tag).
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
import re
import os
import sys
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import elf_info  # noqa: E402
from disc_info import system_cnf  # noqa: E402
from iso_list import SECTOR, list_image, read_file  # noqa: E402
import linkdata  # noqa: E402
import pack  # noqa: E402
import motion  # noqa: E402
import event  # noqa: E402

# Format -> ("done" | "todo", description). Keep in sync with docs/formats/README.md.
FORMAT_STATUS = {
    "Containers": ("done", "LINKDATA and pack tables (3 pack variants), padding"),
    "TIM2": ("done", "Textures (Sony TIM2), convertible to PNG"),
    "MPEG2": ("done", "Movies (Sony PSS: MPEG-2 + ADPCM + AC-3), exportable to MKV"),
    "ANS stream": ("done", "Music streams (SPU ADPCM), decodable to WAV"),
    "PS2": ("done", "3D models with skeleton and skinning, exportable to OBJ"),
    "Motion": ("done", "Animations (keyframed cubic curves per node and component)"),
    "Motion (atypical)": ("todo", "Motions with an unknown track type"),
    "ADPCM sounds": ("done", "Sound-effect bank and other raw SPU ADPCM files, decodable to WAV"),
    "Event motions": ("done", "Motions embedded in the in-engine cutscene (event) files"),
    "Event commands": ("todo", "Command chains of the event files (meaning not decoded yet)"),
    "PS2 variant": ("todo", "'PS2 ' files without nodes (different layout)"),
    "tm3": ("done", "Textures as GS upload packets (8-bit + palettes), convertible to PNG"),
    "TMD2": ("done", "Static scene objects (geometry, UVs, colours, normals), exportable to OBJ"),
    "IPU": ("todo", "IPU images (ipu2)"),
    "PAC0": ("todo", "PAC0 files"),
    "EFB": ("todo", "Visual effects: structure known, parameters not yet"),
    "Unidentified": ("todo", "Leaves without a known signature (models, motions, scripts...)"),
}

SRC_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "src")
FUNCTION_TAG = re.compile(r"/\* 0x([0-9A-Fa-f]{8}), (0x[0-9A-Fa-f]+|\d+) bytes(, matching)?")


def decompiled_functions():
    """{address: (size, matching)} of the functions decompiled in src/, each tagged
    '/* 0xADDRESS, SIZE bytes' (', matching' after it when proven on decomp.me)."""
    seen = {}
    for root, _, files in os.walk(SRC_DIR):
        for name in files:
            if name.endswith((".c", ".h")):
                text = open(os.path.join(root, name), encoding="utf-8").read()
                for addr, size, matching in FUNCTION_TAG.findall(text):
                    seen[int(addr, 16)] = (int(size, 0), bool(matching))
    return seen


def decompiled_code():
    """Bytes of original code covered by src/: matching (proven on decomp.me) and non-matching
    (equivalent C, not verified by compiling)."""
    return split(decompiled_functions().values()), len(decompiled_functions())


def split(functions):
    """{"matching": bytes, "non_matching": bytes} of (size, matching) pairs."""
    functions = list(functions)
    return {"matching": sum(s for s, m in functions if m),
            "non_matching": sum(s for s, m in functions if not m)}


CODE_MAP = os.path.join(os.path.dirname(SRC_DIR), "progress", "code_map.json")


def code_areas(start, end):
    """Split the code into areas by original source file, grouped by theme.

    Each source file is placed by the functions that reference its name (progress/code_map.json);
    a file's estimated range runs from halfway after the previous file's anchors to halfway before
    the next one's. These ranges are estimates until the files' real boundaries are known."""
    cmap = json.load(open(CODE_MAP, encoding="utf-8"))
    anchors = sorted((int(a, 16), name) for name, addrs in cmap["anchors"].items() for a in addrs)
    runs = []                                    # consecutive anchors of the same file
    for addr, name in anchors:
        if runs and runs[-1][0] == name:
            runs[-1][2] = addr
        else:
            runs.append([name, addr, addr])
    ranges = defaultdict(list)
    first = runs[0][1]
    ranges["(start-up and main loop)"].append((start, first))
    for i, (name, lo, hi) in enumerate(runs):
        a = first if i == 0 else (runs[i - 1][2] + lo) // 2
        b = end if i == len(runs) - 1 else (hi + runs[i + 1][1]) // 2
        ranges[name].append((a, b))
    done = decompiled_functions()

    def leaf(name):
        spans = ranges[name]
        total = sum(b - a for a, b in spans)
        mine = {f: s for f, s in done.items() if any(a <= f < b for a, b in spans)}
        where = ", ".join(f"0x{a:06X}-0x{b:06X}" for a, b in spans)
        return {"name": name, "description": f"Estimated range {where}; {len(mine)} function(s) decompiled",
                "code": {"total": total, **split(mine.values())}}

    areas = [leaf("(start-up and main loop)")]
    areas[0]["description"] = "Runtime start-up, scene manager and main loop. " + areas[0]["description"]
    for theme, files in cmap["themes"].items():
        children = [leaf(f) for f in files if f in ranges]
        if children:
            areas.append({"name": theme, "children": children})
    return areas

SKIP_EXTENSIONS = {"IRX", "IMG", "CNF"}
CONTAINER_KIND = {"ANS": "ANS stream", "CNS": "MPEG2"}
LEAF_KIND = {"tm2": "TIM2", "tm3": "tm3", "tmd2": "TMD2", "ps2": "PS2", "pac": "PAC0",
             "ipu": "IPU", "pss": "MPEG2", "efb": "EFB", "bin": "Unidentified"}


def is_raw_adpcm(leaf):
    """Raw SPU ADPCM: starts with a silent frame and every frame looks like ADPCM."""
    if len(leaf) < 64 or len(leaf) % 16 or any(leaf[:16]):
        return False
    frames = range(16, len(leaf), 16)
    good = sum(1 for i in frames if (leaf[i] >> 4) <= 4 and (leaf[i] & 15) <= 12
               and leaf[i + 1] in (0, 1, 2, 3, 4, 6, 7))
    return good >= 0.99 * len(frames)


def motion_parses(leaf):
    try:
        tail = leaf[motion.parse(leaf)["end"]:]
    except (motion.MotionError, ValueError, Exception):
        return False
    return not tail or (len(tail) < 16 and not any(tail))


def count_container(data, sizes, forced_kind=None):
    """Add a LINKDATA container's bytes to `sizes`, by leaf format (opening nested packs)."""
    used = 0
    if forced_kind:
        for e in linkdata.parse_header(data)["entries"]:
            sizes[forced_kind] += e["size"]
            used += e["size"]
    else:
        for _, leaf in pack.iter_leaves(data):
            kind = LEAF_KIND[pack.kind_of(leaf)]
            if kind == "PS2" and leaf[0x10:0x12] == bytes(2):
                kind = "PS2 variant"
            elif kind == "Unidentified" and leaf[:4] == bytes((0x51, 0, 0, 0)):
                kind = "Motion" if motion_parses(leaf) else "Motion (atypical)"
            elif kind == "Unidentified" and is_raw_adpcm(leaf):
                kind = "ADPCM sounds"
            elif kind == "Unidentified" and event.is_event(leaf):
                try:
                    _, end = event.commands(leaf)
                    played = sum(m["end"] for _, _, m in event.motions(leaf, end))
                except (event.EventError, ValueError):
                    played = 0
                sizes["Event motions"] += played
                sizes["Event commands"] += len(leaf) - played
                used += len(leaf)
                continue
            sizes[kind] += len(leaf)
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

    matched, functions = decompiled_code()
    code = {"total": total, **matched}
    start, _, _ = elf_info.estimate_code(elf)
    return {
        "unit": "bytes",
        "code": code,
        "data": {"total": sum(a["data"]["total"] for a in areas),
                 "done": sum(a["data"]["done"] for a in areas)},
        "layout": "treemap",
        "areas": code_areas(start, start + total) + [
            {"name": "Game data", "description": "Files on the disc, by format (data only)",
             "weight": total // 10, "children": areas},
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
