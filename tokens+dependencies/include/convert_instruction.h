#ifndef CONVERT_INSTRUCTION_H
#define  CONVERT_INSTRUCTION_H
#include <stdbool.h>
#include "get_instructions.h"


#include "stdlib.h"
#include "customtypes.h"
#include "utilities.h"

char *slow_getline(FILE * file_in);
void fill_dependencies ( struct instruction_format *instr_format, struct dependencies * deps);
void convert_instruction(struct instruction_definition *definition, struct instruction_format *format) ;
void write_new_definitions(struct instruction_definition *definitions, int num_formats, struct instruction_format *format);
void friendly_output(struct instruction_definition *definitions, int num_formats, struct instruction_format* format);






#endif
