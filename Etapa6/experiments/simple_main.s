	.file	"simple_main.c"
	.comm	a,4,4
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	nop
	popq	%rbp
	ret
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
