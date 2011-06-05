CC=gcc
CFLAGS=-g -O0 -m32 -Wall

all: vuln32 vuln64

vuln32: vuln.c
	$(CC) -m32 vuln.c -o vuln32

vuln64: vuln.c
	$(CC) -m64 vuln.c -o vuln64
