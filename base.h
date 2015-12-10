/* Fonction swap */
void swap(t_carte *carte1, t_carte *carte2);

/* Renvoie la couleur correspondant au numéro de la couleur */
t_couleur selectionCouleur(t_carte carte, int n);

/* Initialisation du paquet */
void initJeu(t_carte jeu[]);

/* Mélange le paquet */
void melangeJeu(t_carte jeu[], int nb);

/* Retourner l'ID d'une carte */
int retournerID(int numero, int couleur);

/* Retourne la carte correspondant à un ID */
t_carteStats retournerCarte(int ID);

/* Affichage des cartes dans un tableau */
void afficheJeu(t_carte jeu[], int nb);

/* Copie depuis le paquet vers une main */
void copierVersMain(t_carte jeu[], t_carte main[], int nb);

/* Place les deux cartes sélectionnées dans le jeu */
void placerMain(t_carte jeu[], t_carte carte1, t_carte carte2);

/* Trie la main par ordre croissant */
void trierMain(t_carte main[]);

/* Affichage de la couleur */
void ecrireCouleur(int couleur);

/* Affichage de la combinaison */
void ecrireCombinaison(t_combi combinaison);

/* Vide la mémoire du buffer pour les saisies sécurisées */
void viderBuffer(int *nb);

/* Décale le paquet de cartes */
int decalerJeu(t_carte jeu[], int nbCarteRestante, int nbAretirer);

/* Copie depuis le jeu vers la main privée */
void copieMainPriv(t_carte jeu[], t_carte mainPriv[], t_carte main[]);

/* Affichage des numéros pour les bonhommes */
void ecrireNumero(int n);
