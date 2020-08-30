#include "../include/utilities.h"
#include "../include/customtypes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>





bool needs_rex_r(const char *input)
{
  return (input[2] > 47 && input[2] < 58);
}

int move_to_endline(const char * input_string, int start_iterator)
{
  for (; input_string[start_iterator] != '\n'; ++start_iterator);
  return start_iterator;
}

int move_to_space (const char * input_string, int start_iterator)
{
  for (; input_string[start_iterator] != ' ' && input_string[start_iterator] != '\n'; ++start_iterator);

  if (input_string[start_iterator] == '\n')
    {
      fprintf(stderr, "Issue reading the input string. An endline was reached prematurely");
      assert(0 == 1);
    }
  else
    {
      return start_iterator;
    }
}


void byte_from_sib_part(const char * in, prefixes *prefix)
{
  // First look for the first register
  // if the 32 bit registers are used for the sib, then 67 will prefix the whole instruction
  // W not needed because SIB is only used for the addressing and not the register size
  
  
  
  
  int start_iterator = 0;
  start_iterator = move_to_general(in,  start_iterator, '%'); start_iterator++; // Now in the right spot for the BASE
  if (in[start_iterator] == 'e')
    {
      prefix->addressing_67_prefix = 0x67;
    }
  else if (needs_rex_r(in + start_iterator))
    {
      prefix->flags |= 0x41; // for the prefix
    }
  start_iterator = move_to_general(in, start_iterator, '%'); // this will follow the size of the other. This is now the size of the index
  if (needs_rex_r(in+ start_iterator))
    {
      prefix->flags |= 0x42; // for the index of this
    }

  
}






int move_to_general(const char * input_string, int start_iterator, char general_char)
{
  for (; input_string[start_iterator] != general_char; ++start_iterator);
  return start_iterator;
}

int move_while_general(const char * input_string, int start_iterator , char general_char)
{
  for (; input_string[start_iterator] == general_char; ++start_iterator);
  return start_iterator;
}


bool compare_strings(char * lhs, const char * rhs)
{
  int max_length = 20;
  int iterator = 0;
  for (; iterator <= max_length; ++iterator)
    {
      if (lhs[iterator] != rhs[iterator])
	{
	  return false;
	}
      if (lhs[iterator] == 0 && rhs[iterator] == 0)
	{
	  return true;
	}
	    
    }

  if (iterator == 21)
    {
      return false;
    }
  
  return true;
    
}




void example_print_value_binary()
{
  // A shift left will shift left inside the register, so it will always become more signifant
  printf("Example unsigned long long int: %d \n", 3);
  unsigned long long int number = 3;
  int shift_length = sizeof(number)*8;
  printf("The length of the shift is %d: \n", shift_length);
  unsigned long long int shifter = 1;
  unsigned int bits = 0;
  //printf("The value of shifter to the left is: %lx  \n", 1<<63);
  for (shifter = (shifter  << (shift_length -  1)) ; shifter > 0; shifter = shifter>>1 )
    {

      (number & shifter)? printf("1"): printf("0");
      bits++;
    }
  printf("\n");
  printf("The number of bits in the long long int is %d \n", bits);


  printf("Example signed int -5: \n");
  signed int neg_five = -5;
  shifter = 1;
  bits = 0;
  for (shifter = shifter<<(sizeof(neg_five)*8-1); shifter != 0; shifter >>= 1)
  {
    (neg_five & shifter)? printf("1"): printf("0");
  }

}

void print_binary(unsigned long int input_number)
{
  printf("The number %lX in binary is: \n", input_number);

  unsigned long int shift = 1; // Should have a size of 64 bits
  int shift_size = sizeof(input_number) * 8;
  for (shift <<= shift_size; shift != 0; shift>>=1)
    (input_number & shift)? printf("1"): printf("0");
}

long unsigned int  name_to_id( char * mnemonic)
{
  // Assumes tghat the mnemonic is null terminated and that it is no bigger than 8 bytes
  int length = 0;
  for (; mnemonic[length] != 0 && length <= 16; ++length);
  
  if (length > 8)
    return 0;
  else
    {
      long unsigned int *ptr = (long unsigned int *)(mnemonic);
      return *ptr;
    }
}



