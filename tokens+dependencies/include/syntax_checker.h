#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H

#include <stdio.h>
#include <stdlib.h>

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
int  look_for_mnemonic(char *instr_mnemonic, int* shorter_mnemonics, int* longer_mnemonics);
void search_line(FILE * in, struct instruction_pieces *arguments);
int  binary_lookup(int in, int* array_in);
int rip_suffix(char *instruction_mnemonic);
void check_memory_operand(struct instruction_pieces* in);
void assert_dependencies(struct instruction_pieces *in); // TODO
int write_modrm(struct instruction_pieces *in);



#endif