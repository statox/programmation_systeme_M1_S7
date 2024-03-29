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
#include "headers/memory.h"
#include "headers/worst-fit.h"
#include "headers/first-fit.h"
#include "headers/best-fit.h"

int menu ();

int main (int argc, char **argv)
{
    Memory memory = NULL;
    int input=0;
    int input1=0;
    int loop = 1;
    int cursorArgs = 1;

    bool assertion = false;
    int assertionIndex = 0;
    bool assertionError = false;

    memory = (Memory) createMemory(9, 3);

    if (argc > 1) {
        while (argc >= cursorArgs + 2 && !assertion) {
            if (strcasecmp("assert", argv[cursorArgs]) == 0) {
                assertion = true;
                cursorArgs++;
            }
            else if (atoi(argv[cursorArgs]) == 1)
            {
                FFallocate(memory, atoi(argv[cursorArgs + 1]));
                cursorArgs += 2;
            }
            else if (atoi(argv[cursorArgs]) == 2)
            {
                BFallocate(memory, atoi(argv[cursorArgs + 1]));
                cursorArgs += 2;
            }
            else if (atoi(argv[cursorArgs]) == 3)
            {
                WFallocate(memory, atoi(argv[cursorArgs + 1]));
                cursorArgs += 2;
            }
            // else if (argv[cursorArgs] == 3)
            // {
            //     printMem(memory);
            //     cursorArgs++;
            // }
            else
            {
                printf("Invalid input\n");
            }
        }
        Block* tmp = memory;
        if (assertion) {
            while (argc > cursorArgs && !assertionError) {
                if (tmp == NULL) {
                    assertionError = true;
                } else {
                    if (atoi(argv[cursorArgs]) != tmp->usedLength) {
                        assertionError = true;
                    } else {
                        assertionIndex++;
                        cursorArgs++;
                        tmp = tmp->next;
                    }
                }
            }
        }
        printMem2(memory);
        if (assertionError) {
            if (tmp == NULL) {
                printf("not enough blocks\n");
            } else {
                printf("Assertion error : %d != %d : at %d.\n", atoi(argv[cursorArgs]), tmp->usedLength, assertionIndex);
                perror("\nAssertion error\n");
            }
            printMem(memory);
        }
        // else {
        //     printf("no error\n");
        //     perror("\nno error\n");
        // }
        printf("\n\n");
    }

    while (loop==1 && ((assertion && assertionError) || !assertion))
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
                    WFallocate(memory, input1);
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

            case 4:
                printf ("Liberation de %d blocs\n", freeMemory(memory) );
                break;

            case 5:
                printf ("Quelle est la taille du bloc dont vous avez besoin?\n");
                scanf("%d", &input);
                memory = defrag(memory, input);
                break;
            case 6:
                printf ("De quel bloc voulez vous liberer de la memoire?\n");
                scanf ("%d", &input);
                printf ("Quelle quantite de memoire voulez vous liberer?\n");
                scanf ("%d", &input1);
                freeBlockLength(memory, input, input1);
                break;

            default:
                loop = 0;

        }
    }

    freeAndDeleteMemoryForGood(memory);
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
        printf ("\t2. Liberer un bloc entier de la memoire\n");
        printf ("\t3. Visualiser la memoire\n");
        printf ("\t4. Liberer toute la memoire\n");
        printf ("\t5. Defragmenter les espaces perdus\n");
        printf ("\t6. Liberer une partie d'un bloc de la memoire\n");
        printf ("\t0. Quitter le programme\n\n");

        printf ("Saisissez votre choix: ");
        scanf("%d", &choix);
    }while (choix<0 || choix>6);

    return choix;
}
