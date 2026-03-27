all: csv

csv: main.o functions.o
	gcc main.o functions.o -o csv

main.o: main.c
	gcc -c main.c -o main.o

functions.o:
	gcc -c functions.c -o functions.o

clean:
	rm -rf *.o csv
