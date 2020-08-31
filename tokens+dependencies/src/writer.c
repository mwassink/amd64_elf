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

  int proper_index = 0;

  memset((void *)&to_be_written,0 ,  sizeof(to_be_written));


  
  union operand_types operand1;
  
  // Switch staement would probably be a better idea 
  if (args_from_the_user.op1 == memory) // there can only be one memory operand
    {
      operand1.mem_op = construct_memory_operand(args_from_the_user.op1_mnemonic);
      // Now need to first look for the displacement
      if (operand1.mem_op.disp_length == 0)  // do nothing mod should be 0
	{
	  to_be_written.modrm |= mod00_table(operand1.mem_op.string);
	}


	
      else if (operand1.mem_op.disp_length == 1)
	{
	  to_be_written.modrm |= 0x40; //set bit 6
	  to_be_written.modrm |= mod10_01_table(operand1.mem_op.string);
	}
      else if (operand1.mem_op.disp_length == 4)
	{
	  to_be_written.modrm |= 0x80; // set bit 7. the most important bit
	  to_be_written.modrm |= mod10_01_table(operand1.mem_op.string);
	}
      else
	fprintf(stderr, "Failure with the calculation of offset. Incorrect value returned or function never called");

      
	
    }
  else if (args_from_the_user.op1 == sib)
    {
      operand1.sib_op = construct_sib_from_string(args_from_the_user.op1_mnemonic);


      if (operand1.sib_op.disp_length_in_bytes == 0)
	{
	  to_be_written.modrm |= 4;
	}

      else if (operand1.sib_op.disp_length_in_bytes == 1)
	{
	  to_be_written.modrm |= 0x40;
	  to_be_written.modrm |= 4;
	}
      else if (operand1.sib_op.disp_length_in_bytes == 4)
	{
	  to_be_written.modrm |= 0x80;
	  to_be_written.modrm |= 4;
	}
      else
	fprintf(stderr, "Failure with the calculation of offset. Incorrect value returned or function never called");
	
      to_be_written.sib = make_sib_byte(operand1.sib_op);
      
    }
  // make a check for the max size of the immediate to produce the right size of the immediate. it
  // will be the largest size 
  
  else if (args_from_the_user.op1 == reg)
    {
      if (table->requirements.one == mem_or_reg)
	{
	  if (operand1.reg_string[1] == 'e')
	    {
	      to_be_written.modrm |=  mod11_e(operand1.reg_string);
	    }
	  else if (needs_rex_r(operand1.reg_string))
	    {
	      to_be_written.modrm |= mod11_rex(operand1.reg_string);
	    }
	  else
	    {
	      to_be_written.modrm |= mod11_r(operand1.reg_string);
	    }
	}
      else
	{
	  int temp = 0;
	  if (operand1.reg_string[1] == 'e')
	    {
	      temp =  mod11_e(operand1.reg_string);
	      temp <<= 3;
	      to_be_written |= temp;
	    }
	  else if (needs_rex_r(operand1.reg_string))
	    {
	      temp = mod11_rex(operand1.reg_string);
	      temp <<= 3;
	      to_be_written |= temp;
	    }
	  else
	    {
	      temp = mod11_r(operand1.reg_string);
	      temp <<= 3;
	      to_be_written |= temp;
	    }
	  
	}
    }
  else if (args_from_the_user.one == xmm)
    {
      if (table->requirements.one == xmm_or_mem)
	{
	  // secondary priority
	  to_be_written.modrm |= mod11_xmm(operand1.reg_string);
	}
      else
	{
	  int temp = mod11_xmm(operand1.reg_string); temp <<= 3;
	  to_be_written.modrm |= temp;
	}
    }
  ///////////////////////////////////////////////
  //OP2/////////////////////////////////////////
  //////////////////////////////////////////////
  union operand2;
   if (args_from_the_user.op2 == memory) // there can only be one memory operand
    {
      operand2.mem_op = construct_memory_operand(args_from_the_user.op2_mnemonic);
      // Now need to first look for the displacement
      if (operand2.mem_op.disp_length == 0)  // do nothing mod should be 0
	{
	  to_be_written.modrm |= mod00_table(operand2.mem_op.string);
	}


	
      else if (operand2.mem_op.disp_length == 1)
	{
	  to_be_written.modrm |= 0x40; //set bit 6
	  to_be_written.modrm |= mod10_01_table(operand2.mem_op.string);
	}
      else if (operand1.mem_op.disp_length == 4)
	{
	  to_be_written.modrm |= 0x80; // set bit 7. the most important bit
	  to_be_written.modrm |= mod10_01_table(operand2.mem_op.string);
	}
      else
	fprintf(stderr, "Failure with the calculation of offset. Incorrect value returned or function never called");

      
	
    }


   else if (args_from_the_user.op2 == immediate)
    {
      int size_immediate = 0;
      if (table->requirements.allowed_sizes.byte_8)
	{
	  size_immediate = 64; // bits
	  fprintf(stderr, "There should not be an immediate of size 64 bits"); 
	}
      else if (table->requirements.allowed_sizes.byte_4)
	{
	  size_immediate = 32; // bits
	  to_be_written.immediate = operand2.immediate;
	}
      else if (table->requirements.allowed_sizes.byte_2)
	{
	  size_immediate = 16; // bits
	  to_be_written.immediate = operand2.immediateshort;
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

   
   else if (args_from_the_user.op2 == sib)
    {
      operand2.sib_op = construct_sib_from_string(args_from_the_user.op2_mnemonic);


      if (operand2.sib_op.disp_length_in_bytes == 0)
	{
	  to_be_written.modrm |= 4;
	}

      else if (operand2.sib_op.disp_length_in_bytes == 1)
	{
	  to_be_written.modrm |= 0x40;
	  to_be_written.modrm |= 4;
	}
      else if (operand2.sib_op.disp_length_in_bytes == 4)
	{
	  to_be_written.modrm |= 0x80;
	  to_be_written.modrm |= 4;
	}
      else
	fprintf(stderr, "Failure with the calculation of offset. Incorrect value returned or function never called");
	
      to_be_written.sib = make_sib_byte(operand2.sib_op);
      
    }
  
    else if (args_from_the_user.op2 == reg)
    {
      if (table->requirements.two == mem_or_reg)
	{
	  if (operand2.reg_string[1] == 'e')
	    {
	      to_be_written.modrm |=  mod11_e(operand2.reg_string);
	    }
	  else if (needs_rex_r(operand2.reg_string))
	    {
	      to_be_written.modrm |= mod11_rex(operand2.reg_string);
	    }
	  else
	    {
	      to_be_written.modrm |= mod11_r(operand2.reg_string);
	    }
	}
      else
	{
	  int temp = 0;
	  if (operand2.reg_string[1] == 'e')
	    {
	      temp = mod11_e(operand2.reg_string);
	      temp <<= 3;
	      to_be_written |= temp;
	    }
	  else if (needs_rex_r(operand2.reg_string))
	    {
	      temp = mod11_rex(operand2.reg_string);
	      temp <<= 3;
	      to_be_written |= temp;
	    }
	  else
	    {
	      temp = mod11_r(operand2.reg_string);
	      temp <<= 3;
	      to_be_written |= temp;
	    }
	  
	}
    }


   else if (args_from_the_user.two == xmm)
    {
      if (table->requirements.two == xmm_or_mem)
	{
	  // secondary priority
	  to_be_written.modrm |= mod11_xmm(operand2.reg_string);
	}
      else
	{
	  int temp = mod11_xmm(operand2.reg_string); temp <<= 3;
	  to_be_written.modrm |= temp;
	}
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
