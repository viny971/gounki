#include "ia.h"

int ia_basique(plateau* p, point** point_1, point** point_2, point** point_3, point** point_4, int* size, int c){
	/* initialisation d'une liste de tous les pions restants du robot */
	liste* l = NULL;
	liste* l2 = NULL;
	liste_pion(p, &l, c);
	while(1){
		/* détecte si un pion est proche de la victoire */
		if(c % 2 == 0){
			if(est_present3(l, 0, *point_1, c)){
				if(end_game(p, *point_1, (c+1))){
					return 3;
				}
			}
		}
		else if(c % 2 == 1){
			if(est_present3(l, 7, *point_1, c)){
				if(end_game(p, *point_1, (c+1))){
					return 3;
				}
			}
		}
		/* sélection aléatoire d'un des pions parmi la liste */
		random_point(l, point_1);
		/* création de la liste des coups envisageables pour ce pion) */
		deplacements_envisageables(p, &l2, *point_1, c);
		if(c % 2 == 0){
			if(est_present3(l2, 0, *point_2, c)){
				if(deplacement_possible(p, *point_1, *point_2, (c+1))){
					return 1;
				}
			}
		}
		if(c % 2 == 1){
			if(est_present3(l2, 7, *point_2, c)){
				if(deplacement_possible(p, *point_1, *point_2, (c+1))){
					return 1;
				}
			}
		}
		/* au lieu de choisir aléatoirement, on essaie d'aller le plus loin possible */
		if(c % 2 == 0){
			if(!est_present3(l2, ((*point_1)->y) - 3, *point_2, c)){
				if(!est_present3(l2, ((*point_1)->y) - 2, *point_2, c)){
					est_present3(l2, ((*point_1)->y) - 1, *point_2, c);
				}
			}
		}
		if(c % 2 == 1){
			if(!est_present3(l2, ((*point_1)->y) + 3, *point_2, c)){
				if(!est_present3(l2, ((*point_1)->y) + 2, *point_2, c)){
					est_present3(l2, ((*point_1)->y) + 1, *point_2, c);
				}
			}
		}
		else{
			random_point(l2, point_2);
		}
		if(deplacement_possible(p, *point_1, *point_2, (c+1))){
			return 1;
		}
	}
	return -1;
}

int ia_random(plateau* p, point** point_1, point** point_2, point** point_3, point** point_4, int* size, int c){
	/* initialisation d'une liste de tous les pions restants du robot */
	liste* l = NULL;
	liste* l2 = NULL;
	sleep(1);
	liste_pion(p, &l, c);
	while(1){
		/* sélection aléatoire d'un des pions parmi la liste */
		random_point(l, point_1);
		if(c % 2 == 0){
			if((*point_1)->y == 0){
				return 3;
			}
		}
		if(c % 2 == 1){
			if((*point_1)->y == 7){
				return 3;
			}
		}
		/* création de la liste des coups envisageables pour ce pion) */
		deplacements_envisageables(p, &l2, *point_1, c);
		/* sélection aléatoire d'un des mouvements possibles de la liste */
		random_point(l2, point_2);
		if(deplacement_possible(p, *point_1, *point_2, (c+1))){
			fprintf(stdout,"(%d,%d) -> (%d,%d)", (*point_1)->x, (*point_1)->y, (*point_2)->x, (*point_2)->y);
			return 1;
		}
	}
	return -1;
}

void liste_pion(plateau* p, liste** l, int joueur){
	int i,j;
	for(i = 0 ; i < 8 ; i++){
		for(j = 0 ; j < 8 ; j++){
			if((p->cell[i][j] != NULL) && ((joueur) % 2 == p->cell[i][j]->couleur)){
				append(l, j, i);
			}
		}
	}
}

