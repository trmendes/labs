lab: stack.o main.o
	gcc -o lab main.o stack.o

main.o: main.c stack.h
	gcc -c main.c
stack.o: stack.c stack.h
	gcc -c stack.c

clean:
	rm lab stack.o main.o

all: lab