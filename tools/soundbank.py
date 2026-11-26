"""Split and decode the sound-effect bank (BNS entry 1384: raw PS2 SPU ADPCM, mono).

The bank is a run of ADPCM sounds with no table: each sound ends on a frame whose flag byte is 1
(followed by a flag-7 padding frame) or 3 (end of a looping sound, whose loop starts on a flag-6
frame). The sample rate is not in the bank; 32000 Hz sounds right (checked by ear, and 32000 appears
in the event commands). Format documented in docs/formats/SOUNDBANK.md.

Usage:
  py tools/soundbank.py --iso image.iso info
  py tools/soundbank.py --iso image.iso out_dir [--rate 32000]
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ans  # noqa: E402

BANK_ENTRY = 1384
FRAME = 16


def split(data):
    """Return [(start, end, looping)] byte ranges of the sounds in the bank."""
    sounds, start, loop = [], 0, False
    for i in range(0, len(data) - FRAME + 1, FRAME):
        flag = data[i + 1]
        if flag == 6:
            loop = True
        if flag in (1, 3):
            sounds.append((start, i + FRAME, flag == 3 or loop))
            start, loop = i + FRAME, False
        elif flag == 7 and start == i:
            start = i + FRAME
    return sounds


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 4 or sys.argv[1] != "--iso":
        print(__doc__)
        sys.exit(1)
    import linkdata
    image, target = sys.argv[2], sys.argv[3]
    rate = int(sys.argv[sys.argv.index("--rate") + 1]) if "--rate" in sys.argv else 32000
    f, base, table = linkdata.open_container(image, "BNS")
    entry = table["entries"][BANK_ENTRY]
    f.seek(base + entry["offset"])
    data = f.read(entry["size"])
    sounds = split(data)
    if target == "info":
        loops = sum(1 for *_, looping in sounds if looping)
        seconds = sum((e - s) // FRAME * 28 for s, e, _ in sounds) / rate
        print(f"{len(sounds)} sounds ({loops} looping), {seconds / 60:.1f} minutes at {rate} Hz")
        return
    os.makedirs(target, exist_ok=True)
    for n, (s, e, looping) in enumerate(sounds):
        name = f"{n:04d}{'_loop' if looping else ''}.wav"
        ans.write_wav(os.path.join(target, name), rate, [ans.decode_adpcm(data[s:e])])
    print(f"{len(sounds)} sounds written to {target} at {rate} Hz")


if __name__ == "__main__":
    main()
