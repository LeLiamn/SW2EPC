"""Check the field offsets of the "one object" structs in src/: a field named g_XXXXXXXX inside
`extern struct { ... } s_YYYYYYYY;` must sit at offset XXXXXXXX - YYYYYYYY (compile-time checks
with GCC on a 32-bit target layout). Usage: py tools/check_layout.py [files...]"""
import glob, os, re, subprocess, sys, tempfile

sys.path.insert(0, os.path.dirname(__file__))
from check_src import find_compiler  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def structs(text):
    for m in re.finditer(r"extern struct \{([^{}]*)\} (s_([0-9A-Fa-f]{8}));", text):
        body, name, base = m.group(1), m.group(2), int(m.group(3), 16)
        for f in re.finditer(r"\bg_([0-9A-Fa-f]{8})\b\s*(?:\[[^\]]*\])*\s*;", body):
            yield name, base, "g_" + f.group(1), int(f.group(1), 16)


def check(path, cc):
    text = open(path, encoding="utf-8").read()
    fields = list(structs(text))
    if not fields:
        return 0
    lines = ['#include "%s"' % os.path.abspath(path).replace("\\", "/")]
    for name, base, field, addr in fields:
        lines.append("#undef %s" % field)
        lines.append('_Static_assert(__builtin_offsetof(__typeof__(%s), %s) == 0x%X, "%s: %s not at 0x%X");'
                     % (name, field, addr - base, os.path.basename(path), field, addr - base))
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write("\n".join(lines) + "\n")
        tmp = f.name
    try:
        r = subprocess.run([cc, "-m32", "-fsyntax-only", "-w", "-I", os.path.join(ROOT, "src"), tmp],
                           capture_output=True, text=True)
        if r.returncode and "-m32" in r.stderr:
            r = subprocess.run([cc, "-fsyntax-only", "-w", "-I", os.path.join(ROOT, "src"), tmp],
                               capture_output=True, text=True)
    finally:
        os.unlink(tmp)
    bad = re.findall(r"static assertion failed: \"([^\"]*)\"", r.stderr)
    for b in bad:
        print("BAD  ", b)
    if r.returncode and not bad:
        print("ERROR", path, r.stderr[:500])
    print("%-5s %s (%d fields)" % ("OK" if not r.returncode else "FAIL", os.path.relpath(path, ROOT), len(fields)))
    return len(bad) + (1 if r.returncode and not bad else 0)


def main():
    cc = find_compiler()
    files = sys.argv[1:] or sorted(glob.glob(os.path.join(ROOT, "src", "*.c")))
    sys.exit(1 if sum(check(p, cc) for p in files) else 0)


if __name__ == "__main__":
    main()
