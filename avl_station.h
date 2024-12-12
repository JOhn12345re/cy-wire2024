#include <stdio.h>
#include <stdlib.h>
#define couleur(param) printf("\033[%sm",param)

//Structures
typedef struct station{
	int id;
	long capacite;
	long conso;
}Station;

typedef struct arbre{
	Station s;
	int eq;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;

//Fonctions
int testSiFichierVide(FILE *fichier);
Station creerStation(FILE *fichier);
Arbre *creerAVL(Station s);
int estVide(Arbre *a);
int estFeuille(Arbre *a);
int existeFilsGauche(Arbre *a);
int existeFilsDroite(Arbre *a);
int hauteur(Arbre *a);
int equilibre(Arbre *a);
int ming(int a, int b, int c);
int mind(int a, int b);
int maxd(int a, int b, int c);
Arbre *RotationGauche(Arbre *a);
Arbre *RotationDroite(Arbre *a);
Arbre *DblRotationGauche(Arbre *a);
Arbre *DblRotationDroite(Arbre *a);
Arbre *equilibreAVL(Arbre *a);
Arbre *insertionAVL(Arbre *a, Station stat, int *h);
void infixe(Arbre *a);
int verifFilsDroit(Arbre *a, int min);
int verifFilsGauche(Arbre *a, int max);
int estABR(Arbre *a);
int estAVL(Arbre *a);
double somme(Arbre *a);
void ecrireStation(Arbre *a);
