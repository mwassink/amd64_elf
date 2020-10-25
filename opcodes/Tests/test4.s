main: push %rbp 
  movq %rsp, %rbp
  xorq %r10, %r10
  xorq %rcx, %rcx
  movq $4,   %r11
  subq $64,  %rsp
  movl $1, -4(%rbp)
  movl $2, -8(%rbp)
  movl $3, -12(%rbp)
  movl $4, -16(%rbp)
  movq %rbp, %rsi
  subq  $16, %rsi
  movl  (%rsi, %rcx, 4), %edi
  addl  %edi, %r10d
  addq  $1, %rcx
  movl  (%rsi, %rcx, 4), %edi
  addl  %edi, %r10d
  addq  $1, %rcx
  movl  (%rsi, %rcx, 4), %edi
  addl  %edi, %r10d
  addq  $1, %rcx
  movl  (%rsi, %rcx, 4), %edi
  addl  %edi, %r10d
  pop %rbp
  addq $64, %rsp
  ret