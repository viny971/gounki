#include "gounki.h"

int read_options(int argc, char* argv[]){
	int i, options = 0;
	/* si il n'y a pas d'option, la fonction return*/
	if(argc <= 1){
		return options;
	}
	else{ 
		for(i=1 ; i < argc ; i++){
			/* recherche du mode test */
			if(!strcmp(argv[i],"-t")){
				options |= 1 << OPTION_TEST;
			}
			/* recherche du joueur blanc*/
			if(!strcmp(argv[i],"-B")){
				/* détermine robot ou humain */
				if((i+1) < argc && !strcmp(argv[i+1],"humain")){
					/* possibilité de personnaliser le nom */
					if((i+2) < argc && argv[i+2][0] != '-'){
						joueur_blanc = argv[i+2];	
					}
				}
				else{
					if((i+1) < argc && !strcmp(argv[i+1],"robot")){
						/* possibilité de choisir le robot */
						if((i+2) < argc && argv[i+2][0] != '-'){
							if(!strcmp(argv[i+2],"basique")){
								options |= 1 << OPTION_JOUEURBLANC_BASIQUE;
								/* change le nom en robot basique */
								joueur_blanc = "robot basique";	
							}
							else{
								options |= 1 << OPTION_JOUEURBLANC_ROBOT;
								/* change le nom en robot basique */
								joueur_blanc = "robot aléatoire";	
							}
						}
					}
				}
			}
			/* recherche du joueur noir*/
			if(!strcmp(argv[i],"-N")){
				/* détermine robot ou humain */
				if((i+1) < argc && !strcmp(argv[i+1],"humain")){
					/* possibilité de personnaliser le nom */
					if((i+2) < argc && argv[i+2][0] != '-'){
						joueur_noir = argv[i+2];	
					}
				}
				else{
					if((i+1) < argc && !strcmp(argv[i+1],"robot")){
						/* possibilité de choisir le robot */
						if((i+2) < argc && argv[i+2][0] != '-'){
							if(!strcmp(argv[i+2],"basique")){
								options |= 1 << OPTION_JOUEURNOIR_BASIQUE;
								/* change le nom en robot */
								joueur_noir = "robot basique";	
							}
							else{
								options |= 1 << OPTION_JOUEURNOIR_ROBOT;
								/* change le nom en robot */
								joueur_noir = "robot aléatoire";	
							}
						}
					}
				}
			}
		}
		return options;
	}
	return options;
}

int trans_options(int options){
	/* on va suivre la règle suivante:
	   0 = Humain blanc vs Humain noir
	   1 = Aléatoire blanc vs Humain noir
	   2 = Basique blanc vs Humain noir
	   3 = Humain blanc vs Aléatoire noir
	   4 = Aléatoire blanc vs Aléatoire noir
	   5 = Basique blanc vs Aléatoire noir
	   6 = Humain blanc vs Basique noir
	   7 = Aléatoire blanc vs Basique noir
	   8 = Basique blanc vs Basique noir */
	int rep = 0;
	/* options du joueur blanc: +3 pour un humain, +4 pour un robot aléatoire, +5 pour un robot basique */
	if(!(options & (1 << OPTION_JOUEURBLANC_ROBOT))){
		if(!(options & (1 << OPTION_JOUEURBLANC_BASIQUE))){
	   		rep += 3;
		}
	}
	if(options & (1 << OPTION_JOUEURBLANC_ROBOT)){
	   	rep += 4;
	}
	if(options & (1 << OPTION_JOUEURBLANC_BASIQUE)){ 
		rep += 5;
	}
	/* options du joueur noir: -3 pour un humain, +0 pour un robot aléatoire, +3 pour un robot basique */
	if(!(options & (1 << OPTION_JOUEURNOIR_ROBOT))){
		if(!(options & (1 << OPTION_JOUEURNOIR_BASIQUE))){
	   		rep -= 3;
		}
	}
	/* ligne inutile mais on laisse pour la clarté */
	if(options & (1 << OPTION_JOUEURNOIR_ROBOT)){
	   	rep += 0;
	}
	if(options & (1 << OPTION_JOUEURNOIR_BASIQUE)){
	   	rep += 3;
	}
	return rep;
}

int read_line(point** point_1, point** point_2, point** point_3, point** point_4,  int* type, int* size_line){
	char* line = NULL;
	int length;
	size_t size;

	/* lecture de la ligne */
	length = getline(&line, &size, stdin);

	/* test de fin de fichier */
	if(length == -1){
		return -1;
	}

	/* retourne 2 si c'est un déploiement */
	if(line[2] == '+' || line[2] == '*'){

		/* si la commande entrée est trop courte ou trop longue */
		if(length < 9 || length > 12){
			return 0;
		}
		/* transformation des coordonées */
		(*point_1)->x = trans_coord(line[0]);
		(*point_1)->y = 7 - trans_coord(line[1]);
		
		if(length == 9 || length == 12) {
			(*point_2)->x = trans_coord(line[3]);
			(*point_2)->y = 7 - trans_coord(line[4]);
			(*point_3)->x = trans_coord(line[6]);
			(*point_3)->y = 7 - trans_coord(line[7]);
		}
		if(length == 12) {
			(*point_4)->x = trans_coord(line[9]);
			(*point_4)->y = 7 - trans_coord(line[10]);
		}
		/* enregistrement du type de déploiement */
		if(line[2] == '+'){
			*type = 1;
		}
		else{
			*type = 2;
		}
		/* entrée de la longueur de la ligne */
		*size_line = length;
		free(line);
		return 2;
	}
	/* retourne 3 si une victoire doit être détectée */
	if(line[2] == '#'){
		(*point_1)->x = trans_coord(line[0]);
		(*point_1)->y = 7 - trans_coord(line[1]);
		free(line);
		return 3;
	}
	/* retourne 1 si c'est un déplacement */
	else if(line[2] == '-'){
		(*point_1)->x = trans_coord(line[0]);
		(*point_1)->y = 7 - trans_coord(line[1]);
		(*point_2)->x = trans_coord(line[3]);
		(*point_2)->y = 7 - trans_coord(line[4]);
		free(line);
		return 1;
	}
	else{
		return 0;
	}
}

