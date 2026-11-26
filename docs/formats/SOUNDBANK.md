# Sound-effect bank (BNS entry 1384) and raw ADPCM sounds

**Status: understood** (sample rate probable). Tool: `tools/soundbank.py` (splits and decodes to WAV).

BNS entry **1384** is a 19 MB file of raw PS2 SPU ADPCM (mono), with no header and no table: the
game's sound-effect bank. It starts with one silent 16-byte frame. Every frame has the usual SPU
ADPCM layout (shift/filter byte, flag byte, 14 bytes of 4-bit samples = 28 samples, see
[ANS.md](ANS.md)).

## Splitting the bank

The sounds are simply laid end to end; the frame flags mark their ends:

| Flag byte | Count | Meaning |
|---:|---:|---|
| 0 | 861,384 | Ordinary frame |
| 2 | 331,044 | Frame inside a loop |
| 6 | 289 | Loop start |
| 3 | 289 | Loop end: last frame of a looping sound |
| 1 | 1,321 | End: last frame of a one-shot sound |
| 7 | 1,321 | Padding frame right after each end frame |

This gives **1,610 sounds** (1,321 one-shot, 289 looping), from 28 samples to 172,032 samples:
**17.4 minutes** at 32,000 Hz.

## Sample rate

Not stored in the bank (the game must keep it in a table elsewhere). **32,000 Hz** is the probable
rate: of the same sound decoded at 22,050, 32,000 and 44,100 Hz, 44,100 is clearly too fast and
22,050 too slow by ear, and the value 32,000 appears in the commands of the event files. The tool
takes `--rate` to try another value.

## Other raw ADPCM files

About 250 smaller leaves elsewhere in BNS are raw ADPCM too (same frame layout from start to end,
starting with a silent frame); they are counted with the bank.
