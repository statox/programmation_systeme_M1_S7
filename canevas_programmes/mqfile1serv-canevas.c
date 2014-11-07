                 /* mqfile1serv.c */
		/*** Remplacer les points par les instructions manquantes ***/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  CLE_MESS     	131     /* La clé associée à la file */

#define  LONG_MESS 	512  	/* La longueur du message */

#define  LONG_MESS_MAX 600    	/* La longueur max du message  */

#define  MON_TYP_CLI 	10      /* Le type de messages adressés au client  */
#define  MON_TYP_SER 	20      /* Le type de messages adressés au serveur */

#define MSG_R   400     	/* Lecture pour le propriétaire */
#define MSG_W   200     	/* Ecriture pour le propriétaire */


struct decrimsg     {
     long     mtype;
     int      pid;
     char     mtext[LONG_MESS];
} ;

main()
{
struct decrimsg msg;             /* message */
int msgid;                      /* Identificateur de la file de messages */

     /*
      * Création de la file de messages
      */
	...

     for (;;)
     {
          /*
           * Réception d'un message
           */
		...

          printf("le serveur %d reçoit un message du client %d\n",getpid(),msg.pid);
          printf("Texte du message reçu: %s\n", msg.mtext) ;

          /*
           * Envoi d'un message (commencer par remplir les champs de msg)
           */
		...

     }
}
