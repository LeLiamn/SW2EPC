"""Writes src/sw2e_protos.h: one prototype per non-static function defined in src/*.c, taken from
its definition (the definition is the reference). Types that are local to a file (structures,
typedefs of other names) become `void *` for pointers; functions taking or returning such types by
value are left out. The header is included by every file in src/ so that each call to a decompiled
function is checked against its real parameters. The prototypes are grouped by defining file, each
group behind a guard (SW2E_FILE_UNIT_C for unit.c) that the defining file sets before including the
header, so its own definitions (which may use its local types) are not declared twice.

Usage: py tools/make_protos.py
"""
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASIC = {'void', 'int', 'u8', 'u16', 'u32', 'u64', 's8', 'short', 'char', 'float', 'ps2ptr',
         'unsigned int', 'unsigned short', 'unsigned char', 'signed char', 'unsigned long long',
         'long long', 'unsigned', 'signed int', 'signed short'}
DEF = re.compile(r'^((?:const )?(?:unsigned |signed )?[A-Za-z_]\w*(?: (?:long|int|short|char))*\s*\**)\s*'
                 r'(func_[0-9A-F]{8})\(([^()]*)\)\s*$', re.M)


def norm_type(t):
    """basic type text, or None when the type is local to a file"""
    t = ' '.join(t.replace('*', ' * ').split())
    stars = t.count('*')
    const = 'const ' if re.match(r'^const\b', t) else ''
    base = t.replace('*', '').replace('const', '').strip()
    base = ' '.join(base.split())
    base = {'u64': 'unsigned long long', 's8': 'signed char', 'u8': 'unsigned char', 'u16': 'unsigned short',
            'u32': 'unsigned int'}.get(base, base)
    if base in BASIC:
        return (const if stars else '') + base + (' ' + '*' * stars if stars else '')
    if stars:
        return const + ('void ' + '*' * stars if stars == 1 else 'void *')
    return None


def param(p):
    p = p.strip()
    if p in ('', 'void'):
        return 'void'
    if '(' in p or '[' in p:
        return None
    m = re.match(r'^(.*?)(\w+)$', p)
    if not m or not m.group(1).strip():
        return norm_type(p)
    t = norm_type(m.group(1))
    return t if t is None else t


def guard_name(name):
    """SW2E_FILE_UNIT_C for unit.c: a file defines it before including this header, which then
    leaves out its own functions (their definitions in the file are the reference)"""
    return 'SW2E_FILE_' + re.sub(r'\W', '_', name).upper()


def main():
    defs = {}
    for f in sorted(glob.glob(os.path.join(ROOT, 'src', '*.c'))):
        text = open(f, encoding='utf-8', errors='replace').read()
        for m in DEF.finditer(text):
            after = text[m.end():m.end() + 3].lstrip('\r\n')
            if not after.startswith('{'):
                continue
            line_start = text.rfind('\n', 0, m.start()) + 1
            if text[line_start:m.start()].strip():
                continue
            ret = norm_type(m.group(1))
            ps = [param(p) for p in m.group(3).split(',')]
            if ret is None or None in ps:
                continue
            if ps == ['void'] and m.group(3).strip() == '':
                continue                    # K&R style: no parameter information
            defs[m.group(2)] = (os.path.basename(f),
                                '%s%s%s(%s);' % (ret, '' if ret.endswith('*') else ' ', m.group(2), ', '.join(ps)))
    out = ['/*',
           ' * sw2e_protos.h - prototypes of the functions defined in src/, written by tools/make_protos.py',
           ' * from their definitions (do not edit by hand). Types local to a file appear as void *.',
           ' * A file defines SW2E_FILE_<NAME>_C before including it, which leaves out its own functions.',
           ' * Where the original callers of a file see a function differently from its definition (they do',
           ' * not mask a byte result, say), the file defines SW2E_OWN_PROTO_func_<ADDR> and declares it',
           ' * itself, on the PS2 build only.',
           ' */',
           '#ifndef SW2E_PROTOS_H',
           '#define SW2E_PROTOS_H',
           '',
           '/* uses only basic C types, plus ps2ptr (sw2e_mem.h) */',
           '']
    # functions some file declares its own way on the PS2 build (SW2E_OWN_PROTO_func_...)
    own = set()
    for f in glob.glob(os.path.join(ROOT, 'src', '*.c')):
        own |= set(re.findall(r'#define SW2E_OWN_PROTO_(func_[0-9A-F]{8})', open(f, encoding='utf-8').read()))
    by_file = {}
    for k in sorted(defs):
        line = defs[k][1]
        if k in own:
            line = '#ifndef SW2E_OWN_PROTO_%s\n%s\n#endif' % (k, line)
        by_file.setdefault(defs[k][0], []).append(line)
    for name in sorted(by_file):
        guard = guard_name(name)
        out += ['#ifndef ' + guard] + by_file[name] + ['#endif', '']
    out += ['', '#endif', '']
    open(os.path.join(ROOT, 'src', 'sw2e_protos.h'), 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
    print(len(defs), 'prototypes')


if __name__ == '__main__':
    main()
