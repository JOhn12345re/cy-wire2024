//Appele du fichier.h "avl_station.h" du programme "avl_station.c"
#include "avl_station.h"


int main(int argc, char ** argv){

FILE* f=NULL;
Station s;

int h;
int ligne;
char c;

if (argc < 2) {
        couleur("31");  // Texte rouge pour les erreurs
        printf("Erreur : Nombre insuffisant d'arguments.\n");
        couleur("0");  // Réinitialisation de la couleur
        printf("Usage: %s <chemin_fichier_txt>\n", argv[0]);
        return 1;
}

// Ouverture du fichier en parametre
f=fopen(argv[1],"r+");

// Message d'erreur si le fichier est NULL
if (f == NULL) {
        couleur("31");
        printf("\nImpossible d'ouvrir le fichier %s.\n", argv[1]);
        couleur("0");
        return 1;
}

if (testSiFichierVide(f)) {
        couleur("33");  // Texte jaune pour avertissement
        printf("Le fichier %s est vide !\n", argv[1]);
        couleur("0");
        fclose(f);
        return 1;
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
if (!estAVL(AVL)) {
        couleur("31");
        printf("\nStructure AVL incorrecte.\n");
        couleur("0");
        free(AVL);  // Libération de la mémoire avant de quitter
        return 1;
}


//Création du fichier.txt de sortie
// Chemin du fichier de sortie dans /tmp

    // Création du fichier de sortie
FILE *fichier = fopen("resultat.txt", "w");
if (fichier == NULL) {
        couleur("31");
        printf("\nErreur lors de la création du fichier de sortie dans /tmp.\n");
        couleur("0");
        free(AVL);  // Libération de la mémoire avant de quitter
        return 1;
}
//Premiére ligne
//Données: identifiants, capacité et consomation totale
fprintf(fichier, "id:capacite:conso_ttl\n");
//Fichier de sortie des résultats
ecrireStation(AVL,fichier);
fclose(fichier);

free(AVL);

couleur("32");  // Texte vert pour succès
printf("Traitement terminé avec succès. Résultats écrits dans 'resultat.txt'.\n");
couleur("0");
	
return 0;
}
