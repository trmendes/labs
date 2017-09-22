lab: dllist.o main.o
	gcc -o lab main.o dllist.o

main.o: main.c dllist.h trace.h
	gcc -c main.c
dllist.o: dllist.c dllist.h trace.h
	gcc -c dllist.c

clean:
	rm lab dllist.o main.o

all: lab