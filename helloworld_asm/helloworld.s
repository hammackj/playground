section .data
hello_world db "HelloWorld!", 0x0a
    
section .text

global start

start:
	mov rax, 0x2000004
	mov rdi, 1
	mov rsi, hello_world
	mov rdx, 14
	syscall

	mov rax, 0x2000001
	mov rdi, 0
	syscall

