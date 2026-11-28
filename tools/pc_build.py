"""Builds the PC port (a first, unplayable stage) and reports what is missing.

    py tools/pc_build.py --upp <UPP repository> [--stub] [--cc gcc] [--report docs/pc_build.md]
                         [--disc <image>] [--runtime <lib or .c/.o files> ...]

The launcher's header (upp.h) is always taken from the UPP repository (--upp, or the SW2E_UPP
environment variable): <UPP>/include/upp/upp.h. SW2EPC keeps no copy of it, so the build always
follows UPP's current interface. The runtime linked is UPP's upp_runtime, from
<UPP>/build/release/upp_runtime.rsp (build UPP first), or the one given with --runtime. With
--stub, the stand-in in port/stub/ is linked instead (no UPP build needed, still UPP's header).

Steps:
  1. tools/pc_rewrite.py turns src/ into build/pc/src/ (globals become accessors into the PS2
     memory block, docs/port.md);
  2. every file is compiled as 64-bit C (`-DSW2E_PC`); main.c's main() becomes sw2e_ps2_main();
  3. the port's own files are compiled: the game entry (port/sw2e/) and the stand-in runtime
     (port/stub/, until the UPP runtime exists);
  4. every function the code calls but that no file defines yet gets a stop, generated in
     build/pc/missing.c, that names it and ends the program (`not decompiled yet: func_...`);
  5. everything is linked into build/pc/sw2epc.exe.

The report lists the files that do not compile, the functions defined twice, and the missing
functions grouped by area (Sony libraries, VU microcode, game code).

Run the result with the player's own disc image:  build/pc/sw2epc.exe --disc <image> [--run]
"""
import argparse
import collections
import glob
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
B = os.path.join(ROOT, 'build', 'pc')
SONY = [(0x107578, 0x114C10), (0x118E98, 0x1206AC), (0x120E00, 0x143964), (0x1708A8, 0x171FA4),
        (0x403D30, 0x405028)]
VU = (0x3F9680, 0x403D30)


def find_cc():
    for c in (os.environ.get('SW2E_CC'), shutil.which('gcc')):
        if c:
            return c
    g = glob.glob(r"E:\C-Lion\*\bin\mingw\bin\gcc.exe") + glob.glob(r"C:\Program Files\JetBrains\*\bin\mingw\bin\gcc.exe")
    return g[0] if g else None


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True)


