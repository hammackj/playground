;Exit Test
;
;nasm -f macho exit.asm
;ld -o exit -e main exit.o
;

section .data

section .text

global main

main:
	xor eax, eax
	mov eax, 0x01
	sub esp, 4
	int 0x80
