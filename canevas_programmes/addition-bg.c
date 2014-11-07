
#include  <pthread.h>
#include   <stdio.h>

void * additionneur(void *);

#define  nbt  2
pthread_t  tid[nbt];      

int  nombre = 0;

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
   for(i=0;i<200000;i++) {
       nombre++;   
   }
   pthread_exit(0);
}    

