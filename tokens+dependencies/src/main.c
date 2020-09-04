#include "../include/writer.h"
#include <stdio.h>
#include <string.h>
#include "../include/customtypes.h"
#include <stdlib.h>
int main(int argc, char ** argv)
{
  
  if (argc < 2)
    printf("Not enough arguments. 2+ needed %d given", argc );
  
  FILE* input_assembly_file = fopen(argv[1], "r");
  if (!input_assembly_file)
    {
      printf("Could not open the assembly file" );
      exit(1);
    }

  
  struct symbols_information symbols;
  memset(&symbols, 0, sizeof(symbols));
  unsigned char bytes_array[20000];
  symbols.instructions = bytes_array;
  
  if (!input_assembly_file)
    {
      printf("Usage: \n <input> -o: <target>\n");
      printf("other options:\n -p: print opcodes");
    }

  writer(input_assembly_file, &symbols);

  // Print the bytes from the assembly. Hopefully this will work
  for (int i = 0; i < symbols.bytes_written; ++i)
    {
      printf("%x ", symbols.instructions[i]);
    }
  
}
