#!/usr/bin/env python3

from PIL import Image


print(" ", "".join(f"{i:2d} " for i in range(1, 21)))

im = Image.open("brigitte.png")
pixels = im.load()

lettres = []

for y in range(200, 220):
    print(f"{y-200+1:2d}", end="")
    p, c = 0, "."
    for x in range(500, 520):
        r, g, b = pixels[x, y]
        r = r & 31
        if r != 0:
            p = x - 500
            c = chr(r + 64)
            print(f" {c} ", end="")
        else:
            print(" . ", end="")
    print()
    lettres.append((p, c))

print()
p = 0
while True:
    p, c = lettres[p]
    if c == ".":
        break
    print(c, end="")
print()
