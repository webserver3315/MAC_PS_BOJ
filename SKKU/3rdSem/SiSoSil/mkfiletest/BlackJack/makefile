OBJ = main.o list.o

main: $(OBJ)
	gcc -o main $(OBJ)

main.o: list.h main.c
	gcc -c main.c

list.o: list.h list.c
	gcc -c list.c

