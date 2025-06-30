#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
*    Point d'entrée principal pour le jeu de Bataille Navale.
*
*    Cette fonction initialise le jeu, traite les arguments de ligne de commande pour déterminer
*    si des statistiques doivent être collectées et où elles doivent être enregistrées. Elle invite ensuite
*    l'utilisateur à saisir la taille du plateau de jeu et démarre une session de jeu en fonction de la présence
*    ou non d'options de statistiques. Le jeu peut être lancé sans arguments, avec une option pour activer
*    les statistiques et éventuellement un nom de fichier pour sauvegarder ces statistiques. La taille du plateau
*    est demandée à l'utilisateur, qui doit être comprise entre 6 et 100 inclus. Selon l'option choisie, le jeu
*    se déroule avec ou sans collecte de statistiques.
*
*    Utilisation:
*    - Sans arguments, démarre un jeu standard sans collecte de statistiques.
*    - Avec "-s" ou "-S" comme premier argument, active la collecte de statistiques. Un deuxième argument optionnel
*      peut spécifier le nom du fichier dans lequel sauvegarder les statistiques. Si aucun nom de fichier n'est fourni,
*      "Stats.txt" est utilisé par défaut.
*    
*    @param argc Nombre d'arguments de ligne de commande.
*    @param argv Tableau des arguments de ligne de commande.
*    @return Un entier indiquant le succès (0) ou l'échec (1) du démarrage du jeu.
*/
int main(int argc, char* argv[]){
   init_nb_aleatoire();
   if (argc != 2 && argc != 3 && argc != 1) {
      printf("erreur : exactement zéro, un ou deux arguments doivent être fournis\n");
      return 1; 
   }

   int option_statistique = 0;
   if (argc == 3 || argc == 2)
   {
      if (strcmp(argv[1],"-s") == 0 || strcmp(argv[1], "-S") == 0)
      {
         option_statistique = 1;
      } else {
         printf("Option inconnue\n");
         return 1;
      }
   }

   char *filename;
   if (argc == 3)
      filename = argv[2];
   else if (argc == 2)
      filename = "Stats.txt"

   printf("Bienvenue au jeu Bataille Navale : \n");
   //Début du jeu
      if(option_statistique) {
      int taille_plateau = -1;
      while(taille_plateau < 6 || taille_plateau > 100){
         printf("Veuillez saisir la taille du plateau (6<= taille <=100): \n");
         scanf("%d", &taille_plateau);
      }
      initialiserEtJouerLeJeuAvecStatistique(taille_plateau,filename);
   } else {
      int taille_plateau = -1;
      while(taille_plateau < 6 || taille_plateau > 100){
         printf("Veuillez saisir la taille du plateau (6<= taille <=100): \n");
         scanf("%d", &taille_plateau);
      }
      initialiserEtJouerLeJeuSansStatistique(taille_plateau);
   }

   return 0;
}