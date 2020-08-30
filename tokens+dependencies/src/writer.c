#include <stdio.h>
#include "../include/customtypes.h"
#include "../include/convert_instruction.h"
#include "../include/machine_instructions.h"
#include "../include/modrm.h"
#include "../include/sib.h"
#include "../include/symbols.h"
#include "../include/syntax_checker.h"
#include "../include/utilities.h"
#include <string.h>

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
  potential_writes to_be_written;
  struct instruction_pieces args_from_the_user;
  search_line(current_spot, &args_from_the_user, text,  symbols_in);


  memset((void *)&to_be_written,0 ,  sizeof(to_be_written));


  
  union operand_types operand1;
  
  // Switch staement would probably be a better idea 
  if (args_from_the_user.op1 == memory) // there can only be one memory operand
    {
      operand1.mem_op = construct_memory_operand(args_from_the_user.op1_mnemonic);
      // Now need to first look for the displacement
      if (operand1.mem_op.disp_length == 0) { } // do nothing mod should be 0

      else if (operand1.mem_op.disp_length == 1)
	to_be_written.modrm |= 0x40; //set bit 6
      
      else if (operand1.mem_op.disp_length == 4)
	to_be_written.modrm |= 0x80; // set bit 7. the most important bit

      else
	fprintf(stderr, "Failure with the calculation of offset. Incorrect value returned or function never called")
	
    }
  else if (args_from_the_user.op1 == sib)
    {
      operand1.sib_op = construct_sib_from_string(args_from_the_user.op1_mnemonic);


      if (operand1.sib_op.disp_length_in_bytes == 0) { }// do nothing

      else if (operand1.sib_op.disp_length_in_bytes == 1)
	to_be_written.modrm |= 0x40;

      else if (operand1.sib_op.disp_length_in_bytes == 4)
	to_be_written.modrm |= 0x80;

      else
	fprintf(stderr, "Failure with the calculation of offset. Incorrect value returned or function never called")
	
	



      
    }
  // make a check for the max size of the immediate to produce the right size of the immediate. it
  // will be the largest size 
  else if (args_from_the_user.op1 == immediate)
    {
      int size_immediate = 0;
      if (table->requirements.allowed_sizes.byte_8)
	{
	  size_immediate = 64; // bits
	  fprintf(stderr, There should not be an immediate of size 64 bits); 
	}
      else if (table->requirements.allowed_sizes.byte_4)
	{
	  size_immediate = 32; // bits
	  to_be_written.immediate = operand1.immediate;
	}
      else if (table->requirements.allowed_sizes.byte_2)
	{
	  size_immediate = 16; // bits
	  to_be_written.immediate = operand1.immediateshort;
	}
      else if (table->requirements.allowed_sizes.one_byte)
	{
	  size_immediate = 8; // bits
	  fprintf(stderr, "Immediates of 8 not supported");
	}

      else
	{
	  fprintf(stderr, "Error with definition from the input file");
	  assert(0 ==1);
	}
      // This will come last 
    }
  else if (args_from_the_user.op1 == reg)
    {
      
    }
  
  
  
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
