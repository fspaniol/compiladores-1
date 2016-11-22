	.file	"allocating_float.c"
	.globl	f
	.data
	.align 4
	.type	f, @object
	.size	f, 4
f:
	.long	1107820544
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.section	.rodata
.LC1:
	.string	"%f"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movss	f(%rip), %xmm1
	movss	.LC0(%rip), %xmm0
	addss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movl	%eax, f(%rip)
	movss	f(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	popq	%rbp
	ret
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1065353216
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
