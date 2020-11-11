# Automatos

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=24)

Category : Stegano

Points : 300

## Description

Un de nos agents ne répond plus depuis quelques jours, nous avons reçu un mail avec une photo d'archives de Brigitte Friang. Cela ne peut pas être une coïncidence. Il a certainement cherché à cacher des informations dans l'image. Nous devons le secourir au plus vite, il est certainement en danger et sur écoute.

Le flag est juste une chaîne de caractères

- brigitte.png (SHA256=31b88d96ff54ef15e6c995aac5a1759068ac8ba43d3cbdf561c7ea44ab42d735) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/brigitte.png


## Solution

L'analyse des plans RGB avec StegSolve fait apparaître une anomalie dans la zone 500x200 des pixels rouges.

La zone est un carré de 20x20 qu'on isole avec un script Python.

De plus, en ne considérant que les 5 bits de poids faible, on obtient un carré avec une seule valeur par ligne et par colonne avec des valeur entre 1 et 21. Compte tenu de la difficulté de construire un tel carré (cf. [problème des huit dames](https://fr.wikipedia.org/wiki/Problème_des_huit_dames)), cela ne peut être un hasard.

```
   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
 1 .  .  .  .  .  .  .  .  A  .  .  .  .  .  .  .  .  .  .  .
 2 .  .  .  P  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
 3 .  .  .  .  .  .  .  .  .  .  .  E  .  .  .  .  .  .  .  .
 4 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  O  .  .  .  .
 5 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  D  .  .  .
 6 .  .  .  .  .  .  N  .  .  .  .  .  .  .  .  .  .  .  .  .
 7 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  I  .
 8 .  E  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
 9 .  .  .  .  .  .  .  .  .  .  R  .  .  .  .  .  .  .  .  .
10 .  .  .  .  .  .  .  .  .  .  .  .  M  .  .  .  .  .  .  .
11 .  .  .  .  .  .  .  .  .  .  .  .  .  B  .  .  .  .  .  .
12 .  .  .  .  .  .  .  D  .  .  .  .  .  .  .  .  .  .  .  .
13 .  .  .  .  .  I  .  .  .  .  .  .  .  .  .  .  .  .  .  .
14 .  .  R  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
15 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  U  .  .
16 .  .  .  .  I  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
17 .  .  .  .  .  .  .  .  .  S  .  .  .  .  .  .  .  .  .  .
18 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  M
19 .  .  .  .  .  .  .  .  .  .  .  .  .  .  M  .  .  .  .  .
20 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
```

En commençant par la première ligne, on a un `A` dans la colonne 9. Puis on va à la ligne 9 et on a un `R` dans la colonne 11. Puis à la ligne 11 où on a un `B` dans la colonne 14. Etc.

On obtient ainsi la suite de lettres `ARBREDEPOIDSMINIMUM` qui est le flag.

## Flag

`ARBREDEPOIDSMINIMUM`
