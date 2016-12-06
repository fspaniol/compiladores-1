	 .data
	 .globl	a
	 .align 4
	 .type	a, @object
	 .size	a, 4
a:
	 .long	0


	 .globl	_temp0
	 .align 4
	 .type	_temp0, @object
	 .size	_temp0, 4
_temp0:
	 .long	0


	 .globl	_const0
	 .align 4
	 .type	_const0, @object
	 .size	_const0, 4
_const0:
	 .long	0


	 .globl	_const32
	 .align 4
	 .type	_const32, @object
	 .size	_const32, 4
_const32:
	 .long	32


	.globl main
	.type   main, @function
main:
	pushq   %rbp
	movq    %rsp, %rbp
	movl    _const32(%rip), %eax
	movl    a(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp0(%rip)
	movl    _temp0(%rip), %eax
	movl    %eax, a(%rip)
	movl    a(%rip), %eax
	popq    %rbp
	ret
