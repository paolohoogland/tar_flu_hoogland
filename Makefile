all: ctar

ctar: main.o args.o list.o extract.o create.o
	gcc -o ctar main.o args.o list.o extract.o create.o

main.o: main.c args.h typedef.h
	gcc -c main.c

args.o: args.c args.h typedef.h
	gcc -c args.c

list.o: list.c list.h typedef.h
	gcc -c list.c

extract.o: extract.c extract.h typedef.h
	gcc -c extract.c

create.o: create.c create.h typedef.h
	gcc -c create.c

clean:
	rm -f *.o ctar