#include <stdio.h>
#include "../include/get_text_tokens.h"
#include "../include/get_instructions.h"



int main()
{
	// Start with the file and a handle on the file 
	FILE* fp = fopen("misc/instructions.txt", "r");
	// The file should now be opened
	if (!fp)
		return 1;

	struct instruction_format test_one_instruction;
	char* char_pool_begin = (char*)malloc(250);
	pool_memory(&test_one_instruction, char_pool_begin);
	gather_instruction(&test_one_instruction, fp);
	free(char_pool_begin);
}