#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "structures.h"
#include "base.h"
#include "saisies.h"

using namespace std;

/* Saisie sécurisée : Nombre de tirages */
int saisieNbTirages(int nbTirageMax = 1000000)
{
    int nb_tirage;
    do
    {
        printf("\n Indiquer le nombre de tirages a effectuer [1; %i]: ", nbTirageMax);
        scanf("%i", &nb_tirage);
        viderBuffer(&nb_tirage);
    } while(nb_tirage < 1 || nb_tirage > nbTirageMax);
    return nb_tirage;
}

/* Saisie sécurisée : Nombre de joueurs */
int saisieNbJoueurs()
{
    int nbJoueurs;
    do
    {
        printf("\n Indiquer le nombre de joueurs [2; 10] : ");
        scanf("%i", &nbJoueurs);
        viderBuffer(&nbJoueurs);
    } while(nbJoueurs < 2 || nbJoueurs > 10);
    return nbJoueurs;
}

/* Saisie sécurisée : Affichage en temps réel */
int saisieRealTime(int nb_tirage, int nb = 1000)
{
    // nb : nombre à partir duquel l'affichage en temps réel est déconseillé
    int realtime;
    do
    {
        printf("\n Voulez-vous l'affichage en temps reel ? ");
        if(nb_tirage > nb)
        {
            printf("(deconseille) ");
        }
        printf("(oui = 1 / non = 0) : ");
        scanf("%i", &realtime);
        viderBuffer(&realtime);
    } while(realtime < 0 || realtime > 1);
    return realtime;
}

/* Saisie sécurisée : Recommencer */
int saisieRecommencer()
{
    int recommencer;
    do
    {
        printf("\n\n Souhaitez-vous recommencer ? (oui = 1 / non = 0) : ");
        scanf("%i", &recommencer);
        viderBuffer(&recommencer);
    } while(recommencer < 0 || recommencer > 1);
    return recommencer;
}

/* Saisie sécurisée : Sélection en mode multijoueurs */
int saisieModeMulti()
{
    int mode;

    system("cls");
    printf("\n Jeu multi-joueurs : Pourcentages de gain\n --\n");
    printf("\n\n Selectionner le mode que vous souhaitez :\n");
    printf(" 0. Retour au menu precedent\n");
    printf(" 1. Paire d'AS contre 2 a 10 joueurs\n");
    printf(" 2. Main selectionnable entre 2 : confrontation au heads-up\n\n");

    do
    {
        printf("\n\n Selection : ");
        scanf("%i", &mode);
        viderBuffer(&mode);
    } while(mode < 0 || mode > 2);
    return mode;
}

/* Saisie sécurisée : Sélection de la main heads-up */
int saisieSelectionMain(int joueur)
{
    int selection;
    /*system("cls");
    printf("\n Jeu multi-joueurs : Pourcentages de gain\n --\n");*/
    printf("\n\n Selection de la main du joueur %i\n", joueur + 1);
    printf(" 1. Une paire\n");
    printf(" 2. Cartes de meme couleur\n");
    printf(" 3. Cartes de couleur differente\n\n");
    do
    {
        printf(" Selection : ");
        scanf("%i", &selection);
        viderBuffer(&selection);
    } while(selection < 1 || selection > 3);
    return selection;
}
