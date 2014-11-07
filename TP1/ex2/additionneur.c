/*
 * Adrien Fabre - M1 - IL
 *
 * TP1 - ex2
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
 *  Réponse à l'exercice:
 *  Le bug de ce programme était le fait que la variable nombre partagée par les thread n'était pas protégée.
 *
 *  De ce fait les threads accédaient en même temps à cette variablece qui causait une incohérence des données (toutes les additions n'étaient pas effectuée)
 *
 *  Pour résoudre ce bug il a fallu protéger la variable en rajoutant une exclusion mutuelle dans l'execution des threads.
 *
 *
 */

#include <pthread.h>
#include <stdio.h>

void * additionneur(void *);

#define nbt 2
pthread_t tid[nbt];
int nombre = 0;

/* l'expace d'exclusion mutuelle que les threads respecterons */
pthread_mutex_t lock;

main( int argc, char *argv[] )
{
  int i;
  
  for (i=0; i<nbt; i++) {
    pthread_create(&tid[i], NULL, additionneur, NULL);
  }
  
  for ( i = 0; i < nbt; i++)
    pthread_join(tid[i], NULL);

  printf("main signale que les %d threads ont terminé\n", i);
  printf("Je suis main ! nombre=%d\n", nombre);
}

void * additionneur(void * parm)
{
  int i;
  printf("Je suis une nouvelle thread !\n");
  
  /* Cette zone est l'exclusion mutuelle */
  pthread_mutex_lock(&lock);

  for(i=0;i<200000;i++) {
    nombre++;
  }
  
  pthread_mutex_unlock(&lock);

  pthread_exit(0);
}

