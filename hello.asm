;Hello World, x86 assembly
;
;nasm -f macho hello.asm -o hello.o
;ld -o hello -e main hello.o
;

section .data

helloWorld db "Hello World!", 0xa
helloWorldLen equ $-helloWorld

section .text

global main

main:

	push dword helloWorldLen
	push dword helloWorld
	push dword 1
	
	mov eax, 0x4
	sub esp, 4
	int 0x80
	
	add esp, 16

	xor eax, eax
	mov eax, 0x01
	sub esp, 4
	int 0x80
	