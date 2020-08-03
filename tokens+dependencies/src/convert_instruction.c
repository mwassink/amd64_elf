#include "dependencies.h"
#include "get_text_tokens.h"
#include "get_instructions.h"
#include "instruction_definition.h"

// The goal of this file is to provide a function to convert from the tabled to the necessary form
// It will provide functions to do this


void fill_in_ops(struct instruction_format *format, struct dependencies *dep)
{

  if (format->op1[0] == 'r' && format->op1[1] == '8') //r8
    {
      dep->max_size = 1;
      dep->one = reg;
    }
  else if (format->op1[0] == 'r' && format->op1[1] == '/' && format->op1[2] == 'm' && format->op1[3] == '8') //r/m8
    {
      dep->max_size = 1;
      dep->one = mem_or_reg;
    }

  else if (format->op1[0] == 'r' && format->op1[1] == '1' && format->op1[2] == '6' && format->op1[3] == '/')
    {
      dep->max_size = 8;
      dep->one = reg;
    }


  else if (format->op1[0] == 'r' && format->op1[1] == '/' && format->op1[2] == 'm' && format->op1[3] == '1') //  r/m16+
    {
      dep->max_size = 8;
      dep->one = mem_or_reg;
    }

  else if (format->op1[0] == 'i' && format->op1[1] == 'm' && format->op1[2] == 'm' && format->op1[3] == '8')
    {
      dep->max_size = 1;
      dep->one = immediate;
    }

  else if (format->op1[0] == 'i' && format->op1[1] == 'm' && format->op1[2] == 'm' && format->op1[3] == '1')
    {
      dep->max_size = 8;
      dep->one = immediate;
    }

  else
    {
      printf("Failure looking through the instructions given from the file");
    }

op_two:


  if (format->op2[0] == 'r' && format->op2[1] == '8') //r8
    {
      dep->max_size = 1;
      dep->one = reg;
    }
  else if (format->op2[0] == 'r' && format->op2[1] == '/' && format->op2[2] == 'm' && format->op2[3] == '8') //r/m8
    {
      dep->max_size = 1;
      dep->one = mem_or_reg;
    }

  else if (format->op2[0] == 'r' && format->op2[1] == '1' && format->op2[2] == '6' && format->op2[3] == '/')
    {
      dep->max_size = 8;
      dep->one = reg;
    }


  else if (format->op2[0] == 'r' && format->op2[1] == '/' && format->op2[2] == 'm' && format->op2[3] == '1') //  r/m16+
    {
      dep->max_size = 8;
      dep->one = mem_or_reg;
    }

}



void convert_instruction(struct instruction_definition *definition, struct instruction_format *format)
{
  definition->mnemonic = format->ID; // Aliases for the same idea
  definition->opcode = format->primary_opcode;
  definition->secondary_opcode = format->secondary_opcode;
  if (format->lock_prefix == 'L')// Will lock
    {
      definition->requirements.lockable = 1;
    }
  else
    {
      definition->requirements.lockable = 0;
    }











}