void deplacements_envisageables(plateau* p, liste** l, point* point, int joueur){
	/* retourne la liste des positions parcourables par la pièce */
	/* coordonnées de départ */
	int x, y;  
	x = point->x;
	y = point->y;
	joueur ++;

	switch(p->cell[y][x]->forme){
		case 1:
			if(joueur % 2 == 0){
				s4(p, l, x, y, 1);
				o4(p, l, x, y, 1);
				e4(p, l, x, y, 1);
			}
			else{
				n4(p, l, x, y, 1);
				o4(p, l, x, y, 1);
				e4(p, l, x, y, 1);
			}
			break;

		case 2:
			if(joueur % 2 == 0){
				s4(p, l, x, y, 2);
				o4(p, l, x, y, 2);
				e4(p, l, x, y, 2);
			}
			else{
				n4(p, l, x, y, 3);
				o4(p, l, x, y, 3);
				e4(p, l, x, y, 3);
			}
			break;

		case 3:
			if(joueur % 2 == 0){
				s4(p, l, x, y, 3);
				o4(p, l, x, y, 3);
				e4(p, l, x, y, 3);
			}
			else{
				n4(p, l, x, y, 3);
				o4(p, l, x, y, 3);
				e4(p, l, x, y, 3);
			}
			break;

		case 4:
			if(joueur % 2 == 0){
				se4(p, l, x, y, 1);
				so4(p, l, x, y, 1);
			}
			else{
				no4(p, l, x, y, 1);
				ne4(p, l, x, y, 1);
			}
			break;

		case 5:
			if(joueur % 2 == 0){
				se4(p, l, x, y, 1);
				so4(p, l, x, y, 1);
				s4(p, l, x, y, 1);
				o4(p, l, x, y, 1);
				e4(p, l, x, y, 1);
			}
			else{
				no4(p, l, x, y, 1);
				ne4(p, l, x, y, 1);
				n4(p, l, x, y, 1);
				o4(p, l, x, y, 1);
				e4(p, l, x, y, 1);
			}
			break;

		case 6:
			if(joueur % 2 == 0){
				se4(p, l, x, y, 1);
				so4(p, l, x, y, 1);
				s4(p, l, x, y, 2);
				o4(p, l, x, y, 2);
				e4(p, l, x, y, 2);
			}
			else{
				no4(p, l, x, y, 1);
				ne4(p, l, x, y, 1);
				n4(p, l, x, y, 3);
				o4(p, l, x, y, 3);
				e4(p, l, x, y, 3);
			}
			break;

		case 8:
			if(joueur % 2 == 0){
				se4(p, l, x, y, 2);
				so4(p, l, x, y, 2);
			}
			else{
				no4(p, l, x, y, 2);
				ne4(p, l, x, y, 2);
			}
			break;

		case 9:
			if(joueur % 2 == 0){
				se4(p, l, x, y, 2);
				so4(p, l, x, y, 2);
				s4(p, l, x, y, 1);
				o4(p, l, x, y, 1);
				e4(p, l, x, y, 1);
			}
			else{
				no4(p, l, x, y, 2);
				ne4(p, l, x, y, 2);
				n4(p, l, x, y, 1);
				o4(p, l, x, y, 1);
				e4(p, l, x, y, 1);
			}
			break;

		case 12:
			if(joueur % 2 == 0){
				se4(p, l, x, y, 3);
				so4(p, l, x, y, 3);
			}
			else{
				no4(p, l, x, y, 3);
				ne4(p, l, x, y, 3);
			}
			break;
	}
}

void so4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y + i)){ 
			append(l, x - i, y + i);
		}
	}
}
void se4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y + i)){ 
			append(l, x + i, y + i);
		}
	}
}
void no4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y - i)){ 
			append(l, x - i, y - i);
		}
	}
}
void ne4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y - i)){ 
			append(l, x + i, y - i);
		}
	}
}
void s4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y + i)){ 
			append(l, x, y + i);
		}
	}
}

void n4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y - i)){ 
			append(l, x, y - i);
		}
	}
}
void e4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y)){ 
			append(l, x + i, y);
		}
	}
}
void o4(plateau* p, liste** l, int x, int y, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y)){ 
			append(l, x - i, y);
		}
	}
}
