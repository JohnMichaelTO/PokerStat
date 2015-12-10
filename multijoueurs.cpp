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
#define TOUCHE_DIRECTIONNELLE 224
#define TOUCHE_HAUT 72
#define TOUCHE_BAS 80
#define TOUCHE_ENTREE 13

/* Compare deux combinaisons */
int compareCombinaison(t_combinaison combinaison, t_combinaison combinaison2)
{
    int gagnant = 0;

    if(combinaison.numero == 1) combinaison.numero = 14;
    if(combinaison2.numero == 1) combinaison2.numero = 14;

    if(combinaison.combi > combinaison2.combi)
    {
        gagnant = 1;
    }
    else if(combinaison.combi < combinaison2.combi)
    {
        gagnant = 2;
    }
    else
    {
        if(combinaison.numero > combinaison2.numero)
        {
            gagnant = 1;
        }
        else if(combinaison.numero < combinaison2.numero)
        {
            gagnant = 2;
        }
        else
        {
            gagnant = 0;
        }
    }
    return gagnant;
}

/* Sélection d'une main en mode multijoueurs */
void selectionMainMulti(t_carte jeu[], int nbCarteRestante, int nbJoueurs, t_selectMain *selection)
{
    int cpt, cpt2, x, y, Y, saisie, touchesDirect, fleche, position;
    int nbSelection, nbCarteAchoisir;
    t_position carte[13];

    for(cpt = 0; cpt < 12; cpt++)
    {
        carte[cpt].nb = 0;
        carte[cpt].num = cpt + 2;
    }
    carte[12].nb = 0;
    carte[12].num = 1;

    for(cpt = 0; cpt < nbJoueurs; cpt++)
    {
        saisie = saisieSelectionMain(cpt);
        nbSelection = 0;

        if(saisie == 1)
        {
            nbCarteAchoisir = 1;
            selection[cpt].c1 = -1;
            selection[cpt].c2 = -1;
        }
        else
        {
            nbCarteAchoisir = 2;
            if(saisie == 2)
            {
                selection[cpt].c1 = -2;
                selection[cpt].c2 = -2;
            }
            else
            {
                selection[cpt].c1 = -1;
                selection[cpt].c2 = -1;
            }
        }
        printf("\n\n");

        x = wherex();
        Y = wherey();
        y = Y;
        for(cpt2 = 0; cpt2 < 13; cpt2++)
        {
            if(cpt2 == 0)
            {
                printf(" > ");
            }
            else
            {
                printf("   ");
            }
            ecrireNumero(carte[cpt2].num);
            printf("\n");
        }
        position = 0;
        do
        {
            while(nbSelection < nbCarteAchoisir && ((touchesDirect = getch()) == TOUCHE_DIRECTIONNELLE || touchesDirect == TOUCHE_ENTREE))
            {
                if(touchesDirect == TOUCHE_ENTREE)
                {
                    if((saisie == 1 && carte[position].nb < 3) || (saisie != 1 && carte[position].nb < 4))
                    {
                        nbSelection++;
                        gotoxy(x + 10, y);

                        if(nbSelection == 1)
                        {
                            carte[position].nb++;
                            if(saisie == 1 && nbCarteAchoisir == 1)
                            {
                                carte[position].nb++;
                                selection[cpt].n1 = carte[position].num;
                                selection[cpt].n2 = selection[cpt].n1;
                                printf("Paire selectionnee");
                            }
                            else
                            {
                                selection[cpt].n1 = carte[position].num;
                                printf("Carte selectionnee");
                            }
                            gotoxy(x, Y + 14);
                            printf("Selection : ");
                            ecrireNumero(carte[position].num);
                        }
                        else
                        {
                            if(carte[position].num == selection[cpt].n1 && saisie == 2)
                            {
                                nbSelection--;
                                gotoxy(x, Y + 14);
                                printf("Selection : carte indisponible");
                            }
                            else
                            {
                                carte[position].nb++;
                                selection[cpt].n2 = carte[position].num;
                                printf("Carte selectionnee");
                            }
                        }
                    }
                    else
                    {
                        gotoxy(x, Y + 14);
                        if(saisie == 1) printf("Selection : paire indisponible");
                        else printf("Selection : carte indisponible");
                    }
                }

                if(nbSelection < nbCarteAchoisir)
                {
                    fleche = getch();
                    switch(fleche)
                    {
                        case TOUCHE_HAUT:
                            position--;
                            gotoxy(x, y);
                            printf("  ");
                            y--;
                            break;
                        case TOUCHE_BAS:
                            position++;
                            gotoxy(x, y);
                            printf("  ");
                            y++;
                            break;
                    }
                }
                if(position < 0) { position = 0; y = Y; }
                if(position > 12) { position = 12; y = Y + 12; }
                gotoxy(x, y);
                printf(" > ");
                ecrireNumero(carte[position].num);
                printf("\t");
            }
        } while(nbSelection < nbCarteAchoisir);

        gotoxy(x, Y + 14);
        printf("Selection : ");
        ecrireNumero(selection[cpt].n1);
        printf(" - ");
        ecrireNumero(selection[cpt].n2);
        printf("\t\t\t\n\n");
        system("pause");
    }
}

