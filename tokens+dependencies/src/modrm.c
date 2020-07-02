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



void reg_table_register_extension(struct temprm * temp, char * reg, bool is_first, bool rex_r)
{
  // With extensions there are usually eight registers all ending with their number
  // So we can easily get the right number by subtracting


  int sum = 0;
  while (reg++ && sum++);

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
  while (reg++ && length++);

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
      if (reg[d] == 'b')
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





