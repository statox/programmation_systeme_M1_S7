#include	"entete2.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

    printf ("On lance le bind\n");
	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

    printf("dg_echo\n");
	dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

    printf("end\n");
}
