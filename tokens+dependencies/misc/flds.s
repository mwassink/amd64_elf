	.text
	.globl main
	.type main, @function

main:

	addl	$10, %eax
	addl	$10, %ebx
	addl	$10, %ecx
	addl	$10, %edx
	addl	$10, %esi
	addl	$10, %edi
	addl	$10, %ebp
	subl	$12, %esp
	push	%rcx
	addl	$15, 4(%rsp)
