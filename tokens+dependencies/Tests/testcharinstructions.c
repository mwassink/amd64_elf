#include <stdio.h>
#include <stdlib.h>
#include "../include/char_to_instructions.h"



int main()
{
  //print_value_binary();
  print_binary(102);

  unsigned char * string = "ADD";
  unsigned long int result = name_to_id(string);

  print_binary(result);
}
