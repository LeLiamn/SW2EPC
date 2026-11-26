"""Read Samurai Warriors 2: Empires motions (files starting 51 00 00 00) and pose models with them.

Format documented in docs/formats/MOTION.md.

Usage:
  py tools/motion.py motion.bin                         list the tracks
  py tools/motion.py --iso image.iso check              parse every motion of LINKDATA.BNS
  py tools/motion.py --iso image.iso pose ENTRY MODEL MOTION FRAME out.obj [--png out.png]
      pose a model with a motion, e.g. pose 1412 1412.1 1412.2 57 pose.obj
"""
import copy
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

MAGIC = 0x51
FLAG_CURVE = 0x8000     # keys of (end frame, a, b, c, d)
FLAG_VALUE = 0x2000     # constant track with stored values (else implicit zero)
COMPONENTS = ("rotate x", "rotate y", "rotate z", "translate x", "translate y", "translate z")


class MotionError(ValueError):
    pass


def parse(data):
    ident, track_count, frames = struct.unpack_from("<3I", data, 0)
    if ident != MAGIC:
        raise MotionError("Not a motion (first word is not 0x51)")
    p, tracks = 12, []
    for _ in range(track_count):
        header = struct.unpack_from("<I", data, p)[0]
        p += 4
        count = header >> 18
        if header & FLAG_CURVE:
            keys = [struct.unpack_from("<5f", data, p + 20 * k) for k in range(count)]
            p += 20 * count
            kind = "curve"
        elif header & FLAG_VALUE:
            keys = list(struct.unpack_from(f"<{count}f", data, p))
            p += 4 * count
            kind = "constant"
        else:
            keys, kind = [0.0], "constant"
        tracks.append(dict(node=header & 0xFF, component=(header >> 8) & 0xF, kind=kind,
                           keys=keys, header=header))
    return dict(frames=frames, tracks=tracks, end=p)


def sample(track, frame):
    """Value of a track at a frame. Curve segment k covers (end of key k-1, end of key k]."""
    if track["kind"] == "constant":
        return track["keys"][0]
    start = 0.0
    for key in track["keys"]:
        if frame <= key[0] or key is track["keys"][-1]:
            span = (key[0] - start) or 1.0
            t = min(max((frame - start) / span, 0.0), 1.0)
            a, b, c, d = key[1:]
            return ((a * t + b) * t + c) * t + d
        start = key[0]
    return 0.0


def apply(model, motion, frame):
    """Return a copy of a parsed ps2model model with its nodes posed at `frame`."""
    posed = copy.deepcopy(model)
    for track in motion["tracks"]:
        if track["node"] >= len(posed["nodes"]) or track["component"] > 5:
            continue
        node = posed["nodes"][track["node"]]
        value = sample(track, frame)
        if track["component"] < 3:
            r = list(node["rotation"])
            r[track["component"]] = value
            node["rotation"] = tuple(r)
        else:
            t = list(node["translation"])
            t[track["component"] - 3] = value
            node["translation"] = tuple(t)
    return posed


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] != "--iso":
        m = parse(open(sys.argv[1], "rb").read())
        print(f"{m['frames']} frames, {len(m['tracks'])} tracks")
        for t in m["tracks"]:
            comp = COMPONENTS[t["component"]] if t["component"] < 6 else f"component {t['component']}"
            print(f"node {t['node']:3d}  {comp:12}  {t['kind']:8}  {len(t['keys'])} key(s)")
        return

    import pack
    image, command = sys.argv[2], sys.argv[3]
    if command == "check":
        ok = odd = 0
        for path, leaf in pack.iter_bns(image):
            if leaf[:4] != b"\x51\x00\x00\x00":
                continue
            try:
                m = parse(leaf)
                tail = leaf[m["end"]:]
                if not tail or (len(tail) < 16 and not any(tail)):
                    ok += 1
                else:
                    odd += 1
            except (MotionError, struct.error):
                odd += 1
        print(f"{ok} motions parse exactly, {odd} atypical")
    elif command == "pose":
        import ps2model
        entry, model_path, motion_path, frame, out = sys.argv[4:9]
        leaves = dict(pack.iter_bns(image, int(entry), int(entry)))
        posed = apply(ps2model.parse(leaves[model_path]), parse(leaves[motion_path]), float(frame))
        with open(out, "w") as f:
            f.write(ps2model.to_obj(posed))
        if "--png" in sys.argv:
            ps2model.preview_png(posed, sys.argv[sys.argv.index("--png") + 1])
        print(f"Posed {model_path} with {motion_path} at frame {frame} -> {out}")


if __name__ == "__main__":
    main()
