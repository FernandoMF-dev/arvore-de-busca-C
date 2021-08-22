CC = gcc
flags = -c -Wall
CFLAGS = -lm
ARQUIVOS = *.o
OBJS = arvore-binaria.o pessoa.o main.o
EXE = main
MAIN = main.c

all: main.o
	$(CC) $(OBJS) -o $(EXE)
	./main

main.o: arvore-binaria.o pessoa.o main.c
	$(CC) $(flags) $(MAIN) $(CLFLAGS)

arvore-binaria.o: arvore-binaria.c
	$(CC) $(flags) arvore-binaria.c

pessoa.o: pessoa.c
	$(CC) $(flags) pessoa.c

passos: main.c
	gcc -E main.c -o main.i
	gcc -S main.i -o main.s
	gcc -c main.s -o main.o
	gcc main.o arvore-binaria.o pessoa.o -o main -lm

run:
	./main

listar:
	ls $(ARQUIVOS)

clean:
	rm -f *.o *.i *.s
	rm -f $(EXE)