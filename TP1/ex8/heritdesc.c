/* heritdesc.c */

/* 
 * Remplacer les points par les instructions
 * ou les paramètres manquants
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void fils(int numero)
{
    int desc ;
    int nlect ;
    char message[100] ;
    desc = numero ;
    printf("Le descripteur est:%d\n",desc) ;
    /*
     * lecture dans le tube
     */
    switch (nlect=read(numero,message,sizeof(message))) {
        case -1:
            printf ("FAILED PIPE READING\n");
            break;
        case 0:
            printf ("END OF FILE\n");
            break;
        default:
            printf("Lecture %d octets:\t%s\n",nlect,message);
    }

}

main()
{
    int     desc[2] ;
    char    chaine[] = "Hey! Hello you :)" ;
    /*
     * Création du tube
     */
    pipe(desc);

    /*
     * Création du fils
     */
    switch (fork()){
        case -1:
            printf ("FAILED FORK\n");
            break;
        // child process
        case 0:
            fils(desc[0]) ;
            exit(0) ;

    }
   
    /*
     * Ecrire dans le tube
     */
    printf ("Ecriture dans le tube\n");
    write(desc[1], chaine, (sizeof(chaine)+1));

}

