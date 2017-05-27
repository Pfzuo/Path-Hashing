all: path

path: test.o path_hashing.o hash.o
	gcc -o path test.o path_hashing.o hash.o -lm

hash.o: hash.c hash.h
	gcc -c hash.c
	
path_hashing.o: path_hashing.c path_hashing.h
	gcc -c path_hashing.c

test.o: test.c path_hashing.h
	gcc -c test.c

clean:
	rm -rf *.o path