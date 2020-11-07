#!/usr/bin/env python3

from PIL import Image

separate = Image.new("RGB", (5 * 21 - 1, 20), (0, 255, 255))
px_separate = separate.load()


for n, bit in enumerate([16, 8, 4, 2, 1]):

    im = Image.open("brigitte.png")
    pixels = im.load()

    bits = ""
    for y in range(384):
        for x in range(682):

            if 500 <= x < 520 and 200 <= y < 220:
                r, g, b = pixels[x, y]

                if r & bit == bit:
                    c = (255, 0, 0)
                else:
                    c = (0, 0, 0)

                px_separate[(x - 500) + n * 21, y - 200] = c

                if n == 0:
                    # print(f"{r&31:3d}", end= " ")
                    if (r & 31) != 0:
                        c = chr(64 + (r & 31))
                        print(c, end=" ")
                    else:
                        print(".", end=" ")
                    # r=r&31
                    # print(f"{r:05b}", end="")

        if 200 <= y < 220 and n == 0:
            print()

separate.save(f"red.png")

print()
