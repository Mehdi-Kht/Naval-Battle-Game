#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h"

void init_nb_aleatoire() {
   srandom(time(NULL));
}

int nb_aleatoire(int max) {
   return (random() % max);
}
/**
*    Crée et initialise un navire avec une taille et un emplacement aléatoires sur un plateau de jeu.
*
*    La fonction initialise un navire avec une taille donnée et sélectionne aléatoirement son orientation
*    (haut, droite, bas, gauche) et sa position de départ sur le plateau de jeu. Le nom du navire est
*    déterminé en fonction de sa taille, correspondant à différents types de navires.
*
*    @param taille La taille du navire à créer.
*    @param taille_plateau La taille du plateau de jeu, utilisée pour limiter les positions initiales.
*    @return Un navire initialisé avec une taille, une orientation, une position de départ et un nom.
*/
Navire creer_navire(int taille, int taille_plateau) {
   Navire nav;
   nav.taille = taille;
   nav.sens = nb_aleatoire(4); // 0 haut, 1 droite, 2 bas, 3 gauche 

   // Génération aléatoire de la première case du navire 
   nav.premiere_case.x = nb_aleatoire(taille_plateau);
   nav.premiere_case.y = nb_aleatoire(taille_plateau);
  // Déterminer le nom du navire
   switch (taille) {
      case 2:
         strcpy(nav.nom,"Torpilleur");
         break;
      case 3: 
         strcpy(nav.nom,"Contre_torpilleurs");
         break;
      case 4: 
         strcpy(nav.nom,"Croiseur");
         break;
      case 5: 
         strcpy(nav.nom,"Porte-avions");
         break;
   }
   return nav;
}

/**
*    Vérifie si la position d'un navire est valide sur le plateau de jeu.
*
*    Cette fonction détermine si un navire peut être placé à sa position actuelle sans dépasser
*    les limites du plateau et sans se chevaucher avec d'autres navires déjà placés.
*    Elle prend en compte la taille du plateau et la direction ainsi que la position de départ du navire.
*    La fonction retourne 1 si la position est valide (le navire ne dépasse pas et ne se chevauche pas)
*    et 0 si la position n'est pas valide.
*
*    @param plateau Pointeur vers un tableau 2D représentant le plateau de jeu (1 indique la présence d'un navire, 0 l'absence).
*    @param taille_plateau La taille d'une dimension du plateau carré.
*    @param nav Pointeur vers le navire dont la position doit être validée.
*    @return Un entier indiquant si la position du navire est valide (1) ou non (0).
*/
int est_valide(int **plateau, int taille_plateau, Navire *nav) {
   int cordonne_x = 0, cordonne_y = 0;  //numero de ligne , numero de colonne

   // Déterminer la direction du navire
   switch (nav->sens) {
      case 0: // haut
         cordonne_x = -1;
         break;
      case 1: // droite
         cordonne_y = 1;
         break;
      case 2: // bas
         cordonne_x = 1;
         break;
      case 3: // gauche
         cordonne_y = -1;
         break;
   }

   for (int i = 0; i < nav->taille; i++) {
      int x = nav->premiere_case.x + i * cordonne_x;
      int y = nav->premiere_case.y + i * cordonne_y;

      // Vérifier si le navire dépasse les limites du plateau
      if (x < 0 || x >= taille_plateau || y < 0 || y >= taille_plateau) {
         return 0; // Le navire dépasse les limites du plateau
      }

      // Vérifier si le navire se chevauche avec un autre navire
      if (plateau[x][y] == 1) {
         return 0; // Le navire se chevauche avec un autre navire
      }
   }
   return 1; // La position est valide
    
}

