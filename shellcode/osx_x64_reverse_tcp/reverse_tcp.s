;nasm -f macho reverse_tcp.s -o reverse_tcp.o
;ld -o reverse_shell -e start reverse_tcp.o

section .data
    
section .text

global start

start:
  xor rbx, rbx

;97	AUE_SOCKET	ALL	{ int socket(int domain, int type, int protocol); } 
;98	AUE_CONNECT	ALL	{ int connect(int s, caddr_t name, socklen_t namelen); }
socket:
  push rbx
  inc rbx
  push rbx

;dup = 41
;41	AUE_DUP		ALL	{ int dup(u_int fd); }
dup:


;2	AUE_FORK	ALL	{ int fork(void); }
fork:


;59
;59	AUE_EXECVE	ALL	{ int execve(char *fname, char **argp, char **envp); } 
exec:
  


	mov rax, 0x2000004
	mov rdi, 1
	mov rsi, hello_world
	mov rdx, 14
	syscall

	mov rax, 0x2000001
	mov rdi, 0
	syscall

