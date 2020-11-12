# Keypad sniffer

## Description
Category : Hardware

Points : 150

Le code d'accès d'un centre militaire de télécommunications est saisi sur un clavier. Un agent a accédé au matériel (Cf. photos face avant et face arrière du clavier) et a inséré un dispositif pour enregister les données binaires qui transitent sur le connecteur du clavier. Le fichier joint (keypad_sniffer.txt) comprend les données binaires (échantillonnées à une fréquence de 15 kHz) au moment où une personne autorisée rentrait le code d'accès. Retrouvez le code d'accès.

Le flag est de la forme DGSESIEE{X} où X est le code saisi

- keypad_sniffer.txt (SHA256=f5660a0b1c8877b67d7e5ce85087138cbd0c061b0b244afc516c489b39a7f79d) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/keypad_sniffer.txt
- keypad_face.jpg (SHA256=b39c0d732f645fc73f41f0955233bec3593008334a8796d2f1208346f927fef2) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/keypad_face.jpg
- keypad_back.jpg (SHA256=1f5d41c3521d04494779e43a4d5fae7cb14aad44e6e99cf36642ff4e88fab69f) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/keypad_back.jpg 

## WIP

==> Disclaimer, je suis sur un qwerty, rip les accents et vos yeux <==

D'apres une datasheet trouvee sur le net, on a compris que 4 des 8 bits de la matrice 4x4 du keypad etaient regulierement stimules (en output du sniffer) pour venir lire les 4 autres bits (en input donc) afin de connaitre la touche appuyee.
De plus, on sait via les photos front/back qu'a ces 8 bits significatifs de la matrice on ajoute 2 couples de bits shorted 2 a 2 (a priori donc un pattern fixe a identifier dans les trames).

Premiere analyse : on essaye de filtrer les doublons consecutifs et on regarde les occurences

```
cat keypad_sniffer.txt | uniq -c
```

Le pattern 1011110xxxx (les xxxx ne contiennent toujours qu'un seul 0 => c'est la ligne/colonne en output a un instant t) ne semble pas significatif.
On semble observer deux "10" a des positions fixes sur tout le jeu de data => ce sont certainement les 2 couples bits shortes entre eux (2 niveaux differents c'est chelou, mais bon soit)

On cherche donc toutes les valeurs de type 10xxxx10yyyy pour lesquels xxxx et yyyy ne peuvent contenir qu'un seul 0 chacuns (ie exactement 4 zeros sur une ligne).

```
cat keypad_sniffer.txt | uniq | egrep -v "^10111110" | uniq
```

On obtient ces 16 valeurs :

```
101110100111
101011101110
101101100111
101101101011
100111101110
101011101011
101110101110
101011101101
101110101101
100111101011
100111101101
101110101011
100111100111
101101101101
100111101011
101011100111
```

Si on enleve les deux "10" identifies comme non significatifs (ex pour la premiere ligne : 101011100111 => 1011 0111)
                                                                                           ^^    ^^
```
11100111
10111110
11010111
11011011
01111110
10111011
11101110
10111101
11101101
01111011
01111101
11101011
01110111
11011101
01111011
10110111
```

Derriere on utilise le petit prog en c++ pour remapper un peu les bits et essayer de retomber sur un truc lisible.
g++ keypad.cpp -o toto
./toto (ca sort des combinaisons possibles mais aucune ne semble marcher .....)
