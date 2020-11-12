# Steganosaurus

[lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=25)

Category : Forensic

Points : 400

## Description

Nos agents ont trouvé dans le camion de livraison une clef USB. Nous vous transférons le filesystem de cette dernière et espérons que votre grande capacité de réflexion pemettra de révéler les secrets les plus sombres d'Evil Country !

Le flag est de la forme DGSEESIEE{x} avec x une chaine de caractères. (Attention au DGEESIEE, une erreur de typo s'est glissée dans le flag)

message (SHA256=3889febebd6b1d35c057c3ba3f6f722798f029d6d0321b484305922a3d55d4d8) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/message

## WIP

Extraction des fichiers:
```bash
fls message
icat message 6 > readme
icat message 9 > steganausorus.apk
icat message 4 > flag.png
```

Analyse `classes.dex`:
```
apt install dex2jar
d2j-dex2jar classes.dex
# install jd-cli from https://github.com/kwart/jd-cli
jd-cli classes-dex2jar.jar
```

## Flag
