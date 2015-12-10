/* Fonction swap */
void swap(t_carte *carte1, t_carte *carte2);

/* Renvoie la couleur correspondant au num�ro de la couleur */
t_couleur selectionCouleur(t_carte carte, int n);

/* Initialisation du paquet */
void initJeu(t_carte jeu[]);

/* M�lange le paquet */
void melangeJeu(t_carte jeu[], int nb);

/* Retourner l'ID d'une carte */
int retournerID(int numero, int couleur);

/* Retourne la carte correspondant � un ID */
t_carteStats retournerCarte(int ID);

/* Affichage des cartes dans un tableau */
void afficheJeu(t_carte jeu[], int nb);

/* Copie depuis le paquet vers une main */
void copierVersMain(t_carte jeu[], t_carte main[], int nb);

/* Place les deux cartes s�lectionn�es dans le jeu */
void placerMain(t_carte jeu[], t_carte carte1, t_carte carte2);

/* Trie la main par ordre croissant */
void trierMain(t_carte main[]);

/* Affichage de la couleur */
void ecrireCouleur(int couleur);

/* Affichage de la combinaison */
void ecrireCombinaison(t_combi combinaison);

/* Vide la m�moire du buffer pour les saisies s�curis�es */
void viderBuffer(int *nb);

/* D�cale le paquet de cartes */
int decalerJeu(t_carte jeu[], int nbCarteRestante, int nbAretirer);

/* Copie depuis le jeu vers la main priv�e */
void copieMainPriv(t_carte jeu[], t_carte mainPriv[], t_carte main[]);

/* Affichage des num�ros pour les bonhommes */
void ecrireNumero(int n);
