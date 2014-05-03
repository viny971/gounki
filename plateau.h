#include "pion.h"
#include <math.h>

typedef struct plateau{
	pion* cell[8][8];
} plateau;

typedef struct liste{
/* liste ayant comme données la position d'un pion */
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

/* fonction relatives au plateau et à ses règles */
plateau* init_plateau();
void free_plateau(plateau* p);
int affiche_plateau(plateau* p, int tour);

void deplacement(plateau* p, point* point_1, point* point_2);
void deplacement2(plateau* p, int x1, int y1, int forme, int couleur);

int trans_coord(char x);

int deplacement_possible(plateau* p, point* point_1, point* point_2, int joueur);
void deplacements_possibles(plateau* p, liste** l, liste** l2, int forme, int x2, int y2, int joueur);
int coord_dans_tab(int x, int y);
/*	test si les coordonnées entrées ne dépassent pas les limites du tableau
	int x, y: coordonnées en x et y
	return: int: 1 = Vrai, 2 = False */
void composition(plateau* p, int x1,  int y1,  int x2,  int y2); 
void composition2(plateau* p, int x1, int y1, int forme);

int meme_sens(int x1, int y1, int x2, int y2, int x3, int y3, int forme);
int deploiement_possible(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int type, int joueur);
/* 	test si le deploiement est possible
	point* point_1 point_2, point_3, point_4: les points utilisés par le déploiement
	return: 1:(Vrai) 2:(Faux) */
void deploiement(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int str_len, int type);
/*	effectue un deploiement
	deploiement du point_1 jusqu'au point 4 en passant par les autres points (ou jusqu'au point 2 ou 3 si le deploiement est plus petit) 
	return: void */
int deplacement_possible2(plateau* p, int x1, int y1, int x2, int y2, int forme, int joueur);

/* Fonctions relatives au liste */
liste* init_liste();
void free_liste(liste* l);
void append(liste** l, int x, int y);
int est_present(liste* l, int x, int y);
liste* concat(liste* l1, liste* l2);
void affiche_liste(liste* l); 
