#ifndef GET_TOKENS_H
#define GET_TOKENS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>




//enumerate valid tokens to assemble
//enumerate valid suffixes to assemble
//at&t syntax first

// %rax, %rbx, %rcx,%rdx %rbp,%rsp,


const char * valid_general_registers[] = {"%rax", "%eax", "%ax", "%rbx", "%ebx", "%bx",
                                  "%rcx","%ecx", "%cx", "%rdx", "%edx", "%dx"      };
const char * utility_registers[] = {"%rsp", "%esp", "%rbp", "%ebp", "%rsi", "%rdi",
                                    "%esi", "edi" };





#endif
