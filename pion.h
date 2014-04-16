#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BG_LIGHT
#define GREEN    "\033[1;32m"
#define PURPLE   "\033[1;35m"
#define DEFAULT_COLOR "\033[0;m"
#endif /* endif BG_LIGHT */

typedef struct pion{
/* * Couleur: Vert(1) ou violet(0)
   * Taille: 1, 2 ou 3 selon le nombre
   * Forme 
   	* 1: carré 
	* 2: carré + carré 
	* 3: carré + carré + carré 
	* 4: rond 
	* 5: carré + rond 
	* 6: carré + carré + rond 
	* 8: rond + rond 
	* 9: carré + rond + rond 
	* 12: rond + rond + rond 
*/
	int couleur; 
	int taille;
	int forme; 
} pion;

pion* init_pion(int couleur, int forme);
void affiche_pion(pion* p);
