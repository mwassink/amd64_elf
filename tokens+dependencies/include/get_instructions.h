#ifndef GET_INSTRUCTIONS_H
#define GET_INSTRUCTIONS_H

#include <stdio.h>
#include "char_to_instructions.h"

struct instruction_format {
    // might have alignment issues, be careful
  int pooled;
    unsigned char prefix; /* 0 if there is no prefix */
    int prefix_OF;
    unsigned char primary_opcode; /* 0 if this is a prefix or does not have one */
    unsigned char secondary_opcode; /* 0 if this does not exist */
    char reg_opcode_field; /* 0 if this is not specified	*/
    unsigned char documentation; // below this should all be 1 normal letter so a signed char should be fine
    unsigned char mode;
    char ring_level;
    unsigned char lock_prefix;
 
    char *mnemonic; //16

    char *op1; //16
    char *op2; //16
    char *op3; //16
    char *op4; //16
    char *iext; //16
    char *tested_flags; //16
    char *modif_flags; //16
    char *def_flags; //16
    char *undef_flags; //16
    char *flag_values; //16
    char *fields; //5
    unsigned long int ID;
};

struct ID_instr_pair
{
  struct instruction_format * instr_ptr;
  unsigned long int ID;
};

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
