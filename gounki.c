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
	else{
		(*point_1)->x = trans_coord(line[0]);
		(*point_1)->y = 7 - trans_coord(line[1]);
		(*point_2)->x = trans_coord(line[3]);
		(*point_2)->y = 7 - trans_coord(line[4]);
		free(line);
		return 1;
	}
	return 0;
}

int game_loop(){
	int type, size, c = 0, action;
	point* point_1 = malloc(sizeof(point));
	point* point_2 = malloc(sizeof(point));
	point* point_3 = malloc(sizeof(point));
	point* point_4 = malloc(sizeof(point));

	/* initialisation puis affichage du plateau de jeu */
	plateau* p = init_plateau();
	affiche_plateau(p,0);

	while(1){
		printf("Au tour de %s%s%s > ", (c % 2 == 0) ? PURPLE : GREEN, (c % 2 == 0) ? joueur_blanc : joueur_noir, DEFAULT_COLOR);
		c++;

		action = read_line(&point_1, &point_2, &point_3, &point_4, &type, &size);

		if(!action){
			printf("Erreur, recommencez.\n");
			c--;
		}

		switch(action){
			/* cas 1: déplacement standard */
			case 1:
				if(!deplacement_possible(p, point_1, point_2, c)){
					printf("Erreur, recommencez.\n");
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
					printf("Déploiement non valide.\n");
					c--;
				}
				else{
					deploiement(p, point_1, point_2, point_3, point_4, size, type);
					affiche_plateau(p,c);	    
				}
				break;
			/* cas 3: victoire (manque fonction de détection de victoire) */
			case 3:
			case -1:
				printf("\nFin de partie !\n");
				return 0;
		}
	}
	free_plateau(p);
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
