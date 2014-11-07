                 /* mqfile1serv.c */
		/*** Remplacer les points par les instructions manquantes ***/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  CLE_MESS     	131     /* La cl� associ�e � la file */

#define  LONG_MESS 	512  	/* La longueur du message */

#define  LONG_MESS_MAX 600    	/* La longueur max du message  */

#define  MON_TYP_CLI 	10      /* Le type de messages adress�s au client  */
#define  MON_TYP_SER 	20      /* Le type de messages adress�s au serveur */

#define MSG_R   400     	/* Lecture pour le propri�taire */
#define MSG_W   200     	/* Ecriture pour le propri�taire */


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
      * Cr�ation de la file de messages
      */
	...

     for (;;)
     {
          /*
           * R�ception d'un message
           */
		...

          printf("le serveur %d re�oit un message du client %d\n",getpid(),msg.pid);
          printf("Texte du message re�u: %s\n", msg.mtext) ;

          /*
           * Envoi d'un message (commencer par remplir les champs de msg)
           */
		...

     }
}
