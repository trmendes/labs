lab: dvector.o main.o
	gcc -o lab main.o dvector.o

main.o: main.c dvector.h
	gcc -c main.c
dvector.o: dvector.c dvector.h
	gcc -c dvector.c

clean:
	rm lab dvector.o main.o

all: lab