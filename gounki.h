#ifndef PLATEAU_FILE
#define GOUNKI_FILE
#include "plateau.h"
#include "ia.h"
#endif

/* Définition des valeurs d'options */
#define OPTION_TEST 0
#define OPTION_JOUEURBLANC_ROBOT 1
#define OPTION_JOUEURNOIR_ROBOT 2
#define OPTION_JOUEURBLANC_BASIQUE 3
#define OPTION_JOUEURNOIR_BASIQUE 4

/* Déclaration des noms des joueurs */
static char* joueur_blanc = "Player 1";
static char* joueur_noir  = "Player 2";

int read_options(int argc, char* argv[]);
/*	Fonction qui permet de lire les options entrées au lancement
	int argc: nombre d'arguments
	char* argv[]: tableau contenant les chaînes de caractères
	return: void */

int read_line(point** point_1, point** point_2, point** point_3, point** point_4,  int* type, int* size_line);
/*	Fonction qui permet de lire une ligne entrée par l'utilisateur
	point** point_1 point_2 point_3 point_4: points à passer en argument
	int* type: + (1) ou * (2) pour les déploiements
	int* size_line: longueur de la ligne
	return: int: 1 pour déplacement, 2 pour déploiement, 3 pour victoire */

int game_loop(int options);
/* 	Fonction qui lance une boucle qui déroule le jeu
	int options: utilisé pour l'ia */

int trans_options(int options);
