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

using namespace std;

/* Détection d'une paire */
/*
t_combinaison detectPaire(t_carte main[])
{
    int cpt, cpt2;
    t_combinaison combinaison;

    combinaison.combi = RIEN;
    combinaison.numero = 0;

    for(cpt = 0; cpt < 7; cpt++)
    {
        for(cpt2 = 0; cpt2 < 7; cpt2++)
        {
            if(cpt != cpt2)
            {
                if(main[cpt].numero == main[cpt2].numero && combinaison.numero <= main[cpt].numero)
                {
                    combinaison.combi = PAIRE;
                    combinaison.numero = main[cpt].numero;
                }
            }
        }
    }
    return combinaison;
}
*/

/* Copier vers un tableau temporaire (détection suite, couleur, quinte flush) */
void copierTab(int tab1[], t_carte tab2[], t_couleur couleur)
{
    int cpt;

    for(cpt = 0; cpt < 7; cpt++)
    {
        tab2[cpt].couleur = couleur;
        tab2[cpt].numero = tab1[cpt];
    }
}

/* Détection d'une suite */
t_combinaison detectSuite(t_carte main[])
{
    int cpt, i, max = 1, suite[7] = {0}, nb_suite = 1;
    t_combinaison combinaison;
    combinaison.combi = RIEN;
    combinaison.numero = 0;

    suite[0] = main[0].numero;
    // printf("suite[%i] = %i\n", 0, suite[0]);
    for(cpt = 1; cpt < 7; cpt++)
    {
        if(suite[max - 1] != main[cpt].numero)
        {
            suite[max] = main[cpt].numero;
            // printf("suite[%i] = %i\n", max, suite[max]);
            max++;
        }
    }
    // printf("max = %i\n", max);
    for(i = 0; i < max - 3; i++)
    {
        // printf("i = %i\n", i);
        nb_suite = 1;
        for(cpt = i; cpt < i + 4; cpt++)
        {
            if(suite[cpt] + 1 == suite[cpt + 1])
            {
                nb_suite = nb_suite + 1;
                // printf("nb_suite = %i\n", nb_suite);

                if(nb_suite == 5)
                {
                    combinaison.numero = suite[cpt + 1];
                    combinaison.combi = SUITE;
                }
            }
        }
        // printf("imax = %i\n", max - 4);
        if(i == (max - 4) && suite[0] == 1 && nb_suite == 4)
        {
            combinaison.numero = 1;
            combinaison.combi = SUITE;
        }
    }

    if(combinaison.combi != SUITE)
    {
        combinaison.combi = RIEN;
        combinaison.numero = suite[max - 1];

        if(suite[0] == 1)
        {
            combinaison.numero = 1;
        }
    }

    return combinaison;
}

