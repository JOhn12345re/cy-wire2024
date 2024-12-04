#include <stdio.h>
#include <stdlib.h>

typedef struct station{
	int id;
	int capacite;
	int cosomation;
}Station;

typedef struct arbre{
	Station s;
	int eq;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;


Arbre *creerAVL(Station s){
	Arbre *n=malloc(sizeof(Arbre));
	if(n==NULL){
		exit(1);
	}
	n->elmt=s;
	n->fg=NULL;
	n->fd=NULL;
	n->eq=0;
	return n;
}

int estVide(Arbre *a){
	if(a==NULL){
		return 1;
	}
	return 0;
}
