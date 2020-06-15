# mark_description "Intel(R) C Intel(R) 64 Compiler for applications running on Intel(R) 64, Version 19.1.1.217 Build 20200306";
# mark_description "-save-temps -masm=intel -o test";
	.intel_syntax noprefix
	.file "test.c"
	.text
..TXTST0:
.L_2__routine_start_main_0:
# -- Begin  main
	.text
# mark_begin;
       .align    16,0x90
	.globl main
# --- main()
main:
..B1.1:                         # Preds ..B1.0
                                # Execution count [1.00e+00]
	.cfi_startproc
..___tag_value_main.1:
..L2:
                                                          #6.1
        push      rbp                                           #6.1
	.cfi_def_cfa_offset 16
        mov       rbp, rsp                                      #6.1
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        and       rsp, -128                                     #6.1
        sub       rsp, 128                                      #6.1
        mov       edi, 3                                        #6.1
        xor       esi, esi                                      #6.1
        call      __intel_new_feature_proc_init                 #6.1
                                # LOE rbx r12 r13 r14 r15
..B1.4:                         # Preds ..B1.1
                                # Execution count [1.00e+00]
        stmxcsr   DWORD PTR [rsp]                               #6.1
        xor       eax, eax                                      #10.10
        or        DWORD PTR [rsp], 32832                        #6.1
        ldmxcsr   DWORD PTR [rsp]                               #6.1
        mov       rsp, rbp                                      #10.10
        pop       rbp                                           #10.10
	.cfi_def_cfa 7, 8
	.cfi_restore 6
        ret                                                     #10.10
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	main,@function
	.size	main,.-main
..LNmain.0:
	.data
# -- End  main
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
# End
