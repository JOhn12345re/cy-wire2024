//Appele du fichier.h "avl_station.h" du programme "avl_station.c"
#include "avl_station.h"


int main(int argc, char ** argv){
FILE* f=NULL;
Station s;
int h;
int n;
//argv[1] f.txt
f=fopen(argv[1],"r+");

if (f == NULL) {
	printf("Impossible d'ouvrir le fichier.\n");
	return 1;
}

char ligne[1000];

// Initialisation de la racine de l'AVL à NULL
Arbre *AVL = NULL; 

char c;
while((c = fgetc(f)) != EOF){
        if(c == '\n'){
            n++;
            printf("nb = %d\n",n);
        }
    }
rewind(f);


//Création de AVL
for(int i = 0; i<n; i++){
	fscanf(f, "%d %ld %ld\n", &s.id, &s.capacite,&s.conso);
        printf("%d %ld %ld\n", s.id, s.capacite,s.conso);
        //printf("Erreur de lecture de la ligne : %s\n", ligne);
        // Insérer les données dans l'AVL
       
	AVL = insertionAVL(AVL,s,&h);
	

}
fclose(f);


//Vérifier si l'arbre est bien un AVL
if(estAVL(AVL)==0){
	printf("structure AVL incorect");
	return 1;
}

//Création du fichier.txt de sortie
ecrireStation(AVL);

return 0;
}
