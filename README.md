# Attax.c
Premier projet du jeu Attax en C.

Le jeu attaxx est une variante du jeu reversi aussi appelé othello.


Pour lancer le programme, rien de plus simple, il vous suffit de compiler le fichier
main.c avec le module -lMLV pour ne pas avoir de soucis.

le module MLV : http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/index.html

Il existe plusieurs modes de jeu, comme le mode ascii ou encore graphique…

2) Pour jouer dans les différents modes, il vous suffit d’intégrer les lettres ci-dessous
dans votre lancement :

  1) -a : pour le mode ASCII (non compatible avec le mode graphique)
  2) -g : pour le mode graphique (non compatible avec le mode ASCII)
  3) -o : pour le mode ordinateur (non compatible avec le mode Humain)
  4) -h : pour le mode humain (non compatible avec le mode ordinateur)
  5) -p : pour le mode propagation, qui propose une propagation différente.
  
Par exemple pour lancer le mode Graphique avec un ordinateur il vous suffira d’écrire :

  -go | après votre lancement.
  
3) Une fois le jeu lancé en ascii il vous suffit d’écrire les coordonnées sur laquelle vous
voulez placer votre point, sans oublier un espace ou un saut de ligne entre vos coordonnées x et y.

Une fois le jeu fini le programme vous renverra qui a gagné avec quel score.
