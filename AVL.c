#include <stdio.h>
#include <stdlib.h>


typedef struct arbre{
	int elmt;
	int eq;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;

typedef struct noeud{
	Arbre* arbr;
	struct noeud* suite;
}Noeud;


Arbre *creerAVL(int val){
	Arbre *n=malloc(sizeof(Arbre));
	if(n==NULL){
		exit(1);
	}
	n->elmt=val;
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

int existeFilsGauche(Arbre *a){
	if(estVide(a)==1||a->fg==NULL){
		return 0;
	}
	return 1;
}

int existeFilsDroite(Arbre *a){
	if(estVide(a)==1||a->fd==NULL){
		return 0;
	}
	return 1;
}

Arbre *ajouterFilsGauche(Arbre *a, int e){
	if(estVide(a)==1){
		printf("vide");
		return a;
	}
	else if(existeFilsGauche(a)==1){
		printf("occupé");
		return a;
	}
	a->fg=creerAVL(e);
	
	return a;
}

Arbre *ajouterFilsDroite(Arbre *a, int e){
	if(estVide(a)==1){
		printf("vide");
		return a;
	}
	else if(existeFilsDroite(a)==1){
		printf("occupé");
		return a;
	}
	a->fd=creerAVL(e);
	return a;
}

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

int maxg(int a, int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

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

int mind(int a, int b){
	if(a<b){
		return a;
	}
	else{
		return b;
	}
}

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

void prefixe(Arbre *a){
	if(a!=NULL){
		printf("%d \n",a->elmt);
		prefixe(a->fg);
		prefixe(a->fd);
	}
}

int equilibre(Arbre *a){
	return hauteur(a->fd)-hauteur(a->fg);
}

Arbre *RotationGauche(Arbre *a){
	Arbre *pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	int eq_a=a->eq;
	int eq_b=pivot->eq;
	a->eq=eq_a-maxg(eq_b,0);
	a->eq=ming(eq_a-2,eq_a+eq_b-2, eq_b-1);
	a=pivot;
	return a;
}

Arbre *RotationDroite(Arbre *a){
	Arbre *pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	int eq_a=a->eq;
	int eq_b=pivot->eq;
	a->eq=eq_a-mind(eq_b,0)+1;
	a->eq=maxd(eq_a+2,eq_a+eq_b+2, eq_b+1);
	a=pivot;
	return a;
}

Arbre *DblRotationGauche(Arbre *a){
	a->fd=RotationDroite(a->fd);
	return RotationGauche(a);
}

Arbre *DblRotationDroite(Arbre *a){
	a->fg=RotationGauche(a->fg);
	return RotationDroite(a);
}

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

Arbre *insertionAVL(Arbre *a, int e, int *h){
	if(estVide(a)==1){
		*h=1;
		return creerAVL(e);
	}
	else if(e<a->elmt){
		a->fg=insertionAVL(a->fg, e, h);
		*h=-*h;
	}
	else if(e>a->elmt){
		a->fd=insertionAVL(a->fd, e, h);
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

Arbre *suppminAVL(Arbre *a, int *h, int *e){
	if(a->fg==NULL){
		*e=a->elmt;
		*h=-1;
		Arbre *arbr=a;
		a=a->fd;
		free(arbr);
		return a;
	}
	else{
		a->fg=suppminAVL(a->fg, h, e);
		*h=-*h;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		if(a->eq==0){
			*h=-1;
		}
		else{
			*h=0;
		}
	}
	return a;
}

Arbre *suppAVL(Arbre *a, int e, int *h){
	if(estVide(a)==1){
		*h=1;
		return a;
	}
	else if(e<a->elmt){
		a->fg=suppAVL(a->fg, e, h);
		*h=-*h;
	}
	else if(e>a->elmt){
		a->fd=suppAVL(a->fd, e, h);
	}
	else if(existeFilsDroite(a)==1){
		a->fd=suppminAVL(a->fd, h, &a->elmt);
	}
	else{
		Arbre *arbr=a;
		a=a->fg;
		free(arbr);
		*h=-1;
		return a;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		a=equilibreAVL(a);
		if(a->eq==0){
			*h=-1;
		}
		else{
			*h=0;
		}
	}
	return a;
}

int verifFilsDroit(Arbre *a, int min){
	if(estVide(a)==1){
		return 1;
	}
	if(a!=NULL){
		
		if(a->elmt<min){
			return 0;
		}
		
		verifFilsDroit(a->fg,min);
		verifFilsDroit(a->fd,min);
	}
	return 1;
}

int verifFilsGauche(Arbre *a, int max){
	if(estVide(a)==1){
		return 1;
	}
	if(a!=NULL){
		
		if(a->elmt>max){
			return 0;
		}
		verifFilsGauche(a->fg,max);
		verifFilsGauche(a->fd,max);
	}
	return 1;
}

int estABR(Arbre *a){
	if(estVide(a)==1||estFeuille(a)==1){
		return 1;
	}
	int veriffd=verifFilsDroit(a->fd,a->elmt);
	int veriffg=verifFilsGauche(a->fg,a->elmt);
	if(veriffd==0||veriffg==0){
		return 0;
	}
	
	return estABR(a->fg) && estABR(a->fd);
}

int estAVL(Arbre *a){
	if(estABR(a)&&(-1<=equilibre(a)||equilibre(a)<=1)){
		return 1;
	}
	return 0;
}


int main(){
Arbre *a=creerAVL(10);
int *h;

insertionAVL(a,3,h);

printf("\n\n");
printf("equilibre: %d\n",equilibre(a));
prefixe(a);
printf("\n\n");

insertionAVL(a,5,h);

printf("\n\n");
printf("equilibre: %d\n",equilibre(a));
prefixe(a);
printf("\n\n");

insertionAVL(a,20,h);

printf("\n\n");
printf("equilibre: %d\n",equilibre(a));
prefixe(a);
printf("\n\n");

insertionAVL(a,15,h);

printf("\n\n");
printf("equilibre: %d\n",equilibre(a));
prefixe(a);
printf("\n\n");

insertionAVL(a,12,h);

printf("\n\n");
printf("equilibre: %d\n",equilibre(a));
prefixe(a);
printf("\n\n");

insertionAVL(a,7,h);

printf("\n\n");
printf("equilibre: %d\n",equilibre(a));
prefixe(a);
printf("\n\n");

insertionAVL(a,9,h);

printf("\n\n");
printf("equilibre: %d\n",equilibre(a));
prefixe(a);
printf("\n\n");

printf("\n%d\n",estAVL(a));

return 0;
}








