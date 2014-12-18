/*
 * Adrien Fabre - M1 - IL
 *
 * TP1 - ex3
 *
 */


/*
 *  IMPORTANT: This file must be compiled with
 *    gcc -o additionneur -lpthread additionneur.c
 *  
 *  to link the pthread librabry
 *
 */


/*
 *  Le but du programme est le suivant:
 *  2 threads incrémentent une variable a tour de rôle tant que cette variable n'a pas attein un certain seuil.
 *  Quand le sueil est attein le thread additionneur signal a un troisieme thread que les operation sont terminées.
 *
 *  On doit donc utiliser les fonctions
 *  pthread_condition pour vérifier le seuil de la variable
 *  pthread_signal pour signal au troisieme thread que les operations sont terminées
 *  pthread_join pour attendre tous les threads. Sans cette fonction lorsque que le premier thread se termine, le programme se termine
 *
 *  voir https://computing.llnl.gov/tutorials/pthreads/#ConditionVariables
 *  Il y a un exemple qui est le même programme
 *
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void * additionneur(void *);
void * watcher(void *);

#define NB_THREADS  3    /* nombre de threads créés par le programme */
#define COUNT_LIMIT 20  /* le seuil auquel les threads arretent d'additionner */
#define COUNT_CHECK 10  /* le seuil qui thread watcher déclenchera un message quand il sera atteint */ 

pthread_t   tid[NB_THREADS] = {0,1,2}; /* Ces ids seront utilisés dans les affichages pour suivre quel thread écrit quoi */
int         nombre = 0; /* la variable que les threads vont incrémenter */

/* l'expace d'exclusion mutuelle que les threads respecterons */
pthread_mutex_t   mutex_count;
/* la condition pour arreter la mutex précédente */
pthread_cond_t    condition_seuil;


main( int argc, char *argv[] )
{
  int i;
 
  /* création du tableau de threads */
  pthread_t threads[3];

  /* creation d'un attribut qui rend les threads utilisables par la fonction pthread_join */
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  printf ("init mutex and condition ");
  /* initialisation de la mutex qui protègera la variable nombre */
  pthread_mutex_init(&mutex_count, NULL);
  /* condition qui sera utilisée pour signal au watcher que la limite est atteinte */
  pthread_cond_init (&condition_seuil, NULL);
  printf ("OK\n");

  printf ("threads creation\n");
  /* creation des 3 threads */ /* on leur passe l'attribut qui les rends joignables */  
    /* le thread qui surveille les autres */
  printf ("\tthread watcher");
  
  if (pthread_create(&threads[2], &attr, watcher, (void *)0) != 0){
    printf ("\t ERROR IN CREATION");
  }
    /* les threads additionneurs */
  printf ("\n\tthread adder 1");
  pthread_create(&threads[1], &attr, additionneur, (void *)1);
  printf ("\n\tthread adder 2");
  pthread_create(&threads[0], &attr, additionneur, (void *)2);
    

  /* on attends que tous les threads aient fini leur execution */
  for ( i = 0; i < NB_THREADS; i++)
    pthread_join(threads[i], NULL);

  printf("main signale que les %d threads ont terminé\n", i);
  printf("Je suis main ! nombre=%d\n", nombre);

  /* on détruit ce qui a besoin de l'etre et on sort du thread */
    pthread_mutex_destroy(&mutex_count);
    pthread_cond_destroy(&condition_seuil);
    pthread_exit(NULL);
}

void * additionneur(void * parmVoid)
{
  int i;
  int parm = (int) parmVoid;
  printf("\nJe suis une nouvelle thread ! numero: %d\n", parm);
  
  /* incrémentation de la variable */
  for (i=0; i<COUNT_LIMIT; i++){
    /* zone d'exclusion où on traite la variable */
    pthread_mutex_lock(&mutex_count);

    /* incrémentation de la variable */
    nombre++;
    
    printf ("\nthread: %d\tnombre= %d", parm, nombre);

    /* on vérifie si la limite est atteinte et on en notifie le thread watcher */
    if (nombre == COUNT_CHECK){
      printf ("\n\tlimite atteinte");
      pthread_cond_signal(&condition_seuil);
    }

    /* fin de la zone d'exclusion */
    pthread_mutex_unlock(&mutex_count);

    /* on crée une pause pour laisser le temps aux threads d'alternet */
    sleep(1);
  }

    
  /* fin du thread */
  pthread_exit(0);
}

void * watcher(void * parm){
  printf("\nDébut de la veille");

  /* on bloque la mutex et on attends le signal des threads additionneurs */
  pthread_mutex_lock(&mutex_count);
  
  /* si le nombre a dépassé la limite, on n'attends pas le signal des threads additionneurs */
  while (nombre<COUNT_LIMIT) {
    /* attente du signal */
    /* cette fonction va automatiquement débloquer la mutex pendant l'attente */
    pthread_cond_wait(&condition_seuil, &mutex_count);
    printf ("\nwatcher\tnombre: %d", nombre);
  }
  pthread_mutex_unlock(&mutex_count);

  pthread_exit(0);
}
