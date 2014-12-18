*************************************
Adrien Fabre - M1 - IL

Programmation système

Compte rendu TP 3 et 4
*************************************


Exercice 1 

a) 
ts.c est le serveur TCP
le programme est a compiler avec la bibliothèque libsrcXX.a

Ici sur un sytème 32 bits: 

gcc ts.c -o ts libsr32.a

Pour le port d'écoute, la ligne 17 est la suivante:
    servaddr.sin_port        = htons(SERV_PORT);

On y définit le port écoute à la valeur SERV_PORT. Cette valeur est définie dans entete2.h à la valeur 9812

b) 
us.c est le serveur UDP.
Il écoute sur le même port SERV_PORT 9812

c)
clu.c

On lance le serveur UDP pour qu'il attende un message:
us
On lance le client en lui donnant l'adresse de loopback puisque le serveur est sur la même machine
clu 127.0.0.1

Le client demande une saisie utilisateur et on peut observer le paquet envoyé avec wireshark
(=> voir wireshark_clu_UDP.png)

Les informations sont donc les suivantes:
IPs sources et destination = 127.0.0.1 
Ce qui est normal puisque les deux programmes tournent en local sur la machine

Port source : 39746 (attribué au client par l'OS)
Port destination : 9811 (défini dans le header)

d)
On peut observer sur wireshark qu'il n'y a pas de réponse du serveur (de plus le client n'affiche pas de réponse comme il le devrait)

Il n'y a pas de réponse du serveur parce que le serveur attend des packets sur 9812 alors que le packet est lancé sur 9811.

e)
On va donc modifier entete1.h en définissant SERV_PORT à 9812.
Ainsi le serveur et le client communiqueront sur le même port et verrons donc les messages.

(=> voir wireshark_udp_reponse_serveur.png)

f)
Si le serveur est éliminé et que le client tente d'envoyer un message, on peut observer un paquet indiquant que le port de destination n'est pas joignable.

(=> voir wireshark_udp_port_unreachable.png)


g)
Cette fois on observe de nouveau que le client envoi son message et le serveur lui renvoi pour qu'il l'affiche.
La partie intéressante est la capture effectuée par wireshark. On peut voir les différents packets SYN et ACK propres au protocol TCP. (=> voir wireshark_tcp.png)

Comme j'avais modifié le ficher entete1.h le client/serveur a fonctionné du premier coup cependant si les ports ne sont pas les même et que la connexion ne peut pas se faire,  TCP est capable de le détecter parce qu'il ne reçoit pas de paquets ACK donc le client est capable d'afficher une erreur


