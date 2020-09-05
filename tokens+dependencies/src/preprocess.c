#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv )
{
  if (argc != 2)
    {
      fprintf(stderr, "Preprocess needs 2 arguments");
    }

  
  FILE * input_file = fopen(argv[1], "r");

  unsigned char *buffer = malloc(200000);
  unsigned long int new_length = 0;
  if (input_file != NULL)
    {
      new_length = fread(buffer, sizeof(char), 200000, input_file);
      
    }

  buffer[new_length] = 0;
  
  printf("%ld", new_length);

  int read_iterator = 0;
  
    
  
  for (; read_iterator < new_length; ++read_iterator)
    {
      if (buffer[read_iterator] == '\t')
	{
	  buffer[read_iterator] = ' ';
	}
      if (buffer[read_iterator] == '\n')
	{
	  for (int i = 1; buffer[read_iterator + i] == '\n'; ++i)
	    {
	      buffer[read_iterator + i] = ' ';
	    }
	}
    }
  FILE * output_file = fopen (argv[1], "w");
  int step = 0;

  if (buffer[0] == '\n')
    step = 1;
  
 strip_end: if (buffer[new_length - 1] == '\n' || buffer[new_length - 1] == ' ' || buffer[new_length - 1] == '\t')
    {
      new_length--;
      goto strip_end;
    }

  

  fwrite(buffer + step, sizeof(char), new_length, output_file);
  
  

}
