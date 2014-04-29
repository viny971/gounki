#include "plateau.h"

/* Définition des valeurs d'options */
#define OPTION_TEST 0
#define OPTION_JOUEURBLANC_ROBOT  1
#define OPTION_JOUEURNOIR_ROBOT   2

/* Déclaration des noms des joueurs */
static char* joueur_blanc = " 1";
static char* joueur_noir  = " 2";

int read_options(int argc, char* argv[]);
/*	Fonction qui permet de lire les options entrées au lancement
	int argc: nombre d'arguments
	char* argv[]: tableau contenant les chaînes de caractères
	return: void */

int read_line(int* x1, int* y1, int* x2, int* y2, int* x3, int* y3, int* x4, int* y4, int* type, int* size_line);
/*	Fonction qui permet de lire une ligne entrée par l'utilisateur
	int* x1, x2, y1, y2, x3, x3, y4, y4: coordonnées lues
	int* type: + (1) ou * (2) pour les déploiements
	int* size_line: longueur de la ligne
	return: int: 1 pour déplacement, 2 pour déploiement, 3 pour victoire */

int game_loop();
/* Fonction qui lance une boucle qui déroule le jeu */
