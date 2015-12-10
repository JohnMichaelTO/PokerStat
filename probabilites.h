/* D�tection d'une paire */
/*
t_combinaison detectPaire(t_carte main[]);
*/

/* Copier vers un tableau temporaire (d�tection suite, couleur, quinte flush) */
void copierTab(int tab1[], t_carte tab2[], t_couleur couleur);

/* D�tection d'une suite */
t_combinaison detectSuite(t_carte main[]);

/* D�tection d'une couleur ou quinte flush */
t_combinaison detectQuinteFlush(t_carte main[]);

/* D�tection de la combinaison d'une main */
t_combinaison detectCombinaison(t_carte main[]);

/* Probabilit�s statistiques */
void statistique1J(t_carte main[], double resultat[]);

/* Affichage du tableau des r�sultats de statistiques */
void afficheTirageStats(double resultat[], int nb_tirage);

/* Effectue un tirage */
void tirageStatistique(t_carte jeu[], t_carte main[], t_carte carte1, t_carte carte2, double resultat[]);

/* S�lectionne une paire */
void selectionPaire(t_carte *carte1, t_carte *carte2, int numero);

/* S�lection d'une main de d�part */
void selectionMainDepart(t_carte jeu[]);
