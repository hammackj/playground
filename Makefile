CC=gcc
CFLAGS=-g -O0 -m32 -Wall

all: simple asm hello

simple: 
	$(CC) $(CFLAGS) simple.c -o simple

asm:
	nasm -f bin exit.asm -o exit.bin
	nasm -f macho exit.asm -o exit.o
	ld -o exit -e main exit.o

hello: 
	nasm -f macho hello.asm -o hello.o
	ld -o hello -e main hello.o

clean:
	rm -rf *o simple exit simple.dSYM