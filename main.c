

//Appele du fichier.h "avl_station.h" du programme "avl_station.c"
#include "avl_station.h"


int main(int argc, char ** argv){
FILE* f=NULL;
Station *station=NULL;
int *h;
//argv[1] f.txt
f=fopen("test.csv","r+");

if (f == NULL) {
	printf("Impossible d'ouvrir le fichier.\n");
	return 1;
}

char ligne[1000];

// Initialisation de la racine de l'AVL à NULL
Arbre *AVL = NULL; 

//Création de AVL
while (fgets(ligne, sizeof(ligne), f) != NULL) {
	station=creerStation(f);
        // Insérer les données dans l'AVL
	AVL = insertionAVL(AVL,*station,h);
}

//Vérifier si l'arbre est bien un AVL
if(estAVL(AVL)==0){
	printf("structure AVL incorect");
	return 1;
}

//Création du fichier.txt de sortie
ecrireStation(AVL);

return 0;
}
