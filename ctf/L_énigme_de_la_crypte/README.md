# L'énigme de la crypte

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=22)

Category : Crypto

Points : 200

## Description

Une livraison de souffre doit avoir lieu 47°N 34 2°W 1 39.

Elle sera effectuée par un certain REJEWSKI. Il a reçu des instructions sur un foulard pour signaler à Evil Gouv son arrivée imminente.

Nous avons une photo du foulard, mais celle-ci n'est pas très nette et nous n'avons pas pu lire toutes les informations. Le fichier foulard.txt, est la retranscription du foulard.

Nous avons un peu avancé sur les parties illisibles :

(texte illisible 1) est deux lettres un espace deux lettres. Il pourrait y avoir un lien avec le dernier code d'accès que vous avez envoyé à Antoine Rossignol.

(texte illisible 2) a été totalement effacé et enfin (texte illisible 3) semble être deux lettres.

REJEWSKI vient d'envoyer un message (final.txt). Il faut que vous arriviez à le déchiffrer. Je vous conseille d'utiliser openssl pour RSA.

Le flag est de la forme DGSESIEE{MESSAGE} où MESSAGE correspond à la partie centrale du texte en majuscules sans espace.

- final.txt (SHA256=1e93526cd819aedb8496430a800a610068e95762536b0366ca7c303a74eaab03) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/final.txt
- foulard.txt (SHA256=9c8b0caf9d72fa68ddb6b4a68e860ee594683f7fe4a01a821914539ef81a1f21) : http://challengecybersec.fr/d3d2bf6b74ec26fdb57f76171c36c8fa/foulard.txt


## Les instructions du foulard

```
Mission Scherbius

Chiffrez un message suivi de votre nom avec la machine de type M3 avec cette disposition :

Uniquement les impairs en ordre croissant
Ringstellung : REJ
Steckerverbindungen : (texte illisible 1)
Grundstellung : MER
(texte illisible 2): B(texte illisible 3)

Le résultat (texte) doit être ensuite chiffré avec RSA en utilisant notre clé publique avant de nous l'envoyer. Je vous rappelle notre clé publique :

Modulus (décimal):

25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784406918290641249515082189298559149176184502808489120072844992687392807287776735971418347270261896375014971824691165077613379859095700097330459748808428401797429100642458691817195118746121515172654632282216870038352484922422622979684865170307405907272815653581732377164114195025335694039872221524699156538352092782201392513118326772302632498764753996118057437198905106508696675497143847180616766425109043955104189270381382844602871223783458512671511503420521749067165952916834014926827585314522687939452292676577212513301

PublicExponent (décimal) : 65537
```

## Solution

### Etape 1: chiffrage RSA

On va utiliser l'outil [RsaCtfTool](https://github.com/Ganapati/RsaCtfTool).

C'est l'attaque Fermat (factorisation pour *p* et *q* proches) qui permet d'obtenir la clé privée:

```bash
RsaCtfTool.py --createpub -n 25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784406918290641249515082189298559149176184502808489120072844992687392807287776735971418347270261896375014971824691165077613379859095700097330459748808428401797429100642458691817195118746121515172654632282216870038352484922422622979684865170307405907272815653581732377164114195025335694039872221524699156538352092782201392513118326772302632498764753996118057437198905106508696675497143847180616766425109043955104189270381382844602871223783458512671511503420521749067165952916834014926827585314522687939452292676577212513301 -e 65537 > public.key

RsaCtfTool.py --publickey public.key --private > private.key

openssl rsautl -decrypt -inkey private.key -in final.txt
```


`final.txt` décrypté :
```
IVQDQT NHABMPSVBYYUCJIYMJBRDWXAXP  THYVCROD
```

### Etape 2: Machine Enigma

#### Programme

