//Appele du fichier.h "avl_station.h" du programme "avl_station.c"
#include "avl_station.h"


int main(int argc, char ** argv){

FILE* f=NULL;
Station s;

int h;
int ligne;
char c;


// Ouverture du fichier en parametre
f=fopen(argv[1],"r+");

// Message d'erreur si le fichier est NULL
if (f == NULL) {
	printf("\nImpossible d'ouvrir le fichier.\n");
	return 1;
}

if(testSiFichierVide(f)){
	printf("Le fichier sortant est vide !\n");
	exit(1);
}
 
// Initialisation de la racine de l'AVL à NULL
Arbre *AVL = NULL; 

// Compte le nombre de ligne du fichier f
while((c = fgetc(f)) != EOF){
        if(c == '\n'){
            ligne++;
        }
    }
rewind(f);

//Création de AVL
for(int i = 0; i<ligne; i++){
//printf("Erreur de lecture de la ligne : %s\n", ligne);
	if(fscanf(f, "%d %ld %ld\n", &s.id, &s.capacite,&s.conso)!=3){
		printf("\nNombre de variable incorrect\n");
		return 1;
	}
        
        // Insérer les données dans l'AVL
	AVL = insertionAVL(AVL,s,&h);
}
fclose(f);


//Vérifier si l'arbre est bien un AVL
if(estAVL(AVL)==0){
	printf("\nStructure AVL incorrect\n");
	return 1;
}


//Création du fichier.txt de sortie
FILE *fichier = fopen("resultat.txt","w");
//Premiére ligne
//Données: identifiants, capacité et consomation totale
fprintf(fichier, "id:capacite:conso_ttl\n");
//Fichier de sortie des résultats
ecrireStation(AVL,fichier);
fclose(fichier);

return 0;
}
