#!/usr/bin/env python3

import re
from subprocess import run, DEVNULL
from pathlib import Path
import sys
import itertools

fuses = re.sub(r"[^01]", r"", open("fuses.txt").read())
assert len(fuses) == 256

# affichage des eFuses
for i in range(32):
    o = fuses[i * 8 : i * 8 + 8]
    print(o, "%02X" % int(o, 2), "%02X" % int(o[::-1], 2), chr(int(o, 2)))

print()
for i in range(16):
    o = fuses[i * 16 : i * 16 + 16]
    print(o[:8],o[8:])
print()


def decodeK(K):
    print(f"K = {K}   ", end="")
    sys.stdout.flush()
    cmd = f"openssl aes-256-ecb -d -in archive_chiffree -K {K} -out clair.{K}"
    run(cmd, shell=True, stderr=DEVNULL)
    try:
        for b in Path(f"clair.{K}").read_bytes()[:32]:
            if b < 32:
                b = 46
            sys.stdout.buffer.write(bytes([b]))
    except:
        pass
    sys.stdout.buffer.write(b"\n")


# K = ""
# for i in range(32):
#     b = fuses[i * 8 : i * 8 + 8]
#     b = int(b, 2)
#     K += f"{b:02x}"
# decodeK(K)


def negate(b):
    r = ""
    for c in b:
        if c == "1":
            r += "0"
        else:
            r += "1"
    return r


start = 0


def test_le16(negate_bits, reverse_bytes, reverse_bits):
    K = ""
    for i in range(15, start -1, -1):
        b = fuses[i * 16 : i * 16 + 16]
        if reverse_bits:
            b = b[::-1]
        if reverse_bytes:
            b = b[8:] + b[:8]
        if negate_bits:
            b = negate(b)
        b = int(b, 2)
        K += f"{b:04x}"
    decodeK(K)


def test_be16(negate_bits, reverse_bytes, reverse_bits):
    K = ""
    for i in range(start, 16):
        b = fuses[i * 16 : i * 16 + 16]
        if reverse_bits:
            b = b[::-1]
        if reverse_bytes:
            b = b[8:] + b[:8]
        if negate_bits:
            b = negate(b)
        b = int(b, 2)
        K += f"{b:04x}"
    decodeK(K)

for i in [0,6,8]:
    start=i
    booleans = [[False, True]] * 2
    for cond in itertools.product(*booleans):
        test_be16(False, *cond)
        test_le16(False, *cond)
