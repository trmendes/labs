lab: bintree.o queue.o main.o
	gcc -g -Wall -o lab main.o bintree.o queue.o

main.o: main.c bintree.h
	gcc -g -Wall -c main.c
bintree.o: bintree.c bintree.h
	gcc -g -Wall -c bintree.c
queue.o: queue.c queue.h
	gcc -g -Wall -c queue.c

clean:
	rm lab bintree.o queue.o main.o

all: lab