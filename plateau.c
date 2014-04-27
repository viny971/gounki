#include "plateau.h"
#include <math.h>
#include <string.h>

plateau* init_plateau(){
	int i,j;
	plateau* plateau = malloc(sizeof(pion*) * 8 * 8);
	for(j=0 ; j < 8 ; j += 2){
		plateau->cell[0][j] = init_pion(GREEN,1);
		plateau->cell[0][j+1] = init_pion(GREEN,4);
		plateau->cell[1][j+1] = init_pion(GREEN,1);
		plateau->cell[1][j] = init_pion(GREEN,4);
		plateau->cell[6][j] = init_pion(PURPLE,1);
		plateau->cell[6][j+1] = init_pion(PURPLE,4);
		plateau->cell[7][j+1] = init_pion(PURPLE,1);
		plateau->cell[7][j] = init_pion(PURPLE,4);
	}
	for(i = 2 ; i < 6 ; i++){
		for(j = 0 ; j < 8 ; j++){
			plateau->cell[i][j] = NULL;
		}
	}
	return plateau;
}

int affiche_plateau(plateau* p){
	int i,j;
	printf("\n    A   B   C   D   E   F   G   H");
	for(i = 0 ; i < 8 ; i++){
		printf("\n %d|", 8-i);
		for(j = 0 ; j < 8 ; j++){
			if(p->cell[i][j] == NULL){
				printf("   |");
			}
			else{
				affiche_pion(p->cell[i][j]);
			}
		}
		printf("%d", 8-i);
		if(i!=7){
			printf("\n   _______________________________");
		}
	}
	printf("\n    A   B   C   D   E   F   G   H\n\n");
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
		case 'E':
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

int deplacement_possible(plateau* p, int x1, int y1, int x2, int y2, int forme, int joueur){
/* retourne 1 si le déplacement est posible, 0 sinon.*/
	/*int rep;*/
	if(x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1) return 0;
	if(joueur%2 == 0 && y2 < y1) return 0; /*interdit les retours en arrière*/
	else if(joueur%2 != 0 && y2 > y1) return 0;/*interdit les retours en arrière*/
	else {
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

			default:
				return 0;
				break;
		}
	}
	/*else{
		liste* l = init_liste(x1, y1);
		l = deplacements_possibles(l, p->cell[y1][x1]->forme);
		affiche_liste(l);
		rep = est_present(l, x2, y2);
		free_liste(l);
		return rep;
	}*/
	return 1;
}

liste* deplacements_possibles(liste* l, int forme){
/* retourne la liste des positions parcourables par la pièce */
	liste* i = l;
	for(; i != NULL ; i = i->suivant){
		switch(forme){
			case 1:
				l = append(l, i->x, i->y - 1);
				l = append(l, i->x + 1, i->y);
				l = append(l, i->x - 1, i->y);
				break;

			case 2:
				l = deplacements_possibles(l, 1);
				l = deplacements_possibles(l, 1);
				break;

			case 3:
				l = deplacements_possibles(l, 2);
				l = deplacements_possibles(l, 1);
				break;

			case 4:
				l = append(l, i->x + 1, i->y - 1);
				l = append(l, i->x - 1, i->y - 1);
				break;

			case 5:
				l = deplacements_possibles(l, 1);
				l = deplacements_possibles(l, 4);
				break;

			case 6:
				l = deplacements_possibles(l, 2);
				l = deplacements_possibles(l, 4);
				break;

			case 8:
				l = deplacements_possibles(l, 4);
				l = deplacements_possibles(l, 4);
				break;

			case 9:
				l = deplacements_possibles(l, 1);
				l = deplacements_possibles(l, 8);
				break;

			case 12:
				l = deplacements_possibles(l, 4);
				l = deplacements_possibles(l, 8);
				break;
		}
	}
	return l;
}

