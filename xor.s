	.text
.globl _xor
_xor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$0, -12(%ebp)
	jmp	L2
L3:
	movl	-12(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %edx
	movl	-12(%ebp), %eax
	addl	12(%ebp), %eax
	movzbl	(%eax), %eax
	xorl	%eax, %edx
	movl	-12(%ebp), %eax
	addl	8(%ebp), %eax
	movb	%dl, (%eax)
	movl	-12(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	movl	%eax, (%esp)
	call	L_putchar$stub
	leal	-12(%ebp), %eax
	incl	(%eax)
L2:
	cmpl	$20, -12(%ebp)
	jle	L3
	movl	$10, (%esp)
	call	L_putchar$stub
	leave
	ret
	.cstring
LC2:
	.ascii "[*] Encrypting %s\12\0"
LC3:
	.ascii "[$] Encrypted string: \0"
LC4:
	.ascii "[*] Decrypting %s\12\0"
LC0:
	.ascii "Pwning noobs is fun~\0"
LC1:
	.ascii "ABCDEABCDEFGHIJFGHIJ\0"
	.text
.globl _main
_main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$68, %esp
	call	L8
"L00000000001$pb":
L8:
	popl	%ebx
	leal	LC0-"L00000000001$pb"(%ebx), %edx
	movl	(%edx), %eax
	movl	%eax, -29(%ebp)
	movl	4(%edx), %eax
	movl	%eax, -25(%ebp)
	movl	8(%edx), %eax
	movl	%eax, -21(%ebp)
	movl	12(%edx), %eax
	movl	%eax, -17(%ebp)
	movl	16(%edx), %eax
	movl	%eax, -13(%ebp)
	movzbl	20(%edx), %eax
	movb	%al, -9(%ebp)
	leal	LC1-"L00000000001$pb"(%ebx), %edx
	movl	(%edx), %eax
	movl	%eax, -50(%ebp)
	movl	4(%edx), %eax
	movl	%eax, -46(%ebp)
	movl	8(%edx), %eax
	movl	%eax, -42(%ebp)
	movl	12(%edx), %eax
	movl	%eax, -38(%ebp)
	movl	16(%edx), %eax
	movl	%eax, -34(%ebp)
	movzbl	20(%edx), %eax
	movb	%al, -30(%ebp)
	leal	-29(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	LC2-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	leal	LC3-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	leal	-50(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-29(%ebp), %eax
	movl	%eax, (%esp)
	call	_xor
	leal	-29(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	LC4-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	leal	LC3-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	leal	-50(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-29(%ebp), %eax
	movl	%eax, (%esp)
	call	_xor
	movl	$0, %eax
	addl	$68, %esp
	popl	%ebx
	leave
	ret
	.section __IMPORT,__jump_table,symbol_stubs,self_modifying_code+pure_instructions,5
L_putchar$stub:
	.indirect_symbol _putchar
	hlt ; hlt ; hlt ; hlt ; hlt
L_printf$stub:
	.indirect_symbol _printf
	hlt ; hlt ; hlt ; hlt ; hlt
	.subsections_via_symbols
