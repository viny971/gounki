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

int coord_dans_tab(int x, int y){
	if(x >= 8) return 0;
	if(x < 0) return 0;
	if(y >= 8) return 0;
	if(y < 0) return 0;
	else return 1;
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
	/* vérifie qu'on reste dans le tableau */
	if((!coord_dans_tab(x1,y1)) || (!coord_dans_tab(x2,y2))){
		return 0;
	}
	/* si un des deux cases entrée n'est pas valide */
	if(x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1){
		return 0;
	}
	/* vérifie que c'est bien un pion appartenant au joueur qui a joué */
	if(p->cell[y1][x1]->couleur == joueur % 2){
		return 0;
	}
	/* cas du déplacement nul avec un double/triple carré */
	if((x1 == 1 || x1 == 6) && (x1 == x2 && y1 == y2) && (p->cell[y1][x1]->forme == 2 || p->cell[y1][x1]->forme == 3 || p->cell[y1][x1]->forme == 6)){
		return 1;
	}
	/* vérifie que la somme des tailles ne dépasse pas 3*/
	if((p->cell[y2][x2] != NULL) && (p->cell[y1][x1]->couleur == p->cell[y2][x2]->couleur) && (p->cell[y1][x1]->taille + p->cell[y2][x2]->taille > 3)){
		return 0;
	}
	/* si la case de départ est la même que la case d'arrivée et qu'il n'y a pas eu de rebond */
	if(x1 == x2 && y1 == y2){
		return 0;
	}
	/* vérifie si c'est un rebond */
	if(rebond_possible1(p,point_1,point_2)){
			return 1;
	}		
	else{
		liste* l = init_liste(x1, y1);
		deplacements_possibles(p, &l, p->cell[y1][x1]->forme, x2, y2, joueur);
		rep = est_present(l, x2, y2);
		free_liste(l);
		return rep;
	}
	return 0;
}

void so(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y + i)){ 
			if((p->cell[y+i][x-i] == NULL) || ((x2 == x - i) && (y2 == y + i))){
				append(l, x - i, y + i);
			}
			else{
				break;
			}
		}
	}
}
void se(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y + i)){ 
			if((p->cell[y+i][x+i] == NULL) || ((x2 == x+i) && (y2 == y + i))){
				append(l, x + i, y + i);
			}
			else{
				break;
			}
		}
	}
}
void no(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y - i)){ 
			if((p->cell[y-i][x-i] == NULL) || ((x2 == x - i) && (y2 == y - i))){
				append(l, x - i, y - i);
			}
			else{
				break;
			}
		}
	}
}
void ne(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y - i)){ 
			if((p->cell[y-i][x+i] == NULL) || ((x2 == x+i) && (y2 == y - i))){
				append(l, x + i, y - i);
			}
			else{
				break;
			}
		}
	}
}
void s(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y + i)){ 
			if((p->cell[y+i][x] == NULL) || ((x2 == x) && (y2 == y + i))){
				append(l, x, y + i);
			}
			else{
				break;
			}
		}
	}
}

void n(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y - i)){ 
			if((p->cell[y-i][x] == NULL) || ((x2 == x) && (y2 == y - i))){
				append(l, x, y - i);
			}
			else{
				break;
			}
		}
	}
}
void e(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y)){ 
			if((p->cell[y][x+i] == NULL) || ((x2 == x + i) && (y2 == y))){
				append(l, x + i, y);
			}
			else{
				break;
			}
		}
	}
}
void o(plateau* p, liste** l, int x, int y, int x2, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y)){ 
			if((p->cell[y][x-i] == NULL) || ((x2 == x - i) && (y2 == y))){
				append(l, x - i, y);
			}
			else{
				break;
			}
		}
	}
}
void deplacements_possibles(plateau* p, liste** l, int forme, int x2, int y2, int joueur){
	/* retourne la liste des positions parcourables par la pièce */
	/* coordonnées de départ */
	int x, y, taille;  
	x = (*l)->x;
	y = (*l)->y;
	taille = p->cell[y][x]->taille;

	switch(forme){
		case 1:
		case 2:
		case 3:
			if(joueur % 2 == 0){
				s(p, l, x, y, x2, y2, taille);
				o(p, l, x, y, x2, y2, taille);
				e(p, l, x, y, x2, y2, taille);
			}
			else{
				n(p, l, x, y, x2, y2, taille);
				o(p, l, x, y, x2, y2, taille);
				e(p, l, x, y, x2, y2, taille);
			}
			break;
		case 4:
		case 8:
		case 12:
			if(joueur % 2 == 0){
				se(p, l, x, y, x2, y2, taille);
				so(p, l, x, y, x2, y2, taille);
			}
			else{
				no(p, l, x, y, x2, y2, taille);
				ne(p, l, x, y, x2, y2, taille);
			}
			break;

		case 5:
			if(joueur % 2 == 0){
				se(p, l, x, y, x2, y2, 1);
				so(p, l, x, y, x2, y2, 1);
				s(p, l, x, y, x2, y2, 1);
				o(p, l, x, y, x2, y2, 1);
				e(p, l, x, y, x2, y2, 1);
			}
			else{
				no(p, l, x, y, x2, y2, 1);
				ne(p, l, x, y, x2, y2, 1);
				n(p, l, x, y, x2, y2, 1);
				o(p, l, x, y, x2, y2, 1);
				e(p, l, x, y, x2, y2, 1);
			}
			break;

		case 6:
			if(joueur % 2 == 0){
				se(p, l, x, y, x2, y2, 1);
				so(p, l, x, y, x2, y2, 1);
				s(p, l, x, y, x2, y2, 2);
				o(p, l, x, y, x2, y2, 2);
				e(p, l, x, y, x2, y2, 2);
			}
			else{
				no(p, l, x, y, x2, y2, 1);
				ne(p, l, x, y, x2, y2, 1);
				n(p, l, x, y, x2, y2, 3);
				o(p, l, x, y, x2, y2, 3);
				e(p, l, x, y, x2, y2, 3);
			}
			break;
		case 9:
			if(joueur % 2 == 0){
				se(p, l, x, y, x2, y2, 2);
				so(p, l, x, y, x2, y2, 2);
				s(p, l, x, y, x2, y2, 1);
				o(p, l, x, y, x2, y2, 1);
				e(p, l, x, y, x2, y2, 1);
			}
			else{
				no(p, l, x, y, x2, y2, 2);
				ne(p, l, x, y, x2, y2, 2);
				n(p, l, x, y, x2, y2, 1);
				o(p, l, x, y, x2, y2, 1);
				e(p, l, x, y, x2, y2, 1);
			}
			break;
	}
}

