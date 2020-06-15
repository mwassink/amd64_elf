
	.intel_syntax noprefix

	.text

	.globl main
main:
	mov	edi, 5
	call	sleep
	mov	edi, 6
	xor	rdi, rdi
	xor	esi, esi
	mov	rsi, 6
	
	lea	eax, [rdi + 2*rsi + 12]

	ret
