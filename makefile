// 'make' pour compiler tous les fichiers
// 'make clean' pour effacer les fichiers sortants

all: exec

main.o : main.c *.h
	gcc -c main.c -o main.o
	
avl_station.o : avl_station.c *.h
	gcc -c avl_station.c -o avl_station.o

exec : main.o avl_station.o
	gcc *.o -o exec

clean :
	rm -f *.o
	rm -f resultat.txt
