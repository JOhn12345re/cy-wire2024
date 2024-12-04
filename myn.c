#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv){

float m=0;
int i;

for(i=1; i<argc; i++){
	m+=atof(argv[i]);
}

printf("\%f\n",m/(argc-1));

return 0;
}
