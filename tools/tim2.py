"""Convert TIM2 textures (Sony's standard PS2 texture format) to PNG. No dependencies.

Handles what Samurai Warriors 2: Empires uses: 4-bit and 8-bit indexed images with 32-bit (and
16/24-bit) palettes, CSM1 palette ordering, several palettes per texture. Also 16/24/32-bit
direct-colour images. Format documented in docs/formats/TIM2.md.

Usage:
  py tools/tim2.py file.tm2 [out.png]                 convert one file (first palette)
  py tools/tim2.py file.tm2 out.png --all-palettes    one PNG per palette (out_p0.png, ...)
  py tools/tim2.py --iso image.iso out_dir            every TIM2 in LINKDATA.BNS, nested too
"""
import os
import struct
import sys
import zlib


class Tim2Error(ValueError):
    pass


def png_bytes(width, height, rgba):
    """Encode raw RGBA rows as a PNG file."""
    stride = width * 4
    raw = b"".join(b"\0" + rgba[y * stride:(y + 1) * stride] for y in range(height))

    def chunk(kind, data):
        return (struct.pack(">I", len(data)) + kind + data
                + struct.pack(">I", zlib.crc32(kind + data) & 0xFFFFFFFF))

    return (b"\x89PNG\r\n\x1a\n"
            + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0))
            + chunk(b"IDAT", zlib.compress(raw, 6))
            + chunk(b"IEND", b""))


def ps2_alpha(a):
    """PS2 alpha goes from 0 to 0x80 (opaque); scale it to 0..255."""
    return min(255, a * 2)


def decode_color(data, off, kind):
    """Return (r, g, b, a) and the size in bytes for colour format kind (1, 2 or 3)."""
    if kind == 1:  # 16-bit: A1 B5 G5 R5
        v = struct.unpack_from("<H", data, off)[0]
        r, g, b = (v & 31) << 3, ((v >> 5) & 31) << 3, ((v >> 10) & 31) << 3
        return (r, g, b, 255 if v & 0x8000 else 0), 2
    if kind == 2:
        return (data[off], data[off + 1], data[off + 2], 255), 3
    if kind == 3:
        return (data[off], data[off + 1], data[off + 2], ps2_alpha(data[off + 3])), 4
    raise Tim2Error(f"Unsupported colour format {kind}")


def csm1_index(i):
    """CSM1 stores 256-colour palettes with entries 8-15 and 16-23 swapped in each block of 32."""
    block = i & 0x18
    if block == 0x08:
        return i + 8
    if block == 0x10:
        return i - 8
    return i


def parse(data):
    if data[:4] != b"TIM2":
        raise Tim2Error("Missing TIM2 signature")
    version, align_fmt, count = struct.unpack_from("<BBH", data, 4)
    pos = 0x80 if align_fmt == 1 else 0x10
    pictures = []
    for _ in range(count):
        (total, clut_size, image_size, header_size, clut_colors, _pict_fmt, mipmaps, clut_type,
         image_type, width, height) = struct.unpack_from("<IIIHHBBBBHH", data, pos)
        image_off = pos + header_size
        clut_off = image_off + image_size
        pictures.append(dict(width=width, height=height, image_type=image_type,
                             clut_type=clut_type, clut_colors=clut_colors, mipmaps=mipmaps,
                             image=data[image_off:image_off + image_size],
                             clut=data[clut_off:clut_off + clut_size]))
        pos += total
    return dict(version=version, pictures=pictures)


def palettes(pic):
    """Return the list of palettes of an indexed picture, each a list of RGBA tuples."""
    kind = pic["clut_type"] & 0x1F
    linear = bool(pic["clut_type"] & 0x80)  # CSM2: already in order
    per_palette = 16 if pic["image_type"] == 4 else 256
    colors = []
    off = 0
    for _ in range(pic["clut_colors"]):
        c, size = decode_color(pic["clut"], off, kind)
        colors.append(c)
        off += size
    result = []
    for start in range(0, len(colors) - per_palette + 1, per_palette):
        pal = colors[start:start + per_palette]
        if per_palette == 256 and not linear:
            pal = [pal[csm1_index(i)] for i in range(256)]
        result.append(pal)
    return result


def to_rgba(pic, palette_index=0):
    w, h, t, img = pic["width"], pic["height"], pic["image_type"], pic["image"]
    out = bytearray(w * h * 4)
    if t in (4, 5):
        pal = palettes(pic)[palette_index]
        lut = [bytes(c) for c in pal]
        if t == 5:
            for i in range(w * h):
                out[i * 4:i * 4 + 4] = lut[img[i]]
        else:
            for i in range(w * h):
                byte = img[i >> 1]
                out[i * 4:i * 4 + 4] = lut[(byte >> 4) if i & 1 else (byte & 0x0F)]
        return bytes(out)
    if t in (1, 2, 3):
        step = {1: 2, 2: 3, 3: 4}[t]
        for i in range(w * h):
            c, _ = decode_color(img, i * step, t)
            out[i * 4:i * 4 + 4] = bytes(c)
        return bytes(out)
    raise Tim2Error(f"Unsupported image type {t}")


def convert(data, out_path, all_palettes=False):
    """Write PNG(s) for the first picture of a TIM2. Returns the list of written paths."""
    tim = parse(data)
    pic = tim["pictures"][0]
    count = len(palettes(pic)) if pic["image_type"] in (4, 5) and all_palettes else 1
    written = []
    for p in range(count):
        path = out_path if count == 1 else out_path.replace(".png", f"_p{p}.png")
        with open(path, "wb") as f:
            f.write(png_bytes(pic["width"], pic["height"], to_rgba(pic, p)))
        written.append(path)
    return written


def iter_bns_tim2(image):
    """Yield (name, bytes) for every TIM2 in LINKDATA.BNS, looking inside nested LINKDATA too."""
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import linkdata
    f, base, table = linkdata.open_container(image, "BNS")
    for e in table["entries"]:
        f.seek(base + e["offset"])
        data = f.read(e["size"])
        if data[:4] == b"TIM2":
            yield f"{e['index']:04d}", data
        elif data[:4] == struct.pack("<I", linkdata.MAGIC):
            for sub in linkdata.parse_header(data)["entries"]:
                blob = data[sub["offset"]:sub["offset"] + sub["size"]]
                if blob[:4] == b"TIM2":
                    yield f"{e['index']:04d}_{sub['index']:03d}", blob


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] == "--iso":
        image, out_dir = sys.argv[2], sys.argv[3]
        os.makedirs(out_dir, exist_ok=True)
        done = failed = 0
        for name, data in iter_bns_tim2(image):
            try:
                convert(data, os.path.join(out_dir, f"{name}.png"), all_palettes=True)
                done += 1
            except (Tim2Error, IndexError, struct.error) as e:
                failed += 1
                print(f"FAIL {name}: {e}")
        print(f"{done} textures converted, {failed} failed, in {out_dir}")
        sys.exit(1 if failed else 0)

    src = sys.argv[1]
    dst = next((a for a in sys.argv[2:] if not a.startswith("--")), os.path.splitext(src)[0] + ".png")
    for path in convert(open(src, "rb").read(), dst, "--all-palettes" in sys.argv):
        print(path)


if __name__ == "__main__":
    main()
