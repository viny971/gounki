#include "gounki.h"

void read_option(int argc, char* argv[]){
}

int read_line(int* x1, int* y1, int* x2, int* y2, int* x3, int* y3, int* x4, int* y4, int* type, int* size_line){
	char* line = NULL;
	size_t size;

	/* lecture de la ligne */
	getline(&line, &size, stdin);

	/* retourne 2 si c'est un déploiement */
	if(line[2] == '+' || line[2] == '*'){

		if(size < 9 || size > 12){
			return 0;
		}

		*x1 = trans_coord(line[0]);
		*y1 = 7 - trans_coord(line[1]);
		
		if(size == 9 || size == 12) {
			*x2 = trans_coord(line[3]);
			*y2 = 7 - trans_coord(line[4]);
			*x3 = trans_coord(line[6]);
			*y3 = 7 - trans_coord(line[7]);
		}
		if(size == 12) {
			*x4 = trans_coord(line[9]);
			*y4 = 7 - trans_coord(line[10]);
		}
		if(line[2] == '+'){
			*type = 1;
		}
		else{
			*type = 2;
		}
		*size_line = size;
		free(line);
		return 2;
	}
	/* retourne 3 si c'est une victoire */
	if(line[2] == '#'){
		*x1 = trans_coord(line[0]);
		*y1 = 7 - trans_coord(line[1]);
		free(line);
		return 3;
	}
	/* retourne 1 si c'est un déplacement */
	else{
		*x1 = trans_coord(line[0]);
		*x2 = trans_coord(line[3]);
		*y1 = 7 - trans_coord(line[1]);
		*y2 = 7 - trans_coord(line[4]);
		free(line);
		return 1;
	}
	return 0;
}

int main(){
	int  x1, y1, x2, y2, x3, y3, x4, y4, type, size, c = 0, action;
	plateau* p = init_plateau();
	affiche_plateau(p);
	while(1){
		printf("Au tour du %sjoueur %d%s > ", (c % 2 == 0) ? PURPLE : GREEN, (c % 2) + 1, DEFAULT_COLOR);
		c++;

		action = read_line(&x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &type, &size);

		if(!action){
			printf("Erreur, recommencez.\n");
			c--;
		}

		switch(action){
			/* cas 1: déplacement standard */
			case 1:
				if(!deplacement_possible(p, x1, y1, x2, y2, c)){
					printf("Erreur, recommencez.\n");
					c--;
				}
				else{
					deplacement(p, x1, y1, x2, y2);
					affiche_plateau(p);
				}
				break;

			/* cas 2: déploiement */
			case 2:
				if(!deploiement_possible(p,x1, y1, x2, y2, x3, y3, x4, y4, type, c)){
					printf("Déploiement non valide.\n");
					c--;
				}
				else{
					deploiement_possible(p,x1, y1, x2, y2, x3, y3, x4, y4, type, size);
					affiche_plateau(p);	    
				}
				break;
		}
	}
	return 0;	
}
