	.file	"TestCharInstructions.c"
	.text
	.globl	string_to_int
	.type	string_to_int, @function
string_to_int:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	string_to_int, .-string_to_int
	.section	.rodata
	.align 8
.LC0:
	.string	"Example unsigned long long int: %d \n"
.LC1:
	.string	"1"
.LC2:
	.string	"0"
	.align 8
.LC3:
	.string	"The number of bits in the long long int is %d"
	.text
	.globl	print_value_binary
	.type	print_value_binary, @function
print_value_binary:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$3, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	$3, -8(%rbp)
	movl	$64, -20(%rbp)
	movl	$0, -24(%rbp)
	movl	-20(%rbp), %eax
	subl	$1, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	cltq
	movq	%rax, -16(%rbp)
	jmp	.L3
.L6:
	movq	-8(%rbp), %rax
	andq	-16(%rbp), %rax
	testq	%rax, %rax
	je	.L4
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L5
.L4:
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L5:
	addl	$1, -24(%rbp)
	shrq	-16(%rbp)
.L3:
	cmpq	$0, -16(%rbp)
	jne	.L6
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	print_value_binary, .-print_value_binary
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	print_value_binary
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.1.0"
	.section	.note.GNU-stack,"",@progbits
