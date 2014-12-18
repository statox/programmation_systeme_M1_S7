#include	"entete2.h"
#include    <pthread.h>
#include    <stdio.h>

void * UdpServer (void * param);
void * TcpServer(void * param);

pthread_t tid[2];


/*
 *Cette version fonctionne mais elle peut être mise en défaut facilement
 *il faut utiliser select() pour le faire fonctionner correctement
 */

int main (int argc, char *argv[])
{

    int i=0;
    pthread_create(&tid[0], NULL, UdpServer, NULL);
    pthread_create(&tid[1], NULL, TcpServer, NULL);
    
    for (i=0; i<2; ++i)
        pthread_join(tid[0], NULL);
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
    // défini le type d'adresses utilisées
	servaddr.sin_family      = AF_INET;
    // converti les parametres passés dans le format du réseau (je pense que c'est pour gérer les big-endien little-endien)
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

    // assigne un nom à la socket
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // marque la socket comme prête à attendre des connexions
	Listen(listenfd, LISTENQ);


	for ( ; ; ) {
        
		clilen = sizeof(cliaddr);
		
        // accept extrait la premiere connection de la liste d'attente de la socket
        // on crée une nouvelle socket en mode connecté et on retourne le fichier de cette socket.
        // la socket originale n'est pas affectée
        connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) { /* Ici le fils ! */
			Close(listenfd);       /* Fermer la socket à l'écoute */
			str_echo(connfd);	/* traiter la requête */
	        printf("sortie: %d\n", connfd);	
            exit(0);
		}
		Close(connfd);		/* Le père ferme la socket connectée */
	}
}
