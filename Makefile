all: ctar

ctar: main.o args.o list.o
	gcc -o ctar main.o args.o list.o

main.o: main.c args.h typedef.h
	gcc -c main.c

args.o: args.c args.h typedef.h
	gcc -c args.c

list.o: list.c list.h typedef.h
	gcc -c list.c
	
clean:
	rm -f *.o ctar