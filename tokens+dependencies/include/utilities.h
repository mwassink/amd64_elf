#ifndef UTILITIES_H
#define UTILITIES_H
#include <stdbool.h>

bool compare_strings(char * lhs, char * rhs);
void example_print_value_binary();
void print_binary(unsigned long int input_number);
long unsigned int  name_to_id( char * mnemonic);
inline int move_to_space (const char * input_string, int start_iterator);
inline int move_to_endline(const char * input_string, int start_iterator);
void switch_on_possible_sizes(int in, struct available_sizes *sizes_in);
void fill_possible_sizes(struct available_sizes *sizes_in, char * instruction_in);
int * possible_sizes(char * available_operands_in);
inline int move_to_general(const char * input_string, int start_iterator, char general_char)
bool check_for_segment_register(char *reg);
enum Basic_Operands type_fallback(const char * in);
enum Basic_Operands operand_type_return(const char *in);
int fill_string_with_line(int max_size, char * string, FILE *fptr);
#endif

