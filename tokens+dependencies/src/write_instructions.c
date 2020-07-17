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

	
	
	struct instruction_format test_one_instruction;
	char* char_pool_begin = (char*)malloc(250);
	pool_memory(&test_one_instruction, char_pool_begin);
	gather_instruction(&test_one_instruction, fp);
	write_instruction_stdout(&test_one_instruction);
	free(char_pool_begin);
	

	// After to see where the fgetc goes
	char* newer_pool = (char*)malloc(250);
	pool_memory(&test_one_instruction, newer_pool);
	gather_instruction(&test_one_instruction, fp);
	write_instruction_stdout(&test_one_instruction);
	free(newer_pool);


}
