#include	"entete1.h"

int
main(int argc, char **argv)
{
	int			sockfd;
	struct sockaddr_in	servaddr;

    /* amelioration: choix du port utilise au lancement du programme */
    if (argc != 3)
        err_quit("usage: clu <adresse-IP-serveur> <port-serveur>");

    /* récupération des paramètres */
    char * adresse = argv[1];
    int serv_port;
    sscanf(argv[2], "%d", &serv_port);


    printf ("client UDP\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(serv_port);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

	exit(0);
}