int game_loop(int options){
	int type, size, c = 0, action, fin;
	point* point_1 = malloc(sizeof(point));
	point* point_2 = malloc(sizeof(point));
	point* point_3 = malloc(sizeof(point));
	point* point_4 = malloc(sizeof(point));

	/* initialisation puis affichage du plateau de jeu */
	plateau* p = init_plateau();
	affiche_plateau(p,0);

	while(!plus_de_pion(p, c)){
		printf("Au tour de %s%s%s > ", (c % 2 == 0) ? PURPLE : GREEN, (c % 2 == 0) ? joueur_blanc : joueur_noir, DEFAULT_COLOR);

		switch(options){
			case 0:
				action = read_line(&point_1, &point_2, &point_3, &point_4, &type, &size);
				break;
			case 1:
				if(c % 2 == 0){
					action = ia_random(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				else if(c % 2 == 1){
					action = read_line(&point_1, &point_2, &point_3, &point_4, &type, &size);
				}
				break;
			case 2:
				if(c % 2 == 0){
					action = ia_basique(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				else if(c % 2 == 1){
					action = read_line(&point_1, &point_2, &point_3, &point_4, &type, &size);
				}
				break;
			case 3:
				if(c % 2 == 0){
					action = read_line(&point_1, &point_2, &point_3, &point_4, &type, &size);
				}
				else if(c % 2 == 1){
					action = ia_random(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				break;
			case 4:
				if(c % 2 == 0){
					action = ia_random(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				else if(c % 2 == 1){
					action = ia_random(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				break;
			case 5:
				if(c % 2 == 0){
					action = ia_basique(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				else if(c % 2 == 1){
					action = ia_random(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				break;
			case 6:
				if(c % 2 == 0){
					action = read_line(&point_1, &point_2, &point_3, &point_4, &type, &size);
				}
				else if(c % 2 == 1){
					action = ia_basique(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				break;
			case 7:
				if(c % 2 == 0){
					action = ia_random(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				else if(c % 2 == 1){
					action = ia_basique(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				break;
			case 8:
				if(c % 2 == 0){
					action = ia_basique(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				else if(c % 2 == 1){
					action = ia_basique(p, &point_1, &point_2, &point_3, &point_4, &size, c);
				}
				break;
		}
		/* incrémentation du numéro du tour */
		c++;

		if(!action){
			printf("Erreur: entrée non reconnue.\n");
			c--;
		}

		switch(action){
			/*case 0:
				fprintf(stderr, "2");
				fprintf(stdout, "Erreur dans la lecture des coordonnées\n");
				return 1; break;*/
			/* cas 1: déplacement standard */
			case 1:
				if(!deplacement_possible(p, point_1, point_2, c)){
					printf("Erreur: déplacement non reconnu.\n");
					c--;
				}
				else{
					deplacement(p, point_1, point_2);
					affiche_plateau(p,c);
				}
				break;
			/* cas 2: déploiement */
			case 2:
				if(!deploiement_possible(p, point_1, point_2, point_3, point_4, type, c)){
					printf("Erreur: déploiement non reconnu.\n");
					c--;
				}
				else{
					deploiement(p, point_1, point_2, point_3, point_4, size, type);
					affiche_plateau(p,c);	    
				}
				break;
			/* cas 3: victoire */
			case 3:
				fin = end_game(p, point_1, c);
				if(!fin){
					printf("Erreur: victoire non reconnue.\n");
					c--;
				}
				else{
					printf("\nVictoire de %s%s%s !\n", ((c+1) % 2 == 0) ? PURPLE : GREEN, ((c+1) % 2 == 0) ? joueur_blanc : joueur_noir, DEFAULT_COLOR);
					free_plateau(p); free(point_1); free(point_2); free(point_3); free(point_4);
					return 0;
				}
				break;
			case  4:
			case -1:
				printf("\nFin de partie !\n");
				free_plateau(p); free(point_1); free(point_2); free(point_3); free(point_4);
				return 0;
		}
	}
	printf("\nFin de partie:");
	printf("\nVictoire de %s%s%s !\n", ((c+1) % 2 == 0) ? PURPLE : GREEN, ((c+1) % 2 == 0) ? joueur_blanc : joueur_noir, DEFAULT_COLOR);
	free_plateau(p); free(point_1); free(point_2); free(point_3); free(point_4);
	return 0;	
}

int main(int argc, char* argv[]){
	int rep, options;

	/* lecture des options */
	options = read_options(argc, argv);
	/* transformation des options */
	options = trans_options(options);
	/* lancement d'une partie */
	rep = game_loop(options);
	
	return rep;
}
