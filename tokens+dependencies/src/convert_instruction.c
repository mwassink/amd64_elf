#include "dependencies.h"
#include "get_text_tokens.h"
#include "get_instructions.h"
#include "instruction_definition.h"

// The goal of this file is to provide a function to convert from the tabled to the necessary form
// It will provide functions to do this


void fill_in_ops(struct instruction_format *format, struct dependencies *dep)
{
  // Look for immediates, xmm, mm, registers, and memory

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

  else if (format->op1[0] == 'x' && format->op1[1] == 'm'  && format->op1[2] == 'm')
    {
      dep->max_size = 16; // Not sure of the significance of this size yet
      dep->one = xmm;
    }

  else if (format->op1[0] == 'm'  && format->op1[1] == 'm')
    {
      dep->max_size = 8; //
      dep->one = xmm;
    }

  else if (format->op1[0] == 's' && format->op1[1] == 't')
    {
      dep->max_size = 8; // No idea how big this register is
      deep->one = stack_reg;
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

   else if (format->op2[0] == 'i' && format->op2[1] == 'm' && format->op2[2] == 'm' && format->op2[3] == '8')
    {
      dep->max_size = 1;
      dep->one = immediate;
    }

  else if (format->op2[0] == 'i' && format->op2[1] == 'm' && format->op2[2] == 'm' && format->op2[3] == '1')
    {
      dep->max_size = 8;
      dep->one = immediate;
    }

  else if (format->op2[0] == 'x' && format->op2[1] == 'm'  && format->op2[2] == 'm')
    {
      dep->max_size = 16; // Not sure of the significance of this size yet
      dep->one = xmm;
    }

  else if (format->op2[0] == 'm'  && format->op2[1] == 'm')
    {
      dep->max_size = 8; //
      dep->one = xmm;
    }

  else if (format->op2[0] == 's' && format->op2[1] == 't')
    {
      dep->max_size = 8; // No idea how big this register is
      deep->one = stack_reg;
    }

  else
    {
      printf("Failure looking through the instructions given from the file");
    }


  
}



void convert_instruction(struct instruction_definition *definition, struct instruction_format *format) // definition is the target
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

  fill_in_ops(format, &definition->requirements);
  definition->prefix = format->prefix;
  definition->prefix_OF = format->prefix_OF;

  
}



void write_new_definitions(struct instruction_definition *definition, int num_formats, struct instruction_format *format)
{
  // Need to write the new definitions to a file as they are processed
  struct instruction_definition definition;
  FILE * fp = fopen("converted_instructions.txt", "wb");

  if (!fp)
    {
      fprintf(stderr, "Failed to open a memory-mapped file handle for writing");
    }



  // There should be 1074 of the formats in the text file
  for (int i = 0; i != num_formats; ++i)
    {
      convert_instruction(definition[i], format[i]);
      size_t written = fwrite(definition + i, sizeof(definition), 1, fp );
      if (written != 1)
	{
	  fprintf(stderr, "Failure to write the binary to a new file");
	  return;
	}
    }
}
