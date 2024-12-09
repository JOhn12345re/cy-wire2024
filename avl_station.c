/*
#include <stdio.h>
#include <stdlib.h>

//Structure de la station
typedef struct station{
	int id;
	int capacite;
	int conso;
}Station;

//Structure de l'arbre
typedef struct arbre{
	Station s;
	int eq;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;
*/

#include "avl_station.h"

//Vérifie si le fichier ouvert est vide ou non
int testSiFichierVide(FILE *fichier){ 
    int caracterePremier = 0;
 
    caracterePremier = fgetc(fichier); 
    if(caracterePremier == EOF){
        return 1; 
    }
    rewind(fichier);
    
    return 0; 
}

//Recupérer les données du fichier texte et les mettre dans la structure station;
Station *creerStation(FILE *fichier){

	int lignes = 0;
	
	if(fichier == NULL){
		exit(1);
	}
	if(testSiFichierVide(fichier)){
		fclose(fichier);
		return NULL;
	}

//Compte le nombre de ligne du fichier
	char c;
	while((c = fgetc(fichier)) != EOF){
        	if(c == '\n'){
            	lignes++;
        	}
    	}
    	rewind(fichier);
    	
//Créer la structure Station
    	Station *s = malloc(lignes * sizeof(Station));
    	for(int i=0; i<lignes; i++){
    		if(fscanf(fichier, "%d %d %d\n", &s->id, &s->capacite ,&s->conso) != 3){
			printf("Le nombre de données n'est pas correcte !\n");
			exit(2);
		}
    	}
	fclose(fichier);
	
	return s;
}

//Créer l'arbre AVL
Arbre *creerAVL(Station s){
	Arbre *n=malloc(sizeof(Arbre));
	if(n==NULL){
		exit(3);
	}
	n->s=s;
	n->fg=NULL;
	n->fd=NULL;
	n->eq=0;
	return n;
}

//Vérifie si AVL est vide
int estVide(Arbre *a){
	if(a==NULL){
		return 1;
	}
	return 0;
}

//Vérifie si le noeud est une feuille
int estFeuille(Arbre *a){
	if(estVide(a)==1){
		printf("vide");
		return 0;
	}
	if(a->fg!=NULL||a->fd!=NULL){
		return 0;
	}
	return 1;
}

//Vérifie si le fils gauche existe
int existeFilsGauche(Arbre *a){
	if(estVide(a)==1||a->fg==NULL){
		return 0;
	}
	return 1;
}

//Vérifie si le fils droit existe
int existeFilsDroite(Arbre *a){
	if(estVide(a)==1||a->fd==NULL){
		return 0;
	}
	return 1;
}

//Calcul la hauteur de AVL
int hauteur(Arbre *a){
	if(estVide(a)==1){
		return -1;
	}
	if(estFeuille(a)==1){
		return 0;
	}
	if(existeFilsGauche(a)==1 && existeFilsDroite(a)==1){
		if(hauteur(a->fg)>hauteur(a->fd)){
			return 1+hauteur(a->fg);
		}
		else{
			return 1+hauteur(a->fd);
		}
	}
}

//Calcul l'équilibre de AVL
int equilibre(Arbre *a){
	return hauteur(a->fd)-hauteur(a->fg);
}

