	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_ab
	.align	4, 0x90
_ab:                                    ## @ab
## BB#0:
	pushq	%rbp
	movq	%rsp, %rbp
	movss	%xmm0, -4(%rbp)
	movss	%xmm1, -8(%rbp)
	movss	-4(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	addss	-8(%rbp), %xmm0
	popq	%rbp
	retq

	.globl	_a
	.align	4, 0x90
_a:                                     ## @a
## BB#0:
	pushq	%rbp
	movq	%rsp, %rbp
	xorps	%xmm0, %xmm0
	popq	%rbp
	retq


.subsections_via_symbols
