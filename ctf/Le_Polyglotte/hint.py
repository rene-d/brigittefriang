#!/usr/bin/env python3

from Crypto.Cipher import AES, DES3
from pathlib import Path


Path("tmp").mkdir(exist_ok=True, parents=True)


data = Path("message.pdf").read_bytes()
data = data[0x99A:]

data = data[6:]  # ignore les 6 \x06
data = bytes([(b + 4) % 256 for b in data])  # décalage comme le flag javascript

# cf. info.txt
key = b"\xce]`^+5w#\x96\xbbsa\x14\xa7\x0ei"
iv = b"\xc4\xa7\x1e\xa6\xc7\xe0\xfc\x82"

print(len(key))
print(len(iv))


def p(file, algo=DES3, mode=None):

    _iv = iv
    if algo == AES:
        # il faut 16 bytes pour l'IV en AES
        _iv += b"\x00\x00\x00\x00\x00\x00\x00\x00"

    if not mode:
        mode = algo.MODE_CBC

    d = Path(file).read_bytes()

    d = d[:0x10000]

    enc = algo.new(key, mode, _iv)
    z = enc.encrypt(d)
    print(file, "enc", z[:32])
    Path(f"tmp/{file}.{mode}.encrypted").write_bytes(z)

    dec = algo.new(key, mode, _iv)
    z = dec.decrypt(d)
    print(file, "dec", z[:32])
    Path(f"tmp/{file}.{mode}.decrypted").write_bytes(z)


# p("message.pdf", DES3)
# p("data", DES3)
# p("data", DES3.MODE_CFB)
# p("data", DES3.MODE_OFB)
# p("data", DES3.MODE_OPENPGP)

p("hint.png", AES)
