lab: stack.o queue.o main.o
	gcc -g -Wall -o lab main.o stack.o queue.o

main.o: main.c stack.h queue.h
	gcc -g -Wall -c main.c
stack.o: stack.c stack.h
	gcc -g -Wall -c stack.c
queue.o: queue.c queue.h
	gcc -g -Wall -c queue.c

clean:
	rm lab stack.o queue.o main.o

all: lab