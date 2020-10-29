# Stranger RSA

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=21)

Category : Crypto

Points : 200

## Description

Un de nos agents est parvenu à dérober une clé privée et un fichier chiffré à Evil Gouv. Retrouvez l'information, avec un peu d'imagination

Le flag est juste une chaîne de caractères (sans le DGESIEE{})

private.pem (SHA256=84f2c60b3d796a01e7762777923a8921433bce8ead72bc94fa26d1676ecef637) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/private.pem
EVIL-FILE.txt.enc (SHA256=aee3dd5b398689bb73a207a52d56a130bca8fb30e3261e419ab22026b447b5ab) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/EVIL-FILE.txt.enc


## Solution

```bash
openssl rsautl -in EVIL-FILE.txt.enc -inkey private.pem -decrypt
```

Résultat:
```
221 x 7
```

Il faut extrait le /prime1/ de la clé privée pour faire apparaître un motif, qui est la flag.


## Flag
`AD26E7D346A2CA64`
