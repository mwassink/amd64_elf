	.file	"utilities.c"
	.text
	.globl	needs_rex_r
	.type	needs_rex_r, @function
needs_rex_r:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jle	.L2
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jg	.L2
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$0, %eax
.L3:
	andl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	needs_rex_r, .-needs_rex_r
	.globl	move_to_endline
	.type	move_to_endline, @function
move_to_endline:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	jmp	.L6
.L7:
	addl	$1, -12(%rbp)
.L6:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L7
	movl	-12(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	move_to_endline, .-move_to_endline
	.section	.rodata
	.align 8
.LC0:
	.string	"Issue reading the input string. An endline was reached prematurely"
.LC1:
	.string	"src/utilities.c"
.LC2:
	.string	"0 == 1"
	.text
	.globl	move_to_space
	.type	move_to_space, @function
move_to_space:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	jmp	.L10
.L12:
	addl	$1, -12(%rbp)
.L10:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L11
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L12
.L11:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L13
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$66, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	call	fwrite
	movl	$__PRETTY_FUNCTION__.1, %ecx
	movl	$29, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	__assert_fail
.L13:
	movl	-12(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	move_to_space, .-move_to_space
	.globl	byte_from_sib_part
	.type	byte_from_sib_part, @function
byte_from_sib_part:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	movl	-4(%rbp), %ecx
	movq	-24(%rbp), %rax
	movl	$37, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	move_to_general
	movl	%eax, -4(%rbp)
	addl	$1, -4(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$101, %al
	jne	.L16
	movq	-32(%rbp), %rax
	movb	$103, (%rax)
	jmp	.L17
.L16:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	needs_rex_r
	testb	%al, %al
	je	.L17
	movq	-32(%rbp), %rax
	movzbl	1(%rax), %eax
	orl	$65, %eax
	movl	%eax, %edx
	movq	-32(%rbp), %rax
	movb	%dl, 1(%rax)
.L17:
	movl	-4(%rbp), %ecx
	movq	-24(%rbp), %rax
	movl	$37, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	move_to_general
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	needs_rex_r
	testb	%al, %al
	je	.L19
	movq	-32(%rbp), %rax
	movzbl	1(%rax), %eax
	orl	$66, %eax
	movl	%eax, %edx
	movq	-32(%rbp), %rax
	movb	%dl, 1(%rax)
.L19:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	byte_from_sib_part, .-byte_from_sib_part
	.globl	move_to_general
	.type	move_to_general, @function
move_to_general:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, %eax
	movb	%al, -16(%rbp)
	jmp	.L21
.L22:
	addl	$1, -12(%rbp)
.L21:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, -16(%rbp)
	jne	.L22
	movl	-12(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	move_to_general, .-move_to_general
	.globl	move_while_general
	.type	move_while_general, @function
move_while_general:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, %eax
	movb	%al, -16(%rbp)
	jmp	.L25
.L26:
	addl	$1, -12(%rbp)
.L25:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, -16(%rbp)
	je	.L26
	movl	-12(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	move_while_general, .-move_while_general
	.globl	compare_strings
	.type	compare_strings, @function
compare_strings:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$20, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L29
.L33:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L30
	movl	$0, %eax
	jmp	.L31
.L30:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L32
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L32
	movl	$1, %eax
	jmp	.L31
.L32:
	addl	$1, -4(%rbp)
.L29:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L33
	cmpl	$21, -4(%rbp)
	jne	.L34
	movl	$0, %eax
	jmp	.L31
.L34:
	movl	$1, %eax
.L31:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	compare_strings, .-compare_strings
	.section	.rodata
	.align 8
.LC3:
	.string	"Example unsigned long long int: %d \n"
	.align 8
.LC4:
	.string	"The length of the shift is %d: \n"
.LC5:
	.string	"1"
.LC6:
	.string	"0"
	.align 8
.LC7:
	.string	"The number of bits in the long long int is %d \n"
.LC8:
	.string	"Example signed int -5: "
	.text
	.globl	example_print_value_binary
	.type	example_print_value_binary, @function
example_print_value_binary:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$3, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movq	$3, -24(%rbp)
	movl	$64, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movq	$1, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	-28(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %ecx
	salq	%cl, -8(%rbp)
	jmp	.L36
.L39:
	movq	-24(%rbp), %rax
	andq	-8(%rbp), %rax
	testq	%rax, %rax
	je	.L37
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L38
.L37:
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L38:
	addl	$1, -12(%rbp)
	shrq	-8(%rbp)
.L36:
	cmpq	$0, -8(%rbp)
	jne	.L39
	movl	$10, %edi
	call	putchar
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC8, %edi
	call	puts
	movl	$-5, -32(%rbp)
	movq	$1, -8(%rbp)
	movl	$0, -12(%rbp)
	salq	$31, -8(%rbp)
	jmp	.L40
.L43:
	movl	-32(%rbp), %eax
	cltq
	andq	-8(%rbp), %rax
	testq	%rax, %rax
	je	.L41
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L42
.L41:
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L42:
	shrq	-8(%rbp)
.L40:
	cmpq	$0, -8(%rbp)
	jne	.L43
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	example_print_value_binary, .-example_print_value_binary
	.section	.rodata
	.align 8
.LC9:
	.string	"The number %lX in binary is: \n"
	.text
	.globl	print_binary
	.type	print_binary, @function
print_binary:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC9, %edi
	movl	$0, %eax
	call	printf
	movq	$1, -8(%rbp)
	movl	$64, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %ecx
	salq	%cl, -8(%rbp)
	jmp	.L45
.L48:
	movq	-24(%rbp), %rax
	andq	-8(%rbp), %rax
	testq	%rax, %rax
	je	.L46
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L47
.L46:
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
.L47:
	shrq	-8(%rbp)
.L45:
	cmpq	$0, -8(%rbp)
	jne	.L48
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	print_binary, .-print_binary
	.globl	name_to_id
	.type	name_to_id, @function
name_to_id:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L50
.L52:
	addl	$1, -4(%rbp)
.L50:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L51
	cmpl	$16, -4(%rbp)
	jle	.L52
.L51:
	cmpl	$8, -4(%rbp)
	jle	.L53
	movl	$0, %eax
	jmp	.L54
.L53:
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
.L54:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	name_to_id, .-name_to_id
	.globl	possible_sizes
	.type	possible_sizes, @function
possible_sizes:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movl	$16, %edi
	call	malloc
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	$16, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movl	$0, -53(%rbp)
	movb	$0, -49(%rbp)
	movl	$0, -58(%rbp)
	movb	$0, -54(%rbp)
	movl	$0, -63(%rbp)
	movb	$0, -59(%rbp)
	movl	$0, -68(%rbp)
	movb	$0, -64(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	jmp	.L56
.L60:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L57
	movq	-48(%rbp), %rax
	jmp	.L85
.L57:
	addl	$1, -20(%rbp)
.L56:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jg	.L61
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jg	.L60
	jmp	.L61
.L63:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-24(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -24(%rbp)
	movzbl	(%rcx), %edx
	cltq
	movb	%dl, -53(%rbp,%rax)
	addl	$1, -20(%rbp)
.L61:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jle	.L64
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jle	.L63
	jmp	.L64
.L67:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L65
	movq	-48(%rbp), %rax
	jmp	.L85
.L65:
	addl	$1, -20(%rbp)
.L64:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jg	.L68
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jg	.L67
	jmp	.L68
.L70:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -28(%rbp)
	movzbl	(%rcx), %edx
	cltq
	movb	%dl, -58(%rbp,%rax)
	addl	$1, -20(%rbp)
.L68:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jle	.L71
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jle	.L70
	jmp	.L71
.L74:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L72
	movq	-48(%rbp), %rax
	jmp	.L85
.L72:
	addl	$1, -20(%rbp)
.L71:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jg	.L75
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jg	.L74
	jmp	.L75
.L77:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-32(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -32(%rbp)
	movzbl	(%rcx), %edx
	cltq
	movb	%dl, -63(%rbp,%rax)
	addl	$1, -20(%rbp)
.L75:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jle	.L78
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jle	.L77
	jmp	.L78
.L81:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L79
	movq	-48(%rbp), %rax
	jmp	.L85
.L79:
	addl	$1, -20(%rbp)
.L78:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jg	.L82
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jg	.L81
	jmp	.L82
.L84:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-36(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -36(%rbp)
	movzbl	(%rcx), %edx
	cltq
	movb	%dl, -68(%rbp,%rax)
	addl	$1, -20(%rbp)
.L82:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jle	.L83
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jle	.L84
.L83:
	leaq	-53(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-48(%rbp), %rax
	leaq	4(%rax), %rbx
	leaq	-58(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, (%rbx)
	movq	-48(%rbp), %rax
	leaq	8(%rax), %rbx
	leaq	-63(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, (%rbx)
	movq	-48(%rbp), %rax
	leaq	12(%rax), %rbx
	leaq	-68(%rbp), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, (%rbx)
	movq	-48(%rbp), %rax
.L85:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	possible_sizes, .-possible_sizes
	.globl	switch_on_possible_sizes
	.type	switch_on_possible_sizes, @function
switch_on_possible_sizes:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	cmpl	$128, -4(%rbp)
	je	.L87
	cmpl	$128, -4(%rbp)
	jg	.L86
	cmpl	$64, -4(%rbp)
	je	.L89
	cmpl	$64, -4(%rbp)
	jg	.L86
	cmpl	$32, -4(%rbp)
	je	.L90
	cmpl	$32, -4(%rbp)
	jg	.L86
	cmpl	$16, -4(%rbp)
	je	.L91
	cmpl	$16, -4(%rbp)
	jg	.L86
	cmpl	$0, -4(%rbp)
	je	.L94
	cmpl	$8, -4(%rbp)
	jne	.L86
	movq	-16(%rbp), %rax
	movb	$1, (%rax)
	jmp	.L86
.L91:
	movq	-16(%rbp), %rax
	movb	$1, 2(%rax)
	jmp	.L86
.L90:
	movq	-16(%rbp), %rax
	movb	$1, 3(%rax)
	jmp	.L86
.L89:
	movq	-16(%rbp), %rax
	movb	$1, 4(%rax)
	jmp	.L86
.L87:
	movq	-16(%rbp), %rax
	movb	$1, 5(%rax)
	jmp	.L86
.L94:
	nop
.L86:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	switch_on_possible_sizes, .-switch_on_possible_sizes
	.globl	fill_possible_sizes
	.type	fill_possible_sizes, @function
fill_possible_sizes:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movb	$0, (%rax)
	movq	-24(%rbp), %rax
	movb	$0, 1(%rax)
	movq	-24(%rbp), %rax
	movb	$0, 5(%rax)
	movq	-24(%rbp), %rax
	movb	$0, 2(%rax)
	movq	-24(%rbp), %rax
	movb	$0, 3(%rax)
	movq	-24(%rbp), %rax
	movb	$0, 4(%rax)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	possible_sizes
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L96
.L97:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movq	-24(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	switch_on_possible_sizes
	addl	$1, -4(%rbp)
.L96:
	cmpl	$3, -4(%rbp)
	jle	.L97
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	fill_possible_sizes, .-fill_possible_sizes
	.globl	check_for_segment_register
	.type	check_for_segment_register, @function
check_for_segment_register:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movzwl	(%rax), %eax
	cwtl
	cmpl	$29555, %eax
	je	.L99
	cmpl	$29555, %eax
	jg	.L100
	cmpl	$26483, %eax
	je	.L101
	cmpl	$26483, %eax
	jg	.L100
	cmpl	$26227, %eax
	je	.L102
	cmpl	$26227, %eax
	jg	.L100
	cmpl	$25971, %eax
	je	.L103
	cmpl	$25971, %eax
	jg	.L100
	cmpl	$25459, %eax
	je	.L104
	cmpl	$25715, %eax
	je	.L105
	jmp	.L100
.L103:
	movl	$1, %eax
	jmp	.L106
.L104:
	movl	$1, %eax
	jmp	.L106
.L99:
	movl	$1, %eax
	jmp	.L106
.L105:
	movl	$1, %eax
	jmp	.L106
.L102:
	movl	$1, %eax
	jmp	.L106
.L101:
	movl	$1, %eax
	jmp	.L106
.L100:
	movl	$0, %eax
.L106:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	check_for_segment_register, .-check_for_segment_register
	.section	.rodata
.LC10:
	.string	"m"
.LC11:
	.string	"r/m"
.LC12:
	.string	"imm"
.LC13:
	.string	"r"
.LC14:
	.string	"moffs"
.LC15:
	.string	"xmm"
.LC16:
	.string	"xmm/m"
.LC17:
	.string	"eFlags"
.LC18:
	.string	"rel"
	.text
	.globl	type_fallback
	.type	type_fallback, @function
type_fallback:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -10(%rbp)
	movw	$0, -6(%rbp)
	movl	$0, -4(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L110
	movl	$0, %eax
	jmp	.L123
.L112:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	movb	%dl, -10(%rbp,%rax)
.L110:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L111
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jle	.L111
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jle	.L112
.L111:
	leaq	-10(%rbp), %rax
	movl	$.LC10, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L113
	movl	$2, %eax
	jmp	.L123
.L113:
	leaq	-10(%rbp), %rax
	movl	$.LC11, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L114
	movl	$5, %eax
	jmp	.L123
.L114:
	leaq	-10(%rbp), %rax
	movl	$.LC12, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L115
	movl	$1, %eax
	jmp	.L123
.L115:
	leaq	-10(%rbp), %rax
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L116
	movl	$3, %eax
	jmp	.L123
.L116:
	leaq	-10(%rbp), %rax
	movl	$.LC14, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L117
	movl	$14, %eax
	jmp	.L123
.L117:
	leaq	-10(%rbp), %rax
	movl	$.LC15, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L118
	movl	$7, %eax
	jmp	.L123
.L118:
	leaq	-10(%rbp), %rax
	movl	$.LC16, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L119
	movl	$17, %eax
	jmp	.L123
.L119:
	leaq	-10(%rbp), %rax
	movq	%rax, %rdi
	call	check_for_segment_register
	testb	%al, %al
	je	.L120
	movl	$9, %eax
	jmp	.L123
.L120:
	leaq	-10(%rbp), %rax
	movl	$.LC17, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L121
	movl	$19, %eax
	jmp	.L123
.L121:
	leaq	-10(%rbp), %rax
	movl	$.LC18, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L122
	movl	$20, %eax
	jmp	.L123
.L122:
	movl	$21, %eax
.L123:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	type_fallback, .-type_fallback
	.section	.rodata
.LC19:
	.string	"imm8"
.LC20:
	.string	"imm16/32"
.LC21:
	.string	"imm16/32/64"
.LC22:
	.string	"r8"
.LC23:
	.string	"r16/32/64"
.LC24:
	.string	"r/m8"
.LC25:
	.string	"r/m16/32/64"
.LC26:
	.string	"r/m16/32"
.LC27:
	.string	"m8"
.LC28:
	.string	"m16"
.LC29:
	.string	"m16/32"
.LC30:
	.string	"m32"
.LC31:
	.string	"m64"
.LC32:
	.string	"m16/32/64"
.LC33:
	.string	"re18"
.LC34:
	.string	"Flags"
.LC35:
	.string	"moffs8"
.LC36:
	.string	"moffs16"
.LC37:
	.string	"ST"
.LC38:
	.string	"STi"
.LC39:
	.string	"mm"
.LC40:
	.string	"rel8"
.LC41:
	.string	"rel16/32"
	.text
	.globl	operand_type_return
	.type	operand_type_return, @function
operand_type_return:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$.LC19, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L125
	movl	$1, %eax
	jmp	.L126
.L125:
	movq	-8(%rbp), %rax
	movl	$.LC20, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L127
	movl	$1, %eax
	jmp	.L126
.L127:
	movq	-8(%rbp), %rax
	movl	$.LC21, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L128
	movl	$1, %eax
	jmp	.L126
.L128:
	movq	-8(%rbp), %rax
	movl	$.LC22, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L129
	movl	$3, %eax
	jmp	.L126
.L129:
	movq	-8(%rbp), %rax
	movl	$.LC23, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L130
	movl	$3, %eax
	jmp	.L126
.L130:
	movq	-8(%rbp), %rax
	movl	$.LC24, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L131
	movl	$5, %eax
	jmp	.L126
.L131:
	movq	-8(%rbp), %rax
	movl	$.LC25, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L132
	movl	$5, %eax
	jmp	.L126
.L132:
	movq	-8(%rbp), %rax
	movl	$.LC26, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L133
	movl	$5, %eax
	jmp	.L126
.L133:
	movq	-8(%rbp), %rax
	movl	$.LC27, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L134
	movl	$2, %eax
	jmp	.L126
.L134:
	movq	-8(%rbp), %rax
	movl	$.LC28, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L135
	movl	$2, %eax
	jmp	.L126
.L135:
	movq	-8(%rbp), %rax
	movl	$.LC29, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L136
	movl	$2, %eax
	jmp	.L126
.L136:
	movq	-8(%rbp), %rax
	movl	$.LC30, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L137
	movl	$2, %eax
	jmp	.L126
.L137:
	movq	-8(%rbp), %rax
	movl	$.LC31, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L138
	movl	$2, %eax
	jmp	.L126
.L138:
	movq	-8(%rbp), %rax
	movl	$.LC32, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L139
	movl	$2, %eax
	jmp	.L126
.L139:
	movq	-8(%rbp), %rax
	movl	$.LC33, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L140
	movl	$11, %eax
	jmp	.L126
.L140:
	movq	-8(%rbp), %rax
	movl	$.LC34, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L141
	movl	$13, %eax
	jmp	.L126
.L141:
	movq	-8(%rbp), %rax
	movl	$.LC35, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L142
	movl	$14, %eax
	jmp	.L126
.L142:
	movq	-8(%rbp), %rax
	movl	$.LC36, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L143
	movl	$14, %eax
	jmp	.L126
.L143:
	movq	-8(%rbp), %rax
	movl	$.LC37, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L144
	movl	$8, %eax
	jmp	.L126
.L144:
	movq	-8(%rbp), %rax
	movl	$.LC38, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L145
	movl	$8, %eax
	jmp	.L126
.L145:
	movq	-8(%rbp), %rax
	movl	$.LC15, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L146
	movl	$7, %eax
	jmp	.L126
.L146:
	movq	-8(%rbp), %rax
	movl	$.LC39, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L147
	movl	$6, %eax
	jmp	.L126
.L147:
	movq	-8(%rbp), %rax
	movl	$.LC40, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L148
	movl	$15, %eax
	jmp	.L126
.L148:
	movq	-8(%rbp), %rax
	movl	$.LC41, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L149
	movl	$15, %eax
	jmp	.L126
.L149:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	type_fallback
.L126:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	operand_type_return, .-operand_type_return
	.globl	fill_string_with_line
	.type	fill_string_with_line, @function
fill_string_with_line:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movb	$0, -1(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L151
.L152:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc
	movb	%al, -1(%rbp)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-1(%rbp), %eax
	movb	%al, (%rdx)
	addl	$1, -8(%rbp)
.L151:
	cmpb	$10, -1(%rbp)
	jne	.L152
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	fill_string_with_line, .-fill_string_with_line
	.globl	check_for_jump_label
	.type	check_for_jump_label, @function
check_for_jump_label:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	$0, (%rax)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L155
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$9, %al
	je	.L155
	movl	$0, -4(%rbp)
	jmp	.L156
.L160:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	je	.L157
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L158
.L157:
	movl	$-1, %eax
	jmp	.L159
.L158:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rcx
	movq	-32(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -4(%rbp)
.L156:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$58, %al
	jne	.L160
	movl	-4(%rbp), %eax
	jmp	.L159
.L155:
	movl	$0, %eax
.L159:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	check_for_jump_label, .-check_for_jump_label
	.section	.rodata
.LC42:
	.string	"dqu"
.LC43:
	.string	"l"
.LC44:
	.string	"ups"
.LC45:
	.string	"aps"
.LC46:
	.string	"dqa"
	.align 8
.LC47:
	.string	"Defaulting to 64 bit with no prefix given"
	.text
	.globl	numbits_from_suffix
	.type	numbits_from_suffix, @function
numbits_from_suffix:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$100, %al
	jne	.L162
	movl	$32, %eax
	jmp	.L163
.L162:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$113, %al
	jne	.L164
	movl	$64, %eax
	jmp	.L163
.L164:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$98, %al
	jne	.L165
	movl	$8, %eax
	jmp	.L163
.L165:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$119, %al
	jne	.L166
	movl	$16, %eax
	jmp	.L163
.L166:
	movq	-8(%rbp), %rax
	movl	$.LC42, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L167
	movl	$128, %eax
	jmp	.L163
.L167:
	movq	-8(%rbp), %rax
	movl	$.LC43, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L168
	movl	$32, %eax
	jmp	.L163
.L168:
	movq	-8(%rbp), %rax
	movl	$.LC44, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L169
	movl	$128, %eax
	jmp	.L163
.L169:
	movq	-8(%rbp), %rax
	movl	$.LC45, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L170
	movl	$128, %eax
	jmp	.L163
.L170:
	movq	-8(%rbp), %rax
	movl	$.LC46, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L171
	movl	$128, %eax
	jmp	.L163
.L171:
	movq	stdout(%rip), %rax
	movq	%rax, %rcx
	movl	$41, %edx
	movl	$1, %esi
	movl	$.LC47, %edi
	call	fwrite
	movl	$64, %eax
.L163:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	numbits_from_suffix, .-numbits_from_suffix
	.section	.rodata
.LC48:
	.string	"lock"
	.text
	.globl	check_for_lock_prefix
	.type	check_for_lock_prefix, @function
check_for_lock_prefix:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	$.LC48, %esi
	movq	%rax, %rdi
	call	compare_strings
	testb	%al, %al
	je	.L173
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	4(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	jmp	.L174
.L173:
	movl	$-1, %eax
.L174:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	check_for_lock_prefix, .-check_for_lock_prefix
	.globl	fill_string_until_character
	.type	fill_string_until_character, @function
fill_string_until_character:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, %eax
	movb	%al, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L176
.L177:
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rcx
	movq	-32(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -36(%rbp)
.L176:
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, -40(%rbp)
	jne	.L177
	movl	-36(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	fill_string_until_character, .-fill_string_until_character
	.globl	byte_from_prefixes
	.type	byte_from_prefixes, @function
byte_from_prefixes:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	cmpl	$2, -20(%rbp)
	jne	.L180
	movl	24(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	leal	1(%rax), %ecx
	movq	16(%rbp), %rax
	movl	$32, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	move_while_general
	movl	%eax, -8(%rbp)
.L180:
	cmpl	$2, -24(%rbp)
	jne	.L181
	movl	64(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	leal	1(%rax), %ecx
	movq	56(%rbp), %rax
	movl	$32, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	move_while_general
	movl	%eax, -12(%rbp)
.L181:
	movb	$0, -14(%rbp)
	movb	$0, -15(%rbp)
	cmpl	$4, -20(%rbp)
	je	.L182
	cmpl	$4, -20(%rbp)
	ja	.L201
	cmpl	$2, -20(%rbp)
	je	.L184
	cmpl	$3, -20(%rbp)
	je	.L185
	jmp	.L201
.L184:
	movq	16(%rbp), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$101, %al
	je	.L186
	movq	16(%rbp), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	needs_rex_r
	testb	%al, %al
	je	.L202
	movq	16(%rbp), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	$3, %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$100, %al
	jne	.L202
.L186:
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movb	$103, (%rax)
	jmp	.L202
.L185:
	movzbl	16(%rbp), %eax
	cmpb	$114, %al
	jne	.L189
	movzbl	-14(%rbp), %eax
	orl	$72, %eax
	movb	%al, -14(%rbp)
.L189:
	movq	16(%rbp), %rax
	movq	%rax, %rdi
	call	needs_rex_r
	testb	%al, %al
	je	.L203
	movzbl	-14(%rbp), %eax
	orl	$68, %eax
	movb	%al, -14(%rbp)
	jmp	.L203
.L182:
	movq	32(%rbp), %rax
	leaq	-15(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	byte_from_sib_part
	jmp	.L188
.L201:
	nop
	jmp	.L188
.L202:
	nop
	jmp	.L188
.L203:
	nop
.L188:
	cmpl	$4, -24(%rbp)
	je	.L191
	cmpl	$4, -24(%rbp)
	ja	.L204
	cmpl	$2, -24(%rbp)
	je	.L193
	cmpl	$3, -24(%rbp)
	je	.L194
	jmp	.L204
.L193:
	movq	56(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$114, %al
	je	.L195
	movq	56(%rbp), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	needs_rex_r
	testb	%al, %al
	je	.L205
	movq	56(%rbp), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	$3, %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$100, %al
	jne	.L205
.L195:
	cmpl	$0, -4(%rbp)
	jle	.L205
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -13(%rbp)
	movq	-32(%rbp), %rax
	movb	$103, (%rax)
	movq	-32(%rbp), %rax
	leaq	1(%rax), %rdx
	movzbl	-13(%rbp), %eax
	movb	%al, (%rdx)
	jmp	.L205
.L194:
	movzbl	16(%rbp), %eax
	cmpb	$114, %al
	jne	.L198
	movzbl	-14(%rbp), %eax
	orl	$72, %eax
	movb	%al, -14(%rbp)
.L198:
	movq	16(%rbp), %rax
	movq	%rax, %rdi
	call	needs_rex_r
	testb	%al, %al
	je	.L206
	movzbl	-14(%rbp), %eax
	orl	$68, %eax
	movb	%al, -14(%rbp)
	jmp	.L206
.L191:
	movq	32(%rbp), %rax
	leaq	-15(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	byte_from_sib_part
	jmp	.L197
.L204:
	nop
	jmp	.L197
.L205:
	nop
	jmp	.L197
.L206:
	nop
.L197:
	movzwl	-15(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	byte_from_prefixes, .-byte_from_prefixes
	.section	.rodata
.LC49:
	.string	"%d"
	.align 8
.LC50:
	.string	"(num_longs + num_shorts) == 1074"
	.text
	.globl	sort_instruction_set
	.type	sort_instruction_set, @function
sort_instruction_set:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -24(%rbp)
	movl	$42960, %edi
	call	malloc
	movq	%rax, -64(%rbp)
	movl	$42960, %edi
	call	malloc
	movq	%rax, -72(%rbp)
	movl	$40, -76(%rbp)
	movl	-76(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC49, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -28(%rbp)
	jmp	.L208
.L211:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	addq	%rdx, %rax
	movq	24(%rax), %rax
	testq	%rax, %rax
	jne	.L209
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-20(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -20(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movl	-28(%rbp), %eax
	cltq
	salq	$7, %rax
	movq	%rax, %rdx
	movq	-192(%rbp), %rax
	addq	%rdx, %rax
	movq	24(%rax), %rax
	leaq	8(%rax), %rdx
	movl	-20(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$3, %rax
	leaq	-40(%rax), %rcx
	movq	-64(%rbp), %rax
	leaq	(%rcx,%rax), %rbx
	movq	%rdx, %rdi
	call	name_to_id
	movq	%rax, 24(%rbx)
	jmp	.L210
.L209:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-24(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -24(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
.L210:
	addl	$1, -28(%rbp)
.L208:
	cmpl	$1073, -28(%rbp)
	jle	.L211
	subq	$40, -64(%rbp)
	subq	$40, -72(%rbp)
	movl	-20(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	cmpl	$1074, %eax
	je	.L212
	movl	$__PRETTY_FUNCTION__.0, %ecx
	movl	$815, %edx
	movl	$.LC1, %esi
	movl	$.LC50, %edi
	call	__assert_fail
.L212:
	movl	$0, -32(%rbp)
	jmp	.L213
.L217:
	movl	$0, -36(%rbp)
	jmp	.L214
.L216:
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	24(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	leaq	1(%rax), %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$3, %rax
	movq	%rax, %rcx
	movq	-64(%rbp), %rax
	addq	%rcx, %rax
	movq	24(%rax), %rax
	cmpq	%rax, %rdx
	jbe	.L215
	movl	-36(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	leaq	-176(%rbp), %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-36(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	leaq	-176(%rbp), %rax
	movl	$40, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
.L215:
	addl	$1, -36(%rbp)
.L214:
	movl	-20(%rbp), %eax
	subl	-32(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -36(%rbp)
	jl	.L216
	addl	$1, -32(%rbp)
.L213:
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L217
	movl	$0, -40(%rbp)
	jmp	.L218
.L222:
	movl	$0, -44(%rbp)
	jmp	.L219
.L221:
	movl	-44(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movq	24(%rax), %rdx
	movl	-44(%rbp), %eax
	cltq
	leaq	1(%rax), %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$3, %rax
	movq	%rax, %rcx
	movq	-72(%rbp), %rax
	addq	%rcx, %rax
	movq	24(%rax), %rax
	cmpq	%rax, %rdx
	jbe	.L220
	movl	-44(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	leaq	-176(%rbp), %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movl	-44(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-44(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movl	-44(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	leaq	-176(%rbp), %rax
	movl	$40, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
.L220:
	addl	$1, -44(%rbp)
.L219:
	movl	-24(%rbp), %eax
	subl	-40(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -44(%rbp)
	jl	.L221
	addl	$1, -40(%rbp)
.L218:
	movl	-40(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L222
	movl	$0, -48(%rbp)
	jmp	.L223
.L224:
	movl	-48(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-48(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	addq	%rdx, %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	addl	$1, -48(%rbp)
.L223:
	movl	-48(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L224
	movl	$0, -52(%rbp)
	jmp	.L225
.L226:
	movl	-52(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-72(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-52(%rbp), %eax
	movslq	%eax, %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-184(%rbp), %rax
	addq	%rdx, %rax
	movl	$40, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	addl	$1, -52(%rbp)
.L225:
	movl	-52(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L226
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	-20(%rbp), %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	sort_instruction_set, .-sort_instruction_set
	.section	.rodata
	.align 8
	.type	__PRETTY_FUNCTION__.1, @object
	.size	__PRETTY_FUNCTION__.1, 14
__PRETTY_FUNCTION__.1:
	.string	"move_to_space"
	.align 16
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 21
__PRETTY_FUNCTION__.0:
	.string	"sort_instruction_set"
	.ident	"GCC: (GNU) 10.2.1 20200723 (Red Hat 10.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
