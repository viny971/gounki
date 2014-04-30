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

int deplacement_possible(plateau* p, int x1, int y1, int x2, int y2, int joueur){
/* retourne 1 si le déplacement est posible, 0 sinon.*/
	int rep;
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
		return rep;
	}
	return 1;
}

void deplacements_possibles(plateau* p, liste** l, liste** l2, int forme, int x2, int y2, int joueur){
/* retourne la liste des positions parcourables par la pièce */
	liste* i = *l;
	for(; i != NULL ; i = i->suivant){
		switch(forme){
			case 1:
				if(joueur % 2 == 0){
					if((p->cell[(i->y)+1][i->x] == NULL) || (p->cell[i->y][i->x]->couleur == ((joueur + 1) % 2) && x2 == i->x && y2 == (i->y) + 1)){
						append(l, i->x, (i->y) + 1);
					}
					if((p->cell[i->y][(i->x)+1] == NULL) || (p->cell[i->y][(i->x)+1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) + 1 && y2 == i->y)){
						append(l, (i->x) + 1, i->y);
					}
					if((p->cell[i->y][(i->x)-1] == NULL) || (p->cell[i->y][(i->x)-1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) - 1 && y2 == i->y)){
						append(l, (i->x) - 1, i->y);
					}
				}
				else{
					if((p->cell[(i->y)-1][i->x] == NULL) || (p->cell[(i->y)-1][i->x]->couleur == ((joueur + 1) % 2) && x2 == i->x && y2 == (i->y) - 1)){
						append(l, i->x, (i->y) - 1);
					}
					if((p->cell[i->y][(i->x)+1] == NULL) || (p->cell[i->y][(i->x)+1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) + 1 && y2 == i->y)){
						append(l, (i->x) + 1, i->y);
					}
					if((p->cell[i->y][(i->x)-1] == NULL) || (p->cell[i->y][(i->x)-1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) - 1 && y2 == i->y)){
						append(l, (i->x) - 1, i->y);
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
					if((p->cell[(i->y)+1][(i->x)+1] == NULL) || (p->cell[(i->y)+1][(i->x)+1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) + 1 && y2 == (i->y) + 1)){
						append(l, (i->x) + 1, (i->y) + 1);
					}
					if((p->cell[(i->y)+1][(i->x)-1] == NULL) || (p->cell[(i->y)+1][(i->x)-1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) - 1 && y2 == (i->y) + 1)){
						append(l, (i->x) - 1, (i->y) + 1);
					}
				}
				else{
					if((p->cell[(i->y)-1][(i->x)+1] == NULL) || (p->cell[(i->y)-1][(i->x)+1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) + 1 && y2 == (i->y) - 1)){
						append(l, i->x + 1, i->y - 1);
					}
					if((p->cell[(i->y)-1][(i->x)-1] == NULL) || (p->cell[(i->y)-1][(i->x)-1]->couleur == ((joueur + 1) % 2) && x2 == (i->x) - 1 && y2 == (i->y) - 1)){
						append(l, i->x - 1, i->y - 1);
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

void deplacement(plateau* p, int x1, int y1, int x2, int y2){
	if(p->cell[y2][x2] != NULL && (p->cell[y1][x1]->couleur == p->cell[y2][x2]->couleur)){
		composition(p,x1,y1,x2,y2);
	}
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
	int a = p->cell[y2][x1]->taille + p->cell[y2][x2]->taille;
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

int deploiement_possible(plateau* p, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int type, int joueur) {
	int forme;

	if(p->cell[y1][x1] == NULL) return 0;
	else forme = p->cell[y1][x1]->forme;

	if(type == 1) {
		switch(forme){
			case 2:
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur)
					|| !meme_sens(x1,y1,x2,y2,x3,y3,1)){
						return 0;
				}

				if(p->cell[y2][x2] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y2][x2]->couleur) return 0;
					if(p->cell[y2][x2]->taille + 1 > 2) return 0;
				}

				if(p->cell[y3][x3] != NULL){
					if(p->cell[y1][x1]->couleur != p->cell[y3][x3]->couleur){
						return 0;
					}
					if(p->cell[y3][x3]->taille + 1 > 2){
						return 0;
					}
				}
				break;

			case 3:
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur) 
					|| !deplacement_possible(p,x3,y3,x4,y4,joueur)
					|| !meme_sens(x1,y1,x2,y2,x3,y3,1) 
					|| !meme_sens(x2,y2,x3,y3,x4,y4,1)){
						return 0;	
				}
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
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) || !deplacement_possible(p,x2,y2,x3,y3,joueur)) return 0;
			
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
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur) 
					|| !deplacement_possible(p,x3,y3,x4,y4,joueur)
					|| !meme_sens(x1,y1,x2,y2,x3,y3,1)){
						return 0;
				}

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
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur) 
					|| !deplacement_possible(p,x3,y3,x4,y4,joueur)
					|| !meme_sens(x2,y2,x3,y3,x4,y4,4)){
						return 0;
				}

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

	else if(type == 2){
		switch(forme){
			case 8:
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur) 
					|| !meme_sens(x1,y1,x2,y2,x3,y3,4)){
						return 0;
				}

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
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur) 
					|| !deplacement_possible(p,x3,y3,x4,y4,joueur)
					|| !meme_sens(x1,y1,x2,y2,x3,y3,4) 
					|| !meme_sens(x2,y2,x3,y3,x4,y4,4)){
						return 0;
				}

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
				if(p->cell[y2][x2] == NULL){
					fprintf(stdout, "coucou");
				}
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) || !deplacement_possible(p,x2,y2,x3,y3,joueur)) return 0;
				
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
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur) 
					|| !deplacement_possible(p,x3,y3,x4,y4,joueur)
					|| !meme_sens(x1,y1,x2,y2,x3,y3,4)){
						return 0;
				}
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
				if(!deplacement_possible(p,x1,y1,x2,y2,joueur) 
					|| !deplacement_possible(p,x2,y2,x3,y3,joueur) 
					|| !deplacement_possible(p,x3,y3,x4,y4,joueur)
					|| !meme_sens(x2,y2,x3,y3,x4,y4,1)){
						return 0;
				}

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


void deploiement(plateau* p, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int str_line, int type) {
	int forme, couleur;

	forme = p->cell[y1][x1]->forme;
	couleur = p->cell[y1][x1]->couleur;

	if(str_line == 9) {
		if(type == 2){
			if(forme == 2){
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,1,couleur);
			}
			else if(forme == 5) {
				deplacement2(p,x2,y2,1,couleur);
				deplacement2(p,x3,y3,4,couleur);
			}		
		}
		else if(type == 1){
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
	else if(str_line == 12) {
		if(type == 2){
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
		else if(type == 1){
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
