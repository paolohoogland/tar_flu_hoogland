all: ctar

ctar: main.o args.o
	gcc -o ctar main.o args.o

main.o: main.c args.h typedef.h
	gcc -c main.c

args.o: args.c args.h typedef.h
	gcc -c args.c

clean:
	rm -f *.o ctar