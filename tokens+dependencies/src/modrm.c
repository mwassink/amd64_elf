#include <stdio.h>
#include "../include/modrm.h"
#include "../include/get_instructions.h"
#include <string.h>
#include <assert.h>

// NOTE: The file should be preprocessed before to standardize the input registers
// In order for this to be pulled together:

// Need to look for the beginning characters in the string to decide which one is the register or which one is the memory
// If it has parenthesis then it needs a memory operand, and the other one must be a register
// the register functions will be used on the register, and the mod function will be used on the memory 

// Unfortunately this cannot be pulled together without a Sib file to table that 
// That will need to be included at the top of this with a header file
// Also, this corresponding header file  needs to be updated 

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

};



inline bool reg_string_compare (char  * in, char  * in2) // before, just cast the address to one of type int, compiler will know what to do 
{
    int* lhs = (int*)in;
    int* rhs = (int*)in2;
    // Mask the last bit if it is a ), this would mean it would have length 3
    // By masking the last bit, I know that a comparison against a null character will work
    // However, other ones might need this
    if (((*in) & 0x000000FF) == ')')
    {
        *lhs &= 0xFFFFFF00; // Not a big deal if the memory is altered 
        return *lhs = *rhs;
    }
    else
        return *lhs = *rhs;
}

int mod00_table(char* in)
{
    // This is written for cleanliness and consistency
#if debug
    // Need to make sure a percent is being passed in by the other functions
    assert(in[0] == '%');
#endif

    if (in[1] == 'r' && !(in[1] > 47 && in[1] < 58))
    {
        if (reg_string_compare(in, "%rax"))
        {
            return 0;
        }

        else if (reg_string_compare(in, "%rcx"))
        {
            return 1;
        }

        else if (reg_string_compare(in, "%rdx"))
        {
            return 2;
        }

        else if (reg_string_compare(in, "%rbx"))
        {
            return 3;
        }

        else if (reg_string_compare(in, "%rbp"))
        {
            return 5;
        }

        else if (reg_string_compare(in, "%rsi"))
        {
            return 6;
        }

        else if (reg_string_compare(in, "%rdi"))
        {
            return 7;
        }

        else
        {
            fprintf(stderr, "improper usage for the modrm ");
            return -1;
        }

        

    }

    else if (in[1] == 'e')
    {
        if (reg_string_compare(in, "%eax"))
        {
            return 0;
        }

        else if (reg_string_compare(in, "%ecx"))
        {
            return 1;
        }

        else if (reg_string_compare(in, "%edx"))
        {
            return 2;
        }

        else if (reg_string_compare(in, "%ebx"))
        {
            return 3;
        }

        else if (reg_string_compare(in, "%ebp"))
        {
            return 5;
        }

        else if (reg_string_compare(in, "%esi"))
        {
            return 6;
        }

        else if (reg_string_compare(in, "%edi"))
        {
            return 7;
        }

        else
        {
            fprintf(stderr, "improper usage for the modrm ");
            return -1;
        }

    }

    else
    {
        // Must be one of the new registers
        if (reg_string_compare(in, "%r8)"))
        {
            return 0;
        }

        else if (reg_string_compare(in, "%r9)"))
        {
            return 1;
        }

        else if (reg_string_compare(in, "%r10"))
        {
            return 2;
        }

        else if (reg_string_compare(in, "%r11"))
        {
            return 3;
        }

        else if (reg_string_compare(in, "%r14"))
        {
            return 6;
        }

        else if (reg_string_compare(in, "%r15"))
        {
            return 7;
        }

        else
        {
            fprintf(stderr, "Unrecognized register for modrm");
            return -1; // This needs to be checked for
        }

    }
    
}




