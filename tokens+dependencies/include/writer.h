#ifndef WRITER_H
#define WRITER_H
#include <stdio.h>
#include <stdbool.h>
#include "../include/customtypes.h"


potential_writes write_instruction_opcode_from_line( struct instruction_definition *table, FILE * current_spot, struct symbols_information *symbols_in);
int  writer( FILE* user_file, struct symbols_information *symbols_in, int*);





#endif