[enigma.c](https://gist.github.com/5167acdc0c75ca909f372a008e0f114c) est un programme en C pour coder/décoder Enigma (initialement écrit pour résoudre le challenge [Machine Enigma](https://www.root-me.org/fr/Challenges/Cryptanalyse/Machine-Enigma)).

Ou le module Python [pyenigma](https://pypi.org/project/pyenigma/), ou [cryptii](https://cryptii.com/pipes/enigma-machine), ou [dcode.fr](https://www.dcode.fr/chiffre-machine-enigma), etc.

#### Observation du texte

Le texte est composé de 6 lettres, puis 26 en partie centrale et enfin, 8 lettres.

Les 6 premières lettres correspondent peut-être à une clé chiffreur (ou [cillies](https://fr.wikipedia.org/wiki/Enigma_(machine)#Préparation_de_la_machine)). Ce sont trois lettres choisies par le chiffreur, transmises deux fois. Puis l'opérateur repositionne les rotors sur ces 3 lettres.

Les 8 dernières lettres, au nom de l'agent (REJEWSKI) (instructions du foulard).

#### Configuration

Le mode opératoire d'Enigma est décrit sur des centaines (voir milliers) de sites. Notamment sur la page [Wikipedia](https://fr.wikipedia.org/wiki/Enigma_(machine)) et aussi en anglais sur cet [excellent site](http://users.telenet.be/d.rijmenants/en/enigmaproc.htm).

Selon les indices et les instructions du foulard, on a :
* *Grundstellung* (« position initiale des rotors ») : `MER` (foulard)
* *Ringstellung* (« positionnement de l'anneau ») : `REJ` (foulard)
* *Walzenlage* (« rotor »): I III V  (foulard: Uniquement les impairs en ordre croissant)
* *Steckerverbindungen*  (« tableau de connexion, plugboard ») : `BE AZ` (deux lettres un espace deux lettres, indice)
* *Umkehrwalze* (« réflecteur, reflector ») : `B` (non mentionné sur le foulard)

#### Les textes illisibles

* texte illisible 1 = `BE AZ`  (indice du défi crypto d'Antoine Rossignol `b a:e z`, et non `BA EZ` !)
* texte illisible 2 = `?`   (certainement clé opérateur, je ne connais pas le terme allemand)
* texte illisible 3 = `B??`  (certainement la clé opérateur, ou *message key*)

#### Clé opérateur (ou clé chiffreur)

On utilise le programme une première fois pour savoir la clé chiffreur:
```bash
$ ./enigma B MER-REJ I III V "BE AZ" "IVQDQT NHABMPSVBYYUCJIYMJBRDWXAXP  THYVCROD"
```
```
BFGBFG CMVEJLFJGTMORQGNFZNQMUCPQY  RYSNOOUR
```

La clé chiffreur est donc `BFG` ([référence](https://en.wikipedia.org/wiki/BFG_(weapon)) amusante et certainement non fortuite 😂).

#### Décodage du message
```bash
./enigma B BFG-REJ I III V "BE AZ" "NHABMPSVBYYUCJIYMJBRDWXAXP  THYVCROD"
```
```
LESSANGLOTSLONGSDESVIOLONS  WJVDLOIT
```

Bingo, sans aucun doute possible, le flag est `LESSANGLOTSLONGSDESVIOLONS`.

#### La signature

Curieusement, le nom est codé avec la même position initiale `BFG` :
```
./enigma B BFG-REJ I III V "BE AZ" "THYVCROD"
```
```
REJEWSKI
```

Ce qui ne correspond pas tout à fait aux usages d'Enigma pour un même message.


### Notes

Le nom de la mission est inspirée par le créateur d'Enigma, [Arthur Scherbius](https://fr.wikipedia.org/wiki/Arthur_Scherbius).

[Marian Rejewski](https://fr.wikipedia.org/wiki/Marian_Rejewski) est un mathématicien et cryptologue polonais à l'origine du cassage du chiffrement Enigma.

La localisation [GPS](https://www.google.com/maps/place/47°34'00.0%22N+2°01'39.0%22W/@47.5666703,-2.0296887,17z/data=!3m1!4b1!4m5!3m4!1s0x0:0x0!8m2!3d47.5666667!4d-2.0275) correspond à un terrain au milieu d'un triangle Vannes-Nantes-Rennes, proche du village de Frégéac. La référence reste mystérieuse (mais il n'y a peut-être aucune référence à trouver).


## Flag

`DGSESIEE{LESSANGLOTSLONGSDESVIOLONS}`
