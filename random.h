/* Calcul la valeur moyenne du tableau statistique */
double Valmoy(t_carteStats tab[]);

/* Calcul l'�cart moyen du tableau statistique */
double EcartMoy(t_carteStats tab[]);

/* Affiche le tableau statistiques */
void afficheStats(t_carteStats tab[]);

/* Initialisation du tableau statistiques */
void initStats(t_carteStats tab[]);

/* G�n�ration des 10 millions de tirages au hasard */
void generate10miliion(t_carte jeu[]);

/* Copier du paquet vers le tableau de statistiques */
void copierVers(t_carte jeu[], int ID1, t_carteStats tab[], int ID2);
