# Code du système de communications pour le satellite CubeSat NB

La branche "master" contient un code fonctionnel, mais n'est pas la plus récente.

La branche "CommunicationAX25" contient les modifications les plus récentes (en développement).

## Comment télécharger le code?

Ouvrir une console Git Bash et exécuter la commande : git clone https://github.com/efl7126/CubeSatNB_PFE.git

## Comment utiliser Git?

Voici un petit tutoriel pour commencer avec Git :

1.	Downloader Git
- https://git-scm.com/downloads
2.	Ouvrir Git Bash
3.	Se rendre au dossier où les codes seront téléchargés
- Commande cd pour ‘’change directory’’
- Commande ls pour montrer les fichiers a l’intérieur du dossier
4.	Une fois rendu au bon dossier, il faut faire les commandes :
- git init
  - Crée un dossier Git
- git add . (avec le point)
  - Crée un index.
- git remote add origin https://github.com/efl7126/CubeSatNB_PFE.git
  - Spécifie le dossier sur le serveur GitHub
- git clone https://github.com/efl7126/CubeSatNB_PFE.git
  - Télécharge tous les fichiers (avec toutes les branches)
  - git branch -a
    - Montre les branches disponibles
- git checkout CommunicationAX25
  - Choisis la bonne branche

Pour changer de branche, faire git checkout branchName. Les fichiers dans le dossier local vont changer à ceux de la branche.

## Trucs pour utiliser SW4STM32

1. Pour trouver la definition d'une fonction ou d'un type, faire cntrl-left click sur son nom.  
2. A chaque fois que vous tombez sur une erreur bizarre, toujours faire un Project->Clean avant Project->Build All
3. En ce qui a trait au code de configuration (p. ex. les interfaces), mieut vaut utiliser STM32CubeMX qui va generer le code automatiquement sans erreur.
