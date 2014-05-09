#ifndef PLATEAU_FILE
#define IA_FILE
#include "plateau.h"
#include <unistd.h>
#endif

int ia_random(plateau* p, point** point_1, point** point_2, point** point_3, point** point_4, int* size, int c);
int ia_basique(plateau* p, point** point_1, point** point_2, point** point_3, point** point_4, int* size, int c);
void liste_pion(plateau* p, liste** l, int joueur);
void so4(plateau* p, liste** l, int x, int y, int taille);
void se4(plateau* p, liste** l, int x, int y, int taille);
void no4(plateau* p, liste** l, int x, int y, int taille);
void ne4(plateau* p, liste** l, int x, int y, int taille);
void s4 (plateau* p, liste** l, int x, int y, int taille);
void n4 (plateau* p, liste** l, int x, int y, int taille);
void e4 (plateau* p, liste** l, int x, int y, int taille);
void o4 (plateau* p, liste** l, int x, int y, int taille);
void deplacements_envisageables(plateau* p, liste** l, point* point, int joueur);
/*	tous les déplacements que pourraient faire un pion */
