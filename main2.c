#include <stdio.h>
#include <stdlib.h>
#include "avl_station.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        couleur("31");  // Texte rouge pour les erreurs
        printf("Erreur : Nombre insuffisant d'arguments.\n");
        couleur("0");  // Réinitialisation de la couleur
        printf("Usage: %s <chemin_fichier_txt>\n", argv[0]);
        return 1;
    }

    // Paramètre récupéré depuis les arguments du shell
    char *chemin_txt = argv[1];  // Le chemin vers le fichier .txt

    // Ouverture du fichier .txt
    FILE *f = fopen(chemin_txt, "r");
    if (f == NULL) {
        couleur("31");
        printf("\nImpossible d'ouvrir le fichier %s.\n", chemin_txt);
        couleur("0");
        return 1;
    }

    if (testSiFichierVide(f)) {
        couleur("33");  // Texte jaune pour avertissement
        printf("Le fichier %s est vide !\n", chemin_txt);
        couleur("0");
        fclose(f);
        return 1;
    }

    // Initialisation de la racine de l'AVL à NULL
    Arbre *AVL = NULL;
    Station s;
    int h;

    // Lecture des données du fichier et insertion dans l'arbre AVL
    while (fscanf(f, "%d %ld %ld", &s.id, &s.capacite, &s.conso) == 3) {
        AVL = insertionAVL(AVL, s, &h);
    }

    fclose(f);

    // Vérification si l'arbre est un AVL
    if (!estAVL(AVL)) {
        couleur("31");
        printf("\nStructure AVL incorrecte.\n");
        couleur("0");
        free(AVL);  // Libération de la mémoire avant de quitter
        return 1;
    }

    // Chemin du fichier de sortie dans /tmp
    const char *chemin_sortie = "/tmp/resultat.txt";

    // Création du fichier de sortie
    FILE *fichier = fopen(chemin_sortie, "w");
    if (fichier == NULL) {
        couleur("31");
        printf("\nErreur lors de la création du fichier de sortie dans /tmp.\n");
        couleur("0");
        free(AVL);  // Libération de la mémoire avant de quitter
        return 1;
    }

    // Première ligne du fichier résultat
    fprintf(fichier, "id:capacite:conso_ttl\n");

    // Écriture des résultats dans le fichier
    ecrireStation(AVL, fichier);
    fclose(fichier);

    // Libération de la mémoire de l'arbre AVL
    free(AVL);

    couleur("32");  // Texte vert pour succès
    printf("Traitement terminé avec succès. Résultats écrits dans '%s'.\n", chemin_sortie);
    couleur("0");

    return 0;
}

