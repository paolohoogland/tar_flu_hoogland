all: ctar

ctar: main.o args.o list.o extract.o
	gcc -o ctar main.o args.o list.o extract.o

main.o: main.c args.h typedef.h
	gcc -c main.c

args.o: args.c args.h typedef.h
	gcc -c args.c

list.o: list.c list.h typedef.h
	gcc -c list.c

extract.o: extract.c extract.h typedef.h
	gcc -c extract.c

clean:
	rm -f *.o ctar