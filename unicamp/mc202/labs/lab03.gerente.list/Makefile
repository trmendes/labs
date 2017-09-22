lab: hd.o main.o
	gcc -g -Wall -o lab main.o hd.o

main.o: main.c hd.h
	gcc -g -Wall -c main.c
hd.o: hd.c hd.h
	gcc -g -Wall -c hd.c

clean:
	rm lab hd.o main.o

all: lab