#!/usr/bin/env python3
"""Generate the sample images used by tests/verify.sh.

Writes into the directory given as argv[1]:
  clean.png     - a small valid RGB PNG, nothing appended
  trailing.png  - the same PNG with a fake ZIP local-file header + junk after IEND
"""

import os
import struct
import sys
import zlib


def _chunk(tag: bytes, data: bytes) -> bytes:
    return (
        struct.pack(">I", len(data))
        + tag
        + data
        + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)
    )


def make_png(path: str, width: int = 8, height: int = 8, rgb=(30, 60, 90)) -> bytes:
    signature = b"\x89PNG\r\n\x1a\n"
    ihdr = struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0)  # 8-bit, colour type 2
    raw = b"".join(b"\x00" + bytes(rgb) * width for _ in range(height))
    png = (
        signature
        + _chunk(b"IHDR", ihdr)
        + _chunk(b"IDAT", zlib.compress(raw, 9))
        + _chunk(b"IEND", b"")
    )
    with open(path, "wb") as handle:
        handle.write(png)
    return png


def main() -> int:
    if len(sys.argv) != 2:
        print(f"usage: {sys.argv[0]} <output-dir>", file=sys.stderr)
        return 1

    out_dir = sys.argv[1]
    os.makedirs(out_dir, exist_ok=True)

    clean = make_png(os.path.join(out_dir, "clean.png"))

    fake_zip = b"PK\x03\x04\x14\x00\x00\x00\x08\x00" + b"hidden-payload-" * 8
    with open(os.path.join(out_dir, "trailing.png"), "wb") as handle:
        handle.write(clean + fake_zip)

    print(f"wrote clean.png and trailing.png to {out_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