/* Détection d'une couleur ou quinte flush */
t_combinaison detectQuinteFlush(t_carte main[])
{
    int cpt, max = 0, carreau = 0, coeur = 0, pique = 0, trefle = 0, numero = 0;
    int tabCarreau[7] = {0}, tabCoeur[7] = {0}, tabPique[7] = {0}, tabTrefle[7] = {0};
    t_carte tab[7];
    t_combinaison suite;
    t_combinaison combinaison;
    combinaison.combi = RIEN;
    combinaison.numero = 0;

    for(cpt = 0; cpt < 7; cpt++)
    {
        if(main[cpt].couleur == CARREAU)
        {
            tabCarreau[carreau] = main[cpt].numero;
            carreau++;
        }
        if(main[cpt].couleur == COEUR)
        {
            tabCoeur[coeur] = main[cpt].numero;
            coeur++;
        }
        if(main[cpt].couleur == PIQUE)
        {
            tabPique[pique] = main[cpt].numero;
            pique++;
        }
        if(main[cpt].couleur == TREFLE)
        {
            tabTrefle[trefle] = main[cpt].numero;
            trefle++;
        }
    }

    if(carreau >= 5) {max = carreau; copierTab(tabCarreau, tab, CARREAU); numero = tab[max - 1].numero;}
    else if(coeur >= 5) {max = coeur; copierTab(tabCoeur, tab, COEUR); numero = tab[max - 1].numero;}
    else if(pique >= 5) {max = pique; copierTab(tabPique, tab, PIQUE); numero = tab[max - 1].numero;}
    else if(trefle >= 5) {max = trefle; copierTab(tabTrefle, tab, TREFLE); numero = tab[max - 1].numero;}

    combinaison.numero = numero;

    if(max >= 5)
    {
        combinaison.combi = COULEUR;

        /* Détection d'une suite */
        suite = detectSuite(tab);

        /* S'il y a une suite + une couleur avec les mêmes cartes => quinte flush */
        if(suite.combi == SUITE)
        {
            combinaison.combi = QUINTE_FLUSH;
            combinaison.numero = suite.numero;
        }
    }

    /* Détection de l'AS pour une couleur */
    if((combinaison.combi != QUINTE_FLUSH) && (combinaison.combi == COULEUR))
    {
        if(tab[0].numero == 1) combinaison.numero = 1;
    }

    /* Détection de l'AS pour RIEN */
    if((combinaison.combi != QUINTE_FLUSH) && (combinaison.combi != COULEUR))
    {
        if(main[0].numero != 1)
        {
            combinaison.numero = main[6].numero;
        }
        else
        {
            combinaison.numero = 1;
        }
    }

    /*printf("max = %i\n", max);
    printf("%i - ", combinaison.numero);
    ecrireCombinaison(combinaison.combi);
    printf("\n");
    system("pause");*/
    return combinaison;
}

/* Détection de la combinaison d'une main */
t_combinaison detectCombinaison(t_carte main[])
{
    int cpt;
    int nb = 0, paire = 0;
    int nb_brelan = 0, brelan = 0;
    int nb_carre = 0, carre = 0;
    int full = 0;
    int suite = 0;
    int couleur = 0;
    int as = 0;

    t_combinaison combinaison;
    combinaison.combi = RIEN;
    combinaison.numero = 0;

    combinaison = detectQuinteFlush(main);
    if(combinaison.combi == COULEUR) couleur = 1;

    if(combinaison.combi != QUINTE_FLUSH)
    {

        if(couleur == 0)
        {
            combinaison = detectSuite(main);
            if(combinaison.combi == SUITE)
            {
                suite = 1;
            }
        }

        for(cpt = 0; cpt < 6; cpt++)
        {
            if(main[cpt].numero == 1)
            {
                as = as + 1;
            }

            if(main[cpt].numero == main[cpt + 1].numero)
            {
                nb = nb + 1;
                nb_brelan = nb_brelan + 1;
                nb_carre = nb_carre + 1;
            }
            else
            {
                nb = 0;
                nb_brelan = 0;
                nb_carre = 0;
            }

            if(nb == 1)
            {
                if(brelan > 0 && combinaison.numero != main[cpt].numero)
                {
                    full = full + 1;
                    #if DEBUG
                    printf("Valide 1\n");
                    #endif
                }
                else if(brelan == 0 && nb_brelan != 2 && suite == 0 && couleur == 0)
                {
                    if(as >= 2)
                    {
                        combinaison.numero = 1;
                    }
                    else
                    {
                        combinaison.numero = main[cpt].numero;
                    }
                }
                paire = paire + 1;
                nb = 0;
            }

            if(nb_brelan == 2 && carre == 0)
            {
                if(paire > 2 && main[cpt].numero == combinaison.numero)
                {
                    full = full + 1;
                    #if DEBUG
                    printf("Valide 2\n");
                    #endif
                }
                if(suite == 0 && couleur == 0)
                {
                    if(as >= 3)
                    {
                        combinaison.numero = 1;
                    }
                    else
                    {
                        combinaison.numero = main[cpt].numero;
                    }
                }
                nb_brelan = 0;
                brelan = brelan + 1;
            }

            if(nb_carre == 3)
            {
                if(as >= 4)
                {
                    combinaison.numero = 1;
                }
                else
                {
                    combinaison.numero = main[cpt].numero;
                }
                nb_carre = 0;
                carre = carre + 1;
            }
        }

        if(carre >= 1) combinaison.combi = CARRE;
        else if(full >= 1 && carre == 0) combinaison.combi = FULL;
        else if(couleur == 1 && full == 0) combinaison.combi = COULEUR;
        else if(suite == 1 && couleur == 0) combinaison.combi = SUITE;
        else if(brelan >= 1 && suite == 0) combinaison.combi = BRELAN;
        else if(paire >= 2 && brelan == 0) combinaison.combi = DEUX_PAIRES;
        else if(paire >= 1 && paire < 2 && brelan == 0) combinaison.combi = PAIRE;
        else
        {
            combinaison.combi = RIEN;
            if(main[0].numero != 1)
            {
                combinaison.numero = main[6].numero;
            }
            else
            {
                combinaison.numero = main[0].numero;
            }

        }
    }

    return combinaison;
}

