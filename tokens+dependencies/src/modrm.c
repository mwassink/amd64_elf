#include <stdio.h>
#include "../include/modrm.h"
#include "../include/char_to_instructions.h"
#include "../include/get_instructions.h"
#include "../include/get_text_tokens.h"
#include <string.h>



struct __instruction encode_registers_rm( char * op1,  char * op2, bool op1_rm)
{
      // The second operand is encoded with the registers
      // The first operand is encoded with the rm
  if (op1[1] == '8' || op1[1] == '9' || op1[1] == '1' ) // these are the r8-r15 registers

}

void table_register_new(struct temprm * temp, char * reg, bool is_first)
{
  // This is for the new reigsters 
  int returned = atoi(reg+1);

  if (is_first)
      temp->first = returned - 8;

  else
    temp->second = returned - 8;
}


unsigned char * encode_rex_none( char * op1,  char * op2, bool op1_rm)
{
  // This will be slow
  struct temprm temp;
  if (op1[0] == 'r' && op1[1] == '8')
    {
      temp.first = 0;
    }
}


void table_register_extension(struct temprm * temp, char * reg, bool is_first)
{
  // With extensions there are usually eight registers all ending with their number
  // So we can easily get the right number by subtracting


  int sum = 0;
  while (reg++ && sum++);

  if (is_first)
    temp->first = reg[sum] + 1;

  else
    temp->second = reg[sum] + 1;
}


void table_high_byte_no_rex(struct temprm * temp, char * reg, bool is_first)
{
  if (reg[0] = 'a')
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

void table_byte_high_rex(struct temprm * temp, char * reg, bool is_first)
{
  int length = 0;
  while (reg++ && length++);

  if (length == 3)
    {
      if (reg[0] == 's')
	{
	  if (is_first)
	    temp->first = 4;
	  else
	    temp->second = 4;
	}
      if (reg[0] == 'b')
	{
	  if (is_first)
	    temp->first = 5;
	  else
	    temp->second = 5;
	}

      if (reg[0] == 's')
	{
	  if (is_first)
	    temp->first = 6;
	  else
	    temp->second = 6;
	}

      if (reg[0] == 'd')
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
      else //b
	{
	  if (is_first)
	    temp->first = 3;
	  else
	    temp->second = 3;
	}
    }

}





