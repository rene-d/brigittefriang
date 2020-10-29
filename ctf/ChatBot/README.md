# ChatBot

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=31)

Category : Web

Points : 100

## Description

EvilGouv a récemment ouvert un service de chat-bot, vous savez ces trucs que personne n'aime. Bon en plus d'être particulièrement nul, il doit forcément y avoir une faille. Trouvez un moyen d'accéder à l'intranet !

Lien : https://challengecybersec.fr/b34658e7f6221024f8d18a7f0d3497e4

Indice : Réseau local

Le flag est de la forme : DGSESIEE{x} avec x un hash


## WIP

### question 1
```bash
curl https://challengecybersec.fr/b34658e7f6221024f8d18a7f0d3497e4/bot\?message\=Bonjour
```
```json
{"message":"Bonjour ! Vous pouvez me poser n'importe quelle question sur les emplois que nous proposons"}%
```

### question 2
```bash
curl https://challengecybersec.fr/b34658e7f6221024f8d18a7f0d3497e4/bot\?message\=Liste%20des%20emplois
```
```json
{"message":"Nous proposons tous types d'emplois, administratifs ou sur le terrain. Nous recherchons principalement des agents, pour le moins secrets"}
```

### question 3
```bash
curl https://challengecybersec.fr/b34658e7f6221024f8d18a7f0d3497e4/bot\?message\=Comment%20candidater%20?
```
```json
{"message":"Vous pouvez postuler en vous rendant sur un moteur de recherche comme https://www.qwant.com/ et rechercher notre administration pour postuler"}
```

## Flag

## Comments

secuinfo.eu (2020-10-25 18:04:11)
0 validation pour un challenge à 100 pts... sous évalué ou pas faisable ? ^^
mansuetus (2020-10-25 18:05:59)
Je me le demande : j'ai un truc qui pourrait sentir bon mais qui semble ne pas fonctionner de manière étrange.
Brigitte Friang Admin (2020-10-25 18:16:41)
Le challenge a été mis à jour il y a quelques heures, re-tentez
secuinfo.eu (2020-10-25 18:19:26)
@mansuetus : Pareil ...
0x1ntegral (2020-10-25 22:07:16)
Serait-il possible d'avoir un indice sur l'adresse de l'intranet à laquelle il faut accéder ? Y'a t-il un rapport avec la première phase du CTF ?
Brigitte Friang Admin (2020-10-25 22:31:11)
Trouver l'adresse de l'intranet fait partie du challenge, réfléchissez aux subnets standards pour un petit réseau
0x1ntegral (2020-10-25 23:21:40)
Oui c'est bon j'ai trouvé une piste !
Patate (2020-10-26 00:17:32)
plus petit subnet officiel pour du privé: 192.168.0.0/16 , j'espère que personne va bf les 65 536 IPs, sinon la plateforme va cracher du sang x)
MathisHammel (2020-10-27 10:33:35)
Bonjour, je pense avoir trouvé une vulnérabilité non prévue par les créateurs du CTF, il n'y a aucun moyen publié pour contacter les administrateurs à l'exception de cette section de commentaires. Pouvez-vous m'envoyer un email au plus vite ? Je veux bien faire la disclosure ici, mais ça risque de vous poser problème... Merci d'avance
secuinfo.eu (2020-10-27 20:06:25)
@Shay je pense surtout que l'épreuve est en PLS à cause de trop de requêtes ;)
Shay (2020-10-27 20:39:06)
@secuinfo.eu allez le foot
Linuz (2020-10-28 14:38:47)
Est-ce qu'il est prévu d'utiliser du bruteforce pour trouver le réseau local ? Je vois que la plateforme a déjà du mal, pas envie d'apporter ma pierre à l'édifice si ce n'est pas utile. Merci !
CrYpT (2020-10-28 14:39:10)
Bonjour, Les erreurs 504 sont-elles normales sur certains ranges svp ? Ou ces ranges sont-ils à exclure ? Merci d'avance, CrYpT
vivescere (2020-10-28 17:52:09)
> Bonjour, le challenge est-il toujours valide ? Je tombe sur une page non-configurée en accédant à l'intranet, pas sur que ça soit normal.
Brigitte Friang Admin (2020-10-28 18:44:50)
> Bonjour, testé à l'instant et fonctionnel, le flag apparait explicitement sur la page d'intranet
Brigitte Friang Admin (2020-10-28 18:46:25)
> @Linuz il est autorisé sur cette épreuve
