	.section .text
.LNDBG_TX:
# mark_description "Intel(R) C Intel(R) 64 Compiler for applications running on Intel(R) 64, Version 19.1.1.217 Build 20200306";
# mark_description "-O0 -save-temps -masm=intel -g -o another";
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
..___tag_value_test.2:
..L3:
                                                          #7.1
..LN0:
	.file   1 "another_test_program.c"
	.loc    1  7  is_stmt 1
        push      rbp                                           #7.1
	.cfi_def_cfa_offset 16
..LN1:
        mov       rbp, rsp                                      #7.1
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
..LN2:
        sub       rsp, 32                                       #7.1
..LN3:
	.loc    1  8  prologue_end  is_stmt 1
        mov       eax, 5                                        #8.3
..LN4:
        mov       edi, eax                                      #8.3
..___tag_value_test.8:
..LN5:
#       sleep(unsigned int)
        call      sleep                                         #8.3
..___tag_value_test.9:
..LN6:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip eax
..B1.6:                         # Preds ..B1.1
                                # Execution count [0.00e+00]
..LN7:
        mov       DWORD PTR [-32+rbp], eax                      #8.3
..LN8:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.2:                         # Preds ..B1.6
                                # Execution count [0.00e+00]
..LN9:
	.loc    1  11  is_stmt 1
        lea       rax, QWORD PTR [-28+rbp]                      #11.3
..LN10:
        mov       DWORD PTR [rax], 1                            #11.3
..LN11:
	.loc    1  14  is_stmt 1
        lea       rax, QWORD PTR [-28+rbp]                      #14.11
..LN12:
        mov       eax, DWORD PTR [rax]                          #14.11
..LN13:
        mov       DWORD PTR [-16+rbp], eax                      #14.9
..LN14:
	.loc    1  16  is_stmt 1
        mov       eax, 10                                       #16.3
..LN15:
        mov       edi, eax                                      #16.3
..___tag_value_test.10:
..LN16:
#       sleep(unsigned int)
        call      sleep                                         #16.3
..___tag_value_test.11:
..LN17:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip eax
..B1.7:                         # Preds ..B1.2
                                # Execution count [0.00e+00]
..LN18:
        mov       DWORD PTR [-12+rbp], eax                      #16.3
..LN19:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B1.3:                         # Preds ..B1.7
                                # Execution count [0.00e+00]
..LN20:
	.loc    1  18  epilogue_begin  is_stmt 1
        leave                                                   #18.1
	.cfi_restore 6
..LN21:
        ret                                                     #18.1
..LN22:
                                # LOE
..LN23:
	.cfi_endproc
# mark_end;
	.type	test,@function
	.size	test,.-test
..LNtest.24:
.LNtest:
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
..___tag_value_main.17:
..L18:
                                                         #21.1
..LN25:
	.loc    1  21  is_stmt 1
        push      rbp                                           #21.1
	.cfi_def_cfa_offset 16
..LN26:
        mov       rbp, rsp                                      #21.1
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
..LN27:
        sub       rsp, 48                                       #21.1
..LN28:
	.loc    1  23  prologue_end  is_stmt 1
        mov       DWORD PTR [-48+rbp], 3                        #23.9
..LN29:
	.loc    1  25  is_stmt 1
        lea       rax, QWORD PTR [-48+rbp]                      #25.16
..LN30:
        mov       QWORD PTR [-32+rbp], rax                      #25.13
..LN31:
	.loc    1  27  is_stmt 1
        mov       eax, 0                                        #27.3
..___tag_value_main.23:
..LN32:
#       test()
        call      test                                          #27.3
..___tag_value_main.24:
..LN33:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B2.2:                         # Preds ..B2.1
                                # Execution count [0.00e+00]
..LN34:
	.loc    1  30  is_stmt 1
        mov       eax, 24                                       #30.16
..LN35:
        mov       rdi, rax                                      #30.16
..___tag_value_main.25:
..LN36:
#       malloc(size_t)
        call      malloc                                        #30.16
..___tag_value_main.26:
..LN37:
                                # LOE rax rbx rbp rsp r12 r13 r14 r15 rip
..B2.7:                         # Preds ..B2.2
                                # Execution count [0.00e+00]
..LN38:
        mov       QWORD PTR [-24+rbp], rax                      #30.16
..LN39:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B2.3:                         # Preds ..B2.7
                                # Execution count [0.00e+00]
