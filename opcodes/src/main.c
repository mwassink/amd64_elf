#include "../include/writer.h"
#include <stdio.h>
#include <string.h>
#include "../include/customtypes.h"
#include <stdlib.h>
int main(int argc, char ** argv)
{
  
  if (argc < 2)
    printf("Not enough arguments. 2+ needed %d given", argc );

  char dest[100] = "./preprocess ";
  strcat(dest, argv[1]);
  system(dest);
  int offArr[200] = {0};

  
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

   writer(input_assembly_file, &symbols, offArr);
   int off_ctr = 0;
   for (int i = 0; i < 200; ++i) {
       if (offArr[i] == 0) break;
       off_ctr++;
    }
  // Print the bytes from the assembly. Hopefully this will work
   int tot_counter = 0;
   printf("Opcodes: \n");
  for (int i = 0; i < off_ctr; ++i)
    {
      for (int k = 0; k < offArr[i]; ++k) {
        printf("%x ", symbols.instructions[tot_counter]);
        tot_counter++;
      }
      printf("\n");
    }
  fflush(stdout);
  return 0;
}