//Maximum entre une valeur a et b
int maxg(int a, int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

//Minimum entre une valeur a,b et c
int ming(int a, int b, int c){
	if(a<b){
		if(a<c){
			return a;
		}
		else{
			return c;
		}
	}
	else{
		if(b<c){
			return b;
		}
		else{
			return c;
		}
	}
}

//Minimum entre une valeur a et b
int mind(int a, int b){
	if(a<b){
		return a;
	}
	else{
		return b;
	}
}

//Maximum entre une valeur a,b et c
int maxd(int a, int b, int c){
	if(a>b){
		if(a>c){
			return a;
		}
		else{
			return c;
		}
	}
	else{
		if(b>c){
			return b;
		}
		else{
			return c;
		}
	}
}

//Rotation gauche
Arbre *RotationGauche(Arbre *a){
	Arbre *pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	int eq_a=a->eq;
	int eq_b=pivot->eq;
	a->eq=eq_a-maxg(eq_b,0)-1;
	pivot->eq=ming(eq_a-2,eq_a+eq_b-2, eq_b-1);
	a=pivot;
	return a;
}

//Rotation droite
Arbre *RotationDroite(Arbre *a){
	Arbre *pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	int eq_a=a->eq;
	int eq_b=pivot->eq;
	a->eq=eq_a-mind(eq_b,0)+1;
	pivot->eq=maxd(eq_a+2,eq_a+eq_b+2, eq_b+1);
	a=pivot;
	return a;
}

//Double rotation gauche
Arbre *DblRotationGauche(Arbre *a){
	a->fd=RotationDroite(a->fd);
	return RotationGauche(a);
}

//Double rotation droite
Arbre *DblRotationDroite(Arbre *a){
	a->fg=RotationGauche(a->fg);
	return RotationDroite(a);
}

//Réequilibrer AVL
Arbre *equilibreAVL(Arbre *a){
	if(equilibre(a)>=2){
		if(equilibre(a->fd)>=0){
			return RotationGauche(a);
		}
		else{
			return DblRotationGauche(a);
		}
	}
	else if(equilibre(a)<=-2){
		if(equilibre(a->fd)<=0){
			return RotationDroite(a);
		}
		else{
			return DblRotationDroite(a);
		}
	}
	return a;
}

//Inserer un nouveaux noeud dans AVL
Arbre *insertionAVL(Arbre *a, Station stat, int *h){
	if(estVide(a)==1){
		*h=1;
		return creerAVL(stat);
	}
	else if(stat.capacite < a->s.capacite){
		a->fg=insertionAVL(a->fg, stat, h);
		*h=-*h;
	}
	else if(stat.capacite > a->s.capacite){
		a->fd=insertionAVL(a->fd, stat, h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		a=equilibreAVL(a);
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

//Parcours Infixe de AVL
void infixe(Arbre *a){
	if(a!=NULL){
		infixe(a->fg);
		printf("%d \n",a->s);
		infixe(a->fd);
	}
}

//Vérifier si le fils droit est en norme
int verifFilsDroit(Arbre *a, int min){
	if(estVide(a)==1){
		return 1;
	}
	if(a!=NULL){
		
		if(a->s.capacite<min){
			return 0;
		}
		
		verifFilsDroit(a->fg,min);
		verifFilsDroit(a->fd,min);
	}
	return 1;
}

//Vérifier si le fils gauche est en norme
int verifFilsGauche(Arbre *a, int max){
	if(estVide(a)==1){
		return 1;
	}
	if(a!=NULL){
		
		if(a->s.capacite>max){
			return 0;
		}
		verifFilsGauche(a->fg,max);
		verifFilsGauche(a->fd,max);
	}
	return 1;
}

//Vérifier si l'arbre est un ABR
int estABR(Arbre *a){
	if(estVide(a)==1||estFeuille(a)==1){
		return 1;
	}
	int veriffd=verifFilsDroit(a->fd,a->s.capacite);
	int veriffg=verifFilsGauche(a->fg,a->s.capacite);
	if(veriffd==0||veriffg==0){
		return 0;
	}
	
	return estABR(a->fg) && estABR(a->fd);
}

//Vérifier si l'arbre est un AVL
int estAVL(Arbre *a){
	if(estABR&&(-1<=equilibre(a)||equilibre(a)<=1)){
		return 1;
	}
	return 0;
}

//Somme de l'ensemble des noeuds de l'arbre
int somme(Arbre *a){
	if (a==NULL){
		return 0;
	}
	if(){
		return a->s.conso+somme(a->fg)+somme(a->fd);
	}
}

//Ecris dans un fichier les données de chaque station stocké dans un arbre
void ecrireStation(Arbre *a){
	
	FILE *fichier = fopen(FICHIER_SORTIE,"w");
	
	if(fichier == NULL){
		exit(4);
	}
	//Premiére ligne
	//Données: identifiants, capacité, consomation totale et production
	fprintf(fichier, "id:capacite:conso_ttl:production\n");
	if(a != NULL){
		ecrireStation(a->fg);
		fprintf(fichier, "%d:%d:%d:%d\n",a->s.id, a->s.capacite, somme(a), (somme(a)/a->s.capacite));
		ecrireStation(a->fd);
	}
	fclose(fichier);
}
