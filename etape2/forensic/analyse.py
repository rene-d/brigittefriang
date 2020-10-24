#!/usr/bin/env python3

import os,sys
from pathlib import Path

set_addr = set()

for l in open("access.log"):
    addr = l.split(" ")[0]
    set_addr.add(addr)

# print(set_addr)

# for a in set_addr:
#     print(f"######################   {a:20}")
#     sys.stdout.flush()
#     os.system(f"whois {a}")


# for a in set_addr:
#    d = Path(a)
#    d.mkdir(exist_ok=True)
#    os.system(f"grep {a} access.log > {a}/access.log")
