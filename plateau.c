#include "plateau.h"

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

int deplacement_possible(plateau* p, int x1, int y1, int x2, int y2, int joueur){
/* retourne 1 si le déplacement est posible, 0 sinon.*/
	int rep;
	if(x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1){
		return 0;
	}
	else{
		liste* l = init_liste(x1, y1);
		l = deplacements_possibles(l, p->cell[y1][x1]->forme);
		affiche_liste(l);
		rep = est_present(l, x2, y2);
		free_liste(l);
		return rep;
	}
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

void composition(plateau* p, int x1, int y1, int x2, int y2){	
	if(p->cell[y1][x1]->taille + p->cell[y2][x2]->taille <= 3){
		p->cell[y2][x2]->taille = p->cell[y1][x1]->taille + p->cell[y2][x2]->taille;
		p->cell[y2][x2]->forme = p->cell[y1][x1]->forme + p->cell[y2][x2]->forme;
		p->cell[y1][x1] = NULL;
	}
}
