#ifndef PION_FILE
#define PLATEAU_FILE
#include "pion.h"
#include <math.h>
#endif

typedef struct plateau{
/*	structure du plateau de jeu: un tableau de taill 8x8 de pions */
	pion* cell[8][8];
} plateau;

typedef struct liste{
/*	liste ayant comme données la position d'un pion */
	int x;
	int y;
	struct liste* suivant;
} liste;

typedef struct point{
/* 	structure contenant les coordonnées d'un point
	permet de passer plus facilement des données d'une fonction à l'autre */	
	int x;
	int y;
} point;

/*	Fonctions relatives au plateau et à ses règles
---------------------------------------------------------------------------------------------------------------------------------------*/
plateau* init_plateau();
/*	initialise un plateau avec des pions
	return: plateau* */
void free_plateau(plateau* p);
/*	libére un plateau avec tout ce qu'il contient
	plateau* p: pointeur vers le plateau à libérer
	return: void */
int affiche_plateau(plateau* p, int tour);
/* 	affiche dans le terminal le plateau
	plateau* p: le plateau à afficher
	int tour: le numéro du tour en cours
	return: int 1 si la fonction termine sans erreur */

void deplacement(plateau* p, point* point_1, point* point_2);
/*	deplace un pion d'un point à un autre
	point* point_1: point de départ. point* point_2: point d'arrivé
	return void */
void deplacement2(plateau* p, int x1, int y1, int forme, int couleur);
/*	met un pion dans la case x1, y1
	int x1, y1: case modifiée
	int forme, couleur: caractéristiques du pion
	return void */

int trans_coord(char x);
/* 	transforme les coordonnées entrées par l'utilisateur en int facilement utilisable dans les fonctions
	char x: le char à transformer en int
	return: int: la valeur simplifiée */

int deplacement_possible(plateau* p, point* point_1, point* point_2, int joueur);
/*	test si le deplacement est possible
	plateau* p: le plateau où les pions sont
	point* point_1, point_2: cases d'arrivée et de départ
	int joueur: numéro du tour pour déterminer le joueur 
	return: int 1 (Vrai), 2 (Faux)*/
void deplacements_possibles(plateau* p, liste** l, int forme, int x2, int y2, int joueur);
/*	fonction auxilliaire utilisant des listes pour déterminer l'ensemble des déplacements possibles
	plateau* p: le plateau où se trouvent les pions
	liste** l, l2: listes à modifier
	int forme: forme du pion
	int x2, y2: case d'arrivée
	int joueur: numéro du tour pour déterminer le joueur 
	return: void */
