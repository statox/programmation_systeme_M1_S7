#include	"entete1.h"
#include    <pthread.h>
#include    <stdio.h>

void * UdpServer (void * param);
void * TcpServer(void * param);
void * SelsutServer (int serv_port);

int main (int argc, char *argv[])
{
    /* petite am�lioration pour changer le port d'�coute au lancement de l'application  */
    /* recuperation des parametres */
    if (argc != 2)                                                       
        err_quit("usage: selsut <port-serveur>");

    int serv_port;                               
        sscanf(argv[1], "%d", &serv_port);

    SelsutServer(serv_port);
}

void * SelsutServer (int serv_port)
{
	int			        udpfd, tcpfd, connfd;   // les files descriptors
    fd_set              rset;                   // set de file descriptors
    int                 maxDescr;
	struct sockaddr_in	servaddr, cliaddr;  // descripteurs d'adresses
	pid_t		        childpid;
	socklen_t	        clilen;
	void		        nozo(int);

    
    /* creation d'une socket TCP en mode �coute */
    printf ("creation de la socket TCP\n");
        // creation de la socket
	tcpfd = Socket(AF_INET, SOCK_STREAM, 0);
        // creation des adresses
    bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(serv_port);
        // nommage de la socket
	Bind(tcpfd, (SA *) &servaddr, sizeof(servaddr));
        // mise en mode �coute
	Listen(tcpfd, LISTENQ);

    /* creation d'une socket UDP en mode �coute */
    printf("creation de la socket UDP\n");
        // creation de la socket
    udpfd = Socket(AF_INET, SOCK_DGRAM, 0);
        // creation des adresses
    bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(serv_port);
	    // nommage de la socket
    Bind(udpfd, (SA *) &servaddr, sizeof(servaddr));

    /* on initialise un set de descripteurs pour select
     * Et on calcule le maximum des 2 descripteurs pour lequel on va attendre
     */
    printf ("initialisation du set de file descriptors\n");
    FD_ZERO(&rset);
    maxDescr = max(tcpfd, udpfd) + 1;

    printf ("lancement du serveur\n");
    for ( ; ; )
    {
        /* on rajoute les 2 sockets au set */
        FD_SET(tcpfd, &rset);
        FD_SET(udpfd, &rset);

        /* avec select on attend le changement d'etat des sockets */
        if(select(maxDescr, &rset, NULL, NULL, NULL) < 0)
        {
            perror("select()");
            exit(errno);
        }


        /* on accepte une nouvelle connection en TCP */
        if (FD_ISSET(tcpfd, &rset))
        {
            clilen = sizeof(cliaddr);
            connfd = Accept(tcpfd, (SA *) &cliaddr, &clilen);

            if ( (childpid = Fork()) == 0) 
            { 
                Close(tcpfd);       
                str_echo(connfd);	
                printf("sortie: %d\n", connfd);	
                exit(0);
            }
            Close(connfd);    
        }

        /* on accepte une nouvelle connection en UDP */
        if (FD_ISSET(udpfd, &rset))
        {
	        dg_echo(udpfd, (SA *) &cliaddr, sizeof(cliaddr));
        }
    }

}

void * UdpServer (void * param)
{
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

    printf ("lancement serveur UDP\n");
	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

	dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

}

void * TcpServer(void * param)
{
	int			listenfd, connfd;
	pid_t			childpid;
	socklen_t		clilen;
	struct sockaddr_in	cliaddr, servaddr;
	void			nozo(int);

    printf ("lancement serveur TCP\n");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    // rempli servaddr de  (il y a sizeof (seraddr) zeros)
	bzero(&servaddr, sizeof(servaddr));
    // d�fini le type d'adresses utilis�es
	servaddr.sin_family      = AF_INET;
    // converti les parametres pass�s dans le format du r�seau (je pense que c'est pour g�rer les big-endien little-endien)
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

    // assigne un nom � la socket
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // marque la socket comme pr�te � attendre des connexions
	Listen(listenfd, LISTENQ);


	for ( ; ; ) {
        
		clilen = sizeof(cliaddr);
		
        // accept extrait la premiere connection de la liste d'attente de la socket
        // on cr�e une nouvelle socket en mode connect� et on retourne le fichier de cette socket.
        // la socket originale n'est pas affect�e
        connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) { /* Ici le fils ! */
			Close(listenfd);       /* Fermer la socket � l'�coute */
			str_echo(connfd);	/* traiter la requ�te */
	        printf("sortie: %d\n", connfd);	
            exit(0);
		}
		Close(connfd);		/* Le p�re ferme la socket connect�e */
	}
}
