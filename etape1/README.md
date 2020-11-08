# Challenge Brigitte Friang : introduction

## Solution page d'accueil

Il faut regarder le source de la page pour voir en commentaire un lien vers une page secrète:

```bash
curl https://www.challengecybersec.fr
```

```html
        <link rel="stylesheet" href="/static/css/style.css">
        <!--/static/message-secret.html-->
    </head>
```

## Solution message secret

La page `message-secret.html` contient un texte bizarre et un titre en forme d'indice: Cesar.

C'est donc un chiffrement de [César](https://fr.wikipedia.org/wiki/Chiffrement_par_décalage).

Après quelques essais, on trouve que le décalage +19 décode un texte en français.

Le script Python3 [cesar.py](./cesar.py) fait le job.

Certaines lettres sont en gras: elles constituent le flag: `/chat`

Avec l'indication contenue dans le texte
> Completez l’URL avec l’information qui est cachee dans ce message.

on a l'URL pour passer à la phase suivante du challenge: https://www.challengecybersec.fr/chat
