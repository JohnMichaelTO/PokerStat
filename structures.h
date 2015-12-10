typedef enum s_couleur
{
    CARREAU, COEUR, PIQUE, TREFLE
} t_couleur;

typedef struct s_carte
{
    int ID;
    int numero;
    t_couleur couleur;
} t_carte;

typedef struct s_carteStats
{
    t_carte carte;
    int nombre;
} t_carteStats;

typedef enum s_combi
{
    RIEN = 0, PAIRE = 1, DEUX_PAIRES = 2, BRELAN = 3, SUITE = 4, COULEUR = 5, FULL = 6, CARRE = 7, QUINTE_FLUSH = 8
} t_combi;

typedef struct s_combinaison
{
    int numero;
    t_combi combi;
} t_combinaison;

typedef struct s_multijoueur
{
    t_carte main[7];
    t_carte mainPriv[2];
    t_combinaison combi;
} t_multijoueur;

typedef struct s_selectMain
{
    int n1, c1, n2, c2;
} t_selectMain;

typedef struct s_position
{
    int num, nb;
} t_position;
