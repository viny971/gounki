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

liste* append(liste* l, int x, int y){
	liste* l2 = init_liste(x,y);
	l2->suivant = l;
	return l2;
}

liste* concat(liste* l1, liste* l2){
	liste* l = l1;
	while(l->suivant != NULL){
		l = l->suivant;
	}
	l->suivant = l2;
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
}
