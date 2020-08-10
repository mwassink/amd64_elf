#include <stdio.h>
#include "../include/convert_instruction.h"
#include <assert.h>
#include <stdbool.h>



int main()
{
  bool str_compare = false;
  char * string1 = "r";
  str_compare = compare_strings(string1, "r");
  assert(str_compare == true);
  string1 = "m16/32";
  str_compare = compare_strings(string1, "m16/32");
  assert(str_compare == true);
  string1 = "m16";
  str_compare = compare_strings(string1, "m16");
    
  
  
  
}
