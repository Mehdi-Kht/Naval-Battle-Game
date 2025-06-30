#ifndef JEU_H
#define JEU_H

typedef struct une_case {
    int x; /* position de la case en x*/
    int y; /* position de la case en y*/
} Case;

typedef struct navire {
    int sens; /* 0 haut 1 droite 2 bas 3 gauche */
    Case premiere_case;
    int taille;
    char nom[100]; // Ajouter le nom du navire ici.
} Navire;

void init_nb_aleatoire();
int nb_aleatoire(int max);
Navire creer_navire(int taille, int taille_plateau);
int est_valide(int **plateau, int taille_plateau, Navire *nav);
void initialisation_plateau(int **plateau, int taille_plateau);
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau);
int parcourirDirection(int **plateau, int taille_plateau, int x, int y, int dx, int dy);
int deduireTailleNavire(int **plateau, int taille_plateau, int x, int y);
void affichage_plateau(int **plateau, int taille_plateau);
void jouer_jusqua_fin_ou_arret(int **plateau,int **prop, int *nb_touche,int *nb_joue, int *nb_touche_nav, int taille_plateau);
void initialiserEtJouerLeJeuSansStatistique(int taille_plateau);
void initialiserEtJouerLeJeuAvecStatistique(int taille_plateau,char *filename);
void libererMemoire(int **plateau, int **prop, int taille_plateau);
#endif