#include "../include/get_instructions.h"
#include "../include/utilities.h"
#include "../include/customtypes.h"
#include "../include/get_instructions.h"
#include <stdlib.h>
#include <stdbool.h>

// The goal of this file is to provide a function to convert from the tabled to the necessary form
// It will provide functions to do this

int missed_instructions_counter = 0;
int instructions_counted = 0;
int dependencies_filled = 0;


bool fill_dependencies ( struct instruction_format *instr_format, struct dependencies * deps)
{
  // May need to be changed if it does not work 
  // Start comparing the strings with the above function
  dependencies_filled++;
 
  deps->one = operand_type_return(instr_format->op1);
  deps->two = operand_type_return(instr_format->op2);

  if (deps->one == not_found)
    {
      return 1;
    }
  else if (deps->two == not_found)
    {
      return 1;
    }
  
  deps->allowed_sizes.one_byte = 0; deps->allowed_sizes.byte_high = 0;
  deps->allowed_sizes.byte_16 = 0;
  deps->allowed_sizes.byte_2 = 0; deps->allowed_sizes.byte_4 = 0;
  deps->allowed_sizes.byte_8 = 0;

  fill_possible_sizes(&deps->allowed_sizes, instr_format->op1);
  fill_possible_sizes(&deps->allowed_sizes, instr_format->op2);


  return 0;
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

  definition->not_supported = fill_dependencies(format, &definition->requirements);
  definition->prefix = format->prefix;
  definition->requirements.highest_ring = format->ring_level;
  definition->prefix_OF = format->prefix_OF;
  definition->r = format->reg_opcode_field;
  

  
}



void write_new_definitions(struct instruction_definition *definitions, int num_formats, struct instruction_format *format)
{
  // Need to write the new definitions to a file as they are processed
  struct instruction_definition for_size;
  FILE * fp = fopen("converted_instructions.bin", "wb");

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

    }

  int num_longs = sort_instruction_set(definitions, format);
  for (int i =0; i < 1074; ++i)
    {
      
      size_t written = fwrite(definitions + i, sizeof(for_size), 1, fp );

      
      if (written != 1)
	{
	  fprintf(stderr, "Failure to write the binary to a new file");
	  return;
	}

     
    }

  printf("Number of longs: %d", num_longs);
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
  
  //friendly_output(definitions_for_new_file, 1074 , array_of_initial_instructions);
  
  free(homes_for_strings);
  free(array_of_initial_instructions);
  free(definitions_for_new_file);
  


  
}



