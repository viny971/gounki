#include "plateau.h"

void read_option(int argc, char* argv[]);
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

int game_loop(plateau* p);
/* Fonction qui lance une boucle qui déroule le jeu */
