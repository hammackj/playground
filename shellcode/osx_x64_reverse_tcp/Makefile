CC=gcc
CFLAGS= -g -Wall
FILE=reverse_tcp


all: ${FILE}

reverse: ${FILE}.c
	${CC} ${CFLAGS} ${FILE}.c -o ${FILE}

asm: reverse_tcp1.s
	/opt/local/bin/nasm -f macho64 reverse_tcp1.s -o reverse_tcp1.o
	ld -arch x86_64 reverse_tcp1.o -o reverse_shell

shell: spawn_shell.s
	/opt/local/bin/nasm -f macho64 spawn_shell.s -o spawn_shell.o
	ld -arch x86_64 -macosx_version_min 10.6 spawn_shell.o -o spawn_shell

clean:
	rm -rf ${FILE}
	rm -rf *.dSYM/

