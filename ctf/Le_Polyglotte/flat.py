#!/usr/bin/env python3

import zlib
from pathlib import Path
import os

s = Path("message.pdf").read_bytes()
s = s[0x99A + 6 :]


for d in range(1, 256):

    s = bytes([(b + d) % 256 for b in s])

    Path("data").write_bytes(s)
    os.system("file data")
    continue

    # ne fonctionne pas ...
    d = zlib.decompress(s)
    print(d)