/* Sélection des deux cartes de départ */
void selectionCarte(t_carte jeu[], int nbCarteRestante, t_carte *carte1, t_carte *carte2, int n1 = 0, int c1 = -1, int n2 = 0, int c2 = -1)
{
    int cpt, n = 1;

    do
    {
        melangeJeu(jeu, nbCarteRestante);
        n = 1;
        for(cpt = 0; cpt < nbCarteRestante; cpt++)
        {
            if(n == 1 && jeu[cpt].numero == n1)
            {
                carte1->numero = jeu[cpt].numero;
                carte1->couleur = jeu[cpt].couleur;
                n++;
            }

            if(n == 2)
            {
                if(c1 == -1 && c2 == -1)
                {
                    /** Paire **/
                    if((n1 == n2 ) && (jeu[cpt].numero == n2) && (jeu[cpt].couleur != carte1->couleur))
                    {
                        carte2->numero = jeu[cpt].numero;
                        carte2->couleur = jeu[cpt].couleur;
                        n++;
                    }
                    /** -1 : couleurs différentes au hasard **/
                    else if((jeu[cpt].numero == n2) && (jeu[cpt].couleur != carte1->couleur))
                    {
                        carte2->numero = jeu[cpt].numero;
                        carte2->couleur = jeu[cpt].couleur;
                        n++;
                    }
                }
                /** -2 : couleurs identiques au hasard **/
                else
                {
                    if((jeu[cpt].numero == n2) && (jeu[cpt].couleur == carte1->couleur))
                    {
                        carte2->numero = jeu[cpt].numero;
                        carte2->couleur = jeu[cpt].couleur;
                        n++;
                    }
                }
            }
        }
    } while(n < 3);

    /*
    int i, j;
    // 0 : numéro au hasard
    if(n1 == 0)
    {
        i = rand() % 13 + 1;
    }
    else
    {
        i = n1;
    }
    carte1->numero = i;

    if(n2 == 0)
    {
        i = rand() % 13 + 1;
    }
    else
    {
        i = n2;
    }
    carte2->numero = i;

    // -1 : couleurs différentes au hasard
    // -2 : couleurs identiques au hasard
    if(c1 == -1 || c1 == -2)
    {
        i = rand() % 4;
    }
    else
    {
        i = c1;
    }
    carte1->couleur = selectionCouleur(*carte1, i);

    if(c2 == -1)
    {
        j = rand() % 3;

        if(i == 0 || (i == 1 && j >= 1) || (i == 2 && j >= 2))
        {
            j = j + 1;
        }
    }
    else if(c2 == -2)
    {
        j = i;
    }
    else
    {
        j = c2;
    }
    carte2->couleur = selectionCouleur(*carte2, j);
    */
}

