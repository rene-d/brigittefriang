#!/usr/bin/env python3

from Crypto.Cipher import AES, DES3
from pathlib import Path


data = Path("message.pdf").read_bytes()
data = data[0x99A:]

data = bytes([(b + 4) % 256 for b in data])
Path(f"data").write_bytes(data)


key = b"\xce]`^+5w#\x96\xbbsa\x14\xa7\x0ei"
iv = b"\xc4\xa7\x1e\xa6\xc7\xe0\xfc\x82"

print(len(key))
print(len(iv))


def p(file, algo=DES3, mode=None):

    _iv = iv
    if algo == AES:
        _iv += b"\x00\x00\x00\x00\x00\x00\x00\x00"

    if not mode:
        mode = algo.MODE_CBC

    with open(file, "rb") as f:
        d = f.read()

    d = d[:0x10000]

    enc = algo.new(key, mode, _iv)
    with open(f"{file}.{mode}.encrypted", "wb") as f:
        z = enc.encrypt(d)
        print(z[:32])
        f.write(z)

    dec = algo.new(key, mode, _iv)
    with open(f"{file}.{mode}.decrypted", "wb") as f:
        z = dec.decrypt(d)
        print(z[:32])
        f.write(z)


# p("message.pdf", DES3)
# p("data", DES3)
# p("data", DES3.MODE_CFB)
# p("data", DES3.MODE_OFB)
# p("data", DES3.MODE_OPENPGP)

p("hint.png", AES)
