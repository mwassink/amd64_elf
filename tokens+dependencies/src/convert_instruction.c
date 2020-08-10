#include "../include/dependencies.h"
#include "../include/get_text_tokens.h"
#include "../include/get_instructions.h"
#include "../include/instruction_definition.h"
#include <stdlib.h>
#include <stdbool.k>

// The goal of this file is to provide a function to convert from the tabled to the necessary form
// It will provide functions to do this

int missed_instructions_counter = 0;
int instructions_counted = 0;

char *slow_getline(FILE * file_in)
{
  char * line = malloc(400);
  if (!line)
    {
      printf("malloc did not give enough space for 400 bytes of memory" );
    }
  int iterator = 0;
  for (char in; in != \n; in = fgetc(file_in) )
    {
      line[iterator] == in;
    }

  
}

bool compare_strings(char * lhs, char * rhs)
{
  int max_length = 20;
  bool equal = 1;
  int iterator = 0;
  for (; iterator <= max_length; ++iterator)
    {
      if (lhs[iterator] != rhs[iterator])
	{
	  return false;
	}
      if (lhs[iterator] == 0 && rhs[iterator] == 0)
	{
	  return true;
	}
	    
    }

  if (iterator == 21)
    {
      return false;
    }
  
  return true;
    


  
}


