#include <stdio.h>
#include "../include/modrm.h"
#include "../include/char_to_instructions.h"
#include "../include/get_instructions.h"
#include "../include/get_text_tokens.h"
#include <string.h>
#include <assert.h>

// NOTE: The file should be preprocessed before to standardize the inpu t registers, too bad fileio is slow

int ascii_to_int_hex(char * input)
{
  int returned = 0;
  int i = 0;
  while (input)
    {
      returned |= (input[i] - 48);
      returned <<= 4;
    }

  return returned;
}


struct __instruction encode_registers_rm( char * op1,  char * op2, bool op1_rm)
{
      // The second operand is encoded with the registers
      // The first operand is encoded with the rm
  fprintf(stderr, "Function is not complete yet");

}

void reg_table_register_new(struct temprm * temp, char * reg, bool is_first)
{
  // This is for the new reigsters 
  int returned = atoi(reg+1);
  if (is_first)
    temp->first = returned - 8;

  else
    temp->second = returned - 8;

  
  
}


int ret_mod(char * input)
{
  if (input[0] == '0' && input[1] == 'x' ) // This will be some sort of offset
    {
      if ((input[3] == 'r' || input[3] == 'e') && input[4] == 'i' && input[5] == 'p')
	return 0;

      int length_disp = 0;
      while(input[length_disp++] != '(');

      if (--length_disp <= 4) //0xXX disp 8
	{
	  return 1;
	}
      return 2;
    }

  if (*input == '(')
    {
      return 0;
    }

  // We have already decided that there is no offset and there is no immediate addressing, must be a register
  return 3;
  
}

inline bool needs_rex_r(char * reg)
{
  return (reg[1] > 47 && reg[1] < 58);
}


void reg_table_register_extension(struct temprm * temp, char * reg, bool is_first, bool rex_r)
{
  // With extensions there are usually eight registers all ending with their number
  // So we can easily get the right number by subtracting


  int sum = 0;
  while (*reg++ && sum++);

  if (is_first && !rex_r)
    temp->first = atoi(reg+sum);

  else if (is_first && rex_r)
    temp->first = atoi(reg+sum) - 8;

  else if (!is_first && !rex_r)
    temp->second = atoi(reg+sum);

  
  else
    temp->second = atoi(reg+sum) - 8;
}


void reg_table_byte_no_rex(struct temprm * temp, char * reg, bool is_first)
{
  if (reg[0] == 'a')
    {
      if (reg[1] == 'l')
	{
	  if (is_first)
	    temp->first = 0;
	  else
	    temp->second = 0;
	}
      else 
	{
	  if (is_first)
	    temp->first = 4;
	  else
	    temp->second = 4;
	}
    }

  if (reg[0] == 'c')
    {
      if (reg[1] == 'l')
	{
	  if (is_first)
	    temp->first = 1;
	  else
	    temp->second = 1;
	}
      else
	{
	  if (is_first)
	    temp->first = 5;
	  else
	    temp->second = 5;
	}
    }

  if (reg[0] == 'd')
    {
      if (reg[1] == 'l')
	{
	  if (is_first)
	    temp->first = 2;
	  else
	    temp->second = 2;
	}
      else
	{
	  if (is_first)
	    temp->first = 6;
	  else
	    temp->second = 6;
	}
    }

  else
    {
      if (reg[1] == 'l')
	{
	  if (is_first)
	    temp->first = 3;
	  else
	    temp->second = 3;
	}
      else
	{
	  if (is_first)
	    temp->first = 7;
	  else
	    temp->second = 7;
	  
	}
    }
}

