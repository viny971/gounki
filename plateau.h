#include "pion.h"

typedef struct plateau{
	pion* cell[8][8];
} plateau;

typedef struct liste{
/* liste ayant comme données la position d'un pion */
	int x;
	int y;
	struct liste* suivant;
} liste;

plateau* init_plateau();
int affiche_plateau(plateau* p);
void deplacement(plateau* p, int x1, int y1, int x2, int y2);
int trans_coord(char x);
int deplacement_possible(plateau* p, int x1, int y1, int x2, int y2, int forme, int joueur);
liste* deplacements_possibles(liste* l, int forme);
int deplacement_possible(plateau* p, int x1, int y1, int x2, int y2, int joueur);
void deplacements_possibles(plateau* p, liste** l, liste** l2, int forme, int joueur);
void composition(plateau* p, int x1,  int y1,  int x2,  int y2); 


liste* init_liste();
void free_liste(liste* l);
void append(liste** l, int x, int y);
int est_present(liste* l, int x, int y);
liste* concat(liste* l1, liste* l2);
void affiche_liste(liste* l); 
int meme_sens(int x1, int y1, int x2, int y2, int x3, int y3, int forme);
int deploiement_possible(plateau* p, char* line, int joueur);
void composition2(plateau* p, int x1, int y1, int forme);
void deplacement2(plateau* p, int x1, int y1, int forme, char* couleur);
void deploiement(plateau* p, char* line);
