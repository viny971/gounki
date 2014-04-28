#include "gounki.h"

void read_options(int argc, char* argv[]){
}

void read_line(int* x1, int* y1, int* x2, int* y2){
	char* line = NULL;
	size_t size;

	getline(&line, &size, stdin);

	*x1 = trans_coord(line[0]);
	*x2 = trans_coord(line[3]);
	*y1 = 7 - trans_coord(line[1]);
	*y2 = 7 - trans_coord(line[4]);
	
	free(line);
}

int main(int argc, char* argv[]){
	int x1, y1, x2, y2, c = 0;
	plateau* p = init_plateau();
	affiche_plateau(p);
	while(1){
		printf("Au tour du %sjoueur %d%s > ", (c % 2 == 0) ? PURPLE : GREEN, (c % 2) + 1, DEFAULT_COLOR);
		c++;
		read_line(&x1, &y1, &x2, &y2);
		if(!deplacement_possible(p, x1, y1, x2, y2, c)){
			printf("Erreur, recommencez\n");
			c--;
		}
		else{
			deplacement(p, x1, y1, x2, y2);
			affiche_plateau(p);
		}
	}
	return 0;
}