void deplacement(plateau* p, point* point_1, point* point_2){
	pion* pion;
	int	x1 = point_1->x; int y1 = point_1->y; int x2 = point_2->x; int y2 = point_2->y; 
	/* cas du deplacement nul avec un double carré */
	if((x1 == 1 || x1 == 6) && (x1 == x2 && y1 == y2) && (p->cell[y1][x1]->forme == 2 || p->cell[y1][x1]->forme == 3 || p->cell[y1][x1]->forme == 6)){
		return;
	}
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

int meme_sens1(int x1, int y1, int x2, int y2, int x3, int y3, int forme) {
	if(forme == 1){
		if((x1 == x2) && (x2 == x3) && (y1 - 1 == y2) && (y2 - 1 == y3)) return 1;
		if((x1 == x2 && x2 != x3) || ((y1 == y2) && ((y2 != y3) || (x3 == x2) || (x3 == x1)))) return 0;
	}
	else if(forme == 4){
		if((x2 == x1 + 1 && x3 != x2 + 1) || (x2 == x1 - 1 && x3 != x2 - 1)) return 0;
	}
	return 1;		
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
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) ||!meme_sens(x1,y1,x2,y2,x3,y3,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				break;

			case 3:
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,1,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,1) || !meme_sens(x2,y2,x3,y3,x4,y4,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 3) return 0;
				}
				break;

			case 5:
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}

				break;

			case 6:
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,4,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 3) return 0;
				}
				break;

			case 9:
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,4,joueur)
						|| !meme_sens(x2,y2,x3,y3,x4,y4,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 3) return 0;
				}
				break;
		}	
	}

	else if(type == 2) {
		switch(forme){
			case 8:
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) ||!meme_sens(x1,y1,x2,y2,x3,y3,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				break;

			case 12:
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,4,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,4) || !meme_sens(x2,y2,x3,y3,x4,y4,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 3) return 0;
				}
				break;

			case 5:
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}

				break;

			case 9:
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,1,joueur)
						|| !meme_sens(x1,y1,x2,y2,x3,y3,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 3) return 0;
				}
				break;

			case 6:
				if(rebond_possible2(p,point_1,point_2,point_3,point_4,joueur)) return 1;
				if(!deplacement_possible2(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible2(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible2(p,x3,y3,x4,y4,1,joueur)
						|| !meme_sens(x2,y2,x3,y3,x4,y4,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 3) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 3) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 3) return 0;
				}
				break;
		}	
	}
	return 1;
}