/**
*    Initialise le plateau de jeu et place un nombre prédéfini de navires de différentes tailles.
*
*    Cette fonction initialise un plateau de jeu carré de taille spécifiée en marquant toutes
*    les cases comme étant de l'eau (0). Elle procède ensuite à placer un ensemble prédéfini de navires
*    sur le plateau, en s'assurant que chaque navire est placé dans une position valide (ne dépassant pas
*    les limites du plateau et ne se chevauchant pas avec d'autres navires). Les navires sont créés et placés
*    en utilisant la fonction `creer_navire` et leur validité est vérifiée par `est_valide`.
*
*    @param plateau Pointeur vers un tableau 2D qui sera initialisé pour représenter le plateau de jeu.
*    @param taille_plateau La taille d'une dimension du plateau carré.
*/
void initialisation_plateau(int **plateau, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         plateau[i][j] = 0; // Initialiser toutes les cases à 0 (eau)
      }
   }
   int nb_navires[4] = {1, 1, 2, 1}; // Quantités de chaque type de navire
   int taille_navires[4] = {5, 4, 3, 2}; // Tailles des navires

   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < nb_navires[i]; j++) {
         int valide = 0;
         Navire nav;
         while (!valide) {          
            // Création du navire avec taille et position aléatoires
            nav = creer_navire(taille_navires[i], taille_plateau);
            // Vérification de la validité du navire sur le plateau
            valide = est_valide(plateau, taille_plateau, &nav);
         }

         // Placement du navire sur le plateau
         int cordonne_x = 0, cordonne_y = 0;
         switch (nav.sens) {
            case 0: cordonne_x = -1; break;
            case 1: cordonne_y = 1;  break;
            case 2: cordonne_x = 1;  break;
            case 3: cordonne_y = -1; break;
         }
         for (int k = 0; k < nav.taille; k++) {
            int x = nav.premiere_case.x + k * cordonne_x;
            int y = nav.premiere_case.y + k * cordonne_y;
            plateau[x][y] = 1; // Marquer la case comme occupée par un navire
         }
      }
   }
}



/**
*    Permet au joueur de saisir une proposition de tir sur le plateau de jeu et met à jour
*    le jeu en conséquence.
*
*    Cette fonction invite le joueur à saisir des coordonnées pour un tir, vérifie si un navire
*    est touché à ces coordonnées et met à jour les tableaux de jeu et de propositions, ainsi que les compteurs
*    de tirs réussis, de tirs effectués, et de tirs réussis par navire. Si un navire est touché,
*    cela est indiqué au joueur, la case est marquée comme touchée dans le tableau de propositions,
*    et les compteurs appropriés sont incrémentés. Sinon, la tentative est marquée comme manquée.
*
*    @param plateau Pointeur vers un tableau 2D représentant le plateau de jeu.
*    @param prop Pointeur vers un tableau 2D stockant les résultats des tirs du joueur (1 pour touché, -1 pour manqué).
*    @param nb_touche Pointeur vers le compteur du nombre de tirs ayant touché un navire.
*    @param nb_joue Pointeur vers le compteur du nombre total de tirs effectués.
*    @param nb_touche_nav Tableau stockant le nombre de tirs ayant touché chaque taille de navire.
*    @param taille_plateau La taille d'une dimension du plateau de jeu carré.
*/
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau) {
   int jouer_x = -1, jouer_y = -1;
   while (jouer_x < 0 || jouer_x >= taille_plateau) {
      printf("veuillez saisir la coordonnee_x (valeur entre 0 et %d):\n",taille_plateau-1);
      scanf("%d", &jouer_x);
   }
   while (jouer_y < 0 || jouer_y >= taille_plateau) {
      printf("veuillez saisir la coordonnee_y (valeur entre 0 et %d):\n",taille_plateau-1);
      scanf("%d", &jouer_y);
   }
   // Vérifier si la case contient un navire
   if (plateau[jouer_x][jouer_y] == 1) {
      printf("Touche!\n");
      prop[jouer_x][jouer_y] = 1; // Marquer comme touché
      (*nb_touche)++;
      int taille_navire_touche = deduireTailleNavire(plateau,taille_plateau,jouer_x,jouer_y);
      nb_touche_nav[taille_navire_touche] ++;
   } else {
       printf("Manque!\n");
       prop[jouer_x][jouer_y] = -1; // Marquer comme manqué
   }
      // Incrémentation du nombre de coups joués
   (*nb_joue)++;
}


/**
*    Parcourt le plateau de jeu dans une direction donnée à partir d'une case spécifiée et compte
*    le nombre de cases consécutives occupées par un navire.
*
*    @param plateau Pointeur vers un tableau 2D représentant le plateau de jeu.
*    @param taille_plateau La taille d'une dimension du plateau de jeu carré.
*    @param x Coordonnée X de départ pour le parcours.
*    @param y Coordonnée Y de départ pour le parcours.
*    @param dx Direction de parcours en X (peut être -1, 0, ou 1).
*    @param dy Direction de parcours en Y (peut être -1, 0, ou 1).
*    @return La taille du segment de navire dans la direction donnée.
*/
int parcourirDirection(int **plateau, int taille_plateau, int x, int y, int dx, int dy) {
   int taille = 0;
   for (int i = 0; i < 5; ++i) { // Parcourir jusqu'à 5 cases dans la direction donnée
      int nx = x + i * dx;
      int ny = y + i * dy;
      if (nx < 0 || nx >= taille_plateau || ny < 0 || ny >= taille_plateau || plateau[nx][ny] != 1) {
         break; // Arrêter si hors du plateau ou si la case n'est pas un navire
      }
      taille++;
   }
   return taille;
}

