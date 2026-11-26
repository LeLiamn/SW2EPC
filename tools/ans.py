"""Decode the music streams of LINKDATA.ANS (PS2 SPU ADPCM, stereo) to WAV. No dependencies.

Format documented in docs/formats/ANS.md.

Usage:
  py tools/ans.py --iso image.iso out_dir [first[-last]]   decode streams to out_dir/NNNN.wav
  py tools/ans.py --iso image.iso info                     list the streams and their length
"""
import os
import struct
import sys
import wave

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import linkdata  # noqa: E402

FRAME = 16                      # one ADPCM frame: 2 header bytes + 14 bytes = 28 samples
COEFS = [(0, 0), (60, 0), (115, -52), (98, -55), (122, -60)]


def parse_header(data):
    header_size, rate, channels, interleave, frames, loop = struct.unpack_from("<6I", data, 0)
    return dict(header_size=header_size, rate=rate, channels=channels, interleave=interleave,
                frames=frames, loop_frame=loop)


def decode_adpcm(frames_bytes):
    """Decode a run of 16-byte SPU ADPCM frames of one channel to a list of 16-bit samples."""
    out = []
    s1 = s2 = 0
    for p in range(0, len(frames_bytes) - FRAME + 1, FRAME):
        head = frames_bytes[p]
        shift, filt = head & 0x0F, min(head >> 4, 4)
        c1, c2 = COEFS[filt]
        for byte in frames_bytes[p + 2:p + FRAME]:
            for nib in (byte & 0x0F, byte >> 4):
                v = (nib << 12) & 0xFFFF
                if v & 0x8000:
                    v -= 0x10000
                v = (v >> shift) + ((s1 * c1 + s2 * c2 + 32) >> 6)
                v = max(-32768, min(32767, v))
                out.append(v)
                s2, s1 = s1, v
    return out


def split_channels(body, channels, interleave):
    """De-interleave the body: blocks of `interleave` bytes alternate between channels."""
    parts = [bytearray() for _ in range(channels)]
    block = interleave * channels
    for p in range(0, len(body) - block + 1, block):
        for c in range(channels):
            parts[c] += body[p + c * interleave:p + (c + 1) * interleave]
    return parts


def decode(data):
    h = parse_header(data)
    body = data[h["header_size"]:]
    body = body[:h["frames"] * FRAME * h["channels"]]
    chans = [decode_adpcm(bytes(c)) for c in split_channels(body, h["channels"], h["interleave"])]
    return h, chans


def write_wav(path, rate, chans):
    n = min(len(c) for c in chans)
    pcm = bytearray()
    for i in range(n):
        for c in chans:
            pcm += struct.pack("<h", c[i])
    with wave.open(path, "wb") as w:
        w.setnchannels(len(chans))
        w.setsampwidth(2)
        w.setframerate(rate)
        w.writeframes(bytes(pcm))


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 4 or sys.argv[1] != "--iso":
        print(__doc__)
        sys.exit(1)
    image, target = sys.argv[2], sys.argv[3]
    f, base, table = linkdata.open_container(image, "ANS")
    first, last = 0, None
    if len(sys.argv) > 4:
        a, _, b = sys.argv[4].partition("-")
        first, last = int(a), int(b or a)
    entries = table["entries"][first:None if last is None else last + 1]
    if target != "info":
        os.makedirs(target, exist_ok=True)
    for e in entries:
        f.seek(base + e["offset"])
        data = f.read(e["size"])
        h = parse_header(data)
        if h["header_size"] == 0:
            print(f"{e['index']:4d}  (empty header, skipped)")
            continue
        seconds = h["frames"] * 28 / h["rate"]
        if target == "info":
            print(f"{e['index']:4d}  {h['rate']} Hz  {h['channels']} ch  {seconds:7.1f} s  "
                  f"loop at {h['loop_frame'] * 28 / h['rate']:.1f} s")
            continue
        _, chans = decode(data)
        write_wav(os.path.join(target, f"{e['index']:04d}.wav"), h["rate"], chans)
        print(f"{e['index']:4d}  {seconds:7.1f} s")


if __name__ == "__main__":
    main()
