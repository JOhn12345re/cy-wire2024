#include <stdio.h>
#include <stdlib.h>

// Permet d'ajouter de la couleur aux textes
#define couleur(param) printf("\033[%sm",param)

//Structure d'une station
typedef struct station{
	int id;
	long capacite;
	long conso;
}Station;

//Structure d'un arbre AVL
typedef struct arbre{
	Station s;
	int eq;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;

//Fonctions
int testSiFichierVide(FILE *fichier);
Arbre *creerAVL(Station s);
int estVide(Arbre *a);
int estFeuille(Arbre *a);
int existeFilsGauche(Arbre *a);
int existeFilsDroite(Arbre *a);
int hauteur(Arbre *a);
int equilibre(Arbre *a);
int min(int a, int b);
int max(int a, int b);
Arbre *RotationGauche(Arbre *a);
Arbre *RotationDroite(Arbre *a);
Arbre *DblRotationGauche(Arbre *a);
Arbre *DblRotationDroite(Arbre *a);
Arbre *equilibreAVL(Arbre *a);
Arbre *insertionAVL(Arbre *a, Station stat, int *h);
int verifFilsDroit(Arbre *a, int min);
int verifFilsGauche(Arbre *a, int max);
int estABR(Arbre *a);
int estEquilibre(Arbre *a);
int estAVL(Arbre *a);
void ecrireStation(Arbre *a, FILE *fichier);