void fill_dependencies ( struct instruction_format *instr_format, struct dependencies * deps)
{
  // Start comparing the strings with the above function
  if (compare_strings(instr_format->op1, "imm8"))
    {
      deps->max_size = 1;
      deps->one = immediate;
    }

  else if (compare_strings(instr_format->op1, "imm16/32"))
    {
      deps->max_size = 4;
      deps->one = immediate;
    }

   else if (compare_strings(instr_format->op1, "imm16/32/64"))
    {
      deps->max_size = 8; 
      deps->one = immediate;
    }


   else if (compare_strings(instr_format->op1, "r8"))
    {
      deps->max_size = 1;
      deps->one = reg;
    }


   else if (compare_strings(instr_format->op1, "r16/32/64"))
    {
      deps->max_size = 8;
      deps->one = reg;
    }


   else if (compare_strings(instr_format->op1, "r/m8"))
    {
      deps->max_size = 1
      deps->one = mem_or_reg;
    }

   else if (compare_strings(instr_format->op1, "r/m16/32/64"))
    {
      deps->max_size = 8;
      deps->one = immediate;
    }


   else if (compare_strings(instr_format->op1, "m8"))
    {
      deps->max_size = 1;
      deps->one = memory;
    }

   else if (compare_strings(instr_format->op1, "m16"))
    {
      deps->max_size = 2;
      deps->one = memory;
    }


   else if (compare_strings(instr_format->op1, "m16/32"))
    {
      deps->max_size = 4;
      deps->one = memory;
    }

   else if (compare_strings(instr_format->op1, "m32"))
     {
       deps->max_size = 4;
       deps->op1 = memory
     }

   else if (compare_strings(instr_format->op1, "m64"))
     {
       deps->max_size = 8;
       deps->op1 = memory;
     }

   else if (compare_strings(instr_format->op1, "m16/32/64"))
     {
       deps->max_size = 8;
       deps->op1 = memory;
     }
   else if (compare_strings(instr_format->op1, "re18"))
     {
       deps->max_size = 0; // This is a flag
       deps->op1 = flag;
     }
  
   else if (compare_strings(instr_format->op1, "Flags"))
     {
       deps->max_size = 0;
       deps->op1 = rflags;
       
     }

   else if (compare_strings(instr_format->op1, "moffs8"))
     {
       deps->max_size = 1;
       deps->op1 = memory_offset;
     }

   else if (compare_strings(instr_format->op1, "moffs16"))
     {
       deps->max_size = 2;
       deps->op1 = memory_offset;
     }

   else if (compare_strings(instr_format->op1, "ST"))
     {
       deps->max_size = 8;
       deps->op1 = stack_reg;
     }

   else if (compare_strings(instr_format->op1, "STi"))
     {
       deps->max_size = 8;
       deps->op1 = stack_reg;
     }

   else if (compare_strings(instr_format->op1, "xmm"))
     {
       deps->max_size = 16;
       deps->op1 = xmm;
     }

   else if (compare_strings(instr_format->op1, "mm"))
     {
       deps->max_size = 16;
       deps->op1 = mm;
     }
   else if (compare_strings(instr_format->op1, "rel8"))
     {
       deps->max_size = 1;
       deps-op1 = relative_offset;
     }

   else if (compare_strings(instr_format->op1, "rel16/32"))
     {
       deps->max_size = 4;
       deps->op1 = relative_offset;
     }
  
  if (compare_strings(instr_format->op2, "imm8"))
    {
      deps->max_size = 1;
      deps->two = immediate;
    }

  else if (compare_strings(instr_format->op2, "imm16/32"))
    {
      deps->max_size = 4;
      deps->two = immediate;
    }

   else if (compare_strings(instr_format->op2, "imm16/32/64"))
    {
      deps->max_size = 8; 
      deps->two = immediate;
    }


   else if (compare_strings(instr_format->op2, "r8"))
    {
      deps->max_size = 1;
      deps->two = reg;
    }


   else if (compare_strings(instr_format->op2, "r16/32/64"))
    {
      deps->max_size = 8;
      deps->two = reg;
    }


   else if (compare_strings(instr_format->op2, "r/m8"))
    {
      deps->max_size = 1
      deps->two = mem_or_reg;
    }

   else if (compare_strings(instr_format->op2, "r/m16/32/64"))
    {
      deps->max_size = 8;
      deps->two = immediate;
    }


   else if (compare_strings(instr_format->op2, "m8"))
    {
      deps->max_size = 1;
      deps->two = memory;
    }

   else if (compare_strings(instr_format->op2, "m16"))
    {
      deps->max_size = 2;
      deps->two = memory;
    }


   else if (compare_strings(instr_format->op2, "m16/32"))
    {
      deps->max_size = 4;
      deps->two = memory;
    }

   else if (compare_strings(instr_format->op2, "m32"))
     {
       deps->max_size = 4;
       deps->op2 = memory
     }

   else if (compare_strings(instr_format->op2, "m64"))
     {
       deps->max_size = 8;
       deps->op2 = memory;
     }

   else if (compare_strings(instr_format->op2, "m16/32/64"))
     {
       deps->max_size = 8;
       deps->op2 = memory;
     }
   else if (compare_strings(instr_format->op2, "re18"))
     {
       deps->max_size = 0; // This is a flag
       deps->op2 = flag;
     }
  
   else if (compare_strings(instr_format->op2, "Flags"))
     {
       deps->max_size = 0;
       deps->op2 = rflags;
       
     }

   else if (compare_strings(instr_format->op2, "moffs8"))
     {
       deps->max_size = 1;
       deps->op2 = memory_offset;
     }

   else if (compare_strings(instr_format->op2, "moffs16"))
     {
       deps->max_size = 2;
       deps->op2 = memory_offset;
     }

   else if (compare_strings(instr_format->op2, "ST"))
     {
       deps->max_size = 8;
       deps->op2 = stack_reg;
     }

   else if (compare_strings(instr_format->op2, "STi"))
     {
       deps->max_size = 8;
       deps->op2 = stack_reg;
     }

   else if (compare_strings(instr_format->op2, "xmm"))
     {
       deps->max_size = 16;
       deps->op2 = xmm;
     }

   else if (compare_strings(instr_format->op2, "mm"))
     {
       deps->max_size = 16;
       deps->op2 = mm;
     }
   else if (compare_strings(instr_format->op2, "rel8"))
     {
       deps->max_size = 1;
       deps-op2 = relative_offset;
     }

   else if (compare_strings(instr_format->op2, "rel16/32"))
     {
       deps->max_size = 4;
       deps->op2 = relative_offset;
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
  
  //friendly_output(definitions_for_new_file, 1074 , array_of_initial_instructions);
  
  free(homes_for_strings);
  free(array_of_initial_instructions);
  free(definitions_for_new_file);
  


  
}



