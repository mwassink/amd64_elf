#include <stdio.h>
#include "../include/get_instructions.h"
#include "../include/machine_instructions.h"
#include "../include/bridgemachineinstructions.h"





void fill_opcode(struct machine_instruction *machine_instruction, struct instruction_format *instr)
{
  int i = 0;
  if (instr->prefix != 0)
    {
      machine_instruction->opcode[i++] = instr->prefix;
    }
  if (instr->prefix_OF != 0)
    {
      machine_instruction->opcode[i++] = instr->prefix_OF;
    }
  machine_instruction->opcode[i++] = instr->primary_opcode;

  if (instr->secondary_opcode != 0)
    {
      machine_instruction->opcode[i++] = instr->secondary_opcode;
    }
  
}

void fill_mode(struct machine_instruction *machine_instruction, struct instruction_format *instr)
{
  machine_instruction->attributes.allowed_modes[smm] = 0;
  if(instr->mode == 0) 
    {
      machine_instruction->attributes.allowed_modes[Real] = 1;
      machine_instruction->attributes.allowed_modes[Protected] = 1;
      machine_instruction->attributes.allowed_modes[bit64] = 1;
    }
  if (instr->mode == 'P')
    {
      machine_instruction->attributes.allowed_modes[Real] = 0;
      machine_instruction->attributes.allowed_modes[Protected] = 1;
      machine_instruction->attributes.allowed_modes[bit64] = 1;
      
    }

  if (instr->mode == 'E')
    {
      machine_instruction->attributes.allowed_modes[bit64] = 1;
      machine_instruction->attributes.allowed_modes[Real] = 0;
      machine_instruction->attributes.allowed_modes[Protected] = 0;
    }
}


void set_lock_status(struct machine_instruction *machine_instruction, struct instruction_format * instr)
{
  if (instr->lock_prefix == 0)
    {
      machine_instruction->attributes.lockable = 0;
    }
  else
    {
      machine_instruction->attributes.lockable = 1;
    }
}



