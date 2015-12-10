#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "structures.h"
#include "base.h"
#include "random.h"

using namespace std;

/* Fonction swap */
void swap(t_carte *carte1, t_carte *carte2)
{
    t_carte temp;
    temp = *carte1;
    *carte1 = *carte2;
    *carte2 = temp;
}

/* Renvoie la couleur correspondant au numéro de la couleur */
t_couleur selectionCouleur(t_carte carte, int n)
{
    switch(n)
    {
        case 0:
            carte.couleur = CARREAU;
            break;
        case 1:
            carte.couleur = COEUR;
            break;
        case 2:
            carte.couleur = PIQUE;
            break;
        case 3:
            carte.couleur = TREFLE;
            break;
    }
    return carte.couleur;
}

/* Initialisation du paquet */
void initJeu(t_carte jeu[])
{
    int carte, numero = 1, couleur = -1;

    for(carte = 0; carte < 52; carte++)
    {
        if(carte % 13 == 0)
        {
            numero = 1;
            couleur = couleur + 1;
        }

        jeu[carte].couleur = selectionCouleur(jeu[carte], couleur);
        jeu[carte].numero = numero;
        jeu[carte].ID = carte;
        numero = numero + 1;
    }
}

/* Mélange le paquet */
void melangeJeu(t_carte jeu[], int nb)
{
    int n = nb, /*n = 52,*/ temp, cpt;

    for(cpt = 2; cpt <= /*52*/nb; cpt = cpt + 2)
    {
        for(n = cpt - 1; n > 0/*(52 - nb)*/; n--)
        {
            temp = rand() % n/* + (52 - nb)*/;
            swap(jeu[n], jeu[temp]);
        }
    }
}

/* Retourner l'ID d'une carte */
int retournerID(int numero, int couleur)
{
    int ID;
    ID = numero + (couleur * 13) - 1;
    return ID;
}

/* Retourne la carte correspondant à un ID */
t_carteStats retournerCarte(int ID)
{
    t_carteStats Carte;
    ID = ID + 1;

    if(ID >= 1 && ID <= 13)
    {
        Carte.carte.couleur = CARREAU;
        Carte.carte.numero = ID;
    }
    else if(ID >= 14 && ID <= 26)
    {
        Carte.carte.couleur = COEUR;
        Carte.carte.numero = ID - 13;
    }
    else if(ID >= 27 && ID <= 39)
    {
        Carte.carte.couleur = PIQUE;
        Carte.carte.numero = ID - 26; // ID - 2 * 13
    }
    else
    {
        Carte.carte.couleur = TREFLE;
        Carte.carte.numero = ID - 39; // ID - 3 * 13;
    }

    return Carte;
}

/* Affichage des cartes dans un tableau */
void afficheJeu(t_carte jeu[], int nb = 52)
{
    int carte;
    cout << "\r\nID\tCouleur\tNumero" << endl << "-------------------------------" << endl;
    for(carte = 0; carte < nb; carte++)
    {
        cout << carte << "\t";
        ecrireCouleur(jeu[carte].couleur);
        cout << "\t";
        ecrireNumero(jeu[carte].numero);
        cout << "\t" << endl;
        // cout << "\t" << retournerID(jeu[carte].numero, jeu[carte].couleur) << endl;
    }
}

/* Copie depuis le paquet vers une main */
void copierVersMain(t_carte jeu[], t_carte main[], int nb = 7)
{
    int cpt;

    for(cpt = 0; cpt < nb; cpt++)
    {
        main[cpt].couleur = jeu[cpt].couleur;
        main[cpt].numero = jeu[cpt].numero;
    }
}

/* Place les deux cartes sélectionnées dans le jeu */
void placerMain(t_carte jeu[], t_carte carte1, t_carte carte2)
{
    int cpt, ID1, ID2;

    ID1 = retournerID(carte1.numero, carte1.couleur);
    ID2 = retournerID(carte2.numero, carte2.couleur);

    for(cpt = 0; cpt < 52; cpt++)
    {
        if(jeu[cpt].ID == ID1)
        {
            if(ID2 == 0)
            {
                swap(jeu[cpt], jeu[1]);
            }
            else
            {
                swap(jeu[cpt], jeu[0]);
            }
        }

        if(jeu[cpt].ID == ID2 && ID2 != 0)
        {
            swap(jeu[cpt], jeu[1]);
        }
    }
}

/* Trie la main par ordre croissant */
void trierMain(t_carte main[])
{
    int cpt, cpt2;

    for(cpt = 0; cpt < 7; cpt++)
    {
        for(cpt2 = 0; cpt2 < 7; cpt2++)
        {
            if(main[cpt2].numero > main[cpt].numero)
            {
                swap(main[cpt], main[cpt2]);
            }
        }
    }
}

/* Affichage de la couleur */
void ecrireCouleur(int couleur)
{
    if(couleur == 0)
    {
        printf("%c", 04);
    }
    else if(couleur == 1)
    {
        printf("%c", 03);
    }
    else if(couleur == 2)
    {
        printf("%c", 06);
    }
    else
    {
        printf("%c", 05);
    }
}

/* Affichage de la combinaison */
void ecrireCombinaison(t_combi combinaison)
{
    if(combinaison == RIEN) printf("RIEN");
    else if(combinaison == PAIRE) printf("PAIRE");
    else if(combinaison == DEUX_PAIRES) printf("DEUX PAIRES");
    else if(combinaison == BRELAN) printf("BRELAN");
    else if(combinaison == SUITE) printf("SUITE");
    else if(combinaison == COULEUR) printf("COULEUR");
    else if(combinaison == FULL) printf("FULL");
    else if(combinaison == CARRE) printf("CARRE");
    else printf("QUINTE FLUSH");
}

/* Vide la mémoire du buffer pour les saisies sécurisées */
void viderBuffer(int *nb)
{
    char c;
    while(((c = getchar()) != '\n') && c != EOF)
    {
        *nb = -1;
    }
}

/* Décale le paquet de cartes */
int decalerJeu(t_carte jeu[], int nbCarteRestante = 52, int nbAretirer = 2)
{
    int cpt;

    if(nbCarteRestante <= 0)
    {
        nbCarteRestante = 52;
        initJeu(jeu);
        melangeJeu(jeu, 52);
    }

    for(cpt = nbAretirer; cpt < nbCarteRestante; cpt++)
    {
        swap(jeu[cpt], jeu[cpt - nbAretirer]);
    }

    nbCarteRestante = nbCarteRestante - nbAretirer;

    for(cpt = nbCarteRestante; cpt < 52; cpt++)
    {
        jeu[cpt].numero = 0;
    }

    return nbCarteRestante;
}

/* Copie depuis le jeu vers la main privée */
void copieMainPriv(t_carte jeu[], t_carte mainPriv[], t_carte main[])
{
    int cpt;

    for(cpt = 0; cpt < 2; cpt++)
    {
        main[cpt].numero = mainPriv[cpt].numero;
        main[cpt].couleur = mainPriv[cpt].couleur;
    }

    for(cpt = 0; cpt < 5; cpt++)
    {
        main[cpt + 2].numero = jeu[cpt].numero;
        main[cpt + 2].couleur = jeu[cpt].couleur;
    }
}

/* Affichage des numéros pour les bonhommes */
void ecrireNumero(int n)
{
    if(n == 1) printf("AS");
    else if(n == 13) printf("ROI");
    else if(n == 12) printf("DAME");
    else if(n == 11) printf("VALET");
    else printf("%i", n);
}
