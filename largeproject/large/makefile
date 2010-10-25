CC=gcc
CFLAGS=-Wall
BINDIR=../build/

all: large

large: 
	${CC} ${CFLAGS} large.c -static a.a -static b.a -static c.a -o ${BINDIR}large

clean:
	rm -rf ${BINDIR}large