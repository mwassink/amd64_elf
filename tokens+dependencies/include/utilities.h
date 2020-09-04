#ifndef UTILITIES_H
#define UTILITIES_H
#include <stdbool.h>
#include "../include/customtypes.h"
#include <stdio.h>
#include <assert.h>


bool needs_rex_r(const char *input);
int move_to_endline(const char * input_string, int start_iterator);
int move_to_space (const char * input_string, int start_iterator);
void byte_from_sib_part(const char * in, prefixes *prefix);
int move_to_general(const char * input_string, int start_iterator, char general_char);
bool compare_strings(char * lhs, const char * rhs);
void example_print_value_binary();
void print_binary(unsigned long int input_number);
long unsigned int  name_to_id( char * mnemonic);
int * possible_sizes(char * available_operands_in);
void switch_on_possible_sizes(int in, struct available_sizes *sizes_in);
void fill_possible_sizes(struct available_sizes *sizes_in, char * instruction_in);
bool check_for_segment_register(char *reg);
enum Basic_Operands type_fallback(const char * in);
enum Basic_Operands operand_type_return(char *in);
int fill_string_with_line(int max_size, char * string, FILE *fptr);

int numbits_from_suffix(char * instruction_at_suffix);
int check_for_lock_prefix( char * string, int *start_index);
int fill_string_until_character(const char *input_string, char *target, int start_iterator, char condition);
prefixes byte_from_prefixes(union operand_types op1, union operand_types op2, enum Basic_Operands type1,
				   enum Basic_Operands type2, unsigned char * write_spot);
int sort_instruction_set(struct instruction_definition *definition_array, struct instruction_format * formats);
int move_while_general(const char * input_string, int start_iterator , char general_char);
int fill_string_until_character(const char *input_string, char *target, int start_iterator, char condition);

#endif

