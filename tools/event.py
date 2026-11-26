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
