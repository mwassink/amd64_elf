#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "customtypes.h"
typedef struct sib sib_pieces;
typedef struct memory_op_info regular_memory_operand;
 // This is shared between the human instructions and the table

bool check_sizes(int size_in, struct available_sizes available);
enum section_types check_for_section_label(const char * input_string, int * iterator_in);
int check_for_jump_label(consth char * input_string);
void init_op_info(struct memory_op_info *in);
int ascii_to_int( char * in, int *returned_index);
void search_line(FILE * file_in, struct instruction_pieces *arguments, enum section_types current_type, struct symbols_information *symbols);
int binary_lookup(unsigned  int in, unsigned  int* array_in);
int rip_suffix(char *instruction_mnemonic, int depth);
int search_for_mnemonic (unsigned long int mnemonic_ID, unsigned long *array);
inline int check_for_offset(char * string, int *start_parentheses, int *disp_value);
regular_memory_operand check_memory_operand(char * memory_instruction_in);
sib_pieces sib_from_string(char *sib_instruction_in);
void check_instruction(struct instruction_pieces *in, unsigned long int *shorter_mnemonics, unsigned long int *longer_mnemonics, struct dependencies *dep);
bool assert_dependencies(struct instruction_pieces *user_in, struct dependencies *table_in);
enum Basic_Operands user_string_to_operand(const char *string_in, int start_index);
char *copy_until_space(char * old);

#endif
