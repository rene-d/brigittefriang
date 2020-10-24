#!/usr/bin/env python3

f = open("evil_country_landscape.jpg", "rb")

f.seek(0x137B6)
g = open("evil_country_landscape.zip", "wb")
while True:
    buf = f.read(1048576)
    g.write(buf)
    if len(buf) != 1048576:
        break