int deplacement_possible2(plateau* p, int x1, int y1, int x2, int y2, int forme, int joueur){
	
 	point* point_1 = malloc(sizeof(point));
 	point* point_2 = malloc(sizeof(point));

	/*if(p->cell[y1][x1] == NULL) return 0;*/
	
	if(joueur % 2 != 0){
		if(y2 > y1) return 0;
	}
	else if(joueur % 2 == 0){
		if(y2 < y1) return 0;
	}
	
	point_1->x = x1;
	point_1->y = y1;
	point_2->x = x2;
	point_2->y = y2;

	if(p->cell[y1][x1] != NULL) {
		if(rebond_possible1(p,point_1,point_2)){
			free(point_1);
			free(point_2);
			return 1;
		}		
	}

	free(point_1);
	free(point_2);

	if(x1 == x2 && y1 == y2) return 0;

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
			if((x1 == x2 || y1 == y2) || (fabs(x1-x2) != fabs(y1-y2)) || (fabs(x1-x2) > 2)) return 0;
			break;

		case 12:
			if((x1 == x2 || y1 == y2) || (fabs(x1-x2) != fabs(y1-y2)) || (fabs(x1-x2) > 3)) return 0;
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

void deploiement(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int str_len, int type, int joueur) {
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
				if(rebond_possible2(p, point_1, point_2, point_3, point_4, joueur)){
					deplacement2(p,x2,y2,1,couleur);
					p->cell[y1][x1]->forme = 1;
					p->cell[y1][x1]->taille = 1;
					return;
				}
				else{
					deplacement2(p,x2,y2,1,couleur);
					deplacement2(p,x3,y3,1,couleur);
				}
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
				if((x1 == 1 || x1 == 6) && rebond_possible2(p, point_1, point_2, point_3, point_4, joueur)){
					deplacement2(p,x2,y2,1,couleur);
					deplacement2(p,x4,y4,1,couleur);
					p->cell[y1][x1]->forme = 1;
					p->cell[y1][x1]->taille = 1;
					return;
				}
				else{
					deplacement2(p,x2,y2,1,couleur);
					deplacement2(p,x3,y3,1,couleur);
					deplacement2(p,x4,y4,1,couleur);
				}
			}
			else if(forme == 6){
				if(rebond_possible2(p, point_1, point_2, point_3, point_4, joueur)){
					deplacement2(p,x2,y2,1,couleur);
					deplacement2(p,x4,y4,4,couleur);
					p->cell[y1][x1]->forme = 1;
					p->cell[y1][x1]->taille = 1;
					return;
				}
				else{
					deplacement2(p,x2,y2,1,couleur);
					deplacement2(p,x3,y3,1,couleur);
					deplacement2(p,x4,y4,4,couleur);
				}
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

int end_game(plateau* p, point* point_1, int joueur){
	int x = point_1->x; int y = point_1->y; int rep;
	liste* l;
	l = init_liste(x, y);
	rep = 0;
	if(p->cell[y][x] == NULL){
		return 0;
	}
	if(deploiement_possible2(p, point_1, 1, joueur) || deploiement_possible2(p, point_1, 2, joueur)){
		return 1;
	}
	switch(p->cell[y][x]->forme){
		case 1:
			if(joueur % 2 == 0){
				s3(p, &l, x, y, 8, 1);
				o3(p, &l, x, y, 8, 1);
				e3(p, &l, x, y, 8, 1);
			}
			else{
				n3(p, &l, x, y, -1, 1);
				o3(p, &l, x, y, -1, 1);
				e3(p, &l, x, y, -1, 1);
			}
			break;

		case 2:
			if(joueur % 2 == 0){
				s3(p, &l, x, y, 8, 2);
				o3(p, &l, x, y, 8, 2);
				e3(p, &l, x, y, 8, 2);
			}
			else{
				n3(p, &l, x, y, -1, 2);
				o3(p, &l, x, y, -1, 2);
				e3(p, &l, x, y, -1, 2);
			}
			break;

		case 3:
			if(joueur % 2 == 0){
				s3(p, &l, x, y, 8, 3);
				o3(p, &l, x, y, 8, 3);
				e3(p, &l, x, y, 8, 3);
			}
			else{
				n3(p, &l, x, y, -1, 3);
				o3(p, &l, x, y, -1, 3);
				e3(p, &l, x, y, -1, 3);
			}
			break;

		case 4:
			if(joueur % 2 == 0){
				se3(p, &l, x, y, 8, 1);
				so3(p, &l, x, y, 8, 1);
			}
			else{
				no3(p, &l, x, y, -1, 1);
				ne3(p, &l, x, y, -1, 1);
			}
			break;

		case 5:
			if(joueur % 2 == 0){
				se3(p, &l, x, y, 8, 1);
				so3(p, &l, x, y, 8, 1);
				s3(p, &l, x, y, 8, 1);
				o3(p, &l, x, y, 8, 1);
				e3(p, &l, x, y, 8, 1);
			}
			else{
				no3(p, &l, x, y, -1, 1);
				ne3(p, &l, x, y, -1, 1);
				n3(p, &l, x, y, -1, 1);
				o3(p, &l, x, y, -1, 1);
				e3(p, &l, x, y, -1, 1);
			}
			break;

		case 6:
			if(joueur % 2 == 0){
				se3(p, &l, x, y, 8, 1);
				so3(p, &l, x, y, 8, 1);
				s3(p, &l, x, y, 8, 2);
				o3(p, &l, x, y, 8, 2);
				e3(p, &l, x, y, 8, 2);
			}
			else{
				no3(p, &l, x, y, -1, 1);
				ne3(p, &l, x, y, -1, 1);
				n3(p, &l, x, y, -1, 3);
				o3(p, &l, x, y, -1, 3);
				e3(p, &l, x, y, -1, 3);
			}
			break;

		case 8:
			if(joueur % 2 == 0){
				se3(p, &l, x, y, 8, 2);
				so3(p, &l, x, y, 8, 2);
			}
			else{
				no3(p, &l, x, y, -1, 2);
				ne3(p, &l, x, y, -1, 2);
			}
			break;

		case 9:
			if(joueur % 2 == 0){
				se3(p, &l, x, y, 8, 2);
				so3(p, &l, x, y, 8, 2);
				s3(p, &l, x, y, 8, 1);
				o3(p, &l, x, y, 8, 1);
				e3(p, &l, x, y, 8, 1);
			}
			else{
				no3(p, &l, x, y, -1, 2);
				ne3(p, &l, x, y, -1, 2);
				n3(p, &l, x, y, -1, 1);
				o3(p, &l, x, y, -1, 1);
				e3(p, &l, x, y, -1, 1);
			}
			break;

		case 12:
			if(joueur % 2 == 0){
				se3(p, &l, x, y, 8, 3);
				so3(p, &l, x, y, 8, 3);
			}
			else{
				no3(p, &l, x, y, -1, 3);
				ne3(p, &l, x, y, -1, 3);
			}
			break;
	}
	rep = est_present2(l, joueur);

	free_liste(l);
	return rep;
} 

void so3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y)){ 
			if((p->cell[y+i][x-i] == NULL) || (y2 == y + i)){
				append(l, x - i, y + i);
			}
			else{
				break;
			}
		}
	}
}
void se3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y)){ 
			if((p->cell[y+i][x+i] == NULL) || (y2 == y + i)){
				append(l, x + i, y + i);
			}
			else{
				break;
			}
		}
	}
}
void no3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y)){ 
			if((p->cell[y-i][x-i] == NULL) || (y2 == y - i)){
				append(l, x - i, y - i);
			}
			else{
				break;
			}
		}
	}
}
void ne3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y)){ 
			if((p->cell[y-i][x+i] == NULL) || (y2 == y - i)){
				append(l, x + i, y - i);
			}
			else{
				break;
			}
		}
	}
}
void s3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y)){ 
			if((p->cell[y+i][x] == NULL) || (y2 == y + i)){
				append(l, x, y + i);
			}
			else{
				break;
			}
		}
	}
}