void reg_table_byte_rex(struct temprm * temp, char * reg, bool is_first)
{
  int length = 0;
  while (*reg++ && length++);

  if (length == 3)
    {
      if (reg[0] == 's' && reg[2] == 'l')
	{
	  if (is_first)
	    temp->first = 4;
	  else
	    temp->second = 4;
	}
      if (reg[0] == 'b'  && reg[2] == 'l')
	{
	  if (is_first)
	    temp->first = 5;
	  else
	    temp->second = 5;
	}

      if (reg[0] == 's'  && reg[2] == 'l')
	{
	  if (is_first)
	    temp->first = 6;
	  else
	    temp->second = 6;
	}

      if (reg[0] == 'd'  && reg[2] == 'l')
	{
	  if (is_first)
	    temp->first = 7;
	  else
	    temp->second = 7;
	}
      
    }

  else
    {
      if (reg[0] == 'a')
	{
	  if (is_first)
	    temp->first = 0;
	  else
	    temp->second = 0;
	}
      if (reg[0] == 'c')
	{
	  if (is_first)
	    temp->first = 1;
	  else
	    temp->second  = 1;
	}
      if (reg[0] == 'd')
	{
	  if (is_first)
	    temp->first = 2;
	  else
	    temp->second = 2;	  
	}
      if (reg[0] == 'b')
	{
	  if (is_first)
	    temp->first = 3;
	  else
	    temp->second = 3;
	}

      else
	fprintf(stderr, "The given arguments cannot be assembled");
    }

}

void table_segment_register(struct temprm * temp, char * reg, bool is_first)
{
  switch (reg[0])
    {
    case 'E':
      if (is_first)
	temp->first = 0;
      else
	temp->second = 0;
      break;
    case 'C':
      if (is_first)
	temp->first = 1;
      else
	temp->second = 1;
      break;
    case 'S':
      if (is_first)
	temp->first = 2;
      else
	temp->second = 2;
      break;
    
    case 'D':
      if (is_first)
	temp->first = 3;
      else
	temp->second = 3;
      break;
    case 'F':
      if (is_first)
	temp->first = 4;
      else
	temp->second = 4;
      break;
    case 'G':
      if (is_first)
	temp->first = 5;
      else
	temp->second = 5;
    default:
      fprintf(stderr, "No segment register for the given argument");
      
    }
}

void table_rm_mod00(struct temprm *temp, char * reg, bool is_first, bool rex_r) // Essentially this just means we have a rip pointer or no displacement
{
  // r/e ax, cx, bx, dx, ip, si, di
  // This will be called when there is no disp8 or disp32, so
  // The MOD specifies these options


  // 00 refers to register indirect addressing or SIB with no displacement or displacement only addressing mode
  // 01 refers to a 1-byte signed displacemnt following the addressing mode, so it knows that it coming e.g 0xAA
  // 10 refers to a four-byte signed displacement follows the addressing mode bytes e.g 0xFFFFAAAA
  // 11 Register addressing mode
  // If I needed to encode an instruction with an offset but no fancy math, then I would use one of these
  // e.g movq -0x12(%rax), %rbx. This would specify that there needs to be a disp8 byte, but no fancy addressing is needed
  // So we just need the modrm
  // 00 is a memory addressing operand, like 01 and 10


  //nonethreless  is is a memory addressing operand, so it will not take a register by itself
  // if a modrm uses a register it will just take 11 instead

  if (reg[0] != '('   && (reg[0] != '0' || reg[1] != 'x') ) // Not a number or the indexing parenthesis
    {
      fprintf(stderr, "The table_rm_mod00 was used improperly, proper usage requires a memory operand with no offset or an instruction pointer");
      return;
    }
  #if debug
  if (reg[0] == '0' && reg[1] == 'x')
    {

      int first_parentheses = 0;
      while (reg[first_parentheses++] != '('  );
      
      if (!((reg[first_parentheses] == 'r' || reg[first_parentheses] == 'e') && reg[first_parentheses+1] == 'i' && reg[first_parentheses + 2] == 'p'))
	{
	  fprintf(stderr, "The modrm 00 function cannot be used with an offset unless that offset is a RIP pointer");
	  return;
	}	
    }
  #endif
  if (reg[0] == '0' && reg[1] == 'x')
    {
      // This means that the register is the instructgion ptr, no exceptions
      if (is_first)
	temp->first = 5;
      else
	temp->second = 5;

      return;
    }

  if (rex_r)
    {
      // TODO
      
      
    }



  else
    {
      // TODO 
    }
}









