#include <stdio.h>
#include "../include/get_text_tokens.h"
#include "../include/get_instructions.h"
#include <stdlib.h>


int main()
{
	// Start with the file and a handle on the file 
        FILE* fp = fopen("../misc/instructions.txt", "r");
	// The file should now be opened
	if (!fp)
            fp = fopen("misc/instructions.txt", "r");
        if (!fp)
            return -1;

	
	for (int i = 0; i < 1074; ++i)
	  {
	    struct instruction_format test_one_instruction;
	    char* char_pool_begin = (char*)malloc(250);
	    pool_memory(&test_one_instruction, char_pool_begin);
	    gather_instruction(&test_one_instruction, fp);
	    write_instruction_stdout(&test_one_instruction);
	    free(char_pool_begin);
	  }

	// After to see where the fgetc goes
	// The text file has 1074 lines and as such will be looped 1074 times
	// So the previous lines are not necessary
	// perhaps after this is done this can be redirected to another file
	

}