..LN40:
        mov       rax, QWORD PTR [-24+rbp]                      #30.16
..LN41:
        mov       QWORD PTR [-16+rbp], rax                      #30.14
..LN42:
	.loc    1  32  is_stmt 1
        mov       rax, QWORD PTR [-16+rbp]                      #32.4
..LN43:
        mov       DWORD PTR [rax], 3                            #32.4
..LN44:
	.loc    1  33  is_stmt 1
        mov       eax, 4                                        #33.5
..LN45:
        add       rax, QWORD PTR [-16+rbp]                      #33.5
..LN46:
        mov       DWORD PTR [rax], 4                            #33.5
..LN47:
	.loc    1  35  is_stmt 1
        mov       eax, 4                                        #35.18
..LN48:
        add       rax, QWORD PTR [-16+rbp]                      #35.18
..LN49:
        mov       eax, DWORD PTR [rax]                          #35.18
..LN50:
        mov       DWORD PTR [-44+rbp], eax                      #35.14
..LN51:
	.loc    1  36  is_stmt 1
        mov       eax, 4                                        #36.17
..LN52:
        add       rax, QWORD PTR [-16+rbp]                      #36.17
..LN53:
        mov       eax, DWORD PTR [rax]                          #36.17
..LN54:
        mov       DWORD PTR [-40+rbp], eax                      #36.15
..LN55:
	.loc    1  39  is_stmt 1
        mov       eax, DWORD PTR [-40+rbp]                      #39.7
..LN56:
        mov       DWORD PTR [-48+rbp], eax                      #39.3
..LN57:
	.loc    1  40  is_stmt 1
        mov       rax, QWORD PTR [-16+rbp]                      #40.3
..LN58:
        mov       rdi, rax                                      #40.3
..___tag_value_main.27:
..LN59:
#       free(void *)
        call      free                                          #40.3
..___tag_value_main.28:
..LN60:
                                # LOE rbx rbp rsp r12 r13 r14 r15 rip
..B2.4:                         # Preds ..B2.3
                                # Execution count [0.00e+00]
..LN61:
	.loc    1  41  is_stmt 1
        mov       eax, 0                                        #41.10
..LN62:
	.loc    1  41  epilogue_begin  is_stmt 1
        leave                                                   #41.10
	.cfi_restore 6
..LN63:
        ret                                                     #41.10
..LN64:
                                # LOE
..LN65:
	.cfi_endproc
# mark_end;
	.type	main,@function
	.size	main,.-main
..LNmain.66:
.LNmain:
	.data
# -- End  main
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .debug_info
	.section .debug_info
.debug_info_seg:
	.align 1
.debug_info_seg:
	.4byte 0x000000ee
	.2byte 0x0004
	.4byte .debug_abbrev_seg
	.byte 0x08
//	DW_TAG_compile_unit:
	.byte 0x01
//	DW_AT_comp_dir:
	.4byte .debug_str
//	DW_AT_name:
	.4byte .debug_str+0x41
//	DW_AT_producer:
	.4byte .debug_str+0x58
	.4byte .debug_str+0xc4
//	DW_AT_language:
	.byte 0x01
//	DW_AT_use_UTF8:
	.byte 0x01
//	DW_AT_low_pc:
	.8byte ..L3
//	DW_AT_high_pc:
	.8byte ..LNmain.66-..L3
	.byte 0x01
//	DW_AT_stmt_list:
	.4byte .debug_line_seg
//	DW_TAG_subprogram:
	.byte 0x02
//	DW_AT_decl_line:
	.byte 0x06
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.4byte .debug_str+0xee
	.4byte .debug_str+0xee
//	DW_AT_low_pc:
	.8byte ..L3
//	DW_AT_high_pc:
	.8byte ..LNtest.24-..L3
//	DW_AT_external:
	.byte 0x01
//	DW_TAG_variable:
	.byte 0x03
//	DW_AT_decl_line:
	.byte 0x09
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.4byte .debug_str+0xf3
//	DW_AT_type:
	.4byte 0x0000006a
//	DW_AT_location:
	.2byte 0x7602
	.byte 0x64
//	DW_TAG_variable:
	.byte 0x04
//	DW_AT_decl_line:
	.byte 0x0e
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.2byte 0x0078
//	DW_AT_type:
	.4byte 0x00000073
