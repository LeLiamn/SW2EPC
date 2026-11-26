"""IPU movies (`ipu2`), see docs/formats/IPU.md.

An `ipu2` file holds a sequence of PS2 IPU frames (MPEG-1-like intra pictures decoded by the
PS2's image processing unit) with a table of frame offsets. This tool rewrites it as the usual
`ipum` stream that FFmpeg reads (its "ipu" demuxer and decoder), and can convert that to a video.

Usage:
  py tools/ipu.py FILE.ipu2                 print the header
  py tools/ipu.py FILE.ipu2 OUT.ipu         write an ipum stream
  py tools/ipu.py FILE.ipu2 OUT.mkv         write a video (needs ffmpeg on the PATH)
"""
import os
import struct
import subprocess
import sys
import tempfile

MAGIC = b"ipu2"
END = b"\x00\x00\x01\xb0"    # end code closing every frame


class IpuError(Exception):
    pass


def parse(data):
    """{"width", "height", "frames": [(offset, size)]} (raises IpuError)."""
    if data[:4] != MAGIC or len(data) < 16:
        raise IpuError("not an ipu2 file")
    size, width, height, count = struct.unpack_from("<IHHI", data, 4)
    if size != len(data) or not count:
        raise IpuError("bad header")
    frames = [struct.unpack_from("<II", data, 16 + 8 * i) for i in range(count)]
    pos = (16 + 8 * count + 15) & ~15
    for i, (off, length) in enumerate(frames):
        frame = data[off:off + length]
        end = frame.rfind(END)
        if off < pos or off + length > len(data) or end < 0 or any(frame[end + 4:]):
            raise IpuError(f"frame {i}: bad position or end")
        pos = off + length
    tail = data[pos:]
    if tail[:4] != b"\x00\x00\x01\xb1" or any(tail[4:]):    # end of the sequence, then padding
        raise IpuError("no sequence end after the last frame")
    return {"width": width, "height": height, "frames": frames}


def to_ipum(data):
    """The same frames as an `ipum` stream: header, then the frames one after the other, each cut
    after its end code (the zero padding would be read as the start of the next frame)."""
    info = parse(data)
    body = b""
    for off, length in info["frames"]:
        frame = data[off:off + length]
        body += frame[:frame.rfind(END) + 4]
    return b"ipum" + struct.pack("<IHHI", len(body) + 16, info["width"], info["height"],
                                 len(info["frames"])) + body


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    data = open(sys.argv[1], "rb").read()
    info = parse(data)
    print(f"{info['width']}x{info['height']}, {len(info['frames'])} frames")
    if len(sys.argv) < 3:
        return
    out = sys.argv[2]
    stream = to_ipum(data)
    if out.lower().endswith(".ipu"):
        open(out, "wb").write(stream)
    else:
        with tempfile.NamedTemporaryFile(suffix=".ipu", delete=False) as tmp:
            tmp.write(stream)
        try:
            subprocess.run(["ffmpeg", "-v", "error", "-y", "-i", tmp.name, out], check=True)
        finally:
            os.unlink(tmp.name)
    print("wrote", out)


if __name__ == "__main__":
    main()
