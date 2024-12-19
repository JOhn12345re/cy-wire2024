#include "avl_station.h"

int main(int argc, char **argv) {
    FILE *f = NULL;
    Station s;
    int h = 0;  // Hauteur de l'arbre AVL (utile pour la rotation)
    int ligne = 0;  // Compteur de lignes
    char c;
    
    // Vérifie si le nombre d'arguments est incorrect
    if (argc < 2) {
        couleur("31");  // Texte rouge pour les erreurs
        printf("Erreur : Nombre insuffisant d'arguments.\n");
        couleur("0");  // Réinitialisation de la couleur
        printf("Usage: %s <chemin_fichier_txt>\n", argv[0]);
        return 1;
    }

    // Ouverture du fichier en paramètre
    f = fopen(argv[1], "r");
    if (f == NULL) {
        couleur("31");
        printf("\nImpossible d'ouvrir le fichier %s.\n", argv[1]);
        couleur("0");
        return 1;
    }

    // Vérifie si le fichier est vide
    if (testSiFichierVide(f)) {
        couleur("33");  // Texte jaune pour avertissement
        printf("Le fichier %s est vide !\n", argv[1]);
        couleur("0");
        fclose(f);
        return 1;
    }

    // Compte le nombre de lignes du fichier
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            ligne++;
        }
    }
    rewind(f);  // Remet le pointeur au début du fichier

    // Initialisation de la racine de l'AVL
    Arbre *AVL = NULL;

    // Lecture et insertion des données dans l'AVL
for(int i = 0; i<ligne; i++){
//printf("Erreur de lecture de la ligne : %s\n", ligne);
	if(fscanf(f, "%d %ld %ld", &s.id, &s.capacite,&s.conso) != 3){
		couleur("31");
		printf("\nNombre de variable incorrect\n");
		couleur("0");
		return 1;
	}
        // Insérer les données dans l'AVL
	AVL = insertionAVL(AVL,s,&h);
}
fclose(f); // Ferme le fichier d'entrée

    // Vérifie si l'arbre est bien un AVL
    if (!estAVL(AVL)) {
        couleur("31");
        printf("\nStructure AVL incorrecte.\n");
        couleur("0");
        free(AVL);  // Libération de la mémoire
        return 1;
    }

    // Création du fichier de sortie
    FILE *fichier = fopen("resultat.txt", "w");
    if (fichier == NULL) {
        couleur("31");
        printf("\nErreur lors de la création du fichier de sortie.\n");
        couleur("0");
        free(AVL);  // Libération de la mémoire
        return 1;
    }

    // Écriture des résultats dans le fichier
    fprintf(fichier, "id:capacite:conso_ttl\n");  // Première ligne
    ecrireStation(AVL, fichier);  // Écriture des stations dans le fichier
    fclose(fichier);  // Ferme le fichier de sortie

    // Libère la mémoire et termine le programme
    free(AVL);
    couleur("32");  // Texte vert pour succès
    printf("Traitement terminé avec succès. Résultats écrits dans 'resultat.txt'.\n");
    couleur("0");
    return 0;
}