//	DW_AT_location:
	.2byte 0x7602
	.byte 0x70
	.byte 0x00
//	DW_TAG_array_type:
	.byte 0x05
//	DW_AT_type:
	.4byte 0x00000073
//	DW_AT_byte_size:
	.byte 0x0c
//	DW_TAG_subrange_type:
	.byte 0x06
//	DW_AT_upper_bound:
	.byte 0x02
	.byte 0x00
//	DW_TAG_base_type:
	.byte 0x07
//	DW_AT_byte_size:
	.byte 0x04
//	DW_AT_encoding:
	.byte 0x05
//	DW_AT_name:
	.4byte 0x00746e69
//	DW_TAG_subprogram:
	.byte 0x08
//	DW_AT_decl_line:
	.byte 0x14
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_type:
	.4byte 0x00000073
//	DW_AT_name:
	.4byte .debug_str+0xfb
	.4byte .debug_str+0xfb
//	DW_AT_low_pc:
	.8byte ..L18
//	DW_AT_high_pc:
	.8byte ..LNmain.66-..L18
	.byte 0x01
//	DW_AT_external:
	.byte 0x01
//	DW_TAG_variable:
	.byte 0x04
//	DW_AT_decl_line:
	.byte 0x17
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.2byte 0x0078
//	DW_AT_type:
	.4byte 0x00000073
//	DW_AT_location:
	.2byte 0x7602
	.byte 0x50
//	DW_TAG_variable:
	.byte 0x04
//	DW_AT_decl_line:
	.byte 0x19
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.4byte 0x00727470
//	DW_AT_type:
	.4byte 0x000000e0
//	DW_AT_location:
	.2byte 0x7602
	.byte 0x60
//	DW_TAG_variable:
	.byte 0x03
//	DW_AT_decl_line:
	.byte 0x1e
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.4byte .debug_str+0x105
//	DW_AT_type:
	.4byte 0x000000e0
//	DW_AT_location:
	.2byte 0x7602
	.byte 0x70
//	DW_TAG_variable:
	.byte 0x03
//	DW_AT_decl_line:
	.byte 0x23
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.4byte .debug_str+0x10a
//	DW_AT_type:
	.4byte 0x00000073
//	DW_AT_location:
	.2byte 0x7602
	.byte 0x54
//	DW_TAG_variable:
	.byte 0x03
//	DW_AT_decl_line:
	.byte 0x24
//	DW_AT_decl_file:
	.byte 0x01
//	DW_AT_name:
	.4byte .debug_str+0x111
//	DW_AT_type:
	.4byte 0x00000073
//	DW_AT_location:
	.2byte 0x7602
	.byte 0x58
	.byte 0x00
//	DW_TAG_pointer_type:
	.byte 0x09
//	DW_AT_type:
	.4byte 0x00000073
//	DW_TAG_pointer_type:
	.byte 0x09
//	DW_AT_type:
	.4byte 0x000000ea
//	DW_TAG_base_type:
	.byte 0x0a
//	DW_AT_byte_size:
	.byte 0x00
//	DW_AT_encoding:
	.byte 0x05
//	DW_AT_name:
	.4byte .debug_str+0x100
	.byte 0x00
// -- Begin DWARF2 SEGMENT .debug_line
	.section .debug_line
.debug_line_seg:
	.align 1
// -- Begin DWARF2 SEGMENT .debug_abbrev
	.section .debug_abbrev
