CC = gcc
SRC =$(wildcard *.c)
HEADER =$(wildcard *.h)
OBJ =$(SRC:.c=.o)

all: exec

%.o : %.c $(HEADER)
		$(CC) -c $< -o $@
exec: $(OBJ)
		$(CC) $^ -o $@
		
clean:
	rm -f *.o
	rm -f exec
