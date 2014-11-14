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
	msgid = open_queue( CLE_MESS );
	if (msgid == -1){
		printf ("Erreur à la creation de la file de message");
		return (EXIT_FAILURE);
	}
	
	int i=0;
	for (i=0; i<10; ++i)
     //for (;;)
     {
          /*
           * Réception d'un message
           */
	
		if ( read_message(msgid, MON_TYP_CLI, &msg ) == -1 ){
			printf("Erreur a l'envoi du message dans la file");
			return (EXIT_FAILURE);
		}

          printf("le serveur %d reçoit un message du client %d\n",getpid(),msg.pid);
          printf("Texte du message reçu: %s\n", msg.mtext) ;

          /*
           * Envoi d'un message (commencer par remplir les champs de msg)
           */
		strcpy(msg.mtext, "Reponse du serveur") ; /* Champ mtext rempli */
     	msg.pid = getpid();
	 	msg.mtype =MON_TYP_SER; /* valeur arbitraire */
     	printf("serveur: envoi du message:%s\n",msg.mtext) ;


		if ( send_message(msgid, &msg) == -1 ){
			printf("Erreur a l'envoi du message dans la file");
			return (EXIT_FAILURE);
		}

     }
}

/* Cette fonction ouvre une nouvelle file et renvoit son identifiant ou -1 en cas d'echec */
int open_queue( key_t keyval )
{
  int     qid;
                  
  if((qid = msgget( keyval, IPC_CREAT | 0660 )) == -1)
  {
    return(-1);
  }
                          
  return(qid);
}

/* Cette fonction envoi un message dans la file */
int send_message( int qid, struct descrimsg *msg )
{
	int     result;
       
	if((result = msgsnd( qid, msg, LONG_MESS, 0)) == -1)
	{
		return(-1);
	}
                                  
	return(result);
}

/* Cette fonction lit un message dans la file */
int read_message( int qid, long  type, struct descrimsg *msg )
{
	int     result;


	if((result = msgrcv( qid, msg, LONG_MESS, type,  0)) == -1)
	{
		return(-1);
	}

	return(result);
}
