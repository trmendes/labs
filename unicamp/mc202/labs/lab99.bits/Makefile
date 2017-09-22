lab: bits.o main.o
	gcc -g -Wall -o lab main.o bits.o

main.o: main.c bits.h
	gcc -g -Wall -c main.c
bits.o: bits.c bits.h
	gcc -g -Wall -c bits.c

clean:
	rm lab bits.o main.o

all: lab