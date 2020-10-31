# VX Elliptique

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=33)

Category : Crypto

Points : 250

## Description
Nous avons intercepté 2 fichiers (VX_elliptique.pdf et livres_Friang.pdf) émis par un sous-marin d'Evil Gouv. La référence à Brigitte Friang ne peut être une coïncidence. Nous savons de source sure qu'Eve Descartes a été enlevée par Evil Gouv et est retenue dans un de leurs sous-marins dans l'océan Atlantique. Ce doit être elle qui a envoyé ces fichiers. Grâce à une de ses crises mathématiques, elle aura sûrement caché l'identification du sous-marin dans ces fichiers. Votre mission est de retrouver l'identification du sous-marin.

Le flag est de la forme DGSESIEE{x} avec x le code d'identification

VX_elliptique.pdf (SHA256=7995fc6529494734bae9e2a0b1800632bf9ebd41cbfab19ce23d834eabcf7523) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/VX_elliptique.pdf
livres_Friang.pdf (SHA256=222a463aeb09ef4c0599b9448184e616462459baea327827469bc7b0dd738b75) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/livres_Friang.pdf

## WIP

```
p = 57896044618658097711785492504343953926634992332820282019728792003956564819949
x = 54387532345611522562080964454373961410727797296305781726528152669705763479709
y = 14361142164866602439359111189873751719750924094051390005776268461061669568849
E = ellinit([x, y], p)
n = ellcard(E)
print(n)
```
```
n = 57896044618658097711785492504343953926413552466900146997688876471107112716167
  = 3 * 293 * 7879 * 312747650519 * 26729747913442327627033479544940117473242066963321135846473
```



###
si x1 et x2 sont trouvés => théorème des restes chinois avec n1=n et n2=(n-1)/2


## Flag
