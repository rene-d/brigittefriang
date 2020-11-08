# Challenge d'Antoine Rossignol du service Crypto

## Dialogue

> Agent 42, félicitations pour votre affectation sur l'affaire Friang ! Je pense avoir une piste sérieuse. Mais avant toute chose, voici les échanges avec votre prédécesseur :

[echange.txt](echange.txt)

> Eve Descartes est une spécialiste des attaques matérielles. Elle travaille dans les salles blanches d'ESIEE Paris et elle nous donne un coup de main de temps en temps. C'est la meilleure dans son domaine

> Merci ! Je vous en dois une !

> Attendez, je ne vous ai pas encore donné les fichiers !

[archive_chiffree](archive_chiffree)

[layout.pdf](layout.pdf)

[compte_rendu_eve.pdf](compte_rendu_eve.pdf)

> Comme vous pouvez le voir, le fichier que nous a envoyé Eve est protégé par un mot de passe et elle ne répond plus. Trouvez un moyen de la contacter pour déchiffrer le fichier

> Décidément, vous ne chômez pas au service crypto !

> Arrêtez votre charme 42. Nous cherchons une information capitale qui est certainement cachée dans archive_chiffree. Si vous trouvez quelque chose envoyez-moi un message !


## Solution

### étape 1

`layout.pdf` est protégé par un mot de passe, l'autre PDF sous-entend qu'il faut contacter Eve Descartes pour connaître le mot de passe du premier.

L'envoi d'un mail provoque une réponse automatique avec un numéro de téléphone. Et le téléphone donne un message en Morse qu'on décode :

```
R ▄  ▄▄▄  ▄
E ▄
S ▄  ▄  ▄
I ▄  ▄
S ▄  ▄  ▄
T ▄▄▄
A ▄  ▄▄▄
N ▄▄▄  ▄
C ▄▄▄  ▄  ▄▄▄  ▄
E ▄
```

Le mot de passe est donc: `resistance` (en minuscule).

### étape 2

`layout.pdf` contient comme annoncé la photo d'un circuit avec 256 eFuses.

En notant 0 un fuse et 1 l'ouverture, on obtient une série de bits. Avec le MSB en haut à gauche, cela donne:
```
100000101000101010100110010000000110010001101010011011000100000010001010100001101000010001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000
```
soit, en hexa:
```
4145532032353620454342202020202020202020202020202020202020202020
```
et en ASCII (ˍ = espace) :
```
AESˍ256ˍECBˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍ
```

Ainsi le chiffrage de `archive_chiffree` est [AES 256 ECB](https://fr.wikipedia.org/wiki/Mode_d%27opération_(cryptographie)#Dictionnaire_de_codes_:_«_Electronic_codebook_»_(ECB)).

Pas de IV pour ECB, juste une clé de 256 bits.
```bash
openssl aes-256-ecb -d -in archive_chiffree -K 4145532032353620454342202020202020202020202020202020202020202020 -out archive.zip
```

### étape 3

Il y a deux fichiers dans l'archive : `archive/code_acces.pdf` et `archive/message.pdf` . Le premier PDF est protégé par mot de passe, le deuxième contient un problème de math basé sur le [théorème des restes chinois](https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois):

* `x³ ≡ 573 mod 8387`
* `x³ ≡ 98 mod 9613`
* `x³ ≡ 2726 mod 7927`

Il y a une solution unique parce que 8387, 9613 et 7927 sont premiers entre eux.
* `x³ = 177693901848`

D'où `x = 5622`

mot de passe de `code_acces.pdf` : `5622`

### étape 4

Le problème (toujours de math) consiste à trouver l'inverse dans le groupe généré par le polynome 0x11b dans GF(2⁸).

http://www.cs.utsa.edu/~wagner/laws/FFM.html

Mot de passe final : `b a:e z`


Le dialogue de fin donne le lien vers le site des CTF:

> C'est ça ! Tiens, ça me fait penser à Enigma. Notez-le ça pourrait vous servir ultérieurement... On sait maintenant qu'Evil Country va utiliser du VX contre sa propre population, connectez-vous sur cette plateforme top secrète pour continuer l'enquête : /7a144cdc500b28e80cf760d60aca2ed3, on ne peut pas prendre le risque qu'un agent double ne s'en rende compte.