void n3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y)){ 
			if((p->cell[y-i][x] == NULL) || (y2 == y - i)){
				append(l, x, y - i);
			}
			else{
				break;
			}
		}
	}
}
void e3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x + i, y)){ 
			if((p->cell[y][x+i] == NULL) || (y2 == y)){
				append(l, x + i, y);
			}
			else{
				break;
			}
		}
	}
}
void o3(plateau* p, liste** l, int x, int y, int y2, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x - i, y)){ 
			if((p->cell[y][x-i] == NULL) || (y2 == y)){
				append(l, x - i, y);
			}
			else{
				break;
			}
		}
	}
}
int plus_de_pion(plateau* p, int joueur){
	int i, j;
	for(i = 0 ; i < 8 ; i++){
		for(j = 0 ; j < 8 ; j++){
			if((p->cell[i][j] != NULL) && ((joueur) % 2 == p->cell[i][j]->couleur)){
				return 0;
			}
		}
	}
	return 1;
}

int rebond_possible1(plateau* p, point* point_1, point* point_2) {

	/*Test si un rebond est possible lors d'un déplacement*/

	int taille, forme;
	int x1 = point_1->x;
	int y1 = point_1->y;
	int x2 = point_2->x;
	int y2 = point_2->y;
	taille = p->cell[y1][x1]->taille;
	forme = p->cell[y1][x1]->forme;

	if(x1 == 0 || x1 == 7) return 0;
	if(taille == 1 || forme == 5) return 0;

	switch(forme){
		case 2:
		case 6:
			if((x1 == 1 || x1 == 6) && (x1 == x2 && y1 == y2)) return 1;
			break;
		case 8:
		case 9:
			if((x1 == 1 || x1 == 6) && (x1 == x2 && (y2 == y1+2 || y2 == y1-2))) return 1;
			/*if(x1 == 1 && x2 == 1 && y2 == y1+2) return 1;
			else if(x1 == 6 && x2 == 6 && y2 == y1+2) return 1;*/
			break;
		case 12:
			if((x1 == 1 && (x2 == 2 || x2 == 1) && (y2 == y1+3 || y2 == y1-3 || y2 == y1+2 || y2 == y1-2))
			|| (x1 == 2 && x2 == 1 && (y2 == y1+3 || y2 == y1-3))
			|| (x1 == 5 && x2 == 6 && (y2 == y1+3 || y2 == y1-3))
			|| (x1 == 6 && (x2 == 5 || x2 == 6) && (y2 == y1+3 || y2 == y1-3 || y2 == y1+2 || y2 == y1-2))) return 1;
			break;
		default:
			return 0;
	}		

	return 0;		
}

