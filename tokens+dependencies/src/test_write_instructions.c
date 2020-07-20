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

	/*
	for (int i = 0; i < 1074; ++i)
	  {
	    struct instruction_format test_one_instruction;
	    char* char_pool_begin = (char*)malloc(250);
	    pool_memory(&test_one_instruction, char_pool_begin);
	    gather_instruction(&test_one_instruction, fp);
	    write_instruction_stdout(&test_one_instruction);
	    free(char_pool_begin);
	  }
	 */

	// Make a bin file with the structs lined up contiguously
	// First malloc 1074 struct pointers on the heap
	struct instruction_format example;
	struct instruction_format* array = (char *)malloc(1074 * sizeof(example)); //1074 structs on the heap
	char* homes_for_strings = (char*)malloc(1074 * 208);

	FILE* char_strings = fopen("../misc/strings.bin", "wb");
	if (!char_strings)
		return -1;

	FILE* struct_strings = fopen("../misc/structs.bin", "wb");
	if (!struct_strings)
		return -1;

	for (int i = 0; i < 1074; ++i)
	{
		// First look at the file of input strings, get them, then print later
		pool_memory(array + i, homes_for_strings + (208 * i)); 
		gather_instruction(array + i, fp);
		array[i].ID = name_to_id(array[i].mnemonic);
	}

	char* array_wo_ptrs = malloc(1074 * 24);
	for (int i = 0; i < 1074; ++i)
	{
		// Be careful of alignment
		int* ptr1 = (int*)(array_wo_ptrs + i * 16);
		*ptr1 = array[i].pooled;
		array_wo_ptrs[i * 16 + 4] = array[i].prefix;
		int* ptr2 = (int*)(array_wo_ptrs + i * 16 + 8);
		*ptr2 = array[i].prefix_OF;
		array_wo_ptrs[i * 16 + 8] = array[i].primary_opcode;
		array_wo_ptrs[i * 16 + 9] = array[i].secondary_opcode;
		array_wo_ptrs[i * 16 + 10] = array[i].reg_opcode_field;
		array_wo_ptrs[i * 16 + 11] = array[i].documentation;
		array_wo_ptrs[i * 16 + 12] = array[i].mode;
		array_wo_ptrs[i * 16 + 13] = array[i].ring_level;
		array_wo_ptrs[i * 16 + 14] = array[i].lock_prefix;
		array_wo_ptrs[i * 16 + 16] = array[i].ID;

	}

	fwrite(array_wo_ptrs, 1, 1074 * 24, struct_strings);
	fwrite(homes_for_strings, 1, 1074 * 208, char_strings);

	free(array);
	free(array_wo_ptrs);
	free(homes_for_strings);
	

}