int mod10_01_table(char* in)
{
    // This is written so I do not have to write if/else branching twice
    // It is also not written in regards to the sib stuff. That is kicked down the road
    if (in[1] == 'r' && !(in[1] > 47 && in[1] < 58 )) // None of the new registers, yet
    {
        if (reg_string_compare(in, "%rax"))
        {
            return 0;
        }

        else if (reg_string_compare(in, "%rcx"))
        {
            return 1;
        }

        else if (reg_string_compare(in, "%rdx"))
        {
            return 2;
        }

        else if (reg_string_compare(in, "%rbx"))
        {
            return 3;
        }

        else if (reg_string_compare(in, "%rbp"))
        {
            return 5;
        }

        else if (reg_string_compare(in, "%rsi"))
        {
            return 6;
        }

        else if (reg_string_compare(in, "%rdi"))
        {
            return 7;
        }

        else
        {
            fprintf(stderr, "Unrecognized register for modrm");
            return -1; // This needs to be checked for
        }
    }

    else if (in[1] == 'e')
    {
        if (reg_string_compare(in, "%eax"))
        {
            return 0;
        }

        else if (reg_string_compare(in, "%ecx"))
        {
            return 1;
        }

        else if (reg_string_compare(in, "%edx"))
        {
            return 2;
        }

        else if (reg_string_compare(in, "%ebx"))
        {
            return 3;
        }

        else if (reg_string_compare(in, "%ebp"))
        {
            return 5;
        }

        else if (reg_string_compare(in, "%esi"))
        {
            return 6;
        }

        else if (reg_string_compare(in, "%edi"))
        {
            return 7;
        }

        else
        {
            fprintf(stderr, "Unrecognized register for modrm");
            return -1; // This needs to be checked for
        }
    }

    else
    {
        //Must be one of the new registers
        if (reg_string_compare(in, "%r8")) // in2 will be null terminated`
        {
            return 0;
        }

        else if (reg_string_compare(in, "%r9")) // in2 will be null terminated
        {
            return 1;
        }

        else if (reg_string_compare(in, "%r10"))
        {
            return 2;
        }

        else if (reg_string_compare(in, "%r11"))
        {
            return 3;
        }

        else if (reg_string_compare(in, "%r13"))
        {
            return 5;
        }

        else if (reg_string_compare(in, "%r14"))
        {
            return 6;
        }

        else if (reg_string_compare(in, "%r15"))
        {
            return 7;
        }

        else
        {
            fprintf(stderr, "Unrecognized register for modrm");
            return -1; // This needs to be checked for
        }
    }


}

int mod11_r(char* in)
{
    // The given prefix is r, so we have %REG

    if (reg_string_compare(in, "%rax"))
    {
        return 0;
    }

    else if (reg_string_compare(in, "%rcx"))
    {
        return 1;
    }
    
    else if (reg_string_compare(in, "%rdx"))
    {
        return 2;
    }

    else if (reg_string_compare(in, "%rbx"))
    {
        return 3;
    }

    else if (reg_string_compare(in, "%rsp"))
    {
        return 4;
    }

    else if (reg_string_compare(in, "%rbp"))
    {
        return 5;
    }

    else if (reg_string_compare(in, "%rsi"))
    {
        return 6;
    }

    else if (reg_string_compare(in, "%rdi"))
    {
        return 7;
    }

    else
    {
        fprintf(stderr, "Improper usage for the mod11_r");
        return -1;
    }

    

}
int mod11_e(char* in)
{
    if (reg_string_compare(in, "%eax"))
    {
        return 0;
    }

    else if (reg_string_compare(in, "%ecx"))
    {
        return 1;
    }

    else if (reg_string_compare(in, "%edx"))
    {
        return 2;
    }

    else if (reg_string_compare(in, "%ebx"))
    {
        return 3;
    }

    else if (reg_string_compare(in, "%esp"))
    {
        return 4;
    }

    else if (reg_string_compare(in, "%ebp"))
    {
        return 5;
    }

    else if (reg_string_compare(in, "%esi"))
    {
        return 6;
    }

    else if (reg_string_compare(in, "%edi"))
    {
        return 7;
    }

    else
    {
        fprintf(stderr, "Improper usage for the mod11_e");
        return -1;
    }



}
int mod11_st(char* in)
{
    // There are just 8 registers for this st0 - st7
    return in[3] - 48;
}

int mod11_mm(char* in)
{
    return in[3] - 48;
}

int mod11_xmm(char* in)
{
    int disp_offset = 0;

    while (in[disp_offset] != ')' && disp_offset++);
    in[disp_offset] = 0;

    int num_label = atoi(in + disp_offset);

    return num_label % 8;
}

int mod11_rex(char* in)
{
    // This one requires one of the newer registers (extensions)
    // r8, r9, r10, etc
    // Move to the front of the word with the )

    int disp = 0;
    while (in[disp++] != ')'); // will overshoot by one
    disp--;
    in[disp] = 0; // Now everything after the number will be null terminated
    return atoi(++in); // Hopefully this will be passed in with the percent sign coming first
    
}

