# Le discret Napier

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=29)

Category : Crypto

Points : 150

## Description

Description
Stockos a encore choisi un code d'accès qui est solution d'une énigme mathématique ! Retrouvez x tel que : 17^x ≡ 183512102249711162422426526694763570228 [207419578609033051199924683129295125643]

Le flag est de la forme : DGSESIEE{x} avec x la solution

## Solution

### avec PARI/GP

[PARI/GP](https://pari.math.u-bordeaux.fr)

```
default(parisize, 120000000)
g=17
y=183512102249711162422426526694763570228
p=207419578609033051199924683129295125643
znlog(Mod(y,p), Mod(g, p), [p-1, factor(p-1)])
```

résultat: 697873717765


### avec Sage Math

`docker run --rm -it sagemath/sagemath:latest`

```
sage: g=17
sage: y=183512102249711162422426526694763570228
sage: p=207419578609033051199924683129295125643
sage: mod(y,p).log(g)
```

Flag: `DGSESIEE{697873717765}`
