"""Read event files (in-engine cutscenes): a chained list of command records followed by the motions
the event plays. Format documented in docs/formats/EVENT.md.

Usage:
  py tools/event.py file.bin                       list the commands and the embedded motions
  py tools/event.py --iso image.iso check          check every event file of LINKDATA.BNS
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import motion  # noqa: E402

SIGNATURE = bytes.fromhex("1000000000000106")   # first record: next = 0x10, command 0x0601...


class EventError(ValueError):
    pass


def is_event(data):
    return data[:8] == SIGNATURE


def commands(data):
    """Follow the chain: each record starts with the offset of the next one (0 ends the chain)."""
    out, pos = [], 0
    while True:
        nxt, command = struct.unpack_from("<2I", data, pos)
        end = nxt if nxt else pos + 16
        out.append(dict(offset=pos, command=command, payload=data[pos + 8:end]))
        if nxt == 0:
            return out, pos + 16
        if nxt <= pos or nxt % 4 or nxt >= len(data):
            raise EventError(f"Broken command chain at 0x{pos:x}")
        pos = nxt


# Parameter types (func_001D6BD0 reads one value of a type; the sizes of the types above 8 come
# from the step lists of the event files).
TYPE_SIZE = {0: 1, 3: 1, 1: 2, 4: 2, 2: 4, 5: 4, 6: 4, 7: 4, 8: 4, 13: 4, 15: 4}
TYPE_NAME = {0: "s8", 1: "s16", 2: "s32", 3: "u8", 4: "u16", 5: "u32", 6: "f32", 7: "u32",
             8: "u32"}
OLD_SIGNATURE = bytes.fromhex("0000000000000106")  # scenario scripts: record number instead of link


def typed_record(data, pos, end=None):
    """One command record: +4 command, +5 sub-command, +6 number of parameters n, +7 their n type
    codes, then (event files) the offset of the values from +7 and n steps from one value to the
    next. Returns (command, sub, [(type, value bytes)], end of the values)."""
    cmd, sub, n = data[pos + 4], data[pos + 5], data[pos + 6]
    types = list(data[pos + 7:pos + 7 + n])
    params = []
    if n and end is not None:                         # event files: use the offset and steps
        p = pos + 7 + data[pos + 7 + n]
        steps = data[pos + 8 + n:pos + 8 + 2 * n]
        for t, step in zip(types, steps):
            size = TYPE_SIZE.get(t, 2)
            params.append((t, data[p:p + size]))
            p += step if step else size
        return cmd, sub, params, p
    p = pos + 8 + 2 * n if n else pos + 8              # scenario scripts: natural alignment
    for t in types:
        size = TYPE_SIZE.get(t, 2)
        p = (p + size - 1) // size * size
        params.append((t, data[p:p + size]))
        p += size
    return cmd, sub, params, p


def check_commands(data):
    """Check that every record of an event file holds exactly its typed values (then zeros)."""
    cmds, _ = commands(data)
    for c in cmds[:-1]:
        end = c["offset"] + 8 + len(c["payload"])
        _, _, _, p = typed_record(data, c["offset"], end)
        if p > end or any(data[p:end]):
            raise EventError(f"record at 0x{c['offset']:x}: values do not fill it")
    return cmds


def is_old_script(data):
    return data[:8] == OLD_SIGNATURE


def old_script(data):
    """Records of a scenario script (no links: records follow each other, each starting with its
    number, values naturally aligned, records aligned to 4); returns (records, end)."""
    out, pos, i = [], 0, 0
    while True:
        if pos + 8 > len(data) or struct.unpack_from("<I", data, pos)[0] != i:
            raise EventError(f"record {i} not found at 0x{pos:x}")
        cmd, sub, params, p = typed_record(data, pos)
        out.append(dict(offset=pos, command=cmd, sub=sub, params=params))
        pos, i = (p + 3) & ~3, i + 1
        if cmd == 0xFF:
            return out, pos



def _pack2(d):
    """(offset, size) entries of a `count, (offset, size)...` pack."""
    n = struct.unpack_from("<I", d, 0)[0]
    return [struct.unpack_from("<II", d, 4 + 8 * i) for i in range(n)]


def check_dialogues(data):
    """Event dialogues (BNS entry 0172, emp_ev_still.c): a pack of records, each itself a pack
    of 3 parts: a table of offsets (relocated by the game), 16 bytes, and the lines (offset table
    then lines of text with their voice numbers). Returns the number of records."""
    records = _pack2(data)
    for o, s in records:
        rec = data[o:o + s]
        parts = _pack2(rec)
        if len(parts) != 3:
            raise EventError(f"record at 0x{o:x}: not 3 parts")
        (a0, s0), (a1, s1), (a2, s2) = parts
        if not (a0 + s0 <= a1 and a1 + s1 <= a2 and a2 + s2 <= s):
            raise EventError(f"record at 0x{o:x}: parts out of order")
        c = struct.unpack_from("<I", rec, a0)[0]
        offs = struct.unpack_from(f"<{c}I", rec, a0 + 4)
        if list(offs) != sorted(offs) or (offs and offs[-1] >= s0):
            raise EventError(f"record at 0x{o:x}: bad offset table")
        if s2:
            k = struct.unpack_from("<I", rec, a2)[0] // 4
            lines = struct.unpack_from(f"<{k}I", rec, a2)
            if list(lines) != sorted(lines) or lines[-1] >= s2:
                raise EventError(f"record at 0x{o:x}: bad line table")
    return len(records)

def motions(data, start):
    """Find the embedded motions after the command chain: (prefix word, offset, parsed motion)."""
    found, pos = [], start
    while True:
        i = data.find(b"\x51\x00\x00\x00", pos)
        if i < 0:
            return found
        try:
            m = motion.parse(data[i:])
            if 0 < m["frames"] < 100000 and m["tracks"] and m["end"] > 12:
                found.append((struct.unpack_from("<i", data, i - 4)[0], i, m))
                pos = i + m["end"]
                continue
        except (motion.MotionError, struct.error):
            pass
        pos = i + 4


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] != "--iso":
        data = open(sys.argv[1], "rb").read()
        cmds, end = commands(data)
        for c in cmds:
            print(f"0x{c['offset']:06x}  command 0x{c['command']:08x}  {len(c['payload'])} bytes")
        for prefix, offset, m in motions(data, end):
            print(f"motion at 0x{offset:06x} (prefix {prefix}): {m['frames']} frames, {len(m['tracks'])} tracks")
        return
    import pack
    files = ok = cmd_total = mot_total = covered = size = 0
    for path, leaf in pack.iter_bns(sys.argv[2]):
        if not is_event(leaf):
            continue
        files += 1
        size += len(leaf)
        try:
            cmds, end = commands(leaf)
            mots = motions(leaf, end)
            ok += 1
            cmd_total += len(cmds)
            mot_total += len(mots)
            covered += sum(m["end"] for _, _, m in mots)
        except (EventError, struct.error) as e:
            print(f"FAIL {path}: {e}")
    print(f"{ok}/{files} event files: {cmd_total} commands, {mot_total} motions "
          f"({covered / max(size, 1) * 100:.1f}% of the bytes)")


if __name__ == "__main__":
    main()
