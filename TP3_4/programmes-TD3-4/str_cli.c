
/* Boucle de traitement du client : lecture d'une ligne de texte � partir de 
 * l'entr�e standard, son �criture sur le serveur, lecture de l'�cho du serveur
 * et �criture de cette ligne d'�cho sur la sortie standard.
*/
#include	"entete1.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: terminaison pr�matur�e du serveur");

		Fputs(recvline, stdout);
	}
}
