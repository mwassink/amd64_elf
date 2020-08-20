#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "customtypes.h"
enum Sections {_text, _bss, data};
 // This is shared between the human instructions and the table



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
void check_instruction(struct instruction_pieces *in, unsigned long int *shorter_mnemonics, unsigned long int *longer_mnemonics, struct dependencies *dep);
int write_modrm(struct instruction_pieces *in);
bool assert_dependencies(struct instruction_pieces *user_in, struct dependencies *table_in);


#endif
