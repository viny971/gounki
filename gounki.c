#include "gounki.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int y1, y2, x1, x2, x3, y3, c = 0;
	char* line;
	size_t size;
	int i = 0;
	plateau* p = init_plateau();
	affiche_plateau(p);
	while(1){
		printf("Au tour du joueur %s:\n", (c % 2 == 0) ? "violet": "vert");
		c++;
		line = NULL;
		getline(&line, &size, stdin);
<<<<<<< HEAD
		printf("%c\n", line[2]);
		if(line[2] == '+' || line[2] == '*'){
			if(!deploiement_possible(p,line,c)){
				printf("Déploiement non valide\n");
				c--;
			}
			else{
		  		deploiement(p,line);
		  		affiche_plateau(p);	    
			}
		}	
		else {
			x1 = trans_coord(line[0]);
		  	x2 = trans_coord(line[3]);
			x3 = trans_coord(line[6]);
		  	y1 = 7 - trans_coord(line[1]);
		  	y2 = 7 - trans_coord(line[4]);
			y3 = 7 - trans_coord(line[7]);
		  	free(line);
			if(p->cell[y1][x1] == NULL){ 
		    		printf("Erreur, recommencez:\n");
		    		c--;
			}
		  	else if(!deplacement_possible(p, x1, y1, x2, y2, p->cell[y1][x1]->forme, c)){
		    		printf("Erreur, recommencez:\n");
		    		c--;
			}
			else{
		    		deplacement(p, x1, y1, x2, y2);
		    		affiche_plateau(p);
		  	}
=======
		x1 = trans_coord(line[0]);
		x2 = trans_coord(line[3]);
		y1 = 7 - trans_coord(line[1]);
		y2 = 7 - trans_coord(line[4]);
		free(line);
		if(!deplacement_possible(p, x1, y1, x2, y2, c)){
			printf("Erreur, recommencez:\n");
			c--;
		}
		else{
			deplacement(p, x1, y1, x2, y2);
			affiche_plateau(p);
>>>>>>> 916f75227657d864d891ca9a43ca1777826ec8c2
		}
	}
	return 0;	
}
