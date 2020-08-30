#include <stdio.h>
#include "../include/customtypes.h"
#include "../include/convert_instruction.h"
#include "../include/machine_instructions.h"
#include "../include/modrm.h"
#include "../include/sib.h"
#include "../include/symbols.h"
#include "../include/syntax_checker.h"
#include "../include/utilities.h"

// This file will pull some of the other files and write opcodes
// It will also deposit other symbols like functions and files into a different file
typedef struct 
{
  prefixes potential_prefixes; // address override, other register prefixes
  char prefix_OF;
  unsigned char primary_opcode;
  unsigned char secondary_opcode;
  unsigned char modrm;
  unsigned char sib;
  int displacement; // max of 32 bits
  int immediate; // max of 32 bits
} potential_writes;


int write_instruction_opcode_from_line( unsigned char * instruction, struct instruction_definition *table, FILE * current_spot, struct Elf64_Sym *symbols_in)
{
  // Make sure that this is not a label first
  
  struct instruction_pieces args_from_the_user;
  search_line(current_spot, &args_from_the_user, text,  symbols_in);

  union operand_types operand1;
  // Switch staement would probably be a better idea 
  if (args_from_the_user.op1 == memory)
    {
      operand1.mem_op = construct_memory_operand(args_from_the_user.op1_mnemonic);
    }
  else if (args_from_the_user.op1 == sib)
    {
      operand1.sib_op = construct_sib_from_string(args_from_the_user.op1_mnemonic);
    }
  // make a check for the max size of the immediate to produce the right size of the immediate. it
  // will be the largest size 
  else if (args_from_the_user.op1 == immediate)
    {
      int size_immediate = 0;
      if (table->requirements.allowed_sizes.byte_8)
	{
	  size_immediate = 64; // bits
	  unsigned long int 
	}
      else if (table->requirements.allowed_sizes.byte_4)
	{
	  size_immediate = 32; // bits 
	}
      else if (table->requirements.allowed_sizes.byte_2)
	{
	  size_immediate = 16; // bits
	}
      else if (table->requirements.allowed_sizes.one_byte)
	{
	  size_immediate = 8; // bits
	}

      else
	{
	  fprintf(stderr, "Error with definition from the input file");
	  assert(0 ==1);
	}
      // This will come last 
    }
  else if ()
  
  
  
}




void writer( char * file_in)
{
  printf("Defaulting to .text as section if none given");
  char string[250] = {0};

  FILE * file_pointer = fopen(file_in, "r");
  
  while (file_pointer)
    {
      
    }
}
