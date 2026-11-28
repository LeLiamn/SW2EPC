"""Rewrite src/*.c for the PC build: every `extern` declaration of a global named after its PS2
address (g_XXXXXXXX, s_XXXXXXXX for structures, g_XXXXXXXX_name for another view of the same
address) becomes an accessor into the PS2 memory block (see docs/port.md and
src/sw2e_mem.h). The sources stay as they are for the PS2 build; the rewritten copies go to an
output folder.

    py tools/pc_rewrite.py [--out build/pc/src] [--report] [file.c ...]

    extern int g_0045D7FC;          ->  #define g_0045D7FC (*(int *)PS2_MEM(0x0045D7FC))
    extern u8 g_00669D60[0x300];    ->  #define g_00669D60 (*(u8 (*)[0x300])PS2_MEM(0x00669D60))
    extern u8 g_00412680[];         ->  #define g_00412680 ((u8 *)PS2_MEM(0x00412680))
    extern struct {...} g_007BF680; ->  typedef struct {...} pc_t_007BF680;
                                        #define g_007BF680 (*(pc_t_007BF680 *)PS2_MEM(0x007BF680))

A global declared with a pointer type is reported. In PS2 memory it is a 4-byte address, so it
has to become a ps2ptr (or an array of them) before the PC build can use it.
"""
import glob
import os
import re
import sys

NAME = re.compile(r'\b[gs]_([0-9A-Fa-f]{8})(?:_\w+)?\b')


def statements(src):
    """(start, end) of each top-level `extern ...;` statement, braces included"""
    i = 0
    while True:
        m = re.compile(r'^extern\b', re.M).search(src, i)
        if not m:
            return
        j, depth = m.end(), 0
        while j < len(src):
            c = src[j]
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
            elif c == ';' and depth == 0:
                break
            j += 1
        yield m.start(), j + 1
        i = j + 1


def split_top(s, sep=','):
    out, depth, cur = [], 0, ''
    for c in s:
        if c in '([{':
            depth += 1
        elif c in ')]}':
            depth -= 1
        if c == sep and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += c
    out.append(cur)
    return out


FNPTR = re.compile(r'\(\s*\*\s*(g_([0-9A-Fa-f]{8}))\s*(\[([^\]]*)\])?\s*\)\s*\(([^()]*)\)')


def rewrite_fnptr(body, report, fname):
    """function pointers stored in PS2 data: tables become views converting each PS2 code address
    to the PC function (sw2e_fntab, from the functions' address tags); single pointers, which the
    game sets itself, become PC variables"""
    ret = body[:body.index('(')].strip()
    out = []
    for m in FNPTR.finditer(body):
        name, addr, dims, n, args = m.group(1), m.group(2).upper(), m.group(3), m.group(4), m.group(5)
        if dims is not None:
            out.append('#define %s ((%s (**)(%s))sw2e_fntab(0x%s, %s))' % (name, ret, args, addr, n.strip() or '0'))
        else:
            out.append('%s (*%s)(%s);   /* a PC variable (PS2 0x%s) */' % (ret, name, args, addr))
            report.append('%s: function pointer %s kept as a PC variable' % (fname, name))
    if not out:
        report.append('%s: function pointer not understood: %s' % (fname, ' '.join(body.split())[:80]))
        return None
    return '\n'.join(out)


def rewrite_decl(text, report, fname):
    """the replacement for one extern statement, or None to keep it"""
    body = text[len('extern'):-1].strip()
    if NAME.search(body) and '{' not in body and '(*' in body:
        return rewrite_fnptr(body, report, fname)
    if not NAME.search(body):
        return None
    # base type: up to the end of a struct body, or up to the first declarator
    if '{' in body:
        k = body.rindex('}') + 1
        base, rest = body[:k], body[k:]
    else:
        m = re.search(r'[\s*]*\b[gs]_[0-9A-Fa-f]{8}(?:_\w+)?\b', body)
        base, rest = body[:m.start()], body[m.start():]
    base = base.strip()
    if base.startswith('const '):
        base_q = base
    else:
        base_q = base
    out = []
    tname = None
    if not NAME.search(rest):
        return None                      # not a global named after its address
    if '{' in base:
        first = NAME.search(rest).group(1).upper()
        tname = 'pc_t_%s' % first
        out.append('typedef %s %s;' % (base, tname))
        base_q = tname
    for d in split_top(rest):
        d = d.strip()
        if not d:
            continue
        m = re.match(r'(\**)\s*([gs]_([0-9A-Fa-f]{8})(?:_\w+)?)\s*((?:\[[^\]]*\])*)\s*$', d)
        if not m:
            report.append('%s: not understood: %s' % (fname, d))
            return None
        stars, addr, dims = m.group(1), m.group(3).upper(), m.group(4)
        name = m.group(2)
        if stars:
            report.append('%s: pointer global %s (%s%s): make it a ps2ptr' % (fname, name, base_q, stars))
        t = base_q + (' ' + stars if stars else '')
        if dims.startswith('[]'):
            rest_dims = dims[2:]
            if rest_dims:
                out.append('#define %s ((%s (*)%s)PS2_MEM(0x%s))' % (name, t, rest_dims, addr))
            else:
                out.append('#define %s ((%s *)PS2_MEM(0x%s))' % (name, t, addr))
        elif dims:
            out.append('#define %s (*(%s (*)%s)PS2_MEM(0x%s))' % (name, t, dims, addr))
        else:
            out.append('#define %s (*(%s *)PS2_MEM(0x%s))' % (name, t, addr))
    return '\n'.join(out)


def rewrite(src, report, fname):
    out, last = [], 0
    for s, e in statements(src):
        new = rewrite_decl(src[s:e], report, fname)
        if new is None:
            continue
        out.append(src[last:s])
        out.append(new)
        last = e
    out.append(src[last:])
    res = ''.join(out)
    # the memory model header, after the typedefs
    if 'sw2e_mem.h' not in res:
        m = re.search(r'typedef unsigned int u32;\n', res)
        if m:
            res = res[:m.end()] + '\n#include "sw2e_mem.h"\n' + res[m.end():]
        else:
            report.append('%s: no u32 typedef, header not added' % fname)
    return res


def main():
    args = sys.argv[1:]
    outdir = os.path.join('build', 'pc', 'src')
    if '--out' in args:
        i = args.index('--out')
        outdir = args[i + 1]
        del args[i:i + 2]
    show = '--report' in args
    args = [a for a in args if a != '--report']
    files = args or sorted(glob.glob(os.path.join('src', '*.c')))
    os.makedirs(outdir, exist_ok=True)
    report = []
    for f in files:
        src = open(f, encoding='utf-8').read()
        open(os.path.join(outdir, os.path.basename(f)), 'w', encoding='utf-8', newline='\n').write(
            rewrite(src, report, os.path.basename(f)))
    for h in glob.glob(os.path.join('src', '*.h')):
        open(os.path.join(outdir, os.path.basename(h)), 'w', encoding='utf-8', newline='\n').write(
            open(h, encoding='utf-8').read())
    ptrs = [r for r in report if 'pointer global' in r]
    other = [r for r in report if 'pointer global' not in r]
    print('%d files rewritten to %s; %d pointer globals to convert; %d other notes'
          % (len(files), outdir, len(ptrs), len(other)))
    if show:
        print('\n'.join(report))


if __name__ == '__main__':
    main()
