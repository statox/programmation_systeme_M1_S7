/* Envoi d'un mail à un utilisateur via un tube */
/*** Remplacer les points par les instructions ou les paramètres manquants ***/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    FILE *fp;
    int idp, desctube[2];
    char *utilisateur, *getlogin();

    /*
     * Trouver l'utilisateur logé
     */
    if ((utilisateur = getlogin()) == NULL) {
        fprintf(stderr, "Pas d'utilisateur logé ?\n");
        exit(1);
    }

    /*
     * Création du tube et appel de fork().
     */
	...

	...
    }

    /* Ici le fils !
     * Envoi par le fils à l'utilisateur du message contenu dans le tube
     */
    if (idp == 0) {
        /*
         * Redirection de l'entrée standard vers le tube
         */
		...
		...
		...

        /*
         * Pour voir la sortie sur l'écran, on ferme le tube en écriture.
         */
		...
        /*
         * Envoi du mail
         */
        execl("/bin/mail", "mail", utilisateur, 0);
        perror("Exec a échoué !");
        exit(1);
    }

    /* Ici le père !
     * Le père écrit le message dans le tube
     */
    printf("Surveillez votre BAL, si tout se passe bien, un message vous sera envoyé \n");
    close(desctube[0]);
    fp = fdopen(...,... );
    fprintf(fp, "C'est le message que vous attendez, cher utilisateur.\n");
    fclose(fp);

    /*
     * Le père attend la terminaison du fils
     */
	...
    exit(0);
}
