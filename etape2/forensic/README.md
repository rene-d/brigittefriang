# Challenge d'Alphonse Bertillon du Service Forensic

## Dialogue

*Alphonse Bertillon*
> Agent 42, mon équipe et moi-même avons détecté une intrusion au sein de notre système

*Agent 42*
> J'écoute

*Alphonse Bertillon*
> Un agent d'Evil Gouv a réussi à se connecter sur notre plateforme, il faut absolument que l'on retrouve son adresse IP

[access.log](access.log)

> Voici les logs de Nginx

*Agent 42*
> Aucun problème Alphonse, je vais traquer cette vipère

*Alphonse Bertillon*
> Envoyez moi l'adresse IP dès que vous la trouvez j'ai une piste très prometteuse sur l'affaire Friang

*Agent 42* (cf. ci-dessous)
> 179.97.58.61

*Alphonse Bertillon*
> Bien joué, nous l'avons bloqué ! Comme promis, voici une image trouvée dans une pièce jointe d'un e-mail provenant d'Evil Country. Nous pensons que la résistance tente de rentrer en contact avec nous.

> Nous savons que leur réseau a été infecté ces derniers jours et qu'ils ont perdu des baies de disques.

> Attention Agent 42, la pièce jointe risque de contenir un malware alors n'exécutez aucune application extraite de ce fichier directement sur votre ordinateur.

evil_country_landscape.jpg

## Solution

### Fichier `access.log`
```
179.97.58.61 - - [Nov 05 2020 16:22:20] "POST /login HTTP/1.1" 200 476 "-" "Evil Browser"
```

D'où l'adresse IP suspecte: `179.97.58.61`

### Fichier `evil_country_landscape.jpg`

```bash
unzip evil_country_landscape.jpg
```

raids possibles (cf. https://docs.oracle.com/cd/E19871-01/820-1847-20/appendixf.html):
* RAID 0
* RAID 1
* RAID 1 Enhanced Arrays
* RAID 5 Arrays

```bash
sudo losetup /dev/loop2 part2.img
sudo losetup /dev/loop3 part3.img

sudo mount /dev/md6 /mnt
unzip /mnt/dump.zip
sudo umount /mnt
sudo mdadm --stop /dev/md6
sudo losetup -D
```

```bash
volatility -f dump.vmem imageinfo
volatility -f dump.vmem --profile Win7SP1x64 envars
# => notepad, dropbox,

volatility -f dump.vmem --profile Win7SP1x64 pstree
    cmd.exe                       1744
    notepad.exe                   1880
    drpbx.exe                     2304

volatility -f dump.vmem --profile Win7SP1x64 memdump -p 1880 -D .
```

Chaînes de caractères présentes dans le dump mémoire de notepad:
```
"J'ai payé, je veux retrouver mes fichiers svp"
"Envoyez 500000 EvilCoins ici:"
"Que les choses soient bien claires, nous ne tolérons aucune entrave à notre plan
Votre action de résistance est vaine et dénuée de sens
Nous vous détruirons sans_
"
```

```bash
volatility -f dump.vmem --profile Win7SP1x64 filescan | grep Documents

0x000000003ddb1890      7      0 R--r-d \Device\HarddiskVolume1\Users\user\Documents\Firefox_installer.exe
0x000000001715ed50     16      0 R--r-- \Device\HarddiskVolume1\Users\user\Documents\informations_attaque.txt.evil
```

```bash
volatility -f dump.vmem --profile Win7SP1x64 dumpfiles -D toto -Q 0x000000003ddb1890  -n
volatility -f dump.vmem --profile Win7SP1x64 dumpfiles -D toto -Q 0x000000001715ed50  -n
```

**Attention** présence du malware [JigSaw](https://fr.wikipedia.org/wiki/Jigsaw_(ransomware))

"Copyright 1999-2012 Firefox and Mozzilla developers. All rights reserved"
dans file.None.0xfffffa800e7892a0.Firefox_installer.exe.dat
