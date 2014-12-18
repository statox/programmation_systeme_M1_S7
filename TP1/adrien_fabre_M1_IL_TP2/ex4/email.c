/*  
 *  Adrien Fabre - M1 - IL
 *
 *  Programmation systeme
 *
 *  TP 1 - ex 4
 *
 *  */

/*
 *  Note importante:
 *  Chez moi ce programme fonctionne en partie: 
 *  lorsque j'utilise la commande 'mail' dans la ligne de commande j'ai après chaque envoi un message m'indiquant
 *  l'echec de l'envoi de mon mail. Je pense donc qu'en configurant correctement l'outil mail de debian ce programme 
 *  serait fonctionnel chez moi. Cependant cette configuration ne relève pas de la programmation système en C et je 
 *  m'en occuperait plus tard .
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


int main (){

  int   fd[2], nbytes, childPID;
  char  msg[] = "Hello world\n";
  char  readbuffer[80];
  char tempFile[] = "./body";     /* fichier temporaire dans lequel on ecrira notre mail */
  

  /* creation du pipe */
  pipe(fd);

  /* creaetion des threads */
  childPID = fork();

  if(childPID >= 0) // fork reussit
  {
      if(childPID == 0) // processus fils
      {
        printf ("\nJe suis le fils et je lis le message\n");
        /* lecture du message dans le pipe */
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        printf("\nReceived string: %s", readbuffer);

        /* ecriture du message dans un fichier temporaire */
        FILE *fp = fopen(tempFile,"w"); /* ouverture du fichier temp */
        fprintf(fp,"%s\n", readbuffer); /* ecriture du message dedans */
        fclose(fp); 
        
        /* envoi du mail */
        system ("mail -s test adrien.fabre92@gmail.com < body");

     }
      else // processus pere
      {
        printf("\nJe suis le pere et j'ecris le message dans le pipe\n");
        /* On écrit le massage dans le pipe */
        write(fd[1], msg, (sizeof(msg)+1));
     }
  }
  else // fork echec
  {
    printf("\nEchec du fork. Fin du programme\n");
    return EXIT_FAILURE;
  }
  


  return EXIT_SUCCESS;
}



