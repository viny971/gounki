#include "liste.h"

liste* init_liste(int x, int y){
	liste* l= malloc(sizeof(liste));
	l->x = x;
	l->y = y;
	l->suivant = NULL;
	return l;
}

void free_liste(liste* l){
	if(l == NULL){
		return;
	}
	else{
		free_liste(l->suivant);
		free(l);
	}
}

void append(liste** l, int x, int y){
	liste* l2 = init_liste(x,y);
	l2->suivant = *l;
	*l = l2;
}

liste* concat(liste* l1, liste* l2){
	while(l1->suivant != NULL){
		l1 = l1->suivant;
	}
	l1->suivant = l2;
	return l1;
}

int est_present(liste* l, int x, int y){
	liste* i = l;
	for(; i != NULL ; i = i->suivant){
		if(i->x == x && i->y == y){
			return 1;
		}
	}
	return 0;
}

void affiche_liste(liste* l){
	liste* i = l;
	for(; i != NULL ; i = i->suivant){
		printf("(%d,%d)->", i->x, i->y);
	}
	fprintf(stdout, "\n");
}

int est_present2(liste* l, int joueur){
	liste* i = l;
	int y;
	if(joueur % 2 == 0) y = 8; 
	else y = 0;

	for(; i != NULL ; i = i->suivant){
		if(i->y == y){
			return 1;
		}
	}
	return 0;
}

void random_point(liste* l, point** p1){
	int r, i;
	liste* tmp = l;
  	srand(time(NULL));
	r = rand() % 100 + 1;
	for(i = 0 ; i < r ; i++){
		if(tmp->suivant == NULL){
		   	tmp = l;
		}
		else{
		   	tmp = tmp->suivant;
		}
	}	
	(*p1)->x = tmp->x;
	(*p1)->y = tmp->y;
}