int mod11_others(char* in)
{
    // This function will be used for the registers without easy to look for prefixes 
    // May be useful for high, low, etc,
    // 5 categories  x, l, h, p, i
    // Expected usage: %ax
    
    switch (in[2])
    {
    case 'l': // Low register
        if (in[1] == 'a')
            return 0;
        else if (in[1] == 'c')
            return 1;
        else if (in[1] == 'd')
            return 2;
        else if (in[1] == 'b')
            return 3;
        else
        {
            fprintf(stderr, "Improper usage of the mod11_others function, looking for a low byte");
        }
        break;
    case 'x': // General purpose register, looking to use 2 bytes 
        if (in[1] == 'a')
            return 0;
        else if (in[1] == 'c')
            return 1;
        else if (in[1] == 'd')
            return 2;
        else if (in[1] == 'b')
            return 3;
        else
        {
            fprintf(stderr, "Improper usage of the mod11_others function, looking for a general register");
        }
        break;
    case 'h': // Looking for the high byte
        if (in[1] == 'a')
            return 4;
        else if (in[1] == 'c')
            return 5;
        else if (in[1] == 'd')
            return 6;
        else if (in[1] == 'b')
            return 7;
        else
        {
            fprintf(stderr, "Improper usage of the mod11_others function, looking for a high byte");
        }
        break;
    case 'p': // For one of the pointers 
        if (in[1] == 's')
            return 4;
        else if (in[1] == 'b')
            return 5;
        else
        {
            fprintf(stderr, "Improper usage of the mod11_others function, looking for a base or stack ptr");
        }

    case 'i':
        if (in[1] == 's')
            return 6;
        else if (in[1] == 'd')
            return 7;
        else
        {
            fprintf(stderr, "Improper usage for the mod11_others, looking for destination index");
        }
    }

}


int mod11_table(char* in)   
{
    // The first thing to look for  is prefixes after the percent sign:
    // e, r, st, mm, xmm, r(extension)

    // in example %rax the second character will be the prefix or the lack of the prefix
    
    switch (in[1])
    {
    case 'e':
        return mod11_e(in);
    case 'm':
        return mod11_mm(in);
    case 'r': // Not as easy as the other ones
        if (needs_rex_r(in))
        {
            return mod11_rex(in);
        }
        else
        {
            return mod11_r(in);
        }
    case 's':
        return mod11_st(in);
    case 'x':
        return mod11_xmm(in);
    default:
        return mod11_others(in);
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
  return (reg[2] > 47 && reg[2] < 58);
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
    // This function needs to figure out which register is being passed in and then based on that assign 3 bits to the temp
    // Oddly enough, the IP gets this 00 mod
#if debug
    if (reg[0] == '0' && reg[1] == 'x')
    {
        int disp_debug = 0;
        while (reg[disp_debug] != '(' && disp_debug++);
        disp_debug++; // Move forward to the percent sign
        assert(reg_string_compare(reg + disp_debug, "%rip"));
    }
#endif
    
   
}


void table_rm_mod01(struct temprm* temp, char* reg, bool is_first, bool rex_r)
{
    // It is assumed that this has a 1 byte offset or "displacement" will be asserted
    // If there is complex memory addressing, then a separate SIB function will be called
    int disp_length = 0;

#if debug
    assert(reg[0] == '0' && reg[1] == 'x');
    assert(reg[2] != '('); // Make sure this is being called correctly
#endif

    while (reg[disp_length] != '(' && disp_length++);

    disp_length++; // This is moved past the parentheses

    int mod = mod10_01_table(reg + disp_length);

#if debug
    assert(mod != -1);
#endif

    if (is_first)
    {
        temp->first = mod;
    }

    else
    {
        temp->second = mod;
    }
}


void table_rm_mod10(struct temprm * temp, char * reg, bool is_first)
{
  
  // For all of these they should have a 4 byte offset that is an immediate. If they can be expressed as one byte
  // then what's the point?
  // This should be called when there is a > 1 byte offset for the memory addressing
  // If there is complex memory addressing, then a separate SIB function will be called

  int disp_length = 0;

#if debug
  assert(reg[0] == '0' && reg[1] == 'x');
  assert(reg[2] != '(' && reg[3] != '('); // Make sure this is being called correctly
#endif
  while ((reg[disp_length] != '(' ) && disp_length++);
  // Disp length is now at the first parenthesis. Needs to be moved past it
  disp_length++;
  // Now disp_length is at the right spot
  // The string compare function I made will be especially useful because the registers all have <= 3 length
  // Now I need to call the function from above on this

  int mod = mod10_01_table(reg + disp_length);

#if debug
  assert(mod != -1); // Make sure the initial check succeeded
#endif 


  if (is_first)
  {
      temp->first = mod;
  }

  else
  {
      temp->second = mod;
  }
  
  

  
}









