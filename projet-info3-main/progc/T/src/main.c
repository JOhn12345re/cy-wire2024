#include "../include/avl.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fichier;
    fichier = fopen("../../tempT.txt", "r");

    
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichierr.\n");
        return 1;
    }

    char ligne[100];
    Node *racineAVL = NULL; // Initialisation de la racine de l'AVL à NULL

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char nom[100];
        int count, total;

        // Utilisation de sscanf pour extraire les données de chaque ligne
        if (sscanf(ligne, "%[^;];%d;%d", nom, &count, &total) != 3) {
            printf("Erreur de lecture de la ligne : %s\n", ligne);
            continue;
        }

        // Insérer les données dans l'AVL
        racineAVL = insert(racineAVL, total, nom, count);
    }

    fclose(fichier);
    fichier = fopen("../../res/resT.txt", "w");

    // Utilisation de l'arbre AVL ici...
    Node *AVLalpha = NULL;

    int compteur = 0;

    addPlusGrand(racineAVL, &compteur, &AVLalpha);

    infixe(AVLalpha, fichier);

    libererArbre(racineAVL);
    libererArbre(AVLalpha);

    fclose(fichier);

    return 0;
}
