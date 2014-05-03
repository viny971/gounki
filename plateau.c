#include "plateau.h"

plateau* init_plateau(){
	int i,j;
	plateau* plateau = malloc(sizeof(pion*) * 8 * 8);
	for(j=0 ; j < 8 ; j += 2){
		plateau->cell[0][j] = init_pion(1,4);
		plateau->cell[0][j+1] = init_pion(1,1);
		plateau->cell[1][j+1] = init_pion(1,4);
		plateau->cell[1][j] = init_pion(1,1);
		plateau->cell[6][j] = init_pion(0,4);
		plateau->cell[6][j+1] = init_pion(0,1);
		plateau->cell[7][j+1] = init_pion(0,4);
		plateau->cell[7][j] = init_pion(0,1);
	}
	for(i = 2 ; i < 6 ; i++){
		for(j = 0 ; j < 8 ; j++){
			plateau->cell[i][j] = NULL;
		}
	}
	return plateau;
}

void free_plateau(plateau* p){
	int i,j;
	for(i = 0 ; i < 8 ; i++){
		for(j = 0 ; j < 8 ; j++){
			if(p->cell[i][j] != NULL){
				free_pion(p->cell[i][j]);
			}
		}
	}
	free(p);
}

int affiche_plateau(plateau* p, int tour){
	int i,j;
	printf("\n                    ______________________________________");
	printf("\n                                Partie de Gounki          ");
	printf("\n                                 Tour numéro %d           ", tour);
	printf("\n                    ______________________________________");
	printf("\n                        A   B   C   D   E   F   G   H");
	for(i = 0 ; i < 8 ; i++){
		printf("\n                    %d |", 8-i);
		for(j = 0 ; j < 8 ; j++){
			if(p->cell[i][j] == NULL){
				printf("   |");
			}
			else{
				affiche_pion(p->cell[i][j]);
			}
		}
		printf(" %d", 8-i);
		if(i!=7){
			printf("\n                       _______________________________");
		}
	}
	printf("\n                        A   B   C   D   E   F   G   H");
	printf("\n                    ______________________________________\n\n");
	return 0;
}

int trans_coord(char x){
	switch(x){
		case '1':
			return 0; break;
		case '2':
			return 1; break;
		case '3':
			return 2; break;
		case '4':
			return 3; break;
		case '5':
			return 4; break;
		case '6':
			return 5; break;
		case '7':
			return 6; break;
		case '8':
			return 7; break;

		case 'a':
		case 'A':
			return 0; break;
		case 'b':
		case 'B':
			return 1; break;
		case 'c':
		case 'C':
			return 2; break;
		case 'd':
		case 'D':
			return 3; break;
		case 'e':
		case 'E' :
			return 4; break;
		case 'f':
		case 'F':
			return 5; break;
		case 'g':
		case 'G':
			return 6; break;
		case 'h':
		case 'H':
			return 7; break;
		default:
			return -1; break;
	}
	return -1;
}

int deplacement_possible(plateau* p, point* point_1, point* point_2, int joueur){
/* retourne 1 si le déplacement est posible, 0 sinon.*/
	int rep;
/* transformation des coordonnées pour faciliter l'utilisation */
	int x1 = point_1->x;
	int y1 = point_1->y;
	int x2 = point_2->x;
	int	y2 = point_2->y;

	/* si la case de départ est vide */
	if(p->cell[y1][x1] == NULL){
		return 0;
	}
	/* si un des deux cases entrée n'est pas valide */
	if(x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1){
		return 0;
	}
	/* si la case de départ est la même que la case d'arrivée */
	if(x1 == x2 && y1 == y2){
		return 0;
	}
	/* vérifie que c'est bien un pion appartenant au joueur qui a joué */
	if(p->cell[y1][x1]->couleur == joueur % 2){
		return 0;
	}
	else{
		liste* l = init_liste(x1, y1);
		liste* l2 = init_liste(x1, y1);
		deplacements_possibles(p, &l, &l2, p->cell[y1][x1]->forme, x2, y2, joueur);
		rep = est_present(l, x2, y2);
		if(rep != 1){
			rep = est_present(l2, x2, y2);
		}
		free_liste(l);
		free_liste(l2);
		return rep;
	}
	return 1;
}

