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



void modrm_rex_r_switch (struct temprm *temp, char *reg_at_offset, bool is_first)
{

  switch (reg_at_offset[0])
    {
    case '8':
      if (is_first)
	temp->first = 0;
      else
	temp->second = 0;
      break;
    case '9':
      if (is_first)
	temp->first = 1;
      else
	temp->second = 1;
      break;
    case '1':
      switch (reg_at_offset[1])
	{
	case '0':
	  if (is_first)
	    temp->first = 2;
	  else
	    temp->second = 2;
	  break;
	case '1':
	  if (is_first)
	    temp->first = 3;
	  else
	    temp->second = 3;
	  break;
	case '4':
	  if (is_first)
	    temp->first = 6;
	  else
	    temp->second = 6;
	  break;
	case '5':
	  if (is_first)
	    temp->first = 7;
	  else
	    temp->second = 7;
	  break;
	}
      break;
	    
  }
  
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
    case 'e':
      if (is_first)
	temp->first = 0;
      else
	temp->second = 0;
      break;
    case 'c':
      if (is_first)
	temp->first = 1;
      else
	temp->second = 1;
      break;
    case 's':
      if (is_first)
	temp->first = 2;
      else
	temp->second = 2;
      break;
    
    case 'd':
      if (is_first)
	temp->first = 3;
      else
	temp->second = 3;
      break;
    case 'f':
      if (is_first)
	temp->first = 4;
      else
	temp->second = 4;
      break;
    case 'g':
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


  // Example instruction movq (%rax), (%rbx) <------ (%rbx or ebx will be given to the function) looking for the bx part 

  
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
      // Look for the third character which will be the register chosen
      modrm_rex_r_switch(temp,  reg + 2, is_first);
    }



  else
    {
      // The thing we are looking for is the third character in the register input
      switch (reg[2])
	{
	case 'a':
	  if (is_first)
	    temp->first = 0;
	  else
	    temp->second = 0;
	  break;
	case 'c':
	  if (is_first)
	    temp->first = 1;
	  else
	    temp->second = 1;
	  break;
	case 'd':
	  if (is_first && reg[3] == 'x')
	    temp->first = 2;
	  else if (is_first && reg[3] == 'i')
	    temp->first = 7;
	  else if (!is_first && reg[3] == 'x')
	    temp->second = 2;
	  else
	    temp->second = 7;
	  break;
	case  'b':
	  if (is_first)
	    temp->first = 3;
	  else
	    temp->second = 3;
	case 's':
	  if (is_first)
	    temp->first = 6;
	  else
	    temp->second = 6;
	  break;
	  
	      
	    
	}
    }
}


void table_rm_mod01(struct temprm *temp, char * reg, bool is_first, bool rex_r)
{
  // The first thing we want to look for is the 8 bit displacement, which will be processed into hexadecimal. This is useful because I do
  // not want to go looking for a valid range for this. I know that the first characters will be a 0x




  // EXAMPLE INSTRUCTION:     movq 0x32(%rax), %rbx
  assert(reg[0] == '0' && reg[1] == 'x');

  int number_disp_length = 0;

  while (reg[number_disp_length] != '(' && number_disp_length++);

  number_disp_length += 2; // Now it should have the proper offset to begin looking at the second character of the register
  // (i.e not including the prefix ), but we do not care about this part for now


  if (rex_r)
    {
      modrm_rex_r_switch(temp, reg + number_disp_length, is_first);
      
    }
  



  else
    {
      // for this we need to look at all the options and table them

      switch (reg[number_disp_length])
	{
	case 'a':
	  if (is_first)
	    temp->first = 0;
	  else
	    temp->second = 0;
	  break;
	case 'c':
	  if (is_first)
	    temp->first = 1;
	  else
	    temp->second = 1;
	  break;
	case 'd':
	  if (is_first && reg[number_disp_length + 1] == 'i')
	    temp->first = 7;
	  else if (!is_first && reg[number_disp_length + 1] == 'i')
	    temp->second = 7;
	  else if (is_first && reg[number_disp_length + 1] == 'x')
	    temp->first = 2;
	  else
	    temp->second = 2;
	  break;
	case 'b':
	  if (is_first)
	    temp->first = 3;
	  else
	    temp->second = 3;
	  break;
	case 'i':
	  if (is_first)
	    temp->first = 5;
	  else
	    temp->second = 5;
	  break;
	case 's':
	  if (is_first)
	    temp->first = 6;
	  else
	    temp->second = 6;
	  break;
	}
	    
	    



      
    }
}


void table_rm_mod10(struct temprm * temp, char * reg, bool is_first)
{
  // For all of these they should have a 4 byte offset that is an immediate. If they can be expressed as one byte
  // then what's the point?

  int disp_length = 0;

  while ((reg[disp_length] != '(' ) && disp_length);
  // Disp length is now at the first parenthesis. Needs to be moved past it and the percent
  disp_length += 2;

  
  

  
}









