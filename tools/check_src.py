"""Check that the decompiled C in src/ is valid C (syntax and types), with any GCC or Clang.

This does not build a PS2 executable: it only compiles each file with -fsyntax-only and warnings on,
to catch typos, wrong types and undeclared names. The compiler is taken from the SW2E_CC
environment variable, else `gcc` on the PATH, else the MinGW GCC bundled with CLion.

Usage: py tools/check_src.py
"""
import glob
import os
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CLION_GCC = glob.glob(r"E:\C-Lion\*\bin\mingw\bin\gcc.exe") + \
    glob.glob(r"C:\Program Files\JetBrains\*\bin\mingw\bin\gcc.exe")


def find_compiler():
    if os.environ.get("SW2E_CC"):
        return os.environ["SW2E_CC"]
    return shutil.which("gcc") or shutil.which("clang") or (CLION_GCC[0] if CLION_GCC else None)


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    cc = find_compiler()
    if not cc:
        sys.exit("No C compiler found: set SW2E_CC to gcc or clang")
    sources = sorted(glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True))
    failed = 0
    for src in sources:
        r = subprocess.run([cc, "-std=c99", "-fsyntax-only", "-Wall", "-Wextra", "-Wno-unused-parameter",
                            "-I", os.path.join(ROOT, "src"), src], capture_output=True, text=True)
        status = "OK" if r.returncode == 0 and not r.stderr.strip() else ("WARN" if r.returncode == 0 else "FAIL")
        failed += r.returncode != 0
        print(f"{status:4}  {os.path.relpath(src, ROOT)}")
        if r.stderr.strip():
            print(r.stderr.strip())
    print(f"{len(sources)} file(s) checked with {os.path.basename(cc)}, {failed} failed")
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
