	.file	"simple_main.c"
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	2
	.globl	v
	.align 4
	.type	v, @object
	.size	v, 4
v:
	.long	4
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	jmp	.L2
.L3:
	movl	a(%rip), %eax
	subl	$1, %eax
	movl	%eax, a(%rip)
.L2:
	movl	a(%rip), %eax
	testl	%eax, %eax
	jg	.L3
	movl	a(%rip), %eax
	popq	%rbp
	ret
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
