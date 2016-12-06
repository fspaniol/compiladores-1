	 .align 4
	 .size	a, 4
a:
	 .long	_const0


	 .align 4
	 .size	_temp0, 4
_temp0:
	 .long	0


	 .align 4
	 .size	_const0, 4
_const0:
	 .long	0


	 .align 4
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
	movl    %eax, _temp0
	movl    a(%rip), %eax
	popq    %rbp
	ret
