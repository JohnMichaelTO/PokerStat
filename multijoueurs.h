/* Compare deux combinaisons */
int compareCombinaison(t_combinaison combinaison, t_combinaison combinaison2);

/* S�lection d'une main en mode multijoueurs */
void selectionMainMulti(t_carte jeu[], int nbCarteRestante, int nbJoueurs, t_selectMain *selection);

/* S�lection des deux cartes de d�part */
void selectionCarte(t_carte jeu[], int nbCarteRestante, t_carte *carte1, t_carte *carte2, int n1, int c1, int n2, int c2);

/* Mode multijoueurs */
void multijoueur(t_carte jeu[]);
