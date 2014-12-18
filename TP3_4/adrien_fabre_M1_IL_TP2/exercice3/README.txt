*************************************
Adrien Fabre - M1 - IL

Programmation système

Compte rendu TP 3 et 4
*************************************

exercice 3

a)
Dans le fichier cltp.c on voit que la fonction main fait appel à la function mescli().
Cette méthode étant définie dans le fichier msg+.c, il faut compiler cltp de la manière suivante:

gcc cltp.c -o cltp msg+.c libsr32.a 

b)
En réutilisant le programme selsut de l'exercice précédent, la communication entre les deux programmes se fait bien
(voir wireshark_selsut_working.png)

Question à voir avec Mr Ahmadi: 
ici il y a plus de packets qui passent: Le client envoi 2 demandes d'ACK auxquelles le serveur répond. Puis le serveur envoi une demande d'ACK à laquelle le client répond.
Alors que précédemment clt n'envoyant qu'une demande d'ACK à laquelle le serveur répondait.

ctlp utilisant le protocole TCP, la communication se fait également avec le programme ts des exercices précédents.

c)
Lorsque l'on tue le serveur, le client ne réagit pas immédiatement: il faut attendre une nouvelle saisie clavier pour afficher une erreur.
Cependant sur la capture wiresharl (cd wireshark_fin_serveur.png) on peut voir que lorsqu'il est tué le serveur envoi un paquet avec le flag RST pour prévenir le client et le client répond à ce paquet.

d)
ici echo $? affiche 130.

Rappelons que $? contient le code de sortie de la dernière commande exécutée. 
C'est à dire la valeur de retour du programme serveur.

le signal correspondant à 130-128=2 correspond au signal d'interruption SIGINT - Terminal interrupt (ANSI)

e)
Je ne trouve pas de manuel correspondant à la fonction Writen.
De plus je ne comprends pas comment le code de msg+.c appréhende et gère un signal envoyé par le serveur. Je n'arrive donc pas à répondre à cette question.