.debug_abbrev_seg:
	.align 1
	.byte 0x01
	.byte 0x11
	.byte 0x01
	.byte 0x1b
	.byte 0x0e
	.byte 0x03
	.byte 0x0e
	.byte 0x25
	.byte 0x0e
	.2byte 0x7681
	.byte 0x0e
	.byte 0x13
	.byte 0x0b
	.byte 0x53
	.byte 0x0c
	.byte 0x11
	.byte 0x01
	.byte 0x12
	.byte 0x07
	.byte 0x6a
	.byte 0x0c
	.byte 0x10
	.byte 0x17
	.2byte 0x0000
	.byte 0x02
	.byte 0x2e
	.byte 0x01
	.byte 0x3b
	.byte 0x0b
	.byte 0x3a
	.byte 0x0b
	.byte 0x03
	.byte 0x0e
	.2byte 0x4087
	.byte 0x0e
	.byte 0x11
	.byte 0x01
	.byte 0x12
	.byte 0x07
	.byte 0x3f
	.byte 0x0c
	.2byte 0x0000
	.byte 0x03
	.byte 0x34
	.byte 0x00
	.byte 0x3b
	.byte 0x0b
	.byte 0x3a
	.byte 0x0b
	.byte 0x03
	.byte 0x0e
	.byte 0x49
	.byte 0x13
	.byte 0x02
	.byte 0x18
	.2byte 0x0000
	.byte 0x04
	.byte 0x34
	.byte 0x00
	.byte 0x3b
	.byte 0x0b
	.byte 0x3a
	.byte 0x0b
	.byte 0x03
	.byte 0x08
	.byte 0x49
	.byte 0x13
	.byte 0x02
	.byte 0x18
	.2byte 0x0000
	.byte 0x05
	.byte 0x01
	.byte 0x01
	.byte 0x49
	.byte 0x13
	.byte 0x0b
	.byte 0x0b
	.2byte 0x0000
	.byte 0x06
	.byte 0x21
	.byte 0x00
	.byte 0x2f
	.byte 0x0b
	.2byte 0x0000
	.byte 0x07
	.byte 0x24
	.byte 0x00
	.byte 0x0b
	.byte 0x0b
	.byte 0x3e
	.byte 0x0b
	.byte 0x03
	.byte 0x08
	.2byte 0x0000
	.byte 0x08
	.byte 0x2e
	.byte 0x01
	.byte 0x3b
	.byte 0x0b
	.byte 0x3a
	.byte 0x0b
	.byte 0x49
	.byte 0x13
	.byte 0x03
	.byte 0x0e
	.2byte 0x4087
	.byte 0x0e
	.byte 0x11
	.byte 0x01
	.byte 0x12
	.byte 0x07
	.byte 0x6a
	.byte 0x0c
	.byte 0x3f
	.byte 0x0c
	.2byte 0x0000
	.byte 0x09
	.byte 0x0f
	.byte 0x00
	.byte 0x49
	.byte 0x13
	.2byte 0x0000
	.byte 0x0a
	.byte 0x24
	.byte 0x00
	.byte 0x0b
	.byte 0x0b
	.byte 0x3e
	.byte 0x0b
	.byte 0x03
	.byte 0x0e
	.2byte 0x0000
	.byte 0x00
// -- Begin DWARF2 SEGMENT .debug_frame
	.section .debug_frame
.debug_frame_seg:
	.align 1
// -- Begin DWARF2 SEGMENT .debug_str
	.section .debug_str,"MS",@progbits,1
.debug_str_seg:
	.align 1
	.8byte 0x616d2f656d6f682f
	.8byte 0x72676f72702f6b72
	.8byte 0x422f676e696d6d61
	.8byte 0x61654c7972616e69
	.8byte 0x6d612f676e696e72
	.8byte 0x657373612d343664
	.8byte 0x65742f72656c626d
	.8byte 0x73656c69665f7473
	.byte 0x00
	.8byte 0x5f726568746f6e61
	.8byte 0x6f72705f74736574
	.4byte 0x6d617267
	.2byte 0x632e
	.byte 0x00
	.8byte 0x2952286c65746e49
	.8byte 0x6c65746e49204320
	.8byte 0x4320343620295228
	.8byte 0x2072656c69706d6f
	.8byte 0x6c70706120726f66
	.8byte 0x736e6f6974616369
	.8byte 0x676e696e6e757220
	.8byte 0x65746e49206e6f20
	.8byte 0x2c3436202952286c
	.8byte 0x6e6f697372655620
	.8byte 0x2e312e312e393120
	.8byte 0x6c69754220373132
	.8byte 0x3330303230322064
	.4byte 0x000a3630
	.8byte 0x7661732d20304f2d
	.8byte 0x2073706d65742d65
	.8byte 0x6e693d6d73616d2d
	.8byte 0x2d20672d206c6574
	.8byte 0x6568746f6e61206f
	.2byte 0x0072
	.4byte 0x74736574
	.byte 0x00
	.8byte 0x005245544e494f50
	.4byte 0x6e69616d
	.byte 0x00
	.4byte 0x64696f76
	.byte 0x00
	.4byte 0x32727470
	.byte 0x00
	.4byte 0x706d6173
	.2byte 0x656c
	.byte 0x00
	.8byte 0x0032656c706d6173
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
	.section .text
.LNDBG_TXe:
# End
