/*
 *  Memory representation by    Matthieu de la Roche Saint Andre
 *                              Adrien Fabre
 *
 *  This programs simulate the allocation memory of an OS following different algorithms
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "headers/structures.h"

int menu ();

int main (int argc, char **argv)
{
    Memory memory = NULL;
    int input=0;
    int input1=0;
    int loop = 1;
    
    memory = createMemory(9, 3);

    /*
     *allocateBlock(memory, 0);
     *allocateBlock(memory, 6);
     *allocateBlock(memory, 9);
     *allocateBlock(memory, 12);
     */


    while (loop==1)
    {
        switch (menu())
        {
            case 1:
                input = -1;
                do
                {
                    printf("Quel algorithme souhaitez vous utiliser?\n");
                    printf("\t1. First Fit\n");
                    printf("\t2. Best  Fit\n");
                    printf("\t3. Worst Fit\n");
                    printf("\nSaisissez votre choix: ");
                    scanf("%d", &input);
                }while (input<1 || input>3);
               
                printf ("Combien de memoire souhaitez vous allouer?\n");
                scanf ("%d", &input1);
                if (input == 1)
                {
                    FFallocate(memory, input1);
                }
                else if (input == 2)
                {
                    BFallocate(memory, input1);
                }
                else
                {
                    printf("To implements: Worst fit\n");
                }
                break;

            case 2:
                printf ("Quel bloc souhaitez vous liberer?\n");
                scanf ("%d", &input);
                freeBlock(memory, input);
                break;

            case 3:
                printMem(memory);
                break;

            default:
                loop = 0;

        }
    }

    return 0;
}


int menu ()
{
    int choix = 0;
    int i = 0;
    
    for (i=0; i<4; ++i)
        printf("\n");
    
    do 
    {
        printf ("Que souhaitez vous faire?\n");
        printf ("\t1. Allouer de la memoire\n");
        printf ("\t2. Liberer de la memoire\n");
        printf ("\t3. Visualiser la memoire\n");
        printf ("\t0. Quitter le programme\n\n");

        printf ("Saisissez votre choix: ");
        scanf("%d", &choix);
    }while (choix<0 || choix>3);   
}
