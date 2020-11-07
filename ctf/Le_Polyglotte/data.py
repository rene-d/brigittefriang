#!/usr/bin/env python3

from pathlib import Path
import re

#
pdf = Path("message.pdf").read_bytes()

#
print("Info dans pdf:")
for m in re.findall(rb"<((?:[0-9a-f]{2} ?)+)> Tj", pdf):
    t = "".join(map(lambda x: chr(int(x, 16)), m.decode().split()))
    print(t)
    print()

#
print("Info dans page html:")
m = re.search(rb"flag = \[((?:\d{2},?)+)\]", pdf)
m = m.group(1)
t = "".join(map(chr, map(int, m.decode().split(","))))
print(t)
print()

#
print("Binaire dans pdf:")
data = pdf[0x99A + 6 :]
Path("data").write_bytes(data)
print(f"{len(data)} octets (0x{len(data):x})")
