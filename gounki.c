#include "gounki.h"

int main(){
	int y1, y2, x1, x2, c = 0;
	char* line;
	size_t size;
	plateau* p = init_plateau();
	affiche_plateau(p);
	while(1){
		printf("Au tour du joueur %s:\n", (c % 2 == 0) ? "violet": "vert");
		c++;
		line = NULL;
		getline(&line, &size, stdin);
		x1 = trans_coord(line[0]);
		x2 = trans_coord(line[3]);
		y1 = 7 - trans_coord(line[1]);
		y2 = 7 - trans_coord(line[4]);
		free(line);
		if(!deplacement_possible(p, x1, y1, x2, y2,c)){
			printf("Erreur, recommencez:\n");
			c--;
		}
		else{
			deplacement(p, x1, y1, x2, y2);
			affiche_plateau(p);
		}
	}
	return 0;
}