def area(addr):
    if any(lo <= addr < hi for lo, hi in SONY):
        return 'Sony libraries'
    if VU[0] <= addr < VU[1]:
        return 'VU microcode area'
    return 'game code'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--cc')
    ap.add_argument('--report', default=os.path.join(ROOT, 'docs', 'pc_build.md'))
    ap.add_argument('--disc', help="the player's disc image: also runs the result once")
    ap.add_argument('--runtime', nargs='+', help='the UPP runtime to link instead of port/stub '
                    '(a static library, objects, or C sources compiled here)')
    ap.add_argument('--upp', default=os.environ.get('SW2E_UPP'),
                    help='the UPP repository (default: the SW2E_UPP environment variable)')
    ap.add_argument('--stub', action='store_true', help='link the stand-in runtime in port/stub/')
    a = ap.parse_args()
    if not a.upp or not os.path.exists(os.path.join(a.upp, 'include', 'upp', 'upp.h')):
        sys.exit('the UPP repository is needed for upp.h: --upp <dir> or SW2E_UPP=<dir> '
                 '(got %r)' % a.upp)
    a.upp_include = os.path.join(a.upp, 'include', 'upp')
    if not a.runtime and not a.stub:
        rsp = os.path.join(a.upp, 'build', 'release', 'upp_runtime.rsp')
        if not os.path.exists(rsp):
            sys.exit('no UPP runtime build: %s is missing (build UPP, or use --stub)' % rsp)
        a.runtime = ['@' + rsp]
        dll = os.path.join(a.upp, 'build', 'release', 'bin', 'libwinpthread-1.dll')
        if os.path.exists(dll):
            os.makedirs(B, exist_ok=True)
            shutil.copy(dll, B)
    cc = a.cc or find_cc()
    if not cc:
        sys.exit('no C compiler: set SW2E_CC')
    nm = os.path.join(os.path.dirname(cc), 'nm.exe' if os.name == 'nt' else 'nm')
    if not os.path.exists(nm):
        nm = shutil.which('nm') or 'nm'
    r = run([sys.executable, os.path.join(ROOT, 'tools', 'pc_rewrite.py'), '--out', os.path.join(B, 'src')])
    if r.returncode:
        sys.exit(r.stdout + r.stderr)
    obj = os.path.join(B, 'obj')
    os.makedirs(obj, exist_ok=True)
    for o in glob.glob(os.path.join(obj, '*.o')):
        os.remove(o)
    flags = ['-m64', '-DSW2E_PC', '-std=gnu99', '-w', '-O0', '-g', '-fno-strict-aliasing', '-fwrapv', '-fcommon']
    failed = {}
    objs = []
    srcs = sorted(glob.glob(os.path.join(B, 'src', '*.c')))
    for s in srcs:
        o = os.path.join(obj, os.path.basename(s)[:-2] + '.o')
        extra = ['-Dmain=sw2e_ps2_main'] if os.path.basename(s) == 'main.c' else []
        r = run([cc] + flags + extra + ['-I', os.path.join(B, 'src'), '-c', s, '-o', o])
        if r.returncode:
            failed[os.path.basename(s)] = [l for l in r.stderr.split('\n') if 'rror' in l][:5]
        else:
            objs.append(o)
    runtime_libs = [x for x in (a.runtime or []) if not x.endswith('.c')]
    port = sorted(glob.glob(os.path.join(ROOT, 'port', 'sw2e', '*.c'))) + \
        ([x for x in a.runtime if x.endswith('.c')] if a.runtime else
         sorted(glob.glob(os.path.join(ROOT, 'port', 'stub', '*.c'))))
    for s in port:
        o = os.path.join(obj, 'port_' + os.path.basename(s)[:-2] + '.o')
        r = run([cc] + flags + ['-I', a.upp_include, '-I', os.path.join(B, 'src'), '-c', s, '-o', o])
        if r.returncode:
            failed['port/' + os.path.basename(s)] = [l for l in r.stderr.split('\n') if 'error' in l][:5]
        else:
            objs.append(o)

    defined = collections.defaultdict(list)
    undefined = collections.defaultdict(set)
    for o in objs:
        r = run([nm, o])
        for l in r.stdout.split('\n'):
            p = l.split()
            if p and p[-1].startswith('.'):
                continue                    # linker helpers (.refptr.*), not symbols of ours
            if len(p) == 3 and p[1] in 'TDBR':
                defined[p[2]].append(os.path.basename(o))
            elif len(p) == 2 and p[0] == 'U':
                undefined[p[1]].add(os.path.basename(o))
    dup = {k: v for k, v in defined.items() if len(v) > 1}
    missing = sorted(k for k in undefined if k not in defined and re.match(r'func_[0-9A-F]{8}$', k))
    other = sorted(k for k in undefined if k not in defined and not re.match(r'func_[0-9A-F]{8}$', k))

    stub = os.path.join(B, 'missing.c')
    with open(stub, 'w', newline='\n') as f:
        f.write('/* generated by tools/pc_build.py: a stop for every function not decompiled yet */\n')
        f.write('void sw2e_missing(const char *name);\n\n')
        for k in missing:
            f.write('int %s() { sw2e_missing("%s"); return 0; }\n' % (k, k))
        # code addresses stored in PS2 data (function tables) -> PC functions
        funcs = sorted(set(k for k in defined if re.match(r'func_[0-9A-F]{8}$', k)) | set(missing))
        f.write('\n/* every function by its PS2 address, for the tables of code addresses in PS2 data */\n')
        f.write('#include <stdlib.h>\n#include <string.h>\n')
        f.write('typedef struct { unsigned int addr; void *fn; } FnEntry;\n')
        for k in funcs:
            f.write('int %s();\n' % k)
        f.write('static const FnEntry g_fns[] = {\n')
        for k in funcs:
            f.write('    { 0x%s, (void *)%s },\n' % (k[5:], k))
        f.write('};\n')
        f.write('''extern unsigned char *sw2e_ram;
unsigned int sw2e_last_bad_code;
static int no_function() { sw2e_missing("a function at an address with no decompiled code (sw2e_last_bad_code)"); return 0; }
static int cmp(const void *a, const void *b)
{
    unsigned int x = *(const unsigned int *)a, y = ((const FnEntry *)b)->addr;
    return x < y ? -1 : x > y;
}
void *sw2e_func(unsigned int a)
{
    const FnEntry *e;
    if (a == 0)
        return 0;
    e = bsearch(&a, g_fns, sizeof(g_fns) / sizeof(g_fns[0]), sizeof(g_fns[0]), cmp);
    if (e)
        return e->fn;
    sw2e_last_bad_code = a;
    return (void *)no_function;
}
/* the PS2 code address of PC function fn (PS2_CODE), 0 for an unknown function */
unsigned int sw2e_code_addr(void *fn)
{
    size_t i;
    if (fn == 0)
        return 0;
    for (i = 0; i < sizeof(g_fns) / sizeof(g_fns[0]); i++)
        if (g_fns[i].fn == fn)
            return g_fns[i].addr;
    sw2e_missing("PS2_CODE of a function with no PS2 address");
    return 0;
}
/* a view of n table entries at PS2 address a, built once per table */
void *const *sw2e_fntab(unsigned int a, int n)
{
    static struct { unsigned int addr; int n; void **v; } cache[256];
    static int ncache;
    int i, k;
    if (n <= 0)
        n = 256;
    for (i = 0; i < ncache; i++)
        if (cache[i].addr == a && cache[i].n >= n)
            return (void *const *)cache[i].v;
    if (ncache == 256)
        ncache = 0;
    i = ncache++;
    cache[i].addr = a;
    cache[i].n = n;
    cache[i].v = malloc(n * sizeof(void *));
    for (k = 0; k < n; k++) {
        unsigned int w;
        memcpy(&w, sw2e_ram + ((a & 0x1FFFFFF) + k * 4), 4);
        cache[i].v[k] = w >= 0x100000 && w < 0x405000 ? sw2e_func(w) : 0;
    }
    return (void *const *)cache[i].v;
}
''')
    mo = os.path.join(obj, 'missing.o')
    r = run([cc] + flags + ['-c', stub, '-o', mo])
    link_errors = []
    exe = os.path.join(B, 'sw2epc.exe' if os.name == 'nt' else 'sw2epc')
    if r.returncode == 0:
        r = run([cc, '-m64'] + objs + [mo] + runtime_libs + ['-o', exe])
        link_errors = [l for l in (r.stdout + r.stderr).split('\n') if l.strip()]
    else:
        link_errors = ['missing.c does not compile'] + r.stderr.split('\n')[:5]

    by_area = collections.Counter(area(int(k[5:], 16)) for k in missing)
    calls = collections.Counter({k: len(undefined[k]) for k in missing})
    out = ['# The PC build', '',
           'Generated by `py tools/pc_build.py` (do not edit by hand). The port is linked with %s;' %
           ('the UPP runtime (`upp_runtime`)' if a.runtime else 'a stand-in for the UPP runtime (`port/stub/`)'),
           'see [port.md](port.md), [upp_integration.md](upp_integration.md) and [launcher.md](launcher.md).', '',
           '## Result', '',
           '| | |', '|---|---|',
           '| Source files compiled | %d of %d |' % (len(srcs) - sum(1 for k in failed if not k.startswith('port/')), len(srcs)),
           '| Port files compiled | %d of %d |' % (len(port) - sum(1 for k in failed if k.startswith('port/')), len(port)),
           '| Functions defined twice | %d |' % len(dup),
           '| Functions called but not decompiled yet | %d |' % len(missing),
           '| Other symbols from outside the sources | %d (C library, port) |' % len(other),
           '| Link | %s |' % ('ok: `build/pc/sw2epc.exe`' if not link_errors and os.path.exists(exe) else 'failed'),
           '']
    if not link_errors and os.path.exists(exe):
        other = []                      # all resolved by the C library and the port files
        if a.disc:
            if a.runtime:
                os.makedirs(os.path.join(B, 'data'), exist_ok=True)
                cmd = [exe, '--disc', a.disc, '--games', os.path.join(a.upp, 'games'),
                       '--data-dir', os.path.join(B, 'data'), '--headless']
            else:
                cmd = [exe, '--disc', a.disc, '--run']
            try:
                r = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
            except subprocess.TimeoutExpired as e:
                err = e.stderr.decode(errors='replace') if isinstance(e.stderr, bytes) else (e.stderr or '')
                r = subprocess.CompletedProcess(cmd, -1, '', err + '\n(stopped after 120 s)')
            out += ['## First run', '', 'With the player\'s own disc image, %s:' %
                    ('UPP runtime, headless' if a.runtime else 'stand-in runtime'), '',
                    '```'] + [l for l in r.stderr.split('\n') if l.strip()][-8:] + ['```', '']
    out += ['## Missing functions by area', '', '| Area | Functions |', '|---|---|']
    out += ['| %s | %d |' % (k, v) for k, v in sorted(by_area.items())]
    out += ['', 'Called from the most files:', '']
    out += ['- `%s` (%s, %d files)' % (k, area(int(k[5:], 16)), n) for k, n in calls.most_common(20)]
    if failed:
        out += ['', '## Files that do not compile', '']
        for k, v in sorted(failed.items()):
            out.append('- `%s`: %s' % (k, ' / '.join(x.split('error: ')[-1] for x in v[:2])))
    if dup:
        out += ['', '## Functions defined twice', '']
        out += ['- `%s`: %s' % (k, ', '.join(v)) for k, v in sorted(dup.items())]
    if other:
        out += ['', '## Other unresolved symbols', '']
        out += ['- `%s` (%s)' % (k, ', '.join(sorted(undefined[k])[:3])) for k in other]
    if link_errors:
        out += ['', '## Link errors (first ones)', '', '```'] + link_errors[:20] + ['```']
    open(a.report, 'w', encoding='utf-8', newline='\n').write('\n'.join(out) + '\n')
    print('\n'.join(out[6:18]))


if __name__ == '__main__':
    main()