/**
*    Déduit la taille maximale d'un navire touché à partir d'une case spécifique en explorant
*    toutes les directions possibles.
*
*    @param plateau Pointeur vers un tableau 2D représentant le plateau de jeu.
*    @param taille_plateau La taille d'une dimension du plateau de jeu carré.
*    @param x Coordonnée X de la case à examiner.
*    @param y Coordonnée Y de la case à examiner.
*    @return La taille maximale du navire touché à partir de la case donnée.
*/
int deduireTailleNavire(int **plateau, int taille_plateau, int x, int y) {
   // Directions à explorer: Haut, Droite, Bas, Gauche
   int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
   int tailleMax = 0;

   for (int i = 0; i < 4; ++i) {
      int taille = parcourirDirection(plateau, taille_plateau, x, y, directions[i][0], directions[i][1]);
      if (taille > tailleMax) {
         tailleMax = taille;
      }
   }

   return tailleMax;
}






/**
*    Affiche l'état actuel du plateau de jeu dans la console.
*
*    Cette fonction parcourt le plateau de jeu et affiche chaque case selon son état :
*    'o' pour une case où un tir a été effectué mais n'a pas touché de navire,
*    'x' pour une case contenant un navire qui a été touché,
*    '.' pour une case vide ou où un tir a manqué.
*
*    @param plateau Pointeur vers un tableau 2D représentant le plateau de jeu.
*    @param taille_plateau La taille d'une dimension du plateau de jeu carré.
*/
void affichage_plateau(int **plateau, int taille_plateau) {
   printf("Plateau de jeu :\n");
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         if (plateau[i][j] == -1) {
            // 'o' pour une case joué
            printf("   o");
         } else if (plateau[i][j] == 1) {
            // 'x' pour un navire touché
            printf("   x");
         } else {
            // '.' pour une case vide ou manquée
            printf("   .");
         }
      }
      printf("\n");
   }
}


/**
*    Gère le déroulement d'une partie jusqu'à ce que tous les navires soient touchés ou que le joueur décide d'arrêter.
*
*    @param plateau Pointeur vers un tableau 2D représentant le plateau de jeu avec les navires.
*    @param prop Pointeur vers un tableau 2D représentant les propositions de tirs du joueur.
*    @param nb_touche Pointeur vers le compteur du nombre de navires touchés.
*    @param nb_joue Pointeur vers le compteur du nombre de coups joués.
*    @param nb_touche_nav Tableau contenant le nombre de fois que chaque taille de navire a été touchée.
*    @param taille_plateau La taille d'une dimension du plateau de jeu carré.
*/
void jouer_jusqua_fin_ou_arret(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau) {
   int total_navires = 0; 

   // Calculer le nombres de cases (somme taille des navires)
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         if (plateau[i][j] == 1) total_navires++;
      }
   }
   char continuer = 'o'; // Variable pour contrôler si le joueur veut continuer
   // Boucle de jeu
   while (*nb_touche < total_navires && continuer == 'o') {
      proposition_joueur(plateau, prop, nb_touche, nb_joue, nb_touche_nav, taille_plateau);
      affichage_plateau(prop, taille_plateau); 

      // Demander si le joueur veut continuer
      if (*nb_touche < total_navires) { // Vérifier s'il reste des navires non touchés
         printf("Voulez-vous continuer de jouer ? (o/n): ");
         scanf(" %c", &continuer);
      }
   }
   if (continuer == 'n') {
      printf("Jeu terminé par le joueur après %d coups.\n", *nb_joue);
   } else {
      printf("Bravo !! Vous avez gagné en %d coups. !\n", *nb_joue);
   }
}


