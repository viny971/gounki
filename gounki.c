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
						options |= 1 << OPTION_JOUEURBLANC_ROBOT;
						/* change le nom en robot */
						joueur_blanc = "robot";	
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
						options |= 1 << OPTION_JOUEURNOIR_ROBOT;
						/* change le nom en robot */
						joueur_noir = "robot";	
					}
				}
			}
		}
		return options;
	}
	return options;
}

int read_line(int* x1, int* y1, int* x2, int* y2, int* x3, int* y3, int* x4, int* y4, int* type, int* size_line){
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
		*x1 = trans_coord(line[0]);
		*y1 = 7 - trans_coord(line[1]);
		
		if(length == 9 || length == 12) {
			*x2 = trans_coord(line[3]);
			*y2 = 7 - trans_coord(line[4]);
			*x3 = trans_coord(line[6]);
			*y3 = 7 - trans_coord(line[7]);
		}
		if(length == 12) {
			*x4 = trans_coord(line[9]);
			*y4 = 7 - trans_coord(line[10]);
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

int game_loop(){
	int  x1, y1, x2, y2, x3, y3, x4, y4, type, size, c = 0, action;

	/* initialisation puis affichage du plateau de jeu */
	plateau* p = init_plateau();
	affiche_plateau(p,0);

	while(1){
		printf("Au tour de %s%s%s > ", (c % 2 == 0) ? PURPLE : GREEN, (c % 2 == 0) ? joueur_blanc : joueur_noir, DEFAULT_COLOR);
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
					affiche_plateau(p,c);
				}
				break;
			/* cas 2: déploiement */
			case 2:
				if(!deploiement_possible(p,x1, y1, x2, y2, x3, y3, x4, y4, type, c)){
					printf("Déploiement non valide.\n");
					c--;
				}
				else{
					/*fprintf(stdout, "\nx1: %d, y1: %d, x2: %d, y2: %d, x3: %d, y3: %d, x4: %d, y4: %d, size: %d, type: %d\n", x1, y1, x2, y2, x3, y3, x4, y4, size, type);
					deploiement(p,x1, y1, x2, y2, x3, y3, x4, y4, size, type);*/
					fprintf(stdout, "Deplacement possible");
					affiche_plateau(p,c);	    
				}
				break;
			/* cas 3: victoire (manque fonction de détection de victoire */
			case 3:
			case -1:
				printf("\nFin de partie !\n");
				return 0;
		}
	}
	return 0;	
}

int main(int argc, char* argv[]){
	int rep, options;

	/* lecture des options */
	options = read_options(argc, argv);
	if(options & (1 << OPTION_TEST)){
	}

	/* lancement d'une partie */
	rep = game_loop();
	
	return rep;
}
