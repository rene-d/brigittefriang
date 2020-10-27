#!/usr/bin/env python3

from Crypto.PublicKey import RSA

with open("private.pem", "r") as fk:
    priv = fk.read()
    fk.close()


priv = RSA.importKey(priv)

print(priv.p)

# en modifiant la taille de l'affichage, le motif suivant apparaît:
# AD26E7D346A2CA64
