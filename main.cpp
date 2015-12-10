#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "structures.h"
#include "base.h"
#include "saisies.h"
#include "random.h"
#include "conio.h"
#include "probabilites.h"
#include "multijoueurs.h"

using namespace std;

int main()
{
    srand(time(NULL));
    t_carte jeu[52];

    int selection = 0, run = 1;

    do
    {
        system("cls");
        printf("\n PokerStats\n --\n\n");
        printf(" 0 - Quitter\n");
        printf(" 1 - Verification de la robustesse du generateur de hasard\n");
        printf(" 2 - Probabilites brutes d'obtenir une combinaison\n");
        printf(" 3 - Jeu multi-joueurs : Pourcentages de gain\n\n");

        do
        {
            printf("\n Selection d'une option : ");
            scanf("%d", &selection);

            if (selection < 0 || selection > 3)
            {
                printf(" /!\\ Erreur : Ceci n'est pas une option selectionnable. /!\\ \n");
            }
            else if (selection != 0)
            {
                printf(" Execution de la fonction desiree.\n\n");
            }
            else
            {
                run = 0;
                exit(1);
            }
        } while (selection < 0 || selection > 3);

        system("cls");
        switch (selection)
        {
            case 1:
                generate10miliion(jeu);
                break;
            case 2:
                selectionMainDepart(jeu);
                break;
            case 3:
                multijoueur(jeu);
                break;
        }
    } while(run != 0);
    return 0;
}
