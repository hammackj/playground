;
; Basic OS X calls to glibc
;
; compile with:
; nasm -g -f macho malloc.asm
; gcc -o a.out malloc.o
;
 
; glibc stuff
extern _puts, _printf, _malloc, _free
 
; static data
segment .data
 
hello_world_str db "Hello world!", 10, 0
int_str db "Address %x", 10, 0
 
; code
segment .text
 
global _main
 
_main:
        push ebp ; setup the frame
        mov  ebp, esp
 
        sub  esp, 4 ; align the stack
        push dword hello_world_str
        call _puts
        add  esp, 4
 
        ; malloc 16 bytes
        push  dword 16
        call  _malloc
        add  esp, 4
 
        ; check if the malloc failed
        test  eax, eax
        jz    fail_exit
         
        sub   esp, 0xC ; align the stack
        mov   ebx, eax
        push  ebx
        push  dword int_str
        call  _printf
        add   esp, 8
        add   esp, 0xC
 
        ; print "A\nB\n..."     
        mov   [ebx], dword 0xD41 ; 'A\n'
 
        mov   edi, 10
        push  ebx
_loop:
        call  _puts
        inc  dword [ebx] 
        dec  edi 
        jnz  _loop
 
        add  esp, 4
         
        ; free the malloc'd memory
        push  ebx
        call  _free
        add  esp, 4
        add  esp, 4 ; cleanup the stack 
        pop  ebp
        ret
         
fail_exit:
        mov  eax, 1
        pop  ebp
        ret

