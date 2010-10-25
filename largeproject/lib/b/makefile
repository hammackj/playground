CC=gcc
CFLAGS=-Wall -g -c

all: b

b: b.c
	${CC} ${CFLAGS} b.c -o b.o
	ar rcs ../../build/b.a b.o
	
clean:
	rm -rf b b.o