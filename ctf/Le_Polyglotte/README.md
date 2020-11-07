# Le Polyglotte

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=32)

Category : Stegano

Points : 150

## Description
Nous avons intercepté un fichier top secret émanant d'Evil Country, il est très certainement en rapport avec leur programme nucléaire. Personne n'arrive à lire son contenu.

Pouvez-vous le faire pour nous ? Une archive était dans le même dossier, elle peut vous servir

Le flag est de la forme : DGSESIEE{x} avec x un hash que vous trouverez

* message.pdf (SHA256=e5aa5c189d3f3397965238fbef5bc02c889de6d5eac713630e87377a5683967c) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/message.pdf
* secrets.zip (SHA256=ae5877bb06ac9af5ad92c8cd40cd15785cbc7377c629ed8ec7443f251eeca91f) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/secrets.zip


## Références

Format [PDF](https://www.adobe.com/content/dam/acom/en/devnet/acrobat/pdfs/PDF32000_2008.pdf)
https://www.adobe.com/content/dam/acom/en/devnet/pdf/pdfs/pdf_reference_archives/PDFReference.pdf

## WIP


### secretz.zip

```bash
fcrackzip secrets.zip -D -p rockyou.txt -u
unzip -P finenuke secrets.zip
```


dans le PDF:

```py
"".join(map(lambda x: chr(int(x, 16)), "...".split()))
```

9 0 obj ==>

'Ce document concerne l operation soleil atomique.\nCette operation est strictement confidentielle et ne doit en aucun cas être devoilee. \nLes informations sur l operation sont disseminées dans ce fichier.\nChaque partie de l information est identifiee par un nombre par ex : \n[0]ae7bca8e correspond a la première partie de l information qu il faut concatener au reste.'


### part 0

dans le code HTML embeddé dans le pdf

```py
"".join(map(chr,[91,48,93,97,97,57,51,56,97,49,54]))
```
résultat: `[0]aa938a16`

### part 1

7 0 obj ==>
```py
"".join(map(lambda x: chr(int(x, 16)),"5b 31 5d 34 64 38 36 32 64 35 61".split()))
```
résultat: `[1]4d862d5a`

###

flat.py cherche à extraire le bloc binaire à la fin du pdf. format inconnu pour l'instant. pas un zlib (méthode utilisée par /FlatDecocde), pas un truc en décalage +4 ou -4 (cf. le javascript), 6 octets égaux à 6 au début.....

## Flag


## Comments

jbedel (2020-10-26 09:32:33)
>Merci pour ce challenge, c'était vraiment génial et original :D

Brigitte Friang Admin (2020-10-26 17:43:52)
>Merci <3

Headorteil (2020-10-28 18:33:12)
>Il y'a 2 fois le [0], c'est normal?

Brigitte Friang Admin (2020-10-28 18:43:48)
>Le premier est un exemple comme expliqué dans le texte du même document

Linuz (2020-10-28 20:00:06)
>Bravo pour ce challenge ! Super fun à faire

Brigitte Friang Admin (2020-10-28 22:41:56)
>Merci ! Content que ça vous ai plu !





## recherche
https://truepolyglot.hackade.org
https://github.com/corkami/pocs
https://www.root-me.org/fr/Challenges/Steganographie/Angecryption

https://github.com/indrora/corkami/tree/master/src/angecryption
https://github.com/Qtty/AngeCryption
