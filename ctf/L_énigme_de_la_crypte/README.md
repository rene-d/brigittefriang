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


## WIP

Lien vers la coordonnée GPS : https://www.google.com/maps/place/47°34'00.0%22N+2°01'39.0%22W/@47.5666667,-2.0296887,17z/data=!3m1!4b1!4m5!3m4!1s0x0:0x0!8m2!3d47.5666667!4d-2.0275

Indice Antoine Rossignol : `b a:e z`  =>  `BA EZ`

[RsaCtfTool](https://github.com/Ganapati/RsaCtfTool)

```bash
RsaCtfTool.py --createpub -n 25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784406918290641249515082189298559149176184502808489120072844992687392807287776735971418347270261896375014971824691165077613379859095700097330459748808428401797429100642458691817195118746121515172654632282216870038352484922422622979684865170307405907272815653581732377164114195025335694039872221524699156538352092782201392513118326772302632498764753996118057437198905106508696675497143847180616766425109043955104189270381382844602871223783458512671511503420521749067165952916834014926827585314522687939452292676577212513301 -e 65537
RsaCtfTool.py --publickey public.key --uncipherfile final.txt --private
```

openssl rsautl -decrypt -inkey private.key -in final.txt

`final.txt` décrypté:
```
IVQDQT NHABMPSVBYYUCJIYMJBRDWXAXP  THYVCROD
```

Selon les indices et le foulard, on devrait avoir:
* *Grundstellung* (« position initiale des rotors ») : `MER` (foulard)
* *Ringstellung* (« positionnement de l'anneau ») : `REJ` (foulard)
* *Walzenlage* (« rotor »): I III V  (foulard: Uniquement les impairs en ordre croissant)
* *Steckerverbindungen*  (« tableau de connexion, plugboard ») : `BA EZ` (deux lettres un espace deux lettres)
* *Umkehrwalze* (« réflecteur, reflector ») : `B` (peut-être, cf. foulard...)

* texte illisible 1 = `BA EZ`  (indice Antoine Rossignol)
* texte illisible 2 = ?
* texte illisible 3 = B??

`ZFGZFG CMFQJLFJDTMORQGNFBAQMUCZQY  RYSNOOUR``

* essai B MER-REJ <tous les rotors> "BA EZ"
* essai B MER-REJ I III V + tous les plugboards à 2 connexions
