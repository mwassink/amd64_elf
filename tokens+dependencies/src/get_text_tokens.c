

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/get_text_tokens.h"

#define MAX_REGISTER_LETTER_LENGTH 4;

//enumerate valid tokens to assemble
//enumerate valid suffixes to assemble
//at&t syntax first

// %rax, %rbx, %rcx,%rdx %rbp,%rsp,




void init_32_64_bit_old_register_from_string(char * input_string, struct  Register * input_register )
{
  input_register->ID = 0;
  input_register->ID |= input_string[0];
  input_register->ID <<= 4;
  input_register->ID |= input_string[1];
  input_register->ID <<= 4;
  input_register->ID |= input_string[2];

  if (input_string[0] == 'e')
    input_register->size = 0x20;
  if (input_string[0] == 'r')
    input_register->size = 0x40;
}

void init_16_bit_old_register_from_string(char * input_string, struct Register * input_register)
{
  
  input_register->ID = 0;
  input_register->ID |= input_string[0];
  input_register->ID <<= 4;
  input_register->ID |= input_string[1];
  
  input_register->size = 0x10;
}


int  init_new_register_from_string(char * input_string, struct Register * input_register, int register_name_length)
{
  /* This includes one of the new registers that came with the 64 bit instruction set, but it does
   not include the very new ones or features */

  /* This functin will look for different lengths, hence why the function asks for the length of the name */
  

  if (register_name_length == 2)
    {
      /* This means that there is no specification, which means it is asking for the 64 bits */
      input_register->size = 0x40;
      input_register->ID |=input_string[0];
      input_register->ID <<= 4;
      input_register->ID |= input_string[1];
      input_register->ID <<= 4;
      return 0;
    }
  else if (register_name_length == 3)
    {
      switch (input_string[2])
	{
	case 'd':
	  input_register->size = 0x20;
	  break;
	case 'w':
	  input_register->size = 0x10;
	  break;
	case 'b':
	  input_register->size = 0x8;
	  break;
	default:
	  fprintf(stderr, "The suffix of the extension register given (%c) is not supported", input_string[2]);
	  return -1;
	}
      input_register->ID = 0;
      input_register->ID = input_string[0];
      input_register->ID <<= 4;
      input_register->ID |= input_string[1];
      input_register->ID <<= 4;
      input_register->ID |= input_string[2];
      return 0;
    }
  else
    {
      fprintf(stderr, "Size not equal to 2 or 3");  
      return -1;
    }
    
  
}

int initialize_register_ID( char * null_term_reg)
{
  int returned_value = 0;
  returned_value |= null_term_reg[0];
  returned_value <<= 4;
  returned_value |= null_term_reg[1];

  if (!null_term_reg[2])
    return returned_value;

  returned_value <<= 4;
  returned_value |= null_term_reg[2];

  return returned_value;
}

int * init_register_tokens()
{
  const char * strings[] = {"rax", "rbx", "rcx", "rdx", "eax", "ebx", "ecx", "edx",
			    "ax", "bx", "cx", "ah", "bh", "ch", "dh", "al", "bl",
			    "cl", "dl", "dx", "rsp", "esp", "sp", "spl", "rbp"
			    ,"ebp", "bp", "bpl", "cs", "ds", "ss", "es", "fs", "gs",
                            "rsi", "esi", "si", "sil", "rdi", "edi", "di", "dil",
			    "rip", "eip", "ip"}; /* 45 */

  int* ID_array = malloc(180);
  
  for (int i = 0; i < 45; ++i)
    {
     ID_array[i] = initialize_register_ID(strings[i]);
    }

  return ID_array;

}

char * other_strings()
{
  char * string_space = (char *)malloc(300); // Not sure of how many header strings and titles exist for the assembly
}