int coord_dans_tab(int x, int y){
	if(x > 8) return 0;
	if(x < 0) return 0;
	if(y > 8) return 0;
	if(y < 0) return 0;
	else return 1;
}


void deplacements_possibles(plateau* p, liste** l, liste** l2, int forme, int x2, int y2, int joueur){
/* retourne la liste des positions parcourables par la pièce */
	liste* i = *l;
	for(; i != NULL ; i = i->suivant){
		switch(forme){
			case 1:
				if(joueur % 2 == 0){
					if((p->cell[(i->y)+1][i->x] == NULL) || ((x2 == i->x) && (y2 == (i->y) + 1))){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x), (i->y)+1)){ 
							append(l, i->x, (i->y) + 1);
						}
					}
					if((p->cell[i->y][(i->x)+1] == NULL) || ((x2 == (i->x) + 1) && y2 == i->y)){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)+1, (i->y))){ 
							append(l, (i->x) + 1, i->y);
						}
					}
					if((p->cell[i->y][(i->x)-1] == NULL) || ((x2 == (i->x) - 1) && y2 == i->y)){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)-1, (i->y))){ 
							append(l, (i->x) - 1, i->y);
						}
					}
				}
				else{
					if((p->cell[(i->y)-1][i->x] == NULL) || ((x2 == i->x) && (y2 == (i->y) - 1))){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x), (i->y)-1)){ 
							append(l, i->x, (i->y) - 1);
						}
					}
					if((p->cell[i->y][(i->x)+1] == NULL) || ((x2 == (i->x) + 1) && y2 == i->y)){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)+1, (i->y))){ 
							append(l, (i->x) + 1, i->y);
						}
					}
					if((p->cell[i->y][(i->x)-1] == NULL) || ((x2 == (i->x) - 1) && y2 == i->y)){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)-1, (i->y))){ 
							append(l, (i->x) - 1, i->y);
						}
					}
				}
				break;

			case 2:
				deplacements_possibles(p, l, l2, 1, x2, y2, joueur);
				deplacements_possibles(p, l, l2, 1, x2, y2, joueur);
				break;

			case 3:
				deplacements_possibles(p, l, l2, 2, x2, y2, joueur);
				deplacements_possibles(p, l, l2, 1, x2, y2, joueur);
				break;

			case 4:
				if(joueur % 2 == 0){
					if((p->cell[(i->y)+1][(i->x)+1] == NULL) || ((x2 == (i->x) + 1) && (y2 == (i->y) + 1))){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)+1, (i->y)+1)){ 
							append(l, (i->x) + 1, (i->y) + 1);
						}
					}
					if((p->cell[(i->y)+1][(i->x)-1] == NULL) || ((x2 == (i->x) - 1) && (y2 == (i->y) + 1))){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)-1, (i->y)+1)){ 
							append(l, (i->x) - 1, (i->y) + 1);
						}
					}
				}
				else{
					if((p->cell[(i->y)-1][(i->x)+1] == NULL) || ((x2 == (i->x) + 1) && (y2 == (i->y) - 1))){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)+1, (i->y)-1)){ 
							append(l, (i->x) + 1, (i->y) - 1);
						}
					}
					if((p->cell[(i->y)-1][(i->x)-1] == NULL) || ((x2 == (i->x) - 1) && (y2 == (i->y) - 1))){
						/* test si les coordonnées sont dans les limites du tableau */
						if(coord_dans_tab((i->x)-1, (i->y)-1)){ 
							append(l, (i->x) - 1, (i->y) - 1);
						}
					}
				}
				break;

			case 5:
				deplacements_possibles(p, l, l2, 1, x2, y2, joueur); 
				deplacements_possibles(p, l2, l, 4, x2, y2, joueur);
				break;

			case 6:
				deplacements_possibles(p, l, l2, 2, x2, y2, joueur);
				deplacements_possibles(p, l2, l, 4, x2, y2, joueur);
				break;

			case 8:
				deplacements_possibles(p, l, l2, 4, x2, y2, joueur);
				deplacements_possibles(p, l, l2, 4, x2, y2, joueur);
				break;

			case 9:
				deplacements_possibles(p, l, l2, 1, x2, y2, joueur);
				deplacements_possibles(p, l2, l, 8, x2, y2, joueur);
				break;

			case 12:
				deplacements_possibles(p, l, l2, 4, x2, y2, joueur);
				deplacements_possibles(p, l, l2, 8, x2, y2, joueur);
				break;
		}
	}
}

