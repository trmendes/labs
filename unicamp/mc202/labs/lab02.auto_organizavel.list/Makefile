lab: lista.o main.o
	gcc -g -Wall -o lab main.o lista.o

main.o: main.c lista.h
	gcc -g -Wall -c main.c
lista.o: lista.c lista.h
	gcc -g -Wall -c lista.c

clean:
	rm lab lista.o main.o

all: lab