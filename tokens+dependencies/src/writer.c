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
#include "stdbool.h"
#include <assert.h>


// This file will pull some of the other files and write opcodes
// It will also deposit other symbols like functions and files into a different file
typedef struct 
{
  prefixes potential_prefixes; // address override, other register prefixes
  int displacement; // max of 32 bits
  int immediate; // max of 32 bits
  char prefix_OF; 
  unsigned char primary_opcode;
  unsigned char secondary_opcode;
  unsigned char modrm;
  unsigned char sib;

  int immediate_max_size;
  bool end_file;
  bool modrm_dirty;
  bool sib_dirty;
  bool so_dirty;
  bool immediate_dirty;
  /* 0 is valid for: 
     primary_opcode
     secondary_opcode 
     modrm
     sib
     immediate 
   */
  
} potential_writes;


potential_writes write_instruction_opcode_from_line( struct instruction_definition *table, FILE * current_spot, struct symbols_information *symbols_in)
{
  // Make sure that this is not a label first
  potential_writes to_be_written;
  struct instruction_pieces args_from_the_user;
  int error = search_line(current_spot, &args_from_the_user,  symbols_in);

  if (error == 2)
    {

      to_be_written.end_file = 1;
      return to_be_written;
    }
  
  memset((void *)&to_be_written,0 ,  sizeof(to_be_written));
  table += binary_lookup(args_from_the_user.instruction, table, !args_from_the_user.instruction);

  
  union operand_types operand1;
  
  // Switch staement would probably be a better idea 
  if (args_from_the_user.op1 == memory) // there can only be one memory operand
    {
      operand1.mem_op = construct_memory_operand(args_from_the_user.op1_mnemonic);
      // Now need to first look for the displacement
      if (operand1.mem_op.disp_length == 0)  // do nothing mod should be 0
	{
	  to_be_written.modrm |= mod00_table(operand1.mem_op.string);
	  to_be_written.modrm_dirty = 1;
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

      to_be_written.displacement = operand1.mem_op.disp;
      
	
    }
  else if (args_from_the_user.op1 == sib)
    {
      to_be_written.sib_dirty = 1;
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
      to_be_written.displacement = operand1.sib_op.disp_value;
      
    }
  // make a check for the max size of the immediate to produce the right size of the immediate. it
  // will be the largest size 
  
  else if (args_from_the_user.op1 == reg)
    {
      to_be_written.modrm_dirty = 1;
      operand1.reg_string = args_from_the_user.op1_mnemonic;
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
	      to_be_written.modrm |= temp;
	    }
	  else if (needs_rex_r(operand1.reg_string))
	    {
	      temp = mod11_rex(operand1.reg_string);
	      temp <<= 3;
	      to_be_written.modrm |= temp;
	    }
	  else
	    {
	      temp = mod11_r(operand1.reg_string);
	      temp <<= 3;
	      to_be_written.modrm |= temp;
	    }
	  
	}
    }
  else if (args_from_the_user.op1 == xmm)
    {
      to_be_written.modrm_dirty = 1;
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
  union operand_types operand2;
   if (args_from_the_user.op2 == memory) // there can only be one memory operand
    {
      to_be_written.modrm_dirty = 1;
      
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

      to_be_written.displacement = operand2.mem_op.disp;
	
    }


   else if (args_from_the_user.op2 == immediate)
    {
      
      to_be_written.immediate_dirty = 1;
      int size_immediate = 0;
      if (table->requirements.allowed_sizes.byte_8)
	{
	  size_immediate = 64; // bits
	  fprintf(stderr, "There should not be an immediate of size 64 bits"); 
	}
      else if (table->requirements.allowed_sizes.byte_4)
	{
	  
	  to_be_written.immediate = operand2.immediate;
	  to_be_written.immediate_max_size = 32;
	}
      else if (table->requirements.allowed_sizes.byte_2)
	{
	  
	  to_be_written.immediate = operand2.immediateshort;
	  to_be_written.immediate_max_size = 16;
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
      to_be_written.sib_dirty = 1;
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

      to_be_written.displacement = operand2.sib_op.disp_value;
      
    }
  
    else if (args_from_the_user.op2 == reg)
    {
      operand2.reg_string = args_from_the_user.instruction_mnemonic;
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
	      to_be_written.modrm |= temp;
	    }
	  else if (needs_rex_r(operand2.reg_string))
	    {
	      temp = mod11_rex(operand2.reg_string);
	      temp <<= 3;
	      to_be_written.modrm |= temp;
	    }
	  else
	    {
	      temp = mod11_r(operand2.reg_string);
	      temp <<= 3;
	      to_be_written.modrm |= temp;
	    }
	  
	}
    }


   else if (args_from_the_user.op2 == xmm)
    {
      to_be_written.modrm_dirty = 1;
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

   if (table->prefix_OF)
     to_be_written.prefix_OF = table->prefix_OF;
   to_be_written.primary_opcode = table->opcode;
   if (table->secondary_opcode)
     {
       to_be_written.secondary_opcode = table->secondary_opcode;
       to_be_written.so_dirty = 1;
     }

   
   return to_be_written;
   
}




void  writer( char * file_in, struct symbols_information *symbols_in)
{
  printf("Defaulting to .text as section if none given");


  // Construct file pointer to start reading the file 
  FILE * file_pointer = fopen(file_in, "r");
  FILE * read_init = fopen("convert_instructions.bin", "rb");
  

  struct instruction_definition for_size;
  struct instruction_definition *table = malloc(1074 * sizeof(for_size ));

  fread(table, sizeof(for_size), 1074, read_init);
  bool prev = 0;
  while (!prev)
    {
#if debug
      int check = symbols_in->current_instruction_number;
#endif
      potential_writes need_to_write = write_instruction_opcode_from_line(table, file_pointer, symbols_in); // this calls for a specific pointer to a symbols_in
      prev = need_to_write.end_file;
      // Now look for the stuff that I need to change
#if debug
      assert(check != symbols_in->current_instruction_number);
#endif
      // Now I need to get the order of the writing correct. it goes:
      /*
	1. Addressing prefix
	2. Combination of the registers prefix



       */

      
    }
}
