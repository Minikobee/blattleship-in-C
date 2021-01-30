OBJS=battleship.o main.o
PROGRAM=./battleship

all: battleship $(PROGRAM) 
battleship: battleship.o main.o 
	gcc -o battleship battleship.o main.o
battleship.o: battleship.c
	gcc -o battleship.o -c battleship.c -Wall 
main.o: main.c battleship.h
	gcc -o main.o -c main.c -Wall
clean:
	rm -rf *.o main $(PROGRAM) 