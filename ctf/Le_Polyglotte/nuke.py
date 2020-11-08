#!/usr/bin/env python3

import os
import re
from pathlib import Path
from Crypto.Cipher import Blowfish


#
# step 1: extraire les fichiers de l'archive protégée par mot de passe
#

os.system("unzip -q -o -P finenuke secrets.zip")


#
# step 2: extraire les textes de message.pdf
#

# chargement du fichier
pdf = Path("message.pdf").read_bytes()

# recherche des textes <hexa hexa....> Tj
print("Info dans pdf:")
for m in re.findall(rb"<((?:[0-9a-f]{2} ?)+)> Tj", pdf):
    t = "".join(map(lambda x: chr(int(x, 16)), m.decode().split()))
    print(t)
    print()

# zone HTML
print("Info dans page html:")
m = re.search(rb"flag = \[((?:\d{2},?)+)\]", pdf)
m = m.group(1)
t = "".join(map(chr, map(int, m.decode().split(","))))
print(t)
print()


#
# step 3: déchiffrer le fichier message.pdf
#

# cf. info.txt
key = b"\xce]`^+5w#\x96\xbbsa\x14\xa7\x0ei"
iv = b"\xc4\xa7\x1e\xa6\xc7\xe0\xfc\x82"

enc = Blowfish.new(key, Blowfish.MODE_CBC, iv)
Path("nuke.jpg").write_bytes(enc.encrypt(Path("message.pdf").read_bytes()))


#
# step 4: extraire le binaire ELF de l'image nuke.jpg
#

Path("nuke.bin").write_bytes(Path("nuke.jpg").read_bytes()[72613:])


#
# step 5: décoder le mot de passe dans le binaire nuke.bin
#

pwd = ""

c = 0x34
pwd = chr(c) + pwd
c = c ^ 6
pwd = chr(c) + pwd
c = c ^ 0x56
pwd = chr(c) + pwd
c = c ^ 0x50
pwd = chr(c) + pwd
c = c ^ 0x57
pwd = chr(c) + pwd
c = c ^ 0x50
pwd = chr(c) + pwd
c = c ^ 0x56
pwd = chr(c) + pwd
c = c ^ 0x38
pwd = chr(c) + pwd
c = c ^ 0x6F
pwd = chr(c) + pwd
c = c ^ 0x69
pwd = chr(c) + pwd

print("Info dans ELF:")
print(pwd)
