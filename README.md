# Naval-Battle-Game

## Description

	Ce Programme illustre le point d'entrée d'un jeu de simulation navale, où le joueur est invité à gérer une grille ou un plateau de jeu peuplé de navires. 

	L'application démarre en initialisant un générateur de nombres aléatoires pour assurer la variété des parties. 
	Elle accepte jusqu'à deux arguments en ligne de commande pour ajuster son comportement : 
	un indicateur optionnel -s qui active un mode statistique.
	un nom de fichier où sauvegarder ces statistiques.

### Configuration Initiale

	Le jeu commence par initialiser le générateur de nombres aléatoires pour garantir que les positions des navires et les tirs soient imprévisibles à chaque partie.

	L'utilisateur est invité à saisir la taille du plateau de jeu, avec des limites minimales et maximales pour assurer la jouabilité.

	Selon les arguments passés au programme, l'utilisateur peut choisir de jouer une partie standard ou une partie avec la collecte de statistiques qui seront sauvegardées dans un fichier spécifié.

### Plateau de Jeu

	Le plateau est représenté par un tableau 2D. Chaque case du plateau peut être vide, contenir une partie d'un navire, 
	ou montrer le résultat d'un tir précédent (touché ou manqué).

	Les navires sont placés aléatoirement sur le plateau. 
	Leur positionnement respecte leur taille et s'assure qu'ils ne se chevauchent pas et ne dépassent pas les limites du plateau.

### Déroulement d'une Partie

	Tir du Joueur : L'utilisateur saisit les coordonnées d'un tir. Le jeu vérifie si un navire se trouve à cette position. 
	Si c'est le cas, le navire est considéré comme touché ; sinon, le tir est un échec, et le jeu continue.

	Vérification des Navires : Après chaque tir, le jeu vérifie si tous les navires ont été coulés. 
	Si tous les navires sont coulés, la partie se termine par la victoire du joueur.

	Statistiques : Si activées, des statistiques sont collectées et comprennent le nombre de tirs effectués, le nombre de tirs réussis, 
	le premier et le dernier navire coulé, et le nombre total de coups à l'eau. 
	Ces informations sont enregistrées dans un fichier si spécifié.


## Compilation 

1. cd /path/to/your/program
2. creer le fichier d'execution :
	1. gcc -o main.c mon_jeu
	2. make
3. Choisir une des ligne de commande suivante :
	1. ./mon_jeu
	2. ./mon_jeu -s
	3. ./mon_jeu -s stats.txt


## Dépendances

Les dépendances pour faire fonctionner ce projet. Dans chaque

.Mettre à jour la liste des paquets :

	sudo apt update

.Installe CUnit pour les tests en C :

	sudo apt install libcunit1 libcunit1-doc libcunit1-dev


.Installer Bats :

	sudo apt install bats

.Verifier l'installation :

	bats --version

.Pour les liens regarder la sections Références.

## Références
CUnit site officiel : 
http://cunit.sourceforge.net/

Bats (Bash Automated Testing System) : 
Bats peut être trouvé et documenté sur GitHub à https://github.com/bats-core/bats-core.