/* Probabilités statistiques */
void statistique1J(t_carte main[], double resultat[])
{
    t_combinaison combinaison;

    combinaison = detectCombinaison(main);

    if(combinaison.combi == RIEN) resultat[0] = resultat[0] + 1;
    else if(combinaison.combi == PAIRE) resultat[1] = resultat[1] + 1;
    else if(combinaison.combi == DEUX_PAIRES) resultat[2] = resultat[2] + 1;
    else if(combinaison.combi == BRELAN) resultat[3] = resultat[3] + 1;
    else if(combinaison.combi == SUITE) resultat[4] = resultat[4] + 1;
    else if(combinaison.combi == COULEUR) resultat[5] = resultat[5] + 1;
    else if(combinaison.combi == FULL) resultat[6] = resultat[6] + 1;
    else if(combinaison.combi == CARRE) resultat[7] = resultat[7] + 1;
    else resultat[8] = resultat[8] + 1;
}

/* Affichage du tableau des résultats de statistiques */
void afficheTirageStats(double resultat[], int nb_tirage)
{
    cout << "\r\n Combinaison\tPourcentage" << endl << " -------------------------------" << endl;
    cout << " RIEN" << "\t\t" << 100.0 * resultat[0] / nb_tirage <<" %\t\t" << endl;
    cout << " PAIRES" << "\t\t" << 100.0 * resultat[1] / nb_tirage <<" %\t\t" << endl;
    cout << " DEUX PAIRES" << "\t" << 100.0 * resultat[2] / nb_tirage << " %\t\t" << endl;
    cout << " BRELAN" << "\t\t" << 100.0 * resultat[3] / nb_tirage <<" %\t\t" << endl;
    cout << " QUINTE" << "\t\t" << 100.0 * resultat[4] / nb_tirage <<" %\t\t"<< endl;
    cout << " COULEUR" << "\t" <<100.0 * resultat[5] / nb_tirage <<" %\t\t" << endl;
    cout << " FULL" << "\t\t" << 100.0 * resultat[6] / nb_tirage << " %\t\t" <<endl;
    cout << " CARRE" << "\t\t" << 100.0 * resultat[7] / nb_tirage <<" %\t\t" << endl;
    cout << " QUINTE FLUSH" << "\t" << 100.0 * resultat[8] / nb_tirage <<" %\t\t"<< endl;
}

/* Effectue un tirage */
void tirageStatistique(t_carte jeu[], t_carte main[], t_carte carte1, t_carte carte2, double resultat[])
{
    t_carte mainPriv[2];
    int nbCarteRestante = 52;

    initJeu(jeu);
    placerMain(jeu, carte1, carte2);
    copierVersMain(jeu, mainPriv, 2);
    nbCarteRestante = decalerJeu(jeu, nbCarteRestante, 2);
    melangeJeu(jeu, nbCarteRestante);

    copieMainPriv(jeu, mainPriv, main);
    nbCarteRestante = decalerJeu(jeu, nbCarteRestante, 5);

    trierMain(main);

    statistique1J(main, resultat);
}

