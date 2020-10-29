# Sous l'océan

[lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=34)

Category : Forensic

Points : 50

## Description

Nous pensons avoir retrouvé la trace d'Eve Descartes. Nous avons reçu un fichier anonyme provenant d'un smartphone Android (probablement celui de son ravisseur). Retrouvez des informations dans son historique de position.

Le flag est de la forme DGSESIEE{x} avec x une chaine de caractères

memdump.txt (SHA256=29c702ff8dc570319e5e8d05fc4cb96c1536b595b9a4e93d6205774f9afd2bff) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/memdump.txt


## Solution

Il faut chercher `Custom Location` dans la section `DUMP OF SERVICE location:`. Il y a des coordonnées GPS qui pointent dans l'océan. Le message est caché dans le dessin formé par les positions.


## Flag

`DGSESIEE{OC34N}`
