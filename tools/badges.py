"""Our own progress tracking, independent of any web site.

Reads progress/report.json (written by tools/progress.py) and writes:
  progress/badges/*.svg   badges shown by the README (decompiled, matching, functions, data)
  progress/history.csv    one line per change of the numbers (date, code, functions, data)
  progress/PROGRESS.md    a readable summary, with the code areas and the history

Usage: py tools/badges.py            (tools/progress.py also runs it after writing the report)
"""
import csv
import datetime
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROG = os.path.join(ROOT, "progress")
SRC = os.path.join(ROOT, "src")
# A decompiled function's tag ('/* 0xADDRESS, SIZE bytes[, matching]'), as in tools/progress.py.
TAG = re.compile(r"/\* 0x([0-9A-Fa-f]{8}), (0x[0-9A-Fa-f]+|\d+) bytes(, matching)?")
YES, NO = "\u2705", "\u2B1C"         # a ticked and an empty box


def source_functions():
    """[(file, [(address, size, matching), ...])] of the functions decompiled in src/, by file."""
    out = []
    for name in sorted(os.listdir(SRC)):
        if name.endswith(".c"):
            text = open(os.path.join(SRC, name), encoding="utf-8").read()
            funcs = sorted({int(a, 16): (int(s, 0), bool(m)) for a, s, m in TAG.findall(text)}.items())
            if funcs:
                out.append((name, [(a, s, m) for a, (s, m) in funcs]))
    return out
FIELDS = ["date", "code_total", "code_matching", "code_non_matching", "functions_total",
          "functions_matching", "data_total", "data_done"]


def text_width(s):
    """Rough width of `s` in pixels at 11 px Verdana (as the usual flat badges)."""
    wide = "MWmw%@"
    narrow = "il.,:;!|' ()1"
    w = 0.0
    for ch in s:
        w += 9.0 if ch in wide else 3.8 if ch in narrow else 7.0
    return int(w + 0.5)


def badge(label, value, colour):
    lw, vw = text_width(label) + 10, text_width(value) + 10
    w = lw + vw
    return f"""<svg xmlns="http://www.w3.org/2000/svg" width="{w}" height="20" role="img" aria-label="{label}: {value}">
<title>{label}: {value}</title>
<linearGradient id="s" x2="0" y2="100%"><stop offset="0" stop-color="#bbb" stop-opacity=".1"/><stop offset="1" stop-opacity=".1"/></linearGradient>
<clipPath id="r"><rect width="{w}" height="20" rx="3" fill="#fff"/></clipPath>
<g clip-path="url(#r)"><rect width="{lw}" height="20" fill="#555"/><rect x="{lw}" width="{vw}" height="20" fill="{colour}"/><rect width="{w}" height="20" fill="url(#s)"/></g>
<g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" font-size="11">
<text x="{lw / 2:.1f}" y="15" fill="#010101" fill-opacity=".3">{label}</text><text x="{lw / 2:.1f}" y="14">{label}</text>
<text x="{lw + vw / 2:.1f}" y="15" fill="#010101" fill-opacity=".3">{value}</text><text x="{lw + vw / 2:.1f}" y="14">{value}</text>
</g></svg>
"""


def colour(frac):
    return ("#e05d44" if frac < 0.05 else "#fe7d37" if frac < 0.25 else "#dfb317" if frac < 0.5
            else "#a4a61d" if frac < 0.75 else "#97ca00" if frac < 1 else "#4c1")


