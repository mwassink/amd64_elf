# mark_description "Intel(R) C Intel(R) 63 Compiler for applications running on Intel(R) 64, Version 19.1.1.217 Build 20200306";
# mark_description "-O0 -save-temps -masm=intel -o another";
	.intel_syntax noprefix
	.file "another_test_program.c"
	.text
..TXTST0:
.L_2__routine_start_test_0:
# -- Begin  test
	.text
# mark_begin;

	.globl test
# --- test()
test:
..B1.1:                         # Preds ..B1.0
                                # Execution count [0.00e+00]
	.cfi_startproc
..___tag_value_test.1:
..L2:
                                                          #7.1
        push      rbp                                           #7.1
	.cfi_def_cfa_offset 16
        mov       rbp, rsp                                      #7.1
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        sub       rsp, 32                                       #7.1
        mov       eax, 5                                        #8.3
        mov       edi, eax                                      #8.3
..___tag_value_test.6:
#       sleep(unsigned int)
        call      sleep                                         #8.3
..___tag_value_test.7:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip eax
..B1.6:                         # Preds ..B1.1
                                # Execution count [0.00e+00]
        mov       DWORD PTR [-32+rbp], eax                      #8.3
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.2:                         # Preds ..B1.6
                                # Execution count [0.00e+00]
        lea       rax, QWORD PTR [-28+rbp]                      #11.3
        mov       DWORD PTR [rax], 1                            #11.3
        lea       rax, QWORD PTR [-28+rbp]                      #14.11
        mov       eax, DWORD PTR [rax]                          #14.11
        mov       DWORD PTR [-16+rbp], eax                      #14.9
        mov       eax, 10                                       #16.3
        mov       edi, eax                                      #16.3
..___tag_value_test.8:
#       sleep(unsigned int)
        call      sleep                                         #16.3
..___tag_value_test.9:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip eax
..B1.7:                         # Preds ..B1.2
                                # Execution count [0.00e+00]
        mov       DWORD PTR [-12+rbp], eax                      #16.3
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.3:                         # Preds ..B1.7
                                # Execution count [0.00e+00]
        leave                                                   #18.1
	.cfi_restore 6
        ret                                                     #18.1
                                # LOE
	.cfi_endproc
# mark_end;
	.type	test,@function
	.size	test,.-test
..LNtest.0:
	.data
# -- End  test
	.text
.L_2__routine_start_main_1:
# -- Begin  main
	.text
# mark_begin;

	.globl main
# --- main()
main:
..B2.1:                         # Preds ..B2.0
                                # Execution count [0.00e+00]
	.cfi_startproc
..___tag_value_main.12:
..L13:
                                                         #21.1
        push      rbp                                           #21.1
	.cfi_def_cfa_offset 16
        mov       rbp, rsp                                      #21.1
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        sub       rsp, 48                                       #21.1
        mov       DWORD PTR [-48+rbp], 3                        #23.9
        lea       rax, QWORD PTR [-48+rbp]                      #25.16
        mov       QWORD PTR [-32+rbp], rax                      #25.13
        mov       eax, 0                                        #27.3
..___tag_value_main.17:
#       test()
        call      test                                          #27.3
..___tag_value_main.18:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B2.2:                         # Preds ..B2.1
                                # Execution count [0.00e+00]
        mov       eax, 24                                       #30.16
        mov       rdi, rax                                      #30.16
..___tag_value_main.19:
#       malloc(size_t)
        call      malloc                                        #30.16
..___tag_value_main.20:
                                # LOE rax rbx rbp rsp r12 r13 r14 r15 rip
..B2.7:                         # Preds ..B2.2
                                # Execution count [0.00e+00]
        mov       QWORD PTR [-24+rbp], rax                      #30.16
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B2.3:                         # Preds ..B2.7
                                # Execution count [0.00e+00]
        mov       rax, QWORD PTR [-24+rbp]                      #30.16
        mov       QWORD PTR [-16+rbp], rax                      #30.14
        mov       rax, QWORD PTR [-16+rbp]                      #32.4
        mov       DWORD PTR [rax], 3                            #32.4
        mov       eax, 4                                        #33.5
        add       rax, QWORD PTR [-16+rbp]                      #33.5
        mov       DWORD PTR [rax], 4                            #33.5
        mov       eax, 4                                        #35.18
        add       rax, QWORD PTR [-16+rbp]                      #35.18
        mov       eax, DWORD PTR [rax]                          #35.18
        mov       DWORD PTR [-44+rbp], eax                      #35.14
        mov       eax, 4                                        #36.17
        add       rax, QWORD PTR [-16+rbp]                      #36.17
        mov       eax, DWORD PTR [rax]                          #36.17
        mov       DWORD PTR [-40+rbp], eax                      #36.15
        mov       eax, DWORD PTR [-40+rbp]                      #39.7
        mov       DWORD PTR [-48+rbp], eax                      #39.3
        mov       rax, QWORD PTR [-16+rbp]                      #40.3
        mov       rdi, rax                                      #40.3
..___tag_value_main.21:
#       free(void *)
        call      free                                          #40.3
..___tag_value_main.22:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B2.4:                         # Preds ..B2.3
                                # Execution count [0.00e+00]
        mov       eax, 0                                        #41.10
        leave                                                   #41.10
	.cfi_restore 6
        ret                                                     #41.10
                                # LOE
	.cfi_endproc
# mark_end;
	.type	main,@function
	.size	main,.-main
..LNmain.1:
	.data
# -- End  main
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
# End