int rebond_possible2(plateau* p, point* point_1, point* point_2, point* point_3, point* point_4, int joueur){
	/*Test si un rebond est possible lors d'un déplacement*/
	int forme, taille;
	int x1 = point_1->x;
	int y1 = point_1->y;
	int x2 = point_2->x;
	int y2 = point_2->y;
	int x3 = point_3->x;
	int y3 = point_3->y;
	int x4 = point_4->x;
	int y4 = point_4->y;

	taille = p->cell[y1][x1]->taille;
	forme = p->cell[y1][x1]->forme;

	if(taille == 1 || forme == 5) return 0;

	switch(forme){
		case 2:
			if(((x1 == 1 && x2 == x1-1 && x3 == x1) || (x1 == 6 && x2 == x1+1 && x3 == x1)) && (y2 == y1 && y3 == y1)) return 1;
			break;
		case 3:
			if(((x1 == 1 && x2 == x1-1 && x3 == x1 && x4 == x1+1)
						|| (x1 == 2 && x2 == x1-1 && x3 == x1-2 && x4 == x1-1)
						|| (x1 == 6 && x2 == x1+1 && x3 == x1 && x4 == x1-1)
						|| (x1 == 5 && x2 == x1+1 && x3 == x1+2 && x4 == x1+1))
					&& (y2 == y1 && y3 == y1 && y4 == y1)) return 1;
			break;
		case 8:
			if(((x1 == 1 && x2 == x1-1 && x3 == x1) || (x1 == 6 && x2 == x1+1 && x3 == x1)) 
					&& ((y2 == y1-1 && y3 == y1-2) || (y2 == y1+1 && y3 == y1+2))) return 1;
			break;
		case 12:
			if(((x1 == 1 && x2 == x1-1 && x3 == x1 && x4 == x1+1)
						|| (x1 == 2 && x2 == x1-1 && x3 == x1-2 && x4 == x1-1)
						|| (x1 == 6 && x2 == x1+1 && x3 == x1 && x4 == x1-1)
						|| (x1 == 5 && x2 == x1+1 && x3 == x1+2 && x4 == x1+1))
					&& ((y2 == y1-1 && y3 == y1-2 && y4 == y1-3) || (y2 == y1+1 && y3 == y1+2 && y4 == y1+3))) return 1;
			break;
		case 6:
			if(((x1 == 1 && x2 == x1-1 && x3 == x1 && (x4 == x1-1 || x4 == x1+1))
						|| (x1 == 6 && x2 == x1+1 && x3 == x1 && (x4 == x1-1 || x4 == x1+1)))
					&& ((y2 == y1 && y3 == y1 && y4 == y1-1) || (y2 == y1 && y3 == y1 && y4 == y1+1))) return 1;
			if((x1 == 0 || x1 == 2) && (x2 == 1 && x3 == 0 && x4 == 1) && (y2 == y1 - 1 && y3 == y1 - 1 && y4 == y1 - 1)) return 1;
			if((x1 == 5 || x1 == 7) && (x2 == 6 && x3 == 7 && x4 == 6) && (y2 == y1 - 1 && y3 == y1 - 1 && y4 == y1 - 1)) return 1;
			if((x1 == 0 || x1 == 2) && (x2 == 1 && x3 == 0 && x4 == 1) && (y2 == y1 + 1 && y3 == y1 + 1 && y4 == y1 + 1)) return 1;
			if((x1 == 5 || x1 == 7) && (x2 == 6 && x3 == 7 && x4 == 6) && (y2 == y1 + 1 && y3 == y1 + 1 && y4 == y1 + 1)) return 1;
			if(x1 == 1 && x2 == 0 && x3 == 1 && x4 == 2 && y2 == y1 - 1 && y3 == y1 - 1 && y4 == y1 - 1) return 1;
			if(x1 == 6 && x2 == 7 && x3 == 6 && x4 == 5 && y2 == y1 - 1 && y3 == y1 - 1 && y4 == y1 - 1) return 1;
			if(x1 == 1 && x2 == 0 && x3 == 1 && x4 == 2 && y2 == y1 + 1 && y3 == y1 + 1 && y4 == y1 + 1) return 1;
			if(x1 == 6 && x2 == 7 && x3 == 6 && x4 == 5 && y2 == y1 + 1 && y3 == y1 + 1 && y4 == y1 + 1) return 1;
			break;
		case 9:
			if(joueur %2 != 0){			
				if(((((x1 == 1 && x2 == x1-1 && x3 == x1) 
									&& ((x4==x1 && y4==y1-3) || (((x4==x1-1 || x4==x1+1) && y4==y1-2)))))
							|| ((x1 == 6 && x2 == x1+1 && x3 == x1) 
								&& ((x4==x1 && y4==y1-3) || (((x4==x1-1 || x4==x1+1) && y4==y1-2)))))
						&& (y2 == y1-1 && y3 == y1-2)) return 1;
				if(x1 == 1 && x2 == 1 && x3 == 0 && x4 == 1 && y2 == y1 - 1 && y3 == y1 - 2 && y4 == y1 - 3) return 1;
				if((x1 == 0 || x1 == 2) && x2 == 1 && x3 == 0 && x4 == 1 && y2 == y1 && y3 == y1 - 1 && y4 == y1 - 2) return 1;
				if(x1 == 6 && x2 == 6 && x3 == 7 && x4 == 6 && y2 == y1 - 1 && y3 == y1 - 2 && y4 == y1 - 3) return 1;
				if((x1 == 5 || x1 == 7) && x2 == 6 && x3 == 7 && x4 == 6 && y2 == y1 && y3 == y1 - 1 && y4 == y1 - 2) return 1;
			}
			else if(joueur %2 == 0) {
				if(((((x1 == 1 && x2 == x1-1 && x3 == x1) 
									&& ((x4==x1 && y4==y1+3) || (((x4==x1-1 || x4==x1+1) && y4==y1+2)))))
							|| ((x1 == 6 && x2 == x1+1 && x3 == x1) 
								&& ((x4==x1 && y4==y1+3) || (((x4==x1-1 || x4==x1+1) && y4==y1+2)))))
						&& (y2 == y1+1 && y3 == y1+2)) return 1;
				if(x1 == 1 && x2 == 1 && x3 == 0 && x4 == 1 && y2 == y1 + 1 && y3 == y1 + 2 && y4 == y1 + 3) return 1;
				if((x1 == 0 || x1 == 2) && x2 == 1 && x3 == 0 && x4 == 1 && y2 == y1 && y3 == y1 + 1 && y4 == y1 + 2) return 1;
				if(x1 == 6 && x2 == 6 && x3 == 7 && x4 == 6 && y2 == y1 + 1 && y3 == y1 + 2 && y4 == y1 + 3) return 1;
				if((x1 == 5 || x1 == 7) && x2 == 6 && x3 == 7 && x4 == 6 && y2 == y1 && y3 == y1 + 1 && y4 == y1 + 2) return 1;
			}
			break;
		default:
			return 0;
	}
	return 0;
}

