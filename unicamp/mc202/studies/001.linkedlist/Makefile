lab: linkedlist.o main.o
	gcc -o lab main.o linkedlist.o

main.o: main.c linkedlist.h trace.h
	gcc -c main.c
linkedlist.o: linkedlist.c linkedlist.h trace.h
	gcc -c linkedlist.c

clean:
	rm lab linkedlist.o main.o

all: lab