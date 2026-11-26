"""Convert tm3 textures to PNG. A tm3 is a ready-made GS upload packet: GIF tags that set the
transfer registers (BITBLTBUF, TRXPOS, TRXREG, TRXDIR) followed by IMAGE data: an 8-bit indexed
image (PSMT8) and one or more 256-colour palettes (PSMCT32 blocks of 16x16, CSM1 order).
Format documented in docs/formats/TM3.md.

Usage:
  py tools/tm3.py file.tm3 out_prefix            one PNG per palette: out_prefix_p0.png, ...
  py tools/tm3.py --iso image.iso out_dir        every tm3 of LINKDATA.BNS
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from tim2 import csm1_index, png_bytes, ps2_alpha  # noqa: E402

MAGIC = b"tm3 "
PSMCT32, PSMT8 = 0x00, 0x13


class Tm3Error(ValueError):
    pass


def transfers(data, p=0x30):
    """Walk the GIF packet; return the image transfers with their GS register settings."""
    regs, out = {}, []
    while p + 16 <= len(data):
        lo, hi = struct.unpack_from("<QQ", data, p)
        p += 16
        nloop, eop, flg, nreg = lo & 0x7FFF, (lo >> 15) & 1, (lo >> 58) & 3, (lo >> 60) & 0xF
        if flg == 0 and nreg == 1 and (hi & 0xF) == 0xE:       # PACKED, A+D register writes
            for _ in range(nloop):
                value, addr = struct.unpack_from("<QQ", data, p)
                p += 16
                regs[addr & 0xFF] = value
        elif flg == 2:                                          # IMAGE data
            bitblt, trxreg = regs.get(0x50, 0), regs.get(0x52, 0)
            out.append(dict(psm=(bitblt >> 56) & 0x3F, width=trxreg & 0xFFF,
                            height=(trxreg >> 32) & 0xFFF, data=data[p:p + 16 * nloop]))
            p += 16 * nloop
        elif lo == 0:                                           # DMA tag between packets
            continue
        else:
            raise Tm3Error(f"Unexpected GIF tag at 0x{p - 16:x}")
        if eop and p >= len(data):
            break
    if p != len(data):
        raise Tm3Error("Packet does not end at the end of the file")
    return out


def parse(data):
    if data[:4] != MAGIC:
        raise Tm3Error("Missing tm3 signature")
    images, palettes = [], []
    for t in transfers(data):
        if t["psm"] == PSMT8 and t["width"] and t["height"]:
            images.append(t)
        elif t["psm"] == PSMCT32:
            w = t["width"]
            colours = [tuple(t["data"][4 * i:4 * i + 4]) for i in range(w * t["height"])]
            for block in range(w // 16):                        # 16x16 blocks side by side
                pal = [colours[r * w + block * 16 + c] for r in range(16) for c in range(16)]
                palettes.append([pal[csm1_index(i)] for i in range(256)])
    return images, palettes


def to_png(image, palette):
    rgba = bytearray()
    for index in image["data"][:image["width"] * image["height"]]:
        r, g, b, a = palette[index]
        rgba += bytes((r, g, b, ps2_alpha(a)))
    return png_bytes(image["width"], image["height"], bytes(rgba))


def palette_swatch(palettes):
    """One 256x16 band per palette (every colour of the palette in order), for palette-only files."""
    width, height = 256, 16 * len(palettes)
    pixels = bytearray()
    for p, pal in enumerate(palettes):
        for _ in range(16):
            for i in range(256):
                r, g, b, _a = pal[i]
                pixels += bytes((r, g, b, 255))
    return png_bytes(width, height, bytes(pixels))


def convert(data, prefix):
    images, palettes = parse(data)
    written = []
    if not images:
        with open(prefix + "_palettes.png", "wb") as f:
            f.write(palette_swatch(palettes))
        return [prefix + "_palettes.png"]
    for i, image in enumerate(images):
        for p, pal in enumerate(palettes):
            path = f"{prefix}{'' if len(images) == 1 else f'_i{i}'}_p{p}.png"
            with open(path, "wb") as f:
                f.write(to_png(image, pal))
            written.append(path)
    return written


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] != "--iso":
        for path in convert(open(sys.argv[1], "rb").read(), sys.argv[2]):
            print(path)
        return
    import pack
    image, out_dir = sys.argv[2], sys.argv[3]
    os.makedirs(out_dir, exist_ok=True)
    ok = failed = pngs = 0
    for path, leaf in pack.iter_bns(image):
        if leaf[:4] != MAGIC:
            continue
        try:
            pngs += len(convert(leaf, os.path.join(out_dir, path.replace("/", "_"))))
            ok += 1
        except (Tm3Error, IndexError, struct.error) as e:
            failed += 1
            print(f"FAIL {path}: {e}")
    print(f"{ok} tm3 files converted ({pngs} PNG), {failed} failed")


if __name__ == "__main__":
    main()
