lab: cvec.o main.o
	gcc -g -Wall -o lab main.o cvec.o

main.o: main.c cvec.h
	gcc -g -Wall -c main.c
cvec.o: cvec.c cvec.h
	gcc -g -Wall -c cvec.c

clean:
	rm lab cvec.o main.o

all: lab