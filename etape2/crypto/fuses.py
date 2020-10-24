#!/usr/bin/env python3

import re
from subprocess import run, DEVNULL
from pathlib import Path
import sys
import itertools

fuses = re.sub(r"[^01]", r"", open("fuses.txt").read())
assert len(fuses) == 256

# affichage des eFuses
for i in range(16):
    o = fuses[i * 8 : i * 8 + 8]
    print(o, "%02X" % int(o, 2), "%02X" % int(o[::-1], 2), chr(int(o, 2)))


def decodeK(K):
    print(f"K = {K}   ", end="")
    sys.stdout.flush()
    cmd = f"openssl aes-256-ecb -d -in archive_chiffree -K {K} -iv 0 -out clair.{K}"
    run(cmd, shell=True, stderr=DEVNULL)
    for b in Path(f"clair.{K}").read_bytes()[:32]:
        if b < 32:
            b = 46
        sys.stdout.buffer.write(bytes([b]))
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


def test_le16(negate_bits, reverse_bytes, reverse_bits):
    K = ""
    for i in range(15, -1, -1):
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
    for i in range(16):
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


booleans = [[False, True]] * 2
for cond in itertools.product(*booleans):
    test_be16(False, *cond)
    test_le16(False, *cond)
