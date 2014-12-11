*************************************
Adrien Fabre - M1 - IL

Programmation système

Compte rendu TP 3 et 4
*************************************

exercice 2

a) 
j'ai utilisé l'appel système select pour traiter des sockets udp et tcp en même temps.

b) 
Pour lancer selsut et ts en même temps il faut qu'ils incluent respectivement entete1.h et entete2.h ce qui permet de les faire fonctionner sur des ports différents.

Afin de manipuler plus simplement les ports utilisés par les serveurs et les clients, j'ai un peu modifié les programmes pour que l'on saisisse le port utilisé sur la ligne de commande au moment du lancement du programme.

c) et d) 
Dans mon code les applications client ont le même entête que l'application selsut, ainsi ces 3 programmes communiquent sur le même port respectivement en UDP et en TCP donc tous les messages passent bien.

Cependant si l'on met des entetes différents pour clt et selsut, la connexion ne peut pas se faire puisque le client essaie de communiquer sur un port qui n'est pas écouté. Wireshark affiche un message d'erreur pour le packet correspondant.

e)
Lorsque l'on élimine le serveur fils, le client est prévenu. On peut le voir via wireshark: un paquet indiquant la fin du serveur est envoyé et le client envoie un ack pour ce paquet (voir wireqhark_fin_serveur.png)

f)
Cependant l'application ne reçoit pas le message immédiatement.
Pour montrer ça, il faut revenir sur le client et essayer de renvoyer un message. A ce moment, le message "str_cli: server terminated prematurely" s'affiche.
Ce délai s'explique par le fait que les entrées clavier bloquaient le client. Il va donc falloir modifier le code avec select pour que le client réagisse.

g)
Ce qui bloque c'est la fonction str_cli() qui bloque en attendant une saisie clavier.
On va donc modifier le code de la fonction dans str_cli.c en lui ajoutant select(). select() permettra de surveiller le réseau et de prévenir l'application si besoin.

On va donc modifier str_cli et il faudra compiler clt.c en donnant à gcc le fichier str_cli.c et en le mettant avec libsr32.a

gcc clt.c -o o/clt str_cli.c libsr32.a

(le nouveau fichier str_cli contient de nombreux commentaires reportant son nouveau fonctionnement)
