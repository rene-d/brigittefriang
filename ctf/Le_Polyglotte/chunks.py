#!/usr/bin/env python3

from pathlib import Path


png = Path("hint.png").open("rb")

tmp = Path("tmp")
tmp.mkdir(exist_ok=True, parents=True)

png_signature = png.read(8)
(tmp / Path("header")).write_bytes(png_signature)

chunk_num = 0

while True:
    chunk_size = png.read(4)
    if not chunk_size:
        break

    chunk_size = int.from_bytes(chunk_size, "big")
    chunk_type = png.read(4).decode()
    chunk_data = png.read(chunk_size)
    chunk_crc = png.read(4)

    print(f"chunk {chunk_type}: offset 0x{png.tell():06x} size 0x{chunk_size:06x}")
    (tmp / Path(f"chunk_{chunk_num}_{chunk_type}")).write_bytes(chunk_data)

    chunk_num += 1
