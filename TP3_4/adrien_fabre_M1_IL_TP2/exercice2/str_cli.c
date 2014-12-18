
/* Boucle de traitement du client : lecture d'une ligne de texte � partir de 
 * l'entr�e standard, son �criture sur le serveur, lecture de l'�cho du serveur
 * et �criture de cette ligne d'�cho sur la sortie standard.
*/

/*
 * Ceci est la deuxieme version de la fonction.
 * La premiere version �tait bloquante sur un appel � Fgets ce qui faisait qu'en cas de fin brutale du serveur l'application n'�tait pas pr�venue.
 *
 * Ici le principe sera de rendre la fonction bloquante sur un appel � select. Ainsi select pr�viendra le programme si la saisie est termin�e mais �galement si la socket r�seau re�oit un message de fin
 *
 * On sait que l'entr�e est finie ou que le serveur n'est plus disponible que les file descriptors correspondants � ces �l�ments passent en mode 'readable'
 *
 */

#include	"entete1.h"

void
str_cli(FILE *fp, int sockfd)
{
    int     maxFileDescr;
    int     iofd;
    fd_set  rset;   // ce set de FileDescriptor permet � select de traiter l'entr�e standar et la socket.
	char	sendline[MAXLINE], recvline[MAXLINE];

    // select ne fonctionne qu'avec des file descriptor. 
    // fileno converti le pointeur vers l'entr�e standard en file descriptor
    iofd = fileno(fp);

    // initialisation du set
    FD_ZERO(&rset);

    for ( ; ; )
    {
        FD_SET(sockfd, &rset);  // ajout du FD de la socket au set
        FD_SET(iofd, &rset);  // ajout de l'entr�e standard au set
        maxFileDescr = max (iofd, sockfd) + 1;
        Select(maxFileDescr, &rset, NULL, NULL, NULL);
    

        // socket readable = fin du serveur
        if (FD_ISSET(sockfd, &rset))
        {
            if (Readline(sockfd, recvline, MAXLINE) == 0)
                err_quit("str_cli: fin prematuree du serveur");
            Fputs(recvline, stdout);  
        }

        // entr�e standard readable = fin de la saisie
        if (FD_ISSET(iofd, &rset))
        {
            // si la chaine est vide ou qu'il y a eu une erreur
            if (Fgets(sendline, MAXLINE, fp) == NULL)
            {
                printf("erreur dans la saisie\n");
                return;
            }
            // si la saisie s'est bien pass� on l'envoi
            Writen(sockfd, sendline, strlen(sendline)); 
        }

    }

}
