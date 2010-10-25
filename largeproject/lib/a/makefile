CC=gcc
CFLAGS=-Wall -g -c

all: a

a: a.c
	${CC} ${CFLAGS} a.c -o a.o
	ar rcs ../../build/a.a a.o
	ranlib ../../build/a.a
	
clean:
	rm -rf a a.o