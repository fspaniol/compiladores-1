	 .data
	 .globl	_const10
	 .align 4
	 .type	_const10, @object
	 .size	_const10, 4
_const10:
	 .long	10


	 .globl	_const876
	 .align 4
	 .type	_const876, @object
	 .size	_const876, 4
_const876:
	 .long	876


	 .globl	a
	 .align 4
	 .type	a, @object
	 .size	a, 4
a:
	 .long	0


	 .globl	b
	 .align 4
	 .type	b, @object
	 .size	b, 4
b:
	 .long	0


	 .globl	c
	 .align 4
	 .type	c, @object
	 .size	c, 4
c:
	 .long	5


	 .globl	d
	 .align 4
	 .type	d, @object
	 .size	d, 4
d:
	 .long	10


	.comm g,0,4
	 .globl	i
	 .align 4
	 .type	i, @object
	 .size	i, 4
i:
	 .long	0


	 .globl	_temp4
	 .align 4
	 .type	_temp4, @object
	 .size	_temp4, 4
_temp4:
	 .long	0


	 .globl	n
	 .align 4
	 .type	n, @object
	 .size	n, 4
n:
	 .long	0


	 .globl	exp
	 .align 4
	 .type	exp, @object
	 .size	exp, 4
exp:
	 .long	10


	 .align 4
	 .size	v, 0
v:
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .long	_const0
	 .globl	_temp10
	 .align 4
	 .type	_temp10, @object
	 .size	_temp10, 4
_temp10:
	 .long	0


	 .globl	x
	 .align 4
	 .type	x, @object
	 .size	x, 4
x:
	 .long	0


	 .globl	_const19
	 .align 4
	 .type	_const19, @object
	 .size	_const19, 4
_const19:
	 .long	19


	 .globl	_const676
	 .align 4
	 .type	_const676, @object
	 .size	_const676, 4
_const676:
	 .long	676


	 .globl	_temp2
	 .align 4
	 .type	_temp2, @object
	 .size	_temp2, 4
_temp2:
	 .long	0


	 .globl	_temp9
	 .align 4
	 .type	_temp9, @object
	 .size	_temp9, 4
_temp9:
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


	 .globl	_const20
	 .align 4
	 .type	_const20, @object
	 .size	_const20, 4
_const20:
	 .long	20


	 .globl	_temp7
	 .align 4
	 .type	_temp7, @object
	 .size	_temp7, 4
_temp7:


	 .globl	_temp13
	 .align 4
	 .type	_temp13, @object
	 .size	_temp13, 4
_temp13:
	 .long	0


	 .globl	_const1
	 .align 4
	 .type	_const1, @object
	 .size	_const1, 4
_const1:
	 .long	1


	 .globl	_const11
	 .align 4
	 .type	_const11, @object
	 .size	_const11, 4
_const11:
	 .long	11


	 .globl	_const2
	 .align 4
	 .type	_const2, @object
	 .size	_const2, 4
_const2:
	 .long	2


	 .globl	_temp5
	 .align 4
	 .type	_temp5, @object
	 .size	_temp5, 4
_temp5:
	 .long	0


	 .globl	_const3
	 .align 4
	 .type	_const3, @object
	 .size	_const3, 4
_const3:
	 .long	3


	 .align 1
	 .size	mat, 0
mat:
	 .byte	1
	 .byte	0
	 .globl	_const5
	 .align 4
	 .type	_const5, @object
	 .size	_const5, 4
_const5:
	 .long	5


	 .globl	_temp3
	 .align 4
	 .type	_temp3, @object
	 .size	_temp3, 4
_temp3:
	 .long	0


	 .globl	_temp12
	 .align 4
	 .type	_temp12, @object
	 .size	_temp12, 4
_temp12:
	 .long	0


	 .globl	bX
	 .align 4
	 .type	bX, @object
	 .size	bX, 4
bX:
	 .long	0


	 .globl	_temp1
	 .align 4
	 .type	_temp1, @object
	 .size	_temp1, 4
_temp1:


	 .globl	_temp8
	 .align 4
	 .type	_temp8, @object
	 .size	_temp8, 4
_temp8:
	 .long	0


	 .globl	_temp11
	 .align 4
	 .type	_temp11, @object
	 .size	_temp11, 4
_temp11:
	 .long	0


	 .globl	_const32
	 .align 4
	 .type	_const32, @object
	 .size	_const32, 4
_const32:
	 .long	32


	 .globl	_temp6
	 .align 4
	 .type	_temp6, @object
	 .size	_temp6, 4
_temp6:
	 .long	0


	.globl ab
	.type   ab, @function
ab:
	pushq   %rbp
	movq    %rsp, %rbp
	movl    a(%rip), %eax
	movl    bX(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp0(%rip)
	movl    _temp0(%rip), %eax
	popq    %rbp
	ret
	.globl main
	.type   main, @function
main:
	pushq   %rbp
	movq    %rsp, %rbp
	movl    _const1(%rip), %eax
	movl    %eax, i(%rip)
_label0:
	movl    _temp1(%rip), %eax
	testl    %eax, %eax
	je    _label1
	 jmp _label0
_label1:
	movl    _const10(%rip), %eax
	movl    %eax, b(%rip)
	movl    _const876(%rip), %eax
	movl    _const32(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp2(%rip)
	movl    a(%rip), %eax
	movl    b(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp3(%rip)
	movl    _temp3(%rip), %eax
	movl    %eax, c(%rip)
	movl    a(%rip), %eax
	movl    b(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp4(%rip)
	movl    c(%rip), %eax
	movl    _temp4(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp5(%rip)
_label3:
	movl    _temp6(%rip), %eax
	testl    %eax, %eax
	je    _label4
_label2:
	movl    _temp7(%rip), %eax
	movl    %eax, a(%rip)
	movl    i(%rip), %eax
	movl    _const1(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp8(%rip)
	movl    _temp8(%rip), %eax
	movl    %eax, a(%rip)
	 jmp _label3
_label4:
	movl    _temp10(%rip), %eax
	testl    %eax, %eax
	je    _label5
_label5:
	movl    _temp11(%rip), %eax
	testl    %eax, %eax
	je    _label6
_label6:
	movl    _temp12(%rip), %eax
	testl    %eax, %eax
	je    _label7
	 jmp _label8
_label7:
_label8:
	.globl incn
	.type   incn, @function
incn:
	pushq   %rbp
	movq    %rsp, %rbp
	movl    x(%rip), %eax
	movl    n(%rip), %edx
	addl    %edx, %eax
	movl    %eax, _temp13(%rip)
	movl    _temp13(%rip), %eax
	popq    %rbp
	ret
	.globl voidfunc
	.type   voidfunc, @function
voidfunc:
	pushq   %rbp
	movq    %rsp, %rbp
	movl    _const3(%rip), %eax
	popq    %rbp
	ret
