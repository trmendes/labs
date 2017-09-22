lab: bintree.o main.o
	gcc -o lab main.o bintree.o

main.o: main.c bintree.h
	gcc -c main.c
bintree.o: bintree.c bintree.h
	gcc -c bintree.c

clean:
	rm lab bintree.o main.o

all: lab