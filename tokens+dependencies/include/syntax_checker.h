#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum Sections {_text, _bss, data};
enum Basic_Operands {immediate, memory, reg, sib};


struct instruction_pieces
{
  char * instruction_mnemonic;
  long unsigned int instruction; // This will match the table which allows for a quick search
  enum Basic_Operands op1;
  int op1_size;
  char * op1_mnemonic;
  enum Basic_Operands op2;
  int op2_size;
  char * op2_mnemonic;
  int size;
};


struct memory_op_info
{
  int disp_offset;
  int disp_length;
  int disp;
  int sib_scale; // -1 if not available
  int reg1_off, reg2_off; // -1 if the register does not exist
  bool sib; // Good easy way to check for the sib byte 
};

/* struct sib
{
    // The first thing needed is the scale
    // Next thing needed is the base register
    int mod_prev;
    int scale;
    char* base; // cannot be rbp
    char* index;
};
*/


void _text_checker(FILE * in);
void process_arguments(struct instruction_pieces *arguments);
int  look_for_mnemonic(char *instr_mnemonic, unsigned long int* shorter_mnemonics, unsigned long int* longer_mnemonics);
void search_line(FILE * in, struct instruction_pieces *arguments);
int binary_lookup(unsigned long int in, unsigned long int* array_in);
int rip_suffix(char *instruction_mnemonic);
struct memory_op_info check_memory_operand(char * memory_instruction_in);
void assert_dependencies(struct instruction_pieces *in, unsigned long int *shorter_mnemonics, unsigned long int *longer_mnemonics);
int write_modrm(struct instruction_pieces *in);



#endif