int deploiement_possible2(plateau* p, point* point_1, int type, int joueur) {
	int forme, rep, couleur;
	liste* l = NULL;
	liste* tmp = NULL;
	/* transformation des coordonnées pour une utilisation simplifiée */
	int x = point_1->x;
	int	y = point_1->y;

	if(p->cell[y][x] == NULL) return 0;
	else{
	   	forme = p->cell[y][x]->forme;
	   	couleur = p->cell[y][x]->couleur;
	}

	/* type 1 est + */
	if(type == 1) {
		switch(forme){
			case 2:
				if(joueur % 2 == 0){
					s_dep(p, &l, x, y, 8, couleur, 2);
					o_dep(p, &l, x, y, 8, couleur, 2);
					e_dep(p, &l, x, y, 8, couleur, 2);
				}
				else{
					n_dep(p, &l, x, y, -1, couleur, 2);
					o_dep(p, &l, x, y, -1, couleur, 2);
					e_dep(p, &l, x, y, -1, couleur, 2);
				}
				break;
			case 3:
				if(joueur % 2 == 0){
					s_dep(p, &l, x, y, 8, couleur, 3);
					o_dep(p, &l, x, y, 8, couleur, 3);
					e_dep(p, &l, x, y, 8, couleur, 3);
				}
				else{
					n_dep(p, &l, x, y, -1, couleur, 3);
					o_dep(p, &l, x, y, -1, couleur, 3);
					e_dep(p, &l, x, y, -1, couleur, 3);
				}
				break;
			case 5:
				if(joueur % 2 == 0){
					s_dep(p, &l, x, y, 8, couleur, 1);
					o_dep(p, &l, x, y, 8, couleur, 1);
					e_dep(p, &l, x, y, 8, couleur, 1);

					s_dep(p, &tmp, x, y, 8, couleur, 1);
					o_dep(p, &tmp, x, y, 8, couleur, 1);
					e_dep(p, &tmp, x, y, 8, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						se_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
						so_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
					}
				}
				else{
					n_dep(p, &l, x, y, -1, couleur, 1);
					o_dep(p, &l, x, y, -1, couleur, 1);
					e_dep(p, &l, x, y, -1, couleur, 1);

					n_dep(p, &tmp, x, y, -1, couleur, 1);
					o_dep(p, &tmp, x, y, -1, couleur, 1);
					e_dep(p, &tmp, x, y, -1, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						no_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
						ne_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
					}
				}	
			case 6:
				if(joueur % 2 == 0){
					s_dep(p, &l, x, y, 8, couleur, 2);
					o_dep(p, &l, x, y, 8, couleur, 2);
					e_dep(p, &l, x, y, 8, couleur, 2);

					s_dep(p, &tmp, x, y, 8, couleur, 2);
					o_dep(p, &tmp, x, y, 8, couleur, 2);
					e_dep(p, &tmp, x, y, 8, couleur, 2);

					for(; tmp != NULL ; tmp = tmp->suivant){
						se_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
						so_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
					}
				}
				else{
					n_dep(p, &l, x, y, -1, couleur, 2);
					o_dep(p, &l, x, y, -1, couleur, 2);
					e_dep(p, &l, x, y, -1, couleur, 2);

					n_dep(p, &tmp, x, y, -1, couleur, 2);
					o_dep(p, &tmp, x, y, -1, couleur, 2);
					e_dep(p, &tmp, x, y, -1, couleur, 2);

					for(; tmp != NULL ; tmp = tmp->suivant){
						no_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
						ne_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
					}
				}	
			case 9:
				if(joueur % 2 == 0){
					s_dep(p, &l, x, y, 8, couleur, 1);
					o_dep(p, &l, x, y, 8, couleur, 1);
					e_dep(p, &l, x, y, 8, couleur, 1);

					s_dep(p, &tmp, x, y, 8, couleur, 1);
					o_dep(p, &tmp, x, y, 8, couleur, 1);
					e_dep(p, &tmp, x, y, 8, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						se_dep(p, &l, tmp->x, tmp->y, 8, couleur, 2);
						so_dep(p, &l, tmp->x, tmp->y, 8, couleur, 2);
					}
				}
				else{
					n_dep(p, &l, x, y, -1, couleur, 1);
					o_dep(p, &l, x, y, -1, couleur, 1);
					e_dep(p, &l, x, y, -1, couleur, 1);

					n_dep(p, &tmp, x, y, -1, couleur, 1);
					o_dep(p, &tmp, x, y, -1, couleur, 1);
					e_dep(p, &tmp, x, y, -1, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						no_dep(p, &l, tmp->x, tmp->y, -1, couleur, 2);
						ne_dep(p, &l, tmp->x, tmp->y, -1, couleur, 2);
					}
				}
		}
	}

	/* type 2 est * */
	else if(type == 2){
		switch(forme){
			case 5:
				if(joueur % 2 == 0){
					se_dep(p, &l, x, y, 8, couleur, 1);
					so_dep(p, &l, x, y, 8, couleur, 1);

					se_dep(p, &tmp, x, y, 8, couleur, 1);
					so_dep(p, &tmp, x, y, 8, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						s_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
						o_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
						e_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
					}
				}
				else{
					no_dep(p, &l, x, y, -1, couleur, 1);
					ne_dep(p, &l, x, y, -1, couleur, 1);

					no_dep(p, &tmp, x, y, -1, couleur, 1);
					ne_dep(p, &tmp, x, y, -1, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						n_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
						o_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
						e_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
					}
				}	
			case 6:
				if(joueur % 2 == 0){
					se_dep(p, &l, x, y, 8, couleur, 1);
					so_dep(p, &l, x, y, 8, couleur, 1);

					se_dep(p, &tmp, x, y, 8, couleur, 1);
					so_dep(p, &tmp, x, y, 8, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						s_dep(p, &l, tmp->x, tmp->y, 8, couleur, 2);
						o_dep(p, &l, tmp->x, tmp->y, 8, couleur, 2);
						e_dep(p, &l, tmp->x, tmp->y, 8, couleur, 2);
					}
				}
				else{
					no_dep(p, &l, x, y, -1, couleur, 1);
					ne_dep(p, &l, x, y, -1, couleur, 1);

					no_dep(p, &tmp, x, y, -1, couleur, 1);
					ne_dep(p, &tmp, x, y, -1, couleur, 1);

					for(; tmp != NULL ; tmp = tmp->suivant){
						n_dep(p, &l, tmp->x, tmp->y, -1, couleur, 2);
						o_dep(p, &l, tmp->x, tmp->y, -1, couleur, 2);
						e_dep(p, &l, tmp->x, tmp->y, -1, couleur, 2);
					}
				}	
			case 8:
				if(joueur % 2 == 0){
					se_dep(p, &l, x, y, 8, couleur, 2);
					so_dep(p, &l, x, y, 8, couleur, 2);
				}
				else{
					no_dep(p, &l, x, y, -1, couleur, 2);
					ne_dep(p, &l, x, y, -1, couleur, 2);
				}	
			case 9:
				if(joueur % 2 == 0){
					se_dep(p, &l, x, y, 8, couleur, 2);
					so_dep(p, &l, x, y, 8, couleur, 2);

					se_dep(p, &tmp, x, y, 8, couleur, 2);
					so_dep(p, &tmp, x, y, 8, couleur, 2);

					for(; tmp != NULL ; tmp = tmp->suivant){
						s_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
						o_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
						e_dep(p, &l, tmp->x, tmp->y, 8, couleur, 1);
					}
				}
				else{
					no_dep(p, &l, x, y, -1, couleur, 2);
					ne_dep(p, &l, x, y, -1, couleur, 2);

					no_dep(p, &tmp, x, y, -1, couleur, 2);
					ne_dep(p, &tmp, x, y, -1, couleur, 2);

					for(; tmp != NULL ; tmp = tmp->suivant){
						n_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
						o_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
						e_dep(p, &l, tmp->x, tmp->y, -1, couleur, 1);
					}
				}	
			case 12:
				if(joueur % 2 == 0){
					se_dep(p, &l, x, y, 8, couleur, 3);
					so_dep(p, &l, x, y, 8, couleur, 3);
				}
				else{
					no_dep(p, &l, x, y, -1, couleur, 3);
					ne_dep(p, &l, x, y, -1, couleur, 3);
				}	
		}	
	}
	rep = est_present2(l, joueur);
	return rep;
}