def pct(a, b):
    return f"{100.0 * a / b:.2f}%" if b else "0%"


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    report = json.load(open(os.path.join(PROG, "report.json"), encoding="utf-8"))
    code, data = report["code"], report["data"]
    funcs = report.get("functions", {"total": 0, "matching": 0})
    done = code["matching"] + code.get("non_matching", 0)

    os.makedirs(os.path.join(PROG, "badges"), exist_ok=True)
    badges = {
        "decompiled": ("decompiled", pct(done, code["total"]), done / code["total"]),
        "matching": ("matching", pct(code["matching"], code["total"]), code["matching"] / code["total"]),
        "functions": ("functions", f"{funcs['matching']} / {funcs['total']}",
                      funcs["matching"] / funcs["total"] if funcs["total"] else 0),
        "data": ("data", pct(data["done"], data["total"]), data["done"] / data["total"]),
    }
    for name, (label, value, frac) in badges.items():
        with open(os.path.join(PROG, "badges", name + ".svg"), "w", encoding="utf-8", newline="\n") as fh:
            fh.write(badge(label, value, colour(frac)))

    # History: a new line only when a number changed.
    hist = os.path.join(PROG, "history.csv")
    rows = list(csv.DictReader(open(hist, encoding="utf-8"))) if os.path.exists(hist) else []
    row = {"date": datetime.date.today().isoformat(), "code_total": code["total"],
           "code_matching": code["matching"], "code_non_matching": code.get("non_matching", 0),
           "functions_total": funcs["total"], "functions_matching": funcs["matching"],
           "data_total": data["total"], "data_done": data["done"]}
    if not rows or any(str(rows[-1][k]) != str(row[k]) for k in FIELDS[1:]):
        rows.append({k: str(v) for k, v in row.items()})
    with open(hist, "w", encoding="utf-8", newline="\n") as fh:
        w = csv.DictWriter(fh, FIELDS, lineterminator="\n")
        w.writeheader()
        w.writerows(rows)

    # Readable summary.
    out = ["# Progress", "",
           "Generated by `tools/badges.py` from `progress/report.json` (no web site involved).", "",
           "| | Done | Total | |", "|---|---:|---:|---:|",
           f"| Code decompiled (bytes) | {done:,} | {code['total']:,} | {pct(done, code['total'])} |",
           f"| Code matching (bytes) | {code['matching']:,} | {code['total']:,} | {pct(code['matching'], code['total'])} |",
           f"| Functions matching | {funcs['matching']:,} | {funcs['total']:,} | {pct(funcs['matching'], funcs['total'])} |",
           f"| Data understood (bytes) | {data['done']:,} | {data['total']:,} | {pct(data['done'], data['total'])} |",
           "", "## Code areas with decompiled code", "",
           f"{YES} = every function decompiled in the area matches the original byte for byte; "
           f"{NO} = some are still non-matching (equivalent C, not yet proven identical). The list of "
           "each function follows the table.", "",
           "| Area | All matching | Functions matching | Matching (bytes) | Non-matching (bytes) | Size (bytes) |",
           "|---|:---:|---:|---:|---:|---:|"]

    def walk(areas, prefix=""):
        for a in areas:
            name = prefix + a["name"]
            if "children" in a:
                walk(a["children"], name + " / ")
            elif "code" in a and (a["code"].get("matching") or a["code"].get("non_matching")):
                c = a["code"]
                f = a.get("decompiled_functions", {})
                n, m = f.get("count", 0), f.get("matching", 0)
                box = YES if n and m == n else NO
                out.append(f"| {name} | {box} | {m} / {n} | {c.get('matching', 0):,} | "
                           f"{c.get('non_matching', 0):,} | {c['total']:,} |")
    walk(report.get("areas", []))
    out += ["", "## Functions by source file", "",
            f"Each function decompiled in `src/`: {YES} matching, {NO} non-matching.", ""]
    for name, funcs in source_functions():
        m = sum(1 for f in funcs if f[2])
        box = YES if m == len(funcs) else NO
        out += [f"<details><summary>{box} <code>src/{name}</code>: {m} / {len(funcs)} matching</summary>", "",
                "| Function | Size (bytes) | Matching |", "|---|---:|:---:|"]
        out += [f"| `func_{a:08X}` | {s:,} | {YES if ok else NO} |" for a, s, ok in funcs]
        out += ["", "</details>", ""]
    out += ["", "## History", "", "| Date | Code matching | Code decompiled | Functions matching | Data |",
            "|---|---:|---:|---:|---:|"]
    for r in reversed(rows):
        ct = int(r["code_total"])
        d = int(r["code_matching"]) + int(r["code_non_matching"])
        out.append(f"| {r['date']} | {pct(int(r['code_matching']), ct)} | {pct(d, ct)} | "
                   f"{r['functions_matching']} | {pct(int(r['data_done']), int(r['data_total']))} |")
    with open(os.path.join(PROG, "PROGRESS.md"), "w", encoding="utf-8", newline="\n") as fh:
        fh.write("\n".join(out) + "\n")
    print(f"Badges, history ({len(rows)} lines) and PROGRESS.md written in {PROG}")


if __name__ == "__main__":
    main()