void deplacement(plateau* p, point* point_1, point* point_2){
	pion* pion;
	int	x1 = point_1->x;
	int	y1 = point_1->y;
	int	x2 = point_2->x;
	int y2 = point_2->y;
	/* la case d'arrivée est un pion ami */
	if(p->cell[y2][x2] != NULL && (p->cell[y1][x1]->couleur == p->cell[y2][x2]->couleur)){
		composition(p,x1,y1,x2,y2);
	}
	/* la case d'arrivée est un pion ennemi */
	else if(p->cell[y2][x2] != NULL && (p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur)){
		pion = p->cell[y2][x2];
		p->cell[y2][x2] = p->cell[y1][x1];
		free_pion(pion);
	}
	/* la case d'arrivée est vide */
	else{
		p->cell[y2][x2] = p->cell[y1][x1];
	}
	p->cell[y1][x1] = NULL;
}

void deplacement2(plateau* p, int x1, int y1, int forme, int couleur) {
	if(p->cell[y1][x1] != NULL){
		composition2(p,x1,y1,forme);
	}
	else{
		p->cell[y1][x1] = init_pion(couleur,forme);
	}
}

void composition(plateau* p, int x1, int y1, int x2, int y2){	
/* fonction de composition de deux pions d'une même couleur */
	int a;

	if(p->cell[y1][x1] == NULL || p->cell[y2][x2] == NULL){
		fprintf(stdout, "Erreur mon gars");
	}
	a = p->cell[y1][x1]->taille + p->cell[y2][x2]->taille;
	if(a <= 3){
		p->cell[y2][x2]->taille = a;
		p->cell[y2][x2]->forme = p->cell[y1][x1]->forme + p->cell[y2][x2]->forme;
		p->cell[y1][x1] = NULL;
	}
}

void composition2(plateau* p, int x1, int y1, int forme){
	p->cell[y1][x1]->taille += 1;
	p->cell[y1][x1]->forme += forme;
}

int meme_sens(int x1, int y1, int x2, int y2, int x3, int y3, int forme) {
	if(forme == 1){
		if((x1 == x2 && x2 != x3) || ((y1 == y2) && ((y2 != y3) || (x3 == x2) || (x3 == x1)))) return 0;
	}
	else if(forme == 4){
		if((x2 == x1 + 1 && x3 != x2 + 1) || (x2 == x1 - 1 && x3 != x2 - 1)) return 0;
	}
	return 1;		
}

int deploiement_possible(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int type, int joueur) {
	int forme;
	/* transformation des coordonnées pour une utilisation simplifiée */
	int x1 = point_1->x;
	int	y1 = point_1->y;
	int	x2 = point_2->x;
	int	y2 = point_2->y;
	int	x3 = point_3->x;
	int	y3 = point_3->y;
	int	x4 = point_4->x;
	int	y4 = point_4->y;

	if(p->cell[y1][x1] == NULL) return 0;
	else forme = p->cell[y1][x1]->forme;

	if(type == 1) {
		switch(forme){
			case 2:
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) ||!meme_sens(x1,y1,x2,y2,x3,y3,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				break;

			case 3:
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,1,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,1) || !meme_sens(x2,y2,x3,y3,x4,y4,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;

			case 5:
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}

				break;

			case 6:
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,4,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;

			case 9:
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,4,joueur)
						|| !meme_sens(x2,y2,x3,y3,x4,y4,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;
		}	
	}

	else if(type == 2) {
		switch(forme){
			case 8:
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) ||!meme_sens(x1,y1,x2,y2,x3,y3,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				break;

			case 12:
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,4,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,4) || !meme_sens(x2,y2,x3,y3,x4,y4,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;

			case 5:
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}

				break;

			case 9:
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,1,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;

			case 6:
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,1,joueur)
						|| !meme_sens(x2,y2,x3,y3,x4,y4,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;
		}	
	}
	return 1;
}

