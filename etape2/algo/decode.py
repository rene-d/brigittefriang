#!/usr/bin/env python3

original = open("original.txt").read()
intercepte = open("intercepte.txt").read()


i = 0
for c in original:
    while True:
        d = intercepte[i]
        if d != c:
            print(d, end="")
            i += 1
        else:
            break
    i += 1