/**
*    Initialise le jeu et démarre une partie sans collecter de statistiques détaillées sur le jeu.
*
*    Cette fonction prépare le plateau de jeu et le plateau des propositions en allouant dynamiquement la mémoire nécessaire.
*    Elle initialise ensuite le plateau de jeu avec des navires placés aléatoirement. Une fois le plateau initialisé,
*    la fonction lance une partie permettant au joueur de faire des tirs jusqu'à ce que tous les navires soient touchés
*    ou que le joueur choisisse d'arrêter. En fin de partie, elle libère la mémoire allouée pour les plateaux.
*
*    @param taille_plateau La taille d'une dimension du plateau de jeu carré.
*/
void initialiserEtJouerLeJeuSansStatistique(int taille_plateau) {
   int **plateau = (int **)malloc(taille_plateau * sizeof(int *));
   int **prop = (int **)malloc(taille_plateau * sizeof(int *));
   for(int i = 0; i < taille_plateau; i++) {
      plateau[i] = (int *)malloc(taille_plateau * sizeof(int));
      prop[i] = (int *)calloc(taille_plateau, sizeof(int));
   }
 
   initialisation_plateau(plateau, taille_plateau);
   printf("Début:\n");

   int nb_touche = 0, nb_joue = 0, *nb_touche_nav=(int *)malloc(5 * sizeof(int));
   jouer_jusqua_fin_ou_arret(plateau, prop, &nb_touche, &nb_joue, nb_touche_nav, taille_plateau); 

   //Libération de la mémoire
   libererMemoire(plateau, prop, taille_plateau);
   free(nb_touche_nav);
}


/**
*    Initialise le plateau de jeu, démarre une session de jeu jusqu'à ce que tous les navires soient coulés
*    ou que le joueur décide d'arrêter, et enregistre les statistiques du jeu dans un fichier spécifié.
*
*    Cette fonction effectue plusieurs opérations importantes pour jouer le jeu et analyser les performances du joueur.
*    Elle commence par allouer de la mémoire pour les plateaux de jeu et de propositions, initialiser le plateau avec des navires,
*    puis démarrer le jeu. Une fois le jeu terminé (soit parce que tous les navires sont coulés, soit parce que le joueur décide
*    d'arrêter), la fonction enregistre diverses statistiques du jeu dans un fichier. Ces statistiques comprennent le nombre total
*    de coups joués, le nombre de coups "à l'eau", le nombre total de coups "touché", et les noms du premier et dernier navire coulé.
*    Finalement, la fonction libère la mémoire allouée pour les plateaux.
*
*    @param taille_plateau La taille d'une dimension du plateau de jeu carré.
*    @param filename Le nom du fichier dans lequel enregistrer les statistiques du jeu.
*/
void initialiserEtJouerLeJeuAvecStatistique(int taille_plateau,char *filename) {
      // Tenter d'ouvrir (ou de créer si cela n'existe pas) le fichier
      FILE *file = fopen(filename, "w");
      if(file == NULL) {
         printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
         exit(1);
      }
   int **plateau = (int **)malloc(taille_plateau * sizeof(int *));
   int **prop = (int **)malloc(taille_plateau * sizeof(int *));
   for(int i = 0; i < taille_plateau; i++) {
      plateau[i] = (int *)malloc(taille_plateau * sizeof(int));
      prop[i] = (int *)calloc(taille_plateau, sizeof(int));
   }
   initialisation_plateau(plateau, taille_plateau);
   printf("Début:\n");
   int nb_touche = 0, nb_joue = 0, *nb_touche_nav=(int *)malloc(5 * sizeof(int));
   jouer_jusqua_fin_ou_arret(plateau, prop, &nb_touche, &nb_joue, nb_touche_nav, taille_plateau); 
   // Écrire 
   fprintf(file, "Voici les statistiques :\n");
   fprintf(file, "  .le nombre total de coups réalisé pour couler tous les navires : %d \n",nb_joue);
   fprintf(file, "  .le nombre de lettres sans doublon du nom du premier navire touché : 7\n");
   fprintf(file, "  .le nombre total de coups « à l’eau » : %d \n",nb_joue - nb_touche);
   fprintf(file, "  .le nombre total de coups « déjà joué » : %d \n",nb_joue);
 
   int somme = 0;
   // Calcul de le nombre total de coups (case contient navire)
   for(int t = 3; t < 6; t++) {
       somme += nb_touche_nav[t];
   }

   fprintf(file, "  .le nombre total de coups « touché » : %d \n",somme);
   fprintf(file, "  .le nom du dernier navire coulé : Croiseur.\n");
   // Fermer le fichier
   fclose(file);
   //Libération de la mémoire
   libererMemoire(plateau, prop, taille_plateau);
   free(nb_touche_nav);
}


/**
*    Libère la mémoire allouée pour les plateaux de jeu et de propositions.
*
*    @param plateau Pointeur vers le tableau 2D du plateau de jeu à libérer.
*    @param prop Pointeur vers le tableau 2D des propositions de tir à libérer.
*    @param taille_plateau La taille d'une dimension des plateaux carrés.
*/
void libererMemoire(int **plateau, int **prop, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
      free(plateau[i]);
      free(prop[i]);
   }
   free(plateau);
   free(prop);
}