/* Sélectionne une paire */
void selectionPaire(t_carte *carte1, t_carte *carte2, int numero = 0)
{
    int i, j, k;
    if(numero == 0)
    {
        i = rand() % 13 + 1;
    }
    else
    {
        i = numero;
    }
    carte1->numero = i;
    carte2->numero = i;

    j = rand() % 4;
    carte1->couleur = selectionCouleur(*carte1, j);

    k = rand() % 3;
    if(j == 0 || (j == 1 && k >= 1) || (j == 2 && k >= 2))
    {
        k = k + 1;
    }
    carte2->couleur = selectionCouleur(*carte2, k);
}

/* Sélection d'une main de départ */
void selectionMainDepart(t_carte jeu[])
{
    t_carte carte1, carte2, main[7];
    int i = -1, j = -1, x, y, nb = 0, cpt;
    int recommencer = 1, nb_tirage, selection, realtime;
    double resultat[9] = {0.0}, progression = 0.0;

    do
    {
        for(cpt = 0; cpt < 9; cpt++)
        {
            resultat[cpt] = 0.0;
        }
        nb = 0;
        progression = 0.0;

        system("cls");
        printf("\n Selection d'une main de depart\n --\n");
        printf(" 0. Retour au menu precedent\n");
        printf(" 1. Une paire\n");
        printf(" 2. Deux cartes qui se suivent mais de couleur differente\n");
        printf(" 3. As et 8 de la meme couleur\n");
        printf(" 4. 'Suited connectors' : 2 cartes qui se suivent dans la meme couleur\n");
        printf(" 5. 7 de trefle et 2 de carreau\n\n");

        do
        {
            printf("\n Selectionner la main de depart : ");
            scanf("%i", &selection);
            viderBuffer(&selection);
        } while(selection < 0 || selection > 5);

        if(selection == 0)
        {
            recommencer = 0;
        }
        else
        {
            nb_tirage = saisieNbTirages(1000000);

            realtime = saisieRealTime(nb_tirage, 1000);

            printf("\n\n");
            x = wherex();
            y = wherey();

            printf(" Tirage en cours..0 %%\t\t\n");
            do
            {
                switch(selection)
                {
                    case 1:
                        selectionPaire(&carte1, &carte2, 0);
                        break;
                    case 2:
                        i = rand() % 13 + 1;
                        carte1.numero = i;
                        if(i == 13)
                        {
                            carte2.numero = 1;
                        }
                        else
                        {
                            carte2.numero = i + 1;
                        }

                        i = rand() % 4;
                        carte1.couleur = selectionCouleur(carte1, i);

                        j = rand() % 3;
                        if(i == 0 || (i == 1 && j >= 1) || (i == 2 && j >= 2))
                        {
                            j = j + 1;
                        }
                        carte2.couleur = selectionCouleur(carte2, j);
                        break;
                    case 3:
                        carte1.numero = 8;
                        carte2.numero = 1;

                        i = rand() % 4;
                        carte1.couleur = selectionCouleur(carte1, i);
                        carte2.couleur = selectionCouleur(carte2, i);
                        break;
                    case 4:
                        i = rand() % 13 + 1;
                        carte1.numero = i;
                        if(i == 13)
                        {
                            carte2.numero = 1;
                        }
                        else
                        {
                            carte2.numero = i + 1;
                        }

                        i = rand() % 4;
                        carte1.couleur = selectionCouleur(carte1, i);
                        carte2.couleur = selectionCouleur(carte2, i);
                        break;
                    case 5:
                        carte1.numero = 7;
                        carte2.numero = 2;

                        carte1.couleur = CARREAU;
                        carte2.couleur = CARREAU;
                        break;
                }

                tirageStatistique(jeu, main, carte1, carte2, resultat);
                nb++;

                progression = 100.0 * nb / nb_tirage;
                if(progression == (int)progression)
                {
                    gotoxy(x, y);
                    printf(" Tirage en cours..%g %%\t\t\n", progression);
                }

                if(realtime == 1)
                {
                    gotoxy(x, y + 2);
                    afficheTirageStats(resultat, nb);
                }
            } while(nb < nb_tirage);

            if(realtime == 0)
            {
                afficheTirageStats(resultat, nb_tirage);
            }

            recommencer = saisieRecommencer();
        }
    } while(recommencer != 0);
}
