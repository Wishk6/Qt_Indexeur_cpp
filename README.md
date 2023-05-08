## Introduction

Ce projet est une application de recherche de fichiers dans une base de données SQLite, avec un dialecte personnalisé pour spécifier les critères de recherche.

Le dialecte de recherche fonctionne comme suit : 

```
SEARCH <filename_part> [OPTIONS]
LAST_MODIFIED:SINCE LAST <number> <unit>
CREATED:dd/mm/yyyy
MAX_SIZE:<number><unit>
MIN_SIZE:<number><unit>
SIZE:BETWEEN <number><unit> AND <number><unit>
EXT:<extension1>,<extension2>,...
```  

#
Pour l'instant, seulement SEARCH est implémenté dans le système de fsm.

Le système d'indexation est à revoir. Je l'ai fait dans la mainwindow, et il n'est pas lié au reste de l'application.
Je me suis trop concentré sur l'indexation.
Je n'aurai pas du continuer dans l'idée de séparer l'indexation de la recherche mais je m'y suis pris trop tard quand j'ai compris que ça n'était pas maintenable et que la mise à jour de la base allait être très complexe. 
Je me suis rendu compte à la fin que vous aviez envoyé le thread d'indexation et le logger dans une conversion Discord.
#

Exemple de recherche :
```
SEARCH "index" EXT:html
```
Dans cet exemple, on recherche tous les fichiers contenant la chaîne de caractères "index" dans leur nom de fichier, avec l'extension "html".

## Fonctionnement de l'application

L'application fonctionne en trois étapes principales : 

1. Indexation des fichiers : Cliquer sur le bouton "Indexer" et de sélectionner le dossier à indexer. Les fichiers sont alors parcourus de manière récursive, et leur nom, leur chemin, leur taille et leur date de dernière modification sont enregistrés dans une base de données SQLite.
2. Recherche de fichiers : Remplir le champ de recherche avec les critères souhaités, en respectant le dialecte de recherche décrit précédemment. Ensuite, il suffit de cliquer sur le bouton "Rechercher" pour lancer la recherche. Les fichiers correspondants sont alors affichés dans une liste déroulante.

V2 :
1. Serveur distant
2. Visualisation de fichiers : une fois les fichiers recherchés, il est possible de les ouvrir en double-cliquant dessus dans la liste déroulante.
3. Supprimer les doublons, vérifier les odublons et faire un système d'update des dossiers indexés
## Structure de l'application

- `mainwindow.ui` : interface graphique de l'application, créée avec Qt Designer.
- `mainwindow.cpp` : implémentation de la logique de l'interface graphique.
- `state.cpp` : implémentation de la machine à états finis pour le dialecte de recherche.
- `querylexer.cpp` : implémentation du lexer pour le dialecte de recherche.
- `databaseUtils.cpp` : implémentation des fonctions pour accéder à la base de données SQLite.
- `mythread.cpp` : thread de lecture de fichier qui permet d'extraire les infos des fichiers.
- `insertionthread.cpp` : thread d'insertion de fichier qui permet d'executer une requte sql toutes les 'X' secondes. 
- `insertionthread.cpp` : thread de recherche de fichier dans la basesqlite qui permet d'executer une requte sql toutes les 'X' secondes. 

## Exemple d'input à tester

Pour tester l'application, vous pouvez utiliser l'exemple de recherche suivant : 

```
SEARCH "index" EXT:html
```
Cela devrait renvoyer tous les fichiers ayant "index" dans leur nom de fichier, avec l'extension "html", si il y a des ficheirs de ce type dans les dossiers précedemment indéxes. 

