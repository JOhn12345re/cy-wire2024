#include "../include/avl.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fichier;
    fichier = fopen("../../tempS.txt", "r"); // Remplacez "votre_fichier.txt" par le nom de votre fichier

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    char ligne[100];
    Node *racineAVL = NULL; // Initialisation de la racine de l'AVL à NULL

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int id;
        float min, avg, max, dif;

        // Utilisation de sscanf pour extraire les données de chaque ligne
        if (sscanf(ligne, "%d;%f;%f;%f;%f", &id, &min, &avg, &max, &dif) != 5) {
            printf("Erreur de lecture de la ligne : %s\n", ligne);
            continue;
        }

        // Insérer les données dans l'AVL
        racineAVL = insert(racineAVL, id, min, avg, max, dif);
    }

    fclose(fichier);
    
    fichier=fopen("../../res/resS.txt","w");
    int compteur=0;
    infixe(racineAVL, fichier, &compteur);
    fclose(fichier);
    

    // Libération de la mémoire allouée pour l'arbre à la fin de l'utilisation
    libererArbre(racineAVL);

    return 0;
}