void deplacement(plateau* p, int x1, int y1, int x2, int y2){
	printf("%d %d %d %d", x1, y1, x2, y2); 
	if(p->cell[y2][x2] != NULL && (p->cell[y1][x1]->couleur == p->cell[y2][x2]->couleur)){
		composition(p,x1,y1,x2,y2);
	}
	else{
		 p->cell[y2][x2] = p->cell[y1][x1];
	}
	p->cell[y1][x1] = NULL;
}

void deplacement2(plateau* p, int x1, int y1, int forme, char* couleur) {

	if(p->cell[y1][x1] != NULL) composition2(p,x1,y1,forme);
	else p->cell[y1][x1] = init_pion(couleur,forme);
	
}
	
void composition(plateau* p, int x1, int y1, int x2, int y2){	
	int a = p->cell[y1][x1]->taille + p->cell[y2][x2]->taille;
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

int deploiement_possible(plateau* p, char* line, int joueur) {

	int x1, y1, x2, y2, x3, y3, x4, y4, tmp, forme;
	if(strlen(line) < 9 || strlen(line) > 12) return 0;
	x1 = trans_coord(line[0]);
	y1 = 7 - trans_coord(line[1]);
	if(strlen(line) == 9 || strlen(line) == 12) {
		x2 = trans_coord(line[3]);
		y2 = 7 - trans_coord(line[4]);
		x3 = trans_coord(line[6]);
		y3 = 7 - trans_coord(line[7]);
	}
	if(strlen(line) == 12) {
		x4 = trans_coord(line[9]);
		y4 = 7 - trans_coord(line[10]);
	}
	printf("x1 = %d, y1 = %d, x2 = %d, y2 = %d, x3 = %d, y3 = %d\n", x1,y1,x2,y2,x3,y3);	
	if(p->cell[y1][x1] == NULL) return 0;
	else forme = p->cell[y1][x1]->forme;

	printf("forme = %d\n", forme);

	if(line[2] == '+') {
		printf("coucou 1\n");
		switch(forme){
			case 2:
				printf("coucou 2\n");
				if(!deplacement_possible(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible(p,x2,y2,x3,y3,1,joueur) ||!meme_sens(x1,y1,x2,y2,x3,y3,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					printf("coucou 3\n");
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					printf("coucou 4\n");
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				break;

			case 3:
				printf("coucou 5\n");
				tmp = meme_sens(x1,y1,x2,y2,x3,y3,1);
				printf("meme_sens = %d\n", tmp);
				tmp = meme_sens(x2,y2,x3,y3,x4,y4,1);
				printf("meme_sens = %d\n", tmp);
				if(!deplacement_possible(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible(p,x3,y3,x4,y4,1,joueur)
				|| !meme_sens(x1,y1,x2,y2,x3,y3,1) || !meme_sens(x2,y2,x3,y3,x4,y4,1)) return 0;
				if(p->cell[y2][x2] != NULL){
					printf("coucou 6\n");
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					printf("coucou 7\n");
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y2][x2] != NULL){
					printf("coucou 8\n");
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;

			case 5:
				printf("coucou 9\n");	
				printf("deplacement_possible(p,x1,y1,x2,y2,1,joueur = %d\n", deplacement_possible(p,x1,y1,x2,y2,1,joueur));
				printf("deplacement_possible(p,x2,y2,x3,y3,2,joueur = %d\n", deplacement_possible(p,x2,y2,x3,y3,4,joueur));
				if(!deplacement_possible(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible(p,x2,y2,x3,y3,4,joueur)) return 0;
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
				printf("coucou 10\n");
				if(!deplacement_possible(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible(p,x3,y3,x4,y4,4,joueur)
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
				printf("coucou 11\n");
				if(!deplacement_possible(p,x1,y1,x2,y2,1,joueur) || !deplacement_possible(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible(p,x3,y3,x4,y4,4,joueur)
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

	else if(line[2] == '*') {
		printf("coucou 12\n");
		switch(forme){
			case 8:
				printf("coucou 2\n");
				if(!deplacement_possible(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible(p,x2,y2,x3,y3,4,joueur) ||!meme_sens(x1,y1,x2,y2,x3,y3,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					printf("coucou 13\n");
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					printf("coucou 14\n");
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				break;

			case 12:
				printf("coucou 15\n");
				printf("meme_sens(x1) = %d\n", meme_sens(x1,y1,x2,y2,x3,y3,4));
				printf("meme_sens(x2) = %d\n", meme_sens(x2,y2,x3,y3,x4,y4,4));
				printf("deplacement_possible(x1) = %d\n", deplacement_possible(p,x1,y1,x2,y2,4,joueur));
				printf("deplacement_possible(x2) = %d\n", deplacement_possible(p,x2,y2,x3,y3,4,joueur));
				printf("deplacement_possible(x3) = %d\n", deplacement_possible(p,x3,y3,x4,y4,4,joueur));
				if(!deplacement_possible(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible(p,x3,y3,x4,y4,4,joueur)
				|| !meme_sens(x1,y1,x2,y2,x3,y3,4) || !meme_sens(x2,y2,x3,y3,x4,y4,4)) return 0;
				if(p->cell[y2][x2] != NULL){
					printf("coucou 16\n");
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}
				if(p->cell[y3][x3] != NULL){
					printf("coucou 17\n");
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur) return 0;
					if(p->cell[y3][x3]->taille + 1 > 2) return 0;
				}
				if(p->cell[y4][x4] != NULL){
					printf("coucou 18\n");
					if(p->cell[y1][x1]->couleur != p->cell[y4][x4]->couleur) return 0;
					if(p->cell[y4][x4]->taille + 1 > 2) return 0;
				}
				break;

			case 5:
				printf("coucou 19\n");	
				printf("deplacement_possible(p,x1,y1,x2,y2,4,joueur = %d\n", deplacement_possible(p,x1,y1,x2,y2,4,joueur));
				printf("deplacement_possible(p,x2,y2,x3,y3,1,joueur = %d\n", deplacement_possible(p,x2,y2,x3,y3,1,joueur));
				if(!deplacement_possible(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible(p,x2,y2,x3,y3,1,joueur)) return 0;
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
				printf("coucou 20\n");
				if(!deplacement_possible(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible(p,x2,y2,x3,y3,4,joueur) || !deplacement_possible(p,x3,y3,x4,y4,1,joueur)
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
				printf("coucou 21\n");
				if(!deplacement_possible(p,x1,y1,x2,y2,4,joueur) || !deplacement_possible(p,x2,y2,x3,y3,1,joueur) || !deplacement_possible(p,x3,y3,x4,y4,1,joueur)
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


void deploiement(plateau* p, char* line){

	printf("dans deploiement\n");

	int x1, y1, x2, y2, x3, y3, x4, y4, forme;
	char* couleur;
	x1 = trans_coord(line[0]);
	y1 = 7 - trans_coord(line[1]);
	forme = p->cell[y1][x1]->forme;
	couleur = p->cell[y1][x1]->couleur;
	if(strlen(line) == 9) {
		x2 = trans_coord(line[3]);
		y2 = 7 - trans_coord(line[4]);
		x3 = trans_coord(line[6]);
		y3 = 7 - trans_coord(line[7]);

		if(line[2] == '+'){
			if(forme == 2){
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,1,couleur);
			}
			else if(forme == 5) {
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,4,couleur);
			}		
		}
		else if(line[2] == '*'){
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
	else if(strlen(line) == 12) {
		x2 = trans_coord(line[3]);
		y2 = 7 - trans_coord(line[4]);
		x3 = trans_coord(line[6]);
		y3 = 7 - trans_coord(line[7]);
		x4 = trans_coord(line[9]);
		y4 = 7 - trans_coord(line[10]);

		if(line[2] == '+'){
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
		else if(line[2] == '*'){
			if(forme == 12){
				printf("bonjour forme 12\n");
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

	

