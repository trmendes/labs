lab: queue.o main.o
	gcc -g -Wall -o lab main.o queue.o

main.o: main.c queue.h
	gcc -g -Wall -c main.c
queue.o: queue.c queue.h
	gcc -g -Wall -c queue.c

clean:
	rm lab queue.o main.o

all: lab