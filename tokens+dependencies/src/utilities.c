#include "../include/utilities.h"
#include "../include/customtypes.h"
#include <stdio.h>
#include <string.h>

inline int move_to_endline(const char * input_string, int start_iterator)
{
  for (; input_string[start_iterator] != '\n'; ++start_iterator);
  return start_iterator;
}

inline int move_to_space (const char * input_string, int start_iterator)
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


inline int move_to_general(const char * input_string, int start_iterator, char general_char)
{
  for (; input_string[start_iterator] != general_char; ++start_iterator);
  return start_iterator;
}




bool compare_strings(char * lhs, char * rhs)
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
  int i = 0; int one_length = 0; int two_length = 0; int three_length = 0; int four_length = 0; int five_length = 0;

  
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

   sizes[0] = atoi(one); size[1] = atoi(two); size[2] = atoi(three); size[3] = atoi(four);
						
   
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
  int iterator = 0;
  sizes_in->one_byte = 0; sizes_in->byte_high = 0; sizes_in->byte_16 = 0;
  sizes_in->byte_2 = 0; sizes_in->byte_4 = 0; sizes_in->byte_8 = 0;

  int * array = possible_sizes(instruction_in);
  
  for (int i = 0; i < 4; ++i)
    {
      switch_on_possible_sizes(array[i], sizes_in)
    }
  
  
}