void s_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y)){ 
			if((y+i) == y2){
				append(l, x, y + i);
				break;
			}
			else if((p->cell[y+i][x] == NULL) || ((couleur == p->cell[y+i][x]->couleur) && (p->cell[y+i][x]->taille <= 2))){
				append(l, x, y + i);
			}
			else{
				break;
			}
		}
	}
}
void so_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x-i, y)){ 
			if((y+i) == y2){
				append(l, x - i, y + i);
				break;
			}
			if(x-i == 0 && taille - i > 0){
				append(l, x - i, y + i);
				se_dep(p, l, x-i, y + i, y2, couleur, taille - i);
			}
			else if((p->cell[y+i][x-i] == NULL) || ((couleur == p->cell[y+i][x-i]->couleur) && (p->cell[y+i][x-i]->taille <= 2))){
				append(l, x - i, y + i);
			}
			else{
				break;
			}
		}
	}
}
void se_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x+i, y)){ 
			if((y+i) == y2){
				append(l, x + i, y + i);
				break;
			}
			if(x+i == 7 && taille - i > 0){
				append(l, x + i, y + i);
				so_dep(p, l, x+i, y + i, y2, couleur, taille - i);
			}
			else if((p->cell[y+i][x+i] == NULL) || ((couleur == p->cell[y+i][x+i]->couleur) && (p->cell[y+i][x+i]->taille <= 2))){
				append(l, x + i, y + i);
			}
			else{
				break;
			}
		}
	}
}
void n_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x, y)){ 
			if((y-i) == y2){
				append(l, x, y - i);
				break;
			}
			else if((p->cell[y-i][x] == NULL) || ((couleur == p->cell[y-i][x]->couleur) && (p->cell[y-i][x]->taille <= 2))){
				append(l, x, y - i);
			}
			else{
				break;
			}
		}
	}
}
void no_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x-i, y)){ 
			if((y-i) == y2){
				append(l, x - i, y - i);
				break;
			}
			if(x-i == 0 && taille - i > 0){
				append(l, x - i, y - i);
				ne_dep(p, l, x-i, y - i, y2, couleur, taille - i);
			}
			else if((p->cell[y-i][x-i] == NULL) || ((couleur == p->cell[y-i][x-i]->couleur) && (p->cell[y-i][x-i]->taille <= 2))){
				append(l, x - i, y - i);
			}
			else{
				break;
			}
		}
	}
}
void ne_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x+i, y)){ 
			if((y-i) == y2){
				append(l, x + i, y - i);
				break;
			}
			if(x+i == 7 && taille - i > 0){
				append(l, x + i, y - i);
				no_dep(p, l, x+i, y - i, y2, couleur, taille - i);
			}
			else if((p->cell[y-i][x+i] == NULL) || ((couleur == p->cell[y-i][x+i]->couleur) && (p->cell[y-i][x+i]->taille <= 2))){
				append(l, x + i, y - i);
			}
			else{
				break;
			}
		}
	}
}
void o_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x-i, y)){ 
			if(y == y2){
				append(l, x - i, y);
				break;
			}
			if(x-i == 0 && taille - i > 0){
				append(l, x - i, y);
				e_dep(p, l, x-i, y, y2, couleur, taille - i);
			}
			else if((p->cell[y][x-i] == NULL) || ((couleur == p->cell[y][x-i]->couleur) && (p->cell[y][x-i]->taille <= 2))){
				append(l, x - i, y);
			}
			else{
				break;
			}
		}
	}
}
void e_dep(plateau* p, liste** l, int x, int y, int y2, int couleur, int taille){
	int i;
	for(i = 1 ; i <= taille ; i++){
		if(coord_dans_tab(x+i, y)){ 
			if(y == y2){
				append(l, x + i, y);
				break;
			}
			if(x+i == 7 && taille - i > 0){
				append(l, x + i, y);
				o_dep(p, l, x+i, y, y2, couleur, taille - i);
			}
			else if((p->cell[y][x+i] == NULL) || ((couleur == p->cell[y][x+i]->couleur) && (p->cell[y][x+i]->taille <= 2))){
				append(l, x + i, y);
			}
			else{
				break;
			}
		}
	}
}
