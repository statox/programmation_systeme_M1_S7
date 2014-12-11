#include	"entete2.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

    /* petite amélioration pour changer le port d'écoute au lancement de l'application  */
    /* recuperation des parametres */
    if (argc != 2)                                                       
        err_quit("usage: us <port-serveur>");

    int serv_port;                               
        sscanf(argv[1], "%d", &serv_port);


	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(serv_port);

    printf ("On lance le bind\n");
	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

    printf("dg_echo\n");
	dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

    printf("end\n");
}
