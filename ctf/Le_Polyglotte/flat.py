#!/usr/bin/env python3

import zlib
from pathlib import Path
import os
import itertools


data = Path("message.pdf").read_bytes()
data = data[0x99A :]
Path(f"data").write_bytes(data)

flag = [91,48,93,97,97,57,51,56,97,49,54]


s = bytes([(b ^ (mask+4)) for b, mask in zip(data, itertools.cycle(flag))])
Path(f"data.xor").write_bytes(s)
