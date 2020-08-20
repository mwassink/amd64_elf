#ifndef GET_INSTRUCTIONS_H
#define GET_INSTRUCTIONS_H

#include <stdio.h>
#include "customtypes.h"
#include <stdbool.h>



int string_restrict(char * input);
void pool_memory(struct instruction_format *instr_ptr, char * char_pool_begin);
unsigned char byte_hexstring_to_int(char * input);
void gather_instruction(struct instruction_format *instr, FILE * read_pointer, int *catches);
void write_instruction_stdout(struct instruction_format *instr);
void example_print_value_binary();
void print_binary(unsigned long int input_number);
long unsigned int name_to_id(char * mnemonic);
void bubble_sort_instructions(struct ID_instr_pair * pair_array, int size);
struct instruction_format*  pool_struct_memory(int instructions);
char * pool_character_memory(int instructions);
unsigned int map_register_to_ID(char * reg);
void pull_instructions_and_rewrite();




#endif
