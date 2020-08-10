#include "../include/dependencies.h"
#include "../include/get_text_tokens.h"
#include "../include/get_instructions.h"
#include "../include/instruction_definition.h"
#include "stdlib.h"

// The goal of this file is to provide a function to convert from the tabled to the necessary form
// It will provide functions to do this

int missed_instructions_counter = 0;
int instructions_counted = 0;

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
      dep->one = stack_reg;
    }

  else
    {
      dep->max_size = 0;
      printf("%d op1: %s not found", instructions_counted, format->op1);
     
    }



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
      dep->one = stack_reg;
    }

  else
    {
      dep->max_size = 0;
      printf("%d op1: %s not found", instructions_counted, format->op2);
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
  

  
}



void write_new_definitions(struct instruction_definition *definitions, int num_formats, struct instruction_format *format)
{
  // Need to write the new definitions to a file as they are processed
  struct instruction_definition for_size;
  FILE * fp = fopen("converted_instructions.txt", "wb");

  if (!fp)
    {
      fprintf(stderr, "Failed to open a memory-mapped file handle for writing");
      return;
    }


  int missing_instruction = 0;
  // There should be 1074 of the formats in the text file
  // No reason for a malloc call here if we're going to write right after
  for (int i = 0; i != num_formats; ++i)
    {
      missing_instruction = 0;
      convert_instruction(definitions + i, format + i);

      if (definitions[i].requirements.max_size == 0)
	{
	  // Operand type was not found
	  missing_instruction++; // Can be used as a breakpoint
	  
	}

      
      size_t written = fwrite(definitions + i, sizeof(for_size), 1, fp );
      if (written != 1)
	{
	  fprintf(stderr, "Failure to write the binary to a new file");
	  return;
	}

     
    }
}



void friendly_output(struct instruction_definition *definitions, int num_formats, struct instruction_format* format)
{
  struct instruction_definition temp;
  
  for (int i = 0; i < num_formats; ++i)
    {
      convert_instruction(&temp, format + i);
      printf("%d: " , i);
      char * letter = (char *)&temp;
      int offset = 0;
      for (int i = 0; i < sizeof(temp); ++i)
	{
	  if (offset++ % 4 == 0)
	    {
	      printf("\n");
	    }
	  int temporary_number = *(letter + i);
	  printf("%d", temporary_number);
	}
      printf("\n");
    }
  
}

int main()
{
  // FIrst manage the memory
  struct instruction_format example_for_size;
  struct instruction_format *array_of_initial_instructions = (struct instruction_format*)malloc(1074 *sizeof(example_for_size));
  if (array_of_initial_instructions == 0)
  {
      printf("Not enough space on the heap");
      return -1;
  }
  char *homes_for_strings = (char *)malloc(1074 * 208);
  if (!homes_for_strings)
  {
      printf("Not enough space on the heap");
      return -1;
  }

  FILE * instruction_handle_in = fopen("../misc/instructions.txt", "r");
  if (!instruction_handle_in)
    {
	  instruction_handle_in = fopen("misc/instructions.txt", "r");
	  if (!instruction_handle_in)
	  {
		  fprintf(stderr, "Failure to create a memory mapped file handle for the instructions");
		  return -1;
	  }
    }
  int catches = 0; 
  for (int i = 0; i < 1074; ++i)
    {
      instructions_counted++;
      pool_memory(array_of_initial_instructions + i, homes_for_strings + (208*i)); // The offset for strings should be 208
      gather_instruction(array_of_initial_instructions + i, instruction_handle_in, &catches);
      array_of_initial_instructions[i].ID = name_to_id(array_of_initial_instructions[i].mnemonic);
    }

  struct instruction_definition def_for_size;
  struct instruction_definition *definitions_for_new_file = (struct instruction_definition*) malloc(1074 * sizeof(def_for_size));
  
  write_new_definitions(definitions_for_new_file, 1074, array_of_initial_instructions);
  
  friendly_output(definitions_for_new_file, 1074 , array_of_initial_instructions);
  
  free(homes_for_strings);
  free(array_of_initial_instructions);
  free(definitions_for_new_file);
  


  
}



