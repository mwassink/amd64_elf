#ifndef MODRM_H
#define MODRM_H

#include <stdbool.h>
#include "customtypes.h"
// The ModR/M byte depends on several factors and input registers
// The Rex determines the registers that will get chosen
// This is supposed to assemble instructions, so I only need the input registers



int ascii_to_int_hex(char* input);
struct __instruction encode_registers_rm(char* op1, char* op2, bool op1_rm);
inline bool reg_string_compare(char* in, char* in2);
int mod00_table(char* in);
int mod10_01_table(char* in);
int mod11_r(char* in);
int mod11_e(char* in);
int mod11_st(char* in);
int mod11_mm(char* in);
int mod11_xmm(char* in);
int mod11_rex(char* in);
int mod11_others(char* in);
void reg_table_register_new(struct temprm* temp, char* reg, bool is_first);
int ret_mod(char* input);
void reg_table_register_extension(struct temprm* temp, char* reg, bool is_first, bool rex_r);
void reg_table_byte_no_rex(struct temprm* temp, char* reg, bool is_first);
void reg_table_byte_rex(struct temprm* temp, char* reg, bool is_first);
void table_segment_register(struct temprm* temp, char* reg, bool is_first);
void table_rm_mod00(struct temprm* temp, char* reg, bool is_first, bool rex_r);
void table_rm_mod01(struct temprm* temp, char* reg, bool is_first, bool rex_r);
void table_rm_mod10(struct temprm* temp, char* reg, bool is_first);


// It is up to the instruction to decide whether it needs to be encoded with this
// It should not need to know which rex is needed as an input, but rather it should figure it out
struct __instruction encode_registers_rm( char * op1,  char * op2, bool op1_rm );

#endif