int * possible_sizes(char * available_operands_in)
{
  int * sizes = malloc(4 * sizeof(int));
  memset(sizes, 0, 4*sizeof(int));
  char one[5] = {0}; char two[5] = {0}; char three[5] = {0};
  char four[5] = {0}; 
  //Start when the character is an ascii character
  int i = 0; int one_length = 0; int two_length = 0; int three_length = 0; int four_length = 0; 

  
  for (; available_operands_in[i] < 48 && available_operands_in[i] > 57; ++i) // Jump to number
    {
      if (available_operands_in[i] == 0)
	{
	  return sizes;
	}
    }  
  for (; available_operands_in[i] >= 48 && available_operands_in[i] <= 57; ++i )
    {
      one[one_length++] = available_operands_in[i];
    }

  
   for (; available_operands_in[i] < 48 && available_operands_in[i] > 57; ++i) // Jump to number
    {
      if (available_operands_in[i] == 0)
	{
	  return sizes;
	}
    }
   for (; available_operands_in[i] >= 48 && available_operands_in[i] <= 57; ++i )
    {
      two[two_length++] = available_operands_in[i];
    }


   for (; available_operands_in[i] < 48 && available_operands_in[i] > 57; ++i) // Jump to number
    {
      if (available_operands_in[i] == 0)
	{
	  return sizes;
	}
    }
   for (; available_operands_in[i] >= 48 && available_operands_in[i] <= 57; ++i )
    {
      three[three_length++] = available_operands_in[i];
    }


   for (; available_operands_in[i] < 48 && available_operands_in[i] > 57; ++i) // Jump to number
    {
      if (available_operands_in[i] == 0)
	{
	  return sizes;
	}
    }
   for (; available_operands_in[i] >= 48 && available_operands_in[i] <= 57; ++i )
    {
      four[four_length++] = available_operands_in[i];
    }

   sizes[0] = atoi(one); sizes[1] = atoi(two); sizes[2] = atoi(three); sizes[3] = atoi(four);
						
   
  return sizes;
}


void switch_on_possible_sizes(int in, struct available_sizes *sizes_in)
{
  switch(in)
    {
    case 0:
      return;
    case 8:
      sizes_in->one_byte = true;
      return;
    case 16:
      sizes_in->byte_2 = true;
      return;
    case 32:
      sizes_in->byte_4 = true;
      return;
    case 64:
      sizes_in->byte_8 = true;
      return;
    case 128:
      sizes_in->byte_16 = true;
      return;
    }
}



void fill_possible_sizes(struct available_sizes *sizes_in, char * instruction_in)
{
  
  sizes_in->one_byte = 0; sizes_in->byte_high = 0; sizes_in->byte_16 = 0;
  sizes_in->byte_2 = 0; sizes_in->byte_4 = 0; sizes_in->byte_8 = 0;

  int * array = possible_sizes(instruction_in);
  
  for (int i = 0; i < 4; ++i)
    {
      switch_on_possible_sizes(array[i], sizes_in);
    }

  
  
}



bool check_for_segment_register(char *reg)
{
  // Compilers like to use the stack registers
  short int* ptr = (short int*)reg;
  if (sizeof (*ptr) == 2)
    {
      // es cs ss ds fs gs 0x65 0x63 0x73 0x64 0x66 0x67
      switch (*ptr)
        {
        case 0x6573:
          return true;
        case 0x6373:
          return true;
        case 0x7373:
          return true;
        case 0x6473:
          return true;
        case 0x6673:
          return true;
        case 0x6773:
          return true;
        default:
          return false;
        }
    }

  else
    {
      char arr[4];
      arr[0] = reg[0]; arr[1] = reg[1];
      arr[2] = 0; arr[3] = 0;
      int *ptr = (int *)reg;
      switch (*ptr)
        {
        case 0x65730000:
          return true;
        case 0x63730000:
          return true;
        case 0x73730000:
          return true;
        case 0x64730000:
          return true;
        case 0x66730000:
          return true;
        case 0x67730000:
          return true;
        default:
          return false;
        }


    }

}


enum Basic_Operands type_fallback(const char * in)
{
  char type[6] = {0};
  int iterator = 0;



  if (in[0] == 0) {
    return none;
  }



    
  while (in[iterator] != 0 && (in[iterator] > 57 && in[iterator] < 48)) // not a number or a zero
    {
      type[iterator] = in[iterator];
    }

