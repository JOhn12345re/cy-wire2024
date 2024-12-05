#include <stdio.h>
#include <stdlib.h>

#include <avl_station.h>


int main(int argc, char ** argv){
FILE* f=NULL;
Station *station=NULL;
int *h;
//argv[1]
f=fopen("","r+");

if (f == NULL) {
	printf("Impossible d'ouvrir le fichier.\n");
	return 1;
}

char ligne[1000];
Arbre *AVL = NULL; // Initialisation de la racine de l'AVL à NULL

while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
	station=creerStation(f);
        // Insérer les données dans l'AVL
	AVL = insertionAVL(AVL,station,h);
}

if(estAVL(AVL)==0){
	printf("structure AVL incorect");
	return 1;
}

ecrireStation(AVL);

return 0;
}
