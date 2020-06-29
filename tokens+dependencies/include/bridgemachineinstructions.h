#ifndef BRIDGEMACHINEINSTRUCTIONS_H
#define BRIDGEMACHINEINSTRUCTIONS_H

#include "get_instructions.h"
#include "machine_instructions.h"


void fill_opcode(struct machine_instruction *machine_instruction, struct instruction_format *instr );
void fill_mode(struct machine_instruction *machine_instruction, struct instruction_format *instr );
void set_lock_status(struct machine_instruction *machine_instruction, struct instruction_format *instr );



#endif