  if (compare_strings(type, "m"))
    {
      return memory;
      
    }
  
  else if (compare_strings(type, "r/m"))
    {
      return mem_or_reg;
    }

  else if (compare_strings(type, "imm"))
    {
      return immediate;
    }

  else if (compare_strings(type, "r"))
    {
      return reg;
    }

  else if (compare_strings(type, "moffs"))
    {
      return memory_offset;
    }

  else if (compare_strings(type, "xmm"))
    {
      return xmm;
    }

  else if (compare_strings(type, "xmm/m"))
    {
      return xmm_or_mem;
    }

  else if (check_for_segment_register(type))
    {
      return segment;
    }

  // Already checked for the stack register
  else if (compare_strings(type, "eFlags"))
    {
      return eflags;
    }

  else if(compare_strings(type, "rel"))
    {
      return rel;
    }

  else
    {
      return not_found;
    }
    
  
}

enum Basic_Operands operand_type_return(char *in)
{
  // Read until a size, a slash or a 0
   if (compare_strings(in, "imm8"))
    {
      return immediate;
    }

  else if (compare_strings(in, "imm16/32"))
    {
      return immediate;
    }

   else if (compare_strings(in, "imm16/32/64"))
    {

      return  immediate;
    }


   else if (compare_strings(in, "r8"))
    {

      return  reg;
    }


   else if (compare_strings(in, "r16/32/64"))
    {

      return reg;
    }


   else if (compare_strings(in, "r/m8"))
    {

      return  mem_or_reg;
    }

   else if (compare_strings(in, "r/m16/32/64"))
    {

      return  mem_or_reg;
    }

   else if (compare_strings(in, "r/m16/32"))
     {

       return mem_or_reg;
     }


   else if (compare_strings(in, "m8"))
    {

      return  memory;
    }

   else if (compare_strings(in, "m16"))
    {

      return memory;
    }


   else if (compare_strings(in, "m16/32"))
    {

      return memory;
    }

   else if (compare_strings(in, "m32"))
     {

       return memory;
     }

   else if (compare_strings(in, "m64"))
     {

       return  memory;
     }

   else if (compare_strings(in, "m16/32/64"))
     {

       return memory;
     }
   else if (compare_strings(in, "re18"))
     {

       return  flag;
     }
  
   else if (compare_strings(in, "Flags"))
     {

       return rflags;
       
     }

   else if (compare_strings(in, "moffs8"))
     {

       return memory_offset;
     }

   else if (compare_strings(in, "moffs16"))
     {

       return  memory_offset;
     }

   else if (compare_strings(in, "ST"))
     {

       return stack_reg;
     }

   else if (compare_strings(in, "STi"))
     {

       return stack_reg;
     }

   else if (compare_strings(in, "xmm"))
     {

       return xmm;
     }

   else if (compare_strings(in, "mm"))
     {

       return  mm;
     }
   else if (compare_strings(in, "rel8"))
     {

       return relative_offset;
     }

   else if (compare_strings(in, "rel16/32"))
     {

       return relative_offset;
     }

   else
     {
       return type_fallback(in);
     }

   
}

int fill_string_with_line(int max_size, char * string, FILE *fptr)
{
  char in = 0;
  int iterator = 0;
  for (; in != '\n'; ++iterator)
    {
      in = fgetc(fptr);
      string[iterator] = in;
    }

  return iterator;
}

int check_for_jump_label(const char *string_in, char *replaced, int *current_spot)
{
  *current_spot = 0;
  if (string_in[0] != ' ' && string_in[0] != 9)
    {
      int i = 0;
      for (; string_in[i] != ':'; ++i)
	{
	  if (string_in[i] == '\n' || string_in[i] == ' ')
	    {
	      return -1;
	    }
	  replaced[i] = string_in[i];
	}
      return i;
    }

  else
    {
      return 0;
    }
}


