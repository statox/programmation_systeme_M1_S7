
/* Boucle de traitement du client : lecture d'une ligne de texte à partir de 
 * l'entrée standard, son écriture sur le serveur, lecture de l'écho du serveur
 * et écriture de cette ligne d'écho sur la sortie standard.
*/

/*
 * Ceci est la deuxieme version de la fonction.
 * La premiere version était bloquante sur un appel à Fgets ce qui faisait qu'en cas de fin brutale du serveur l'application n'était pas prévenue.
 *
 * Ici le principe sera de rendre la fonction bloquante sur un appel à select. Ainsi select préviendra le programme si la saisie est terminée mais également si la socket réseau reçoit un message de fin
 *
 * On sait que l'entrée est finie ou que le serveur n'est plus disponible que les file descriptors correspondants à ces éléments passent en mode 'readable'
 *
 */

#include	"entete1.h"

void
str_cli(FILE *fp, int sockfd)
{
    int     maxFileDescr;
    int     iofd;
    fd_set  rset;   // ce set de FileDescriptor permet à select de traiter l'entrée standar et la socket.
	char	sendline[MAXLINE], recvline[MAXLINE];

    // select ne fonctionne qu'avec des file descriptor. 
    // fileno converti le pointeur vers l'entrée standard en file descriptor
    iofd = fileno(fp);

    // initialisation du set
    FD_ZERO(&rset);

    for ( ; ; )
    {
        FD_SET(sockfd, &rset);  // ajout du FD de la socket au set
        FD_SET(iofd, &rset);  // ajout de l'entrée standard au set
        maxFileDescr = max (iofd, sockfd) + 1;
        Select(maxFileDescr, &rset, NULL, NULL, NULL);
    

        // socket readable = fin du serveur
        if (FD_ISSET(sockfd, &rset))
        {
            if (Readline(sockfd, recvline, MAXLINE) == 0)
                err_quit("str_cli: fin prematuree du serveur");
            Fputs(recvline, stdout);  
        }

        // entrée standard readable = fin de la saisie
        if (FD_ISSET(iofd, &rset))
        {
            // si la chaine est vide ou qu'il y a eu une erreur
            if (Fgets(sendline, MAXLINE, fp) == NULL)
            {
                printf("erreur dans la saisie\n");
                return;
            }
            // si la saisie s'est bien passé on l'envoi
            Writen(sockfd, sendline, strlen(sendline)); 
        }

    }

}
