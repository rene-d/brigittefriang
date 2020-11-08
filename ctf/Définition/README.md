# Définition

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=30)

Category : Misc

Points : 50

## Description

Un de vos collègues a créé un petite énigme, il est un peu lourd et vous demande depuis des semaines de la résoudre, faites lui plaisir. Voici l'énigme : Quelle heure est-t-il ?

Connectez-vous via nc challengecybersec.fr 6660

Le flag est de la forme : DGSESIEE{x} avec x un hash

## Solution

Le collègue attend l'[heure UNIX](https://fr.wikipedia.org/wiki/Heure_Unix) en secondes.
```bash
date +%s | nc challengecybersec.fr 6660
```

## Flag

`DGSESIEE{cb3b3481e492ccc4db7374274d23c659}`
