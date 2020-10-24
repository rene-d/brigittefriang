texte = open("texte").read()

r = ""
for c in texte:
    if "a" <= c <= "z":
        c = chr(((ord(c) - 97) + 19) % 26 + 97)
    if "A" <= c <= "Z":
        c = chr(((ord(c) - 65) + 19) % 26 + 65)
    r += c
print(r)