/* Mode multijoueurs */
void multijoueur(t_carte jeu[])
{
    t_carte carte1, carte2;
    int cpt, cpt2, x, y, mode, nb = 0;
    int recommencer = 1, realtime;
    int nbCarteRestante = 52;
    double progression = 0.0;
    int nb_tirage, nbJoueurs, gagnant;
    t_multijoueur *J = 0;
    double *resultat = 0;
    t_selectMain *selection = 0;

    mode = saisieModeMulti();
    if(mode != 0)
    {
        do
        {
            progression = 0.0;
            nb = 0;
            system("cls");
            printf("\n Jeu multi-joueurs : Pourcentages de gain\n --\n");

            if(mode == 2)
            {
                nbJoueurs = 2;
            }
            else
            {
                nbJoueurs = saisieNbJoueurs();
            }

            nb_tirage = saisieNbTirages(1000000);
            realtime = saisieRealTime(nb_tirage, 1000);

            J = new t_multijoueur[nbJoueurs];
            resultat = new double[nbJoueurs];
            selection = new t_selectMain[nbJoueurs];

            for(cpt = 0; cpt < nbJoueurs; cpt++)
            {
                resultat[cpt] = 0.0;
            }

            if(mode == 2)
            {
                nbCarteRestante = 52;
                initJeu(jeu);
                selectionMainMulti(jeu, nbCarteRestante, nbJoueurs, selection);
            }

            printf("\n\n");
            x = wherex();
            y = wherey();

            do
            {
                nb++;
                nbCarteRestante = 52;
                initJeu(jeu);

                if(mode == 2)
                {
                    /** Joueurs 1 à 2 **/
                    for(cpt = 0; cpt < nbJoueurs; cpt++)
                    {
                        melangeJeu(jeu, nbCarteRestante);
                        selectionCarte(jeu, nbCarteRestante, &carte1, &carte2, selection[cpt].n1, selection[cpt].c1, selection[cpt].n2, selection[cpt].c2);
                        placerMain(jeu, carte1, carte2);
                        copierVersMain(jeu, J[cpt].mainPriv, 2);
                        nbCarteRestante = decalerJeu(jeu, nbCarteRestante, 2);
                    }
                }
                else
                {
                    /** Joueur 1 **/
                    selectionPaire(&carte1, &carte2, 1);
                    // selectionCarte(&carte1, &carte2, 1, 0, 1, 3);
                    placerMain(jeu, carte1, carte2);
                    copierVersMain(jeu, J[0].mainPriv, 2);

                    nbCarteRestante = decalerJeu(jeu, nbCarteRestante, 2);

                    /** Mélange du paquet **/
                    melangeJeu(jeu, nbCarteRestante);

                    /** Joueurs 2 à 10 **/
                    for(cpt = 1; cpt < nbJoueurs; cpt++)
                    {
                        copierVersMain(jeu, J[cpt].mainPriv, 2);
                        nbCarteRestante = decalerJeu(jeu, nbCarteRestante, 2);
                    }
                }

                for(cpt = 0; cpt < nbJoueurs; cpt++)
                {
                    /** Main de chaque joueur + les 5 cartes de la table **/
                    copieMainPriv(jeu, J[cpt].mainPriv, J[cpt].main);

                    /** Trie par ordre croissant de la main de chaque joueur **/
                    trierMain(J[cpt].main);

                    /** Détection des combinaisons des joueurs **/
                    J[cpt].combi = detectCombinaison(J[cpt].main);
                }

                /** Décalage des cartes dans le paquet suite à la distribution des 5 cartes de la table **/
                nbCarteRestante = decalerJeu(jeu, nbCarteRestante, 5);

                /** Détection du gagnant **/
                for(cpt = 0; cpt < nbJoueurs; cpt++)
                {
                    gagnant = 1;

                    for(cpt2 = 0; cpt2 < nbJoueurs; cpt2++)
                    {
                        if((cpt != cpt2) && (compareCombinaison(J[cpt].combi, J[cpt2].combi) != 1))
                        {
                            gagnant = 0;
                        }
                    }
                    if(gagnant == 1) resultat[cpt] = resultat[cpt] + 1.0;
                }

                progression = 100.0 * nb / nb_tirage;
                if(progression == (int)progression)
                {
                    gotoxy(x, y);
                    printf("\n Tirage en cours..%g %%\t\t\n", progression);
                }

                if(realtime == 1)
                {
                    gotoxy(x, y + 2);
                    for(cpt = 0; cpt < nbJoueurs; cpt++)
                    {
                        printf("\n Pourcentage de gain du joueur %i : %g %%\t\t\n", cpt + 1, 100.0 * resultat[cpt] / nb);
                    }
                }

            } while(nb < nb_tirage);

            if(realtime == 0)
            {
                for(cpt = 0; cpt < nbJoueurs; cpt++)
                {
                    printf("\n Pourcentage de gain du joueur %i : %g %%\t\t\n", cpt + 1, 100.0 * resultat[cpt] / nb);
                }
            }

            delete [] J;
            delete [] resultat;
            delete [] selection;
            J = 0;
            resultat = 0;
            selection = 0;

            recommencer = saisieRecommencer();
        } while(recommencer != 0);
    }
}
