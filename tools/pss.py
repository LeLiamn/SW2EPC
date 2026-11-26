"""Export the movies of LINKDATA.CNS (Sony PSS) as MKV files with both audio tracks.

Each PSS is an MPEG-2 program stream with:
- video in stream 0xE0 (standard MPEG-2, read directly by ffmpeg);
- in private stream 1 (0xBD), two sub-streams selected by the second payload byte:
  0xA1 = stereo SPU ADPCM with a Sony SShd/SSbd header (decoded with tools/ans.py),
  0x90 = Dolby Digital (AC-3) 5.1 with its 16-bit words byte-swapped.
Format documented in docs/formats/PSS.md.

Writing MKV needs ffmpeg on the PATH; without it the tool writes the separate streams
(.wav, .ac3) next to an .m2v video.

Usage:
  py tools/pss.py --iso image.iso out_dir [first[-last]]
  py tools/pss.py file.pss out_dir
"""
import os
import shutil
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ans  # noqa: E402
import linkdata  # noqa: E402

SUB_ADPCM = 0xA1
SUB_AC3 = 0x90


def demux_private(data):
    """Return {sub-stream id: bytes} for private stream 1 packets (4-byte sub-header removed)."""
    streams = {}
    p = 0
    while True:
        p = data.find(b"\x00\x00\x01\xbd", p)
        if p < 0 or p + 9 > len(data):
            break
        length = struct.unpack_from(">H", data, p + 4)[0]
        payload = data[p + 9 + data[p + 8]:p + 6 + length]
        if len(payload) > 4:
            streams.setdefault(payload[1], bytearray()).extend(payload[4:])
        p += 6 + length
    return streams


def adpcm_track(raw):
    """Decode the SShd/SSbd stereo ADPCM sub-stream. Returns (rate, channels as sample lists)."""
    i = raw.find(b"SShd")
    _, codec, rate, channels, interleave = struct.unpack_from("<5I", raw, i + 4)
    if codec != 0x10:
        raise ValueError(f"Unknown SShd codec 0x{codec:x}")
    j = raw.find(b"SSbd")
    size = struct.unpack_from("<I", raw, j + 4)[0]
    body = bytes(raw[j + 8:j + 8 + size])
    chans = [ans.decode_adpcm(bytes(c)) for c in ans.split_channels(body, channels, interleave)]
    return rate, chans


def swap16(raw):
    raw = raw[:len(raw) // 2 * 2]
    out = bytearray(len(raw))
    out[0::2] = raw[1::2]
    out[1::2] = raw[0::2]
    return bytes(out)


def export(data, out_dir, name):
    os.makedirs(out_dir, exist_ok=True)
    streams = demux_private(data)
    ffmpeg = shutil.which("ffmpeg")
    with tempfile.TemporaryDirectory() as tmp:
        pss = os.path.join(tmp, "in.pss")
        with open(pss, "wb") as f:
            f.write(data)
        # Some movies have video packets without timestamps: let ffmpeg generate them.
        inputs, maps = ["-fflags", "+genpts", "-i", pss], ["-map", "0:v:0"]
        track = 1
        if SUB_ADPCM in streams:
            rate, chans = adpcm_track(streams[SUB_ADPCM])
            wav = os.path.join(tmp if ffmpeg else out_dir, f"{name}_stereo.wav")
            ans.write_wav(wav, rate, chans)
            inputs += ["-i", wav]
            maps += ["-map", f"{track}:a:0"]
            track += 1
        if SUB_AC3 in streams:
            ac3 = os.path.join(tmp if ffmpeg else out_dir, f"{name}_5.1.ac3")
            with open(ac3, "wb") as f:
                f.write(swap16(streams[SUB_AC3]))
            inputs += ["-i", ac3]
            maps += ["-map", f"{track}:a:0"]
        if not ffmpeg:
            with open(os.path.join(out_dir, f"{name}.m2v"), "wb") as f:
                f.write(data)  # the PSS itself plays its video in most players
            return "separate streams (ffmpeg not found)"
        out = os.path.join(out_dir, f"{name}.mkv")
        cmd = [ffmpeg, "-hide_banner", "-v", "error", "-y", *inputs, *maps,
               "-c:v", "copy", "-c:a", "copy", out]
        if SUB_ADPCM in streams:
            cmd[cmd.index(out):cmd.index(out)] = ["-c:a:0", "flac"]
        subprocess.run(cmd, check=True)
        return out


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] != "--iso":
        print(export(open(sys.argv[1], "rb").read(), sys.argv[2],
                     os.path.splitext(os.path.basename(sys.argv[1]))[0]))
        return
    image, out_dir = sys.argv[2], sys.argv[3]
    first, last = 0, None
    if len(sys.argv) > 4:
        a, _, b = sys.argv[4].partition("-")
        first, last = int(a), int(b or a)
    f, base, table = linkdata.open_container(image, "CNS")
    for e in table["entries"][first:None if last is None else last + 1]:
        f.seek(base + e["offset"])
        result = export(f.read(e["size"]), out_dir, f"{e['index']:04d}")
        print(f"{e['index']:4d}  {result}")


if __name__ == "__main__":
    main()