int deplacement_possible2(plateau* p, int x1, int y1, int x2, int y2, int forme, int joueur){
	switch(forme){
		case 1:
			if((x1 != x2 && y1 != y2) || fabs(x1-x2) > 1 || fabs(y1-y2) > 1) return 0;
			break;
		case 2:
			if((x1 != x2 && y1 != y2) || fabs(x1-x2) > 2 || fabs(y1-y2) > 2) return 0;
			break;

		case 3:
			if((x1 != x2 && y1 != y2) || fabs(x1-x2) > 3 || fabs(y1-y2) > 3) return 0;
			break;

		case 4:
			if((x1 == x2 || y1 == y2) || fabs(x1-x2) > 1) return 0;
			break;

		case 8:
			if((x1 == x2 || y1 == y2) || fabs(x1-x2) > 2) return 0;
			break;

		case 12:
			if((x1 == x2 || y1 == y2) || fabs(x1-x2) > 3) return 0;
			break;

		case 5:
			if(fabs(x1-x2) > 1 || fabs(y1-y2) > 1) return 0;
			break;

		case 9:
			if(((y2-y1 == 0 || fabs(y2-y1) == 1)  && fabs(x1-x2) > 1) || (fabs(y1-y2) == 2 && fabs(x1-x2) != 2) || (fabs(y1-y2) > 2)) return 0;
			break;

		case 6:
			if(((y1 == y2) && fabs(x1-x2) > 2) || (fabs(y1-y2) == 1 && fabs(x1-x2) > 1) || (fabs(y1-y2) == 2 && x1 != x2) || (fabs(y1-y2) > 2)) return 0;
			break;
	}
	return 1;
}

void deploiement(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int str_len, int type) {
	int forme, couleur;
	/* transformation des coordonées pour une utilisation simplifiée */
	int	x1 = point_1->x;
	int	y1 = point_1->y;
	int	x2 = point_2->x;
	int	y2 = point_2->y;
	int	x3 = point_3->x;
	int	y3 = point_3->y;
	int	x4 = point_4->x;
	int	y4 = point_4->y;

	forme = p->cell[y1][x1]->forme;
	couleur = p->cell[y1][x1]->couleur;

	if(str_len == 9) {
		if(type == 1){
			if(forme == 2){
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,1,couleur);
			}
			else if(forme == 5) {
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,4,couleur);
			}		
		}
		else if(type == 2){
			if(forme == 8){
				deplacement2(p,x2,y2,4,couleur);
				deplacement2(p,x3,y3,4,couleur);
			}
			else if(forme == 5){
				deplacement2(p,x2,y2,4,couleur);
				deplacement2(p,x3,y3,1,couleur);
			}
		}
	}
	else if(str_len == 12) {
		if(type == 1){
			if(forme == 3){
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,1,couleur);
				deplacement2(p,x4,y4,1,couleur);
			}
			else if(forme == 6){
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,1,couleur);
				deplacement2(p,x4,y4,4,couleur);
			}
			else if(forme == 9){
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,4,couleur);
				deplacement2(p,x4,y4,4,couleur);
			}
		}
		else if(type == 2){
			if(forme == 12){
				deplacement2(p,x2,y2,4,couleur);
				deplacement2(p,x3,y3,4,couleur);
				deplacement2(p,x4,y4,4,couleur);
			}
			else if(forme == 9){
				deplacement2(p,x2,y2,4,couleur);
				deplacement2(p,x3,y3,4,couleur);
				deplacement2(p,x4,y4,1,couleur);
			}
			else if(forme == 6){
				deplacement2(p,x2,y2,4,couleur);
				deplacement2(p,x3,y3,1,couleur);
				deplacement2(p,x4,y4,1,couleur);
			}
		}

	}
	p->cell[y1][x1] = NULL;
}
