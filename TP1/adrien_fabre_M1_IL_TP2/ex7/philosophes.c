#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>

#define N 5 			/* Nombre de philosophes */

#define PENSE 0			/* Le philosophe pense */
#define AVOIR_FAIM 1	/* Le philosophe essaie de prendre les fourchettes */
#define MANGE 2			/* Le philosophe mange */

#define GAUCHE (numero_phil+N-1)%N	/* numéro du voisin de gauche */
#define DROITE (numero_phil+1)%N	/* numéro du voisin de droite */

#define lock    pthread_mutex_lock       /* raccourcis pour les mutex */
#define unlock  pthread_mutex_unlock
  
sem_t           mutex; 	/* Exclusion mutuelle pour les sections critiques */
sem_t	        S[N]; 	/* Un sémaphore par philosophe */

pthread_mutex_t m_etat;   /* Exclusion mutuelle pour le changement d'etat des philosophes */

void * philosophe(void *num);
void prendre_fourchettes(int);
void poser_fourchettes(int);
void test(int);

int etat[N];
int numero_phil[N]={0,1,2,3,4};

int main()
{
	int 		i;
	pthread_t 	thread_id[N];
	
	srand(time(NULL));

    /* initialisation d */
    // Le deuxieme paramètre indique s'ils sont partagés (0 partagés par les threads, 1 partagés par les process)
    // Le troisième paramètre indique la valeur du sémaphore
	sem_init(&mutex,0,1);
	
	for(i=0;i<N;i++)
		sem_init(&S[i],0,1);


    /*
     *pthread_create(&thread_id[0],NULL,philosophe,&numero_phil[0]);
     *pthread_join(thread_id[0],NULL); 
     */

    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philosophe,&numero_phil[i]);
        printf("Philosophe %d commence a penser\n",i+1);
    }
    
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}

void *philosophe(void *num)
{
	while(1)
	{
		int *i = num;

        etat[*i] = PENSE;
		// on fait en sorte que le philosophe ait faim de temps en temps
		int r = rand () % 3;
		
        
        lock(&m_etat);
        if (etat[*i] == PENSE && r == 0){
			etat[*i] = AVOIR_FAIM;
		}
        unlock(&m_etat);

        // affichage de l'état du philosophe
        switch (etat[*i])
        {
            case PENSE:
                printf ("Philosophe %d pense\n", (*i)+1);
                break;
            case AVOIR_FAIM:
                printf ("Philosophe %d a faim\n", (*i)+1);
                break;
            case MANGE:
                printf ("Philosophe %d mange\n", (*i)+1);
                break;        
        }


        sleep(1);
        prendre_fourchettes(*i);
        sleep(1);
        poser_fourchettes(*i);
	}
}

void test(int numero_phil)
{

	if (etat[numero_phil] == AVOIR_FAIM && etat[GAUCHE] != MANGE && etat[DROITE] != MANGE)
	{
        if (sem_wait(&S[numero_phil]) != 0 ){
            printf("Refus de l'accès aux fourchettes\n");
        }
		etat[numero_phil] = MANGE;
		sleep(2);
		printf("\nPhilosophe %d prend fourchette %d et %d\n",numero_phil+1,GAUCHE+1,numero_phil+1);
        printf("Philosophe %d etat: %d\n", numero_phil+1, etat[numero_phil]);
		printf("Philosophe %d est en train de manger\n",numero_phil+1);
		sem_post(&S[numero_phil]);
	}
    
    if (etat[numero_phil] == MANGE)
	{
        sem_wait(&S[numero_phil]);
		etat[numero_phil] = PENSE;
		sleep(2);
		printf("\nPhilosophe %d pose fourchette %d et %d\n",numero_phil+1,GAUCHE+1,numero_phil+1);
        printf("Philosophe %d etat: %d\n", numero_phil+1, etat[numero_phil]);
        printf("Philosophe %d est en train de penser\n",numero_phil+1);
		sem_post(&S[numero_phil]);
	}
}

void prendre_fourchettes(int i){
	test(i);
}

void poser_fourchettes(int i){
	test(i);
}

