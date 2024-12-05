#include <stdio.h>
#include <stdlib.h>

typedef struct station{
	int id;
	int capacite;
	int conso;
}Station;

typedef struct arbre{
	Station s;
	int eq;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;

int testSiFichierVide(FILE *fichier){ // vérifie si le fichier ouvert est vide ou non
    int caracterePremier = 0;
 
    caracterePremier = fgetc(fichier); 
    if(caracterePremier == EOF){
        return 1; 
    }
    rewind(fichier);
    
    return 0; 
}

// recupérer les données du fichier texte et les mettre dans la structure station;
Station *creerStation(File *fichier){

	lignes = 0;
	
	if(fichier == NULL){
		exit(1);
	}
	if(testSiFichierVide(fichier){
		fclose(fichier);
		return NULL;
	}
	
	while((c = fgetc(fichier)) != EOF){
        	if(c == '\n'){
            	lignes++;
        	}
    	}
    	rewind(fichier);
    	
    	Station *s = malloc(lignes * sizeof(Station));
    	for(int i=0; i<lignes i++){
    		scanf(fichier, "%d;%d;%d\n", &s->id, &s->capacite, &s->conso);
    	}
	fclose(fichier);
	
	return s;
}


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

int equilibre(Arbre *a){
	return hauteur(a->fd)-hauteur(a->fg);
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

Arbre *insertionAVL(Arbre *a, Station stat, int *h){
	if(estVide(a)==1){
		*h=1;
		return creerAVL(stat);
	}
	else if(stat->capacite < a->s->capacite){
		a->fg=insertionAVL(a->fg, stat, h);
		*h=-*h;
	}
	else if(stat->capacite > a->s->capacite){
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

void infixe(Arbre *a){
	if(a!=NULL){
		infixe(a->fg);
		printf("%d \n",a->elmt);
		infixe(a->fd);
	}
}

int verifFilsDroit(Arbre *a, int min){
	if(estVide(a)==1){
		return 1;
	}
	if(a!=NULL){
		
		if(a->s->capacite<min){
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
		
		if(a->s->capacite>max){
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
	int veriffd=verifFilsDroit(a->fd,a->s->capacite);
	int veriffg=verifFilsGauche(a->fg,a->s->capacite);
	if(veriffd==0||veriffg==0){
		return 0;
	}
	
	return estABR(a->fg) && estABR(a->fd);
}

int estAVL(Arbre *a){
	if(estABR&&(-1<=equilibre(a)||equilibre(a)<=1)){
		return 1;
	}
	return 0;
}

int somme(Arbre *a){
	if (a==NULL){
		return 0;
	}
	return a->s->conso+somme(a->fg)+somme(a->fd);
}

// ecris dans un fichier les données de chaque station stocké dans un arbre
void ecrireStation(Arbre *a){
	
	FILE *fichier = fopen(FICHIER_SORTIE,"w");
	
	if(fichier == NULL){
		exit(2);
	}
	fprintf(fichier, "id:capacite:conso_ttl:production\n");
	if(a != NULL){
		ecrireStation(a->fg);
		fprintf(fichier, "%d:%d:%d:%d\n",s->id, s->capacite, somme(a), (somme(a)/s->capacite));
		ecrireStation(a->fd);
	}
	fclose(fichier);
}

int main(int argc, char ** argv){
FILE* f=NULL;
Station *station=NULL;
int *h;

f=fopen("","r+");

if (f == NULL) {
	printf("Impossible d'ouvrir le fichier.\n");
	return 1;
}

char ligne[1000];
Arbre *AVL = NULL; // Initialisation de la racine de l'AVL à NULL

while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
	station=creerStation(f);
        // Insérer les données dans l'AVL
	AVL = insertionAVL(AVL,station,h);
}

if(estAVL(AVL)==0){
	printf("structure AVL incorect");
	return 1;
}

ecrireStation(AVL);

return 0;
}
