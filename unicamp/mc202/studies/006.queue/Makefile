lab: queue.o main.o
	gcc -o lab main.o queue.o

main.o: main.c queue.h
	gcc -c main.c
queue.o: queue.c queue.h
	gcc -c queue.c

clean:
	rm lab queue.o main.o

all: lab