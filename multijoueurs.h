/* Compare deux combinaisons */
int compareCombinaison(t_combinaison combinaison, t_combinaison combinaison2);

/* Sélection d'une main en mode multijoueurs */
void selectionMainMulti(t_carte jeu[], int nbCarteRestante, int nbJoueurs, t_selectMain *selection);

/* Sélection des deux cartes de départ */
void selectionCarte(t_carte jeu[], int nbCarteRestante, t_carte *carte1, t_carte *carte2, int n1, int c1, int n2, int c2);

/* Mode multijoueurs */
void multijoueur(t_carte jeu[]);
