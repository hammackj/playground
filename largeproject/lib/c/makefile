CC=gcc
CFLAGS=-Wall -g -c

all: c

c: c.c
	${CC} ${CFLAGS} c.c -o c.o
	ar rcs ../../build/c.a c.o

clean:
	rm -rf c c.o