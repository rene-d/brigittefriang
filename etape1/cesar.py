#!/usr/bin/env python3

import re


def uncesar(texte, decal=19):
    r = ""
    for c in texte:
        if "a" <= c <= "z":
            c = chr(((ord(c) - 97) + 19) % 26 + 97)
        elif "A" <= c <= "Z":
            c = chr(((ord(c) - 65) + 19) % 26 + 65)
        r += c
    print(r)
    return "".join(re.findall(r"<u>(.+?)</u>", r, re.DOTALL))


texte = open("message-secret.html").read()
flag = ""
for s in re.findall(r"<p>(.+?)</p>", texte, re.DOTALL):
    flag += uncesar(s)
print(flag)
