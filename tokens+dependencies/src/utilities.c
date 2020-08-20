#include "../include/utilities.h"
#include <stdio.h>


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

