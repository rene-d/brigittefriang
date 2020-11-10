# VX Elliptique

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=33)

Category : Crypto

Points : 250

## Description

Nous avons intercepté 2 fichiers (VX_elliptique.pdf et livres_Friang.pdf) émis par un sous-marin d'Evil Gouv. La référence à Brigitte Friang ne peut être une coïncidence. Nous savons de source sure qu'Eve Descartes a été enlevée par Evil Gouv et est retenue dans un de leurs sous-marins dans l'océan Atlantique. Ce doit être elle qui a envoyé ces fichiers. Grâce à une de ses crises mathématiques, elle aura sûrement caché l'identification du sous-marin dans ces fichiers. Votre mission est de retrouver l'identification du sous-marin.

Le flag est de la forme DGSESIEE{x} avec x le code d'identification

- VX_elliptique.pdf (SHA256=7995fc6529494734bae9e2a0b1800632bf9ebd41cbfab19ce23d834eabcf7523) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/VX_elliptique.pdf
l- ivres_Friang.pdf (SHA256=222a463aeb09ef4c0599b9448184e616462459baea327827469bc7b0dd738b75) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/livres_Friang.pdf

## Solution

Le problème revient à :

1. trouver l'équation de la courbe elliptique à partir de P => Curve25519
2. trouver les racines des polynomes du troisième degré dans GF(n) => merci SageMath
3. appliquer le théorème des restes chinois pour trouver z => merci SageMath

Il y a trois racines pour x1. La première est la bonne.

```
z = 1626912004825687681266928944940137740110044614947501502667974700957265876831665835249437745227202257555252761324145945972681589648893511804029315415851794
```

Le PDF contient les couvertures de 3 livres, dont un avec un code grossièrement ajouté: `BF-2703-9020-RTQM`

## Flag

`DGSESIEE{BF-2703-9020-RTQM}`
