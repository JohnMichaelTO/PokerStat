#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "structures.h"
#include "base.h"
#include "saisies.h"
#include "random.h"
#include "conio.h"
#define NB_TIRAGES 10000000.0

using namespace std;

/* Calcul la valeur moyenne du tableau statistique */
double Valmoy(t_carteStats tab[])
{
    int carte;
    double nombre = 0.0;

    for(carte = 0; carte < 52; carte++)
    {
        nombre = nombre + tab[carte].nombre;
    }
    nombre = nombre / 52.0;
    return nombre;
}

/* Calcul l'écart moyen du tableau statistique */
double EcartMoy(t_carteStats tab[])
{
    double ecart = 0.0;
    int carte;
    double nb = 0.0, valeur;

    valeur = Valmoy(tab);

    for(carte = 0; carte < 52; carte++)
    {
        ecart = ((valeur - tab[carte].nombre));

        if(ecart < 0.0)
        {
            ecart = -ecart;
        }

        nb = nb + ecart;
    }
    nb = nb / 52.0;

    if(valeur == 0.0)
    {
        nb = 0.0;
    }
    return nb;
}

/* Affiche le tableau statistiques */
void afficheStats(t_carteStats tab[])
{
    int carte;
    double ecart, nombre = Valmoy(tab);
    double valeur, absolue, pourcent = 0.0;
    valeur = NB_TIRAGES / 52.0;
    cout << "\r\n ID\tCouleur\tNumero\tNombre\tEcart relatif" << endl << " -------------------------------" << endl;

    for(carte = 0; carte < 52; carte++)
    {
        absolue = tab[carte].nombre - valeur;
        if(absolue < 0.0)
        {
            absolue = -absolue;
        }
        absolue = (absolue / valeur) * 100.0;
        cout << " " << carte << "\t";
        ecrireCouleur(tab[carte].carte.couleur);
        cout << "\t";
        ecrireNumero(tab[carte].carte.numero);
        cout << "\t" << tab[carte].nombre << "\t" << absolue << " %" << endl;

        pourcent = pourcent + absolue;
    }

    cout.precision(10);
    cout << "\r\n Moyenne = " << nombre << endl;
    ecart = EcartMoy(tab);

    if(ecart == 0.0)
    {
        nombre = 1.0;
    }

    cout << "\r\n Ecart moyen = " << ecart << endl;
    cout << "\r En pourcentage : " << ecart * 100.0 / nombre  << "%" << endl;
    cout << "\r Pourcentage d'erreur moyen : " << pourcent / 52.0  << "%" << endl;
}

/* Initialisation du tableau statistiques */
void initStats(t_carteStats tab[])
{
    int cpt;

    for(cpt = 0; cpt < 52; cpt++)
    {
        tab[cpt] = retournerCarte(cpt);
        tab[cpt].nombre = 0;
    }
}

/* Génération des 10 millions de tirages au hasard */
void generate10miliion(t_carte jeu[])
{
    int cpt, ID, recommencer = 1, x, y;
    double compteur = 0.0;
    t_carteStats tabStats[52];

    do
    {
        system("cls");
        printf("\n Verification de la robustesse du generateur de hasard\n --\n\n");
        printf(" Le chargement risque de mettre du temps, soyez patient svp !\n\n\n\n");
        initJeu(jeu);
        melangeJeu(jeu, 52);
        initStats(tabStats);

        x = wherex();
        y = wherey();

        for(cpt = 0; cpt < NB_TIRAGES; cpt++)
        {
            melangeJeu(jeu, 52);
            ID = retournerID(jeu[0].numero, jeu[0].couleur);
            tabStats[ID].nombre = tabStats[ID].nombre + 1;

            compteur = 100.0 * cpt / NB_TIRAGES;

            if(compteur == (int)compteur)
            {
                gotoxy(x, y);
                printf(" Generation des 10 millions de tirages en cours..%g %%\t\t\n", compteur);
            }
        }

        afficheStats(tabStats);

        recommencer = saisieRecommencer();
    } while(recommencer != 0);
}

/* Copier du paquet vers le tableau de statistiques */
void copierVers(t_carte jeu[], int ID1, t_carteStats tab[], int ID2)
{
    tab[ID2].carte.couleur = jeu[ID1].couleur;
    tab[ID2].carte.numero = jeu[ID1].numero;
    tab[ID2].nombre = 0;
}
