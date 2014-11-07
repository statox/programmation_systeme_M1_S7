/* Envoi d'un mail � un utilisateur via un tube */
/*** Remplacer les points par les instructions ou les param�tres manquants ***/

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
     * Trouver l'utilisateur log�
     */
    if ((utilisateur = getlogin()) == NULL) {
        fprintf(stderr, "Pas d'utilisateur log� ?\n");
        exit(1);
    }

    /*
     * Cr�ation du tube et appel de fork().
     */
	...

	...
    }

    /* Ici le fils !
     * Envoi par le fils � l'utilisateur du message contenu dans le tube
     */
    if (idp == 0) {
        /*
         * Redirection de l'entr�e standard vers le tube
         */
		...
		...
		...

        /*
         * Pour voir la sortie sur l'�cran, on ferme le tube en �criture.
         */
		...
        /*
         * Envoi du mail
         */
        execl("/bin/mail", "mail", utilisateur, 0);
        perror("Exec a �chou� !");
        exit(1);
    }

    /* Ici le p�re !
     * Le p�re �crit le message dans le tube
     */
    printf("Surveillez votre BAL, si tout se passe bien, un message vous sera envoy� \n");
    close(desctube[0]);
    fp = fdopen(...,... );
    fprintf(fp, "C'est le message que vous attendez, cher utilisateur.\n");
    fclose(fp);

    /*
     * Le p�re attend la terminaison du fils
     */
	...
    exit(0);
}
