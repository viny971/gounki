#include "pion.h"

pion* init_pion(int couleur, int forme){
	pion* p = malloc(sizeof(pion));
	p->couleur = couleur;
	p->forme = forme;
	p->taille = 1;
	return p;
}

void free_pion(pion* p){
	free(p);
}
	

void affiche_pion(pion* p){
	char* rep;
	switch(p->forme){
		case 1:
			rep = " # "; break;
		case 2:
			rep = " ##"; break;
		case 3:
			rep = "###"; break;
		case 4:
			rep = " o "; break;
		case 5:
			rep = " #o"; break;
		case 6:
			rep = "##o"; break;
		case 8:
			rep = " oo"; break;
		case 9:
			rep = "#oo"; break;
		case 12:
			rep = "ooo"; break;
	}
	printf("%s%s%s|", (p->couleur == 1) ? GREEN : PURPLE, rep, DEFAULT_COLOR);
}