void se(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
void so(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
void ne(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
void no(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
void s(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
void n(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
void e(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
void o(plateau* p, liste** l, int x, int y, int x2, int y2, int taille);
/*	ajoutent un certain nombre de déplacement possibles. Vers le nord(n), sud(s), est(e), ouest(o)
	liste** l: liste à laquelle sont ajoutées les déplacements possibles
	int x,y: case de départ
	int x2,y2: case d'arrivée
	int taille: taille du pion
	return: void */
int coord_dans_tab(int x, int y);
/*	test si les coordonnées entrées ne dépassent pas les limites du tableau
	int x, y: coordonnées en x et y
	return: int: 1 = Vrai, 2 = False */

void composition(plateau* p, int x1,  int y1,  int x2,  int y2); 
/*	compose deux pions lors d'un déplacement
	plateau* p: le plateau où se trouvent les pions
	int x1, y1: case de départ
	int x2, y2: case d'arrivée
	return: void */
void composition2(plateau* p, int x1, int y1, int forme);
/*	compose deux pions lors d'un déploiement
	plateau* p: le plateau où se trouvent les pions
	int x1, y1: case à modifier
	int forme: forme à ajouter
	return: void */

int meme_sens1(int x1, int y1, int x2, int y2, int x3, int y3, int forme);
/*	test si la case (x3,y3) est un déplacement s'effectuant dans le même sens que de (x1,y1) à (x2,y2)
	int x1, y1, x2, y2, x3, y3: coordonnées
	int forme: la forme pour déterminer le déplacement
	return: int: 1 (Vrai), 0 (False) */
int meme_sens(int x1, int y1, int x2, int y2, int x3, int y3, int forme);
/*	test si la case (x3,y3) est un déploiement s'effectuant dans le même sens que de (x1,y1) à (x2,y2)
	int x1, y1, x2, y2, x3, y3: coordonnées
	int forme: la forme pour déterminer le déplacement
	return: int: 1 (Vrai), 0 (False) */
int deploiement_possible(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int type, int joueur);
/* 	test si le deploiement est possible
	point* point_1 point_2, point_3, point_4: les points utilisés par le déploiement
	int type: type de déploiement 1:+ 2:*
	int joueur: numéro du tour pour déterminer le joueur
	return: 1:(Vrai) 2:(Faux) */
void deploiement(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int str_len, int type);
/*	effectue un deploiement
	deploiement du point_1 jusqu'au point 4 en passant par les autres points (ou jusqu'au point 2 ou 3 si le deploiement est plus petit) 
	return: void */
int deplacement_possible2(plateau* p, int x1, int y1, int x2, int y2, int forme, int joueur);


int end_game(plateau* p, point* point, int joueur);
/*	teste une fin de partie éventuelle
	plateau* p: le plateau à tester
	point* point: les coordonnées de la piéce à tester
	int joueur: int qui permet de déteriminer quel joueur joue
	return: int: 1 (Vrai) 0 (False)*/
void so3(plateau* p, liste** l, int x, int y, int y2, int taille);
void se3(plateau* p, liste** l, int x, int y, int y2, int taille);
void no3(plateau* p, liste** l, int x, int y, int y2, int taille);
void ne3(plateau* p, liste** l, int x, int y, int y2, int taille);
void s3 (plateau* p, liste** l, int x, int y, int y2, int taille);
void n3 (plateau* p, liste** l, int x, int y, int y2, int taille);
void e3 (plateau* p, liste** l, int x, int y, int y2, int taille);
void o3 (plateau* p, liste** l, int x, int y, int y2, int taille);
int plus_de_pion(plateau* p, int joueur);
/* test si il ne reste qu'un pion à l'adversaire. Si c'est le cas, ses coordonnées sont renvoyées par last
	int joueur: numéro du tour pour déterminer le joueur
	return: int 1 (Vrai) 0 (Faux) */


/* Fonctions relatives aux listes
---------------------------------------------------------------------------------------------------------------------------------------*/
liste* init_liste(int x, int y);
/* alloue de l'espace pour une liste dont la valeur est x et y et dont le suivant est NULL
	int x,y: valeurs à entrer
	return: liste* */
void free_liste(liste* l);
/*	libére l'espace alloué à la liste
	liste* l: liste à libérer
	return void */
void append(liste** l, int x, int y);
/*	ajoute l'élément (x,y) à une liste
	int x,y: int à ajouter
	liste* l1: listes à modifier
	return void */
int est_present(liste* l, int x, int y);
/*	test si (x,y) est dans la liste
	liste* l: liste à tester
	return: int: 1 (Vrai) 0 (Faux) */
int est_present2(liste* l, int joueur);
/*	test si 0 ou 8 (selon le joueur) est dans la liste
	liste* l: liste à tester
	return: int: 1 (Vrai) 0 (Faux) */
int est_present3(liste* l, int y, point* point, int joueur);
/*	test si y est dans la liste
	liste* l: liste à tester
	point* point: point à initialiser si on a trouvé le y
	return: int: 1 (Vrai) 0 (Faux) */
liste* concat(liste* l1, liste* l2);
/*	concaténe deux listes
	liste* l1, l2: listes à concaténer
	return liste* */
void affiche_liste(liste* l); 
/*	affiche la liste
	liste* l: liste à afficher
	return void */
void random_point(liste* l, point** point_1);
/*	renvoie un point au hasard parmi ceux présent dans la liste */
