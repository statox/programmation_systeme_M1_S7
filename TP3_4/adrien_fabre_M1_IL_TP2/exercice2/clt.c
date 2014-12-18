#include	"entete1.h"

int
main(int argc, char **argv)
{
	int			sockfd;
	struct sockaddr_in	servaddr;


    /* amelioration: choix du port utilise au lancement du programme */
    if (argc != 3)
        err_quit("usage: clt <adresse-IP-serveur> <port-serveur>");

    /* récupération des paramètres */
    char * adresse = argv[1];
    int serv_port;
    sscanf(argv[2], "%d", &serv_port);



    printf ("client TCP\n");
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(serv_port);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);		

	exit(0);
}