int numbits_from_suffix( char * instruction_at_suffix)
{
  if (instruction_at_suffix[0] == 'd')
    {
      return 32;
    }

  else if (instruction_at_suffix[0] == 'q')
    {
      return 64;
    }

  else if (instruction_at_suffix[0] == 'b')
    {
      return 8;
    }

  else if (instruction_at_suffix[0] == 'w')
    {
      return 16;
    }

  else if (compare_strings(instruction_at_suffix, "dqu"))
    {
      return 128;
    }

  else if (compare_strings(instruction_at_suffix, "l"))
    {
      return 32;
    }

  else if (compare_strings(instruction_at_suffix, "ups"))
    {
      return 128;
    }

  else if (compare_strings(instruction_at_suffix, "aps"))
    {
      return 128;
    }

  else if (compare_strings(instruction_at_suffix, "dqa"))
    {
      return 128;
    }
  else
    {
      fprintf(stdout, "Defaulting to 64 bit with no prefix given");
      return 64;
    }

  
}

int check_for_lock_prefix( char * string, int *start_index)
{


  if (compare_strings(string + *start_index, "lock"))
    {
      *start_index += 4;
      return *start_index;
    }

  else
    {
      return -1;
    }
}

// I want to inline this function. may put it into a header file with just inlined functions
int fill_string_until_character(const char *input_string, char *target, int start_iterator, char condition)
{
  for (int iterator = 0; input_string[start_iterator] != condition; ++start_iterator)
    {
      target[iterator] = input_string[start_iterator];
    }
  return start_iterator;
}

prefixes byte_from_prefixes(union operand_types op1, union operand_types op2, enum Basic_Operands type1,
				 enum Basic_Operands type2, unsigned char * write_spot)
{
  // if 32 bits are used to address, then the bit 67 will precede the other prefix
  // There is at most 1 byte that's
  // the register is always the more important instruction
  // for the second instruction down there, coder64 would have %eax as op1
  // 10 ----> (%rax), %edx     45 ------->" -0x04(%rbp) <-----op2, %eax <---op1"

 

  // int direction = INSTRUCTION & 2; if this returns true then we know that op1 was for sure a reg where
  // op2 was r/m. op2 would be less significant
  int iterator = 0;
  int start_reg_1 = 0;
  int start_reg_2 = 0;
  if (type1 == memory)
    {
      start_reg_1 = op1.mem_op.first_paren_offset;
      start_reg_1 = move_while_general(op1.mem_op.string, start_reg_1 + 1, ' '); // need to make sure that this returns something
    }
  
  if (type2 == memory)
    {
       start_reg_2 = op2.mem_op.first_paren_offset;
      start_reg_2 = move_while_general(op2.mem_op.string, start_reg_2 + 1, ' ');
      // need to make sure that this returns something
    }
  

  prefixes returned_prefix;
  returned_prefix.flags = 0;
  returned_prefix.addressing_67_prefix = 0;
  
  switch (type1)// the furthest right with the AT&T syntax, the TARGET
    {
    case memory: // default for the target memory to be 64 bit
      if (op1.mem_op.string[start_reg_1] == 'e' || (needs_rex_r(op1.mem_op.string + start_reg_1) && op1.mem_op.string[start_reg_1 + 3] == 'd'))
	write_spot[iterator++] = 0x67;
      break;
    case reg:
      if (op1.reg_string[0] == 'r')
	returned_prefix.flags |= 0x48;
      if (needs_rex_r(op1.mem_op.string))
	returned_prefix.flags |= 0x44;
      break;
    case sib: // hassle call the sib function
      byte_from_sib_part(op1.sib_op.operand, &returned_prefix); // this will be in the right order
      break;
    default:
      break; // for the compiler to stop
    }

  switch (type2)
    {
    case memory:
      if (op2.mem_op.string[start_reg_2] == 'r' || (needs_rex_r(op2.mem_op.string + start_reg_1) && op2.mem_op.string[start_reg_1 + 3] == 'd'))
	{
	  if (iterator > 0)
	    {
	      unsigned char temp = write_spot[0];
	      write_spot[0] = 0x67;
	      write_spot[1] = temp;
	    }
	}
      break;
    case reg:
      if (op1.reg_string[0] == 'r')
	{
	  returned_prefix.flags |= 0x48;
	}
      if (needs_rex_r(op1.mem_op.string))
	returned_prefix.flags |= 0x44;
      break;
    case sib: // this is fine now
      byte_from_sib_part(op1.sib_op.operand, &returned_prefix);
      break;
    default:
      break; // for the compiler to stop
    }
  // cast the struct to a character of bytes
  return returned_prefix;
  
}




