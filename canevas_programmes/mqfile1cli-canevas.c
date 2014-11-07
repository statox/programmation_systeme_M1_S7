                 /* mqfile1cli.c */
		/*** Remplacer les points par les instructions manquantes ***/


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  CLE_MESS     	131      /* La clé associée à la file de messages */

#define  LONG_MESS 	512  	/* La longueur du message */

#define  LONG_MESS_MAX 	600    	/* la longueur max du message */

#define  MON_TYP_CLI 10       	/* Le type de messages adressés au client  */ 
#define  MON_TYP_SER 20      	/* Le type des messages adressés au serveur */

struct decrimsg     {
     long     mtype;
     int      pid;
     char     mtext[LONG_MESS];
} ;

main()
{
struct decrimsg msg;                         /* message */
int msgid;                                  /* identificateur de la file */
char *message_t10 = "Ici l'EFREI: bonjour L3a" ;   /* texte du message */

     /*
      * Récupération de l'identificateur de la file de messages
      */

	...
     /*
      * Envoi d'un message (commencer par remplir les champs de msg)
      */
     strcpy(msg.mtext,message_t10) ; /* Champ mtext rempli */
     printf("client: envoi du message:%s\n",msg.mtext) ;
	
	...
     /* 
      * Réception d'un message 
      */
     printf("client: attente de message\n") ;

	...

     printf("processus client = %d reçoit un message du serveur %d\n", getpid(), msg.pid);
}
