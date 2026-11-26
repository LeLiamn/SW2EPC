# PSS: the movies (`LINKDATA.CNS`)

**Status: understood.** Tool: `tools/pss.py` (exports MKV files with both audio tracks; uses ffmpeg
for the final mux).

`LINKDATA.CNS` holds the game's **21 movies** (about 19 minutes): 17 cutscenes from 35 s to 3 min 07
with both audio tracks, and 4 five-second clips (logos?) with the stereo track only, two of them at
44.1 kHz. All 21 export to MKV and decode without a single error. Each one is a Sony PSS file: an MPEG-2 program stream
(`00 00 01 BA`) with one video stream and two audio tracks.

## Streams

| Stream | What it is |
|---|---|
| `0xE0` | Video: MPEG-2 Main profile, 25 fps (640×408 or 640×512, 3.5–4.5 Mbit/s). Standard; ffmpeg reads it directly. Some files have video packets without timestamps (ffmpeg needs `-fflags +genpts` to remux them) |
| `0xBD` (private stream 1), sub-stream `0xA1` | **Stereo** audio: Sony SShd/SSbd header + SPU ADPCM |
| `0xBD` (private stream 1), sub-stream `0x90` | **Dolby Digital 5.1** (AC-3, 448 kbit/s) with its 16-bit words byte-swapped |

In private stream 1 packets, the payload starts with 4 bytes: `FF`, the sub-stream id (`A1` or `90`),
`00 00`. The rest is the sub-stream data.

## The stereo track (sub-stream 0xA1)

```
"SShd" u32 size (0x18)  u32 codec (0x10 = SPU ADPCM)  u32 rate (48000)  u32 channels (2)
       u32 interleave (0x20)  u32 loop start (-1)  u32 loop end (-1)
"SSbd" u32 size         ADPCM data, channels interleaved every 0x20 bytes
```

Check: with the 0x20 interleave given by the header, the left and right channels of movie 0 have a
correlation of 0.984 and no clipping; other interleaves give noise. The SSbd size matches the data
found in the stream exactly.

## The 5.1 track (sub-stream 0x90)

The data starts `77 0B`: the AC-3 sync word `0B 77` with its bytes swapped. Swapping every pair of
bytes gives a standard AC-3 stream that ffmpeg decodes without error (5.1 side, 48 kHz, 448 kbit/s,
same duration as the video).
