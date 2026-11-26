"""Find interesting ASCII strings in a binary (a simplified `strings`).

Usage:
  py tools/find_strings.py file                 every string (>= 5 characters)
  py tools/find_strings.py file --report        source file names, paths, mangled C++ names
"""
import re
import sys


def extract(data, min_len=5):
    pattern = rb"[\x20-\x7e]{%d,}" % min_len
    return [(m.start(), m.group().decode("ascii")) for m in re.finditer(pattern, data)]


def report(strings):
    texts = [s for _, s in strings]
    sources = sorted({m for s in texts for m in re.findall(r"[A-Za-z0-9_]+\.(?:cpp|c|cc|h|hpp|s)\b", s)})
    print(f"== Source files named: {len(sources)}")
    print(" ".join(sources))
    backslash = chr(92)
    paths = sorted({s for s in texts
                    if ("/" in s or backslash in s or "%s" in s) and re.search(r"\.\w{2,4}\b", s)})
    print(f"\n== Paths / file name templates: {len(paths)}")
    print("\n".join(paths))
    mangled = sorted({s for s in texts if re.search(r"__[A-Z0-9]", s)})
    print(f"\n== Likely mangled C++ names: {len(mangled)}")
    print("\n".join(mangled[:100]))


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    strings = extract(open(sys.argv[1], "rb").read())
    if "--report" in sys.argv:
        report(strings)
    else:
        for off, s in strings:
            print(f"{off:08x}  {s}")


if __name__ == "__main__":
    main()
