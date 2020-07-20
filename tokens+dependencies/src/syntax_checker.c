#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/get_instructions.h"
#include "../include/syntax_checker.h"
#include <stdbool.h>
#include "../include/sib.h"
// This file needs to go through line by line and check for tokens. It will just look for whitespace and endlines

enum Sections { _text, _bss, data};
enum Basic_Operands {immediate, memory, reg, sib};

// text holds the actual instructions and registers
// the other sections have to look through the declared variables and stuff






void search_line(FILE * in, struct instruction_pieces *arguments)
{
  // The fp has information on where in the file we are, this assumes that we
  // are at the beginning of the line and that the file is opened already
  // If the beginning of the line is not a space then it should be a label
  char input_string[250] = {0};// Allocate 250 bytes for the string
  size_t line_length;
  int offset = 0;
  // Hopefully whoever wrote the assembly makes good use of endlines
  line_length  = getline(&input_string, &line_length, in);
  char label[100] = {0};
  char mnemonic[16] = {0};
  char op1_mnemonic[16] = {0};
  char op2_mnemonic[16] = {0};
  if (input_string[0] != '\n') // This should be a label
    {
      for (; input_string[offset] != ' '; ++offset)\
	{
	  label[offset] = input_string[offset];
	}
      label[offset+1] = 0;
    }

  for (; input_string[offset] == ' '; ++offset); // Need to keep looking until the end of a line is found
  // Regardless we can keep going until we find the mnemonic for the instruction
  // NOTE: that this will be put into the checker and search the array for the right insdtr
  // If the instr does not exist then this will die
  for (int i = 0; input_string[offset] != ' '; ++offset, ++i)
    {
      mnemonic[i] = input_string[offset];
     
    }

  for (; input_string[offset] == ' '; ++offset);

  // $ denotes immediate, number will denote offset, ( will denote a mem, % just reg

  if (input_string[offset] == '(') // Thsi is a memory operand, probably does need some type of special loop until the next parentheses
    {
      arguments->op1 = memory;
      for (int i = 0; input_string[offset] != ')'; ++offset)
	{
	  op1_mnemonic[i] = input_string[offset];
	}
    }

  else if (input_string[offset] == '%') // this is a register, does not need a special loop
    {arguments->op1 = reg;
      for (int i = 0; input_string[offset] != ' '; ++offset)
	{
	  op1_mnemonic[i] = input_string[offset]; // wil point at right one later
	}
    }

  else if (input_string[offset] > 48 && input_string[offset]  < 58) // should be an integer or a 0 which would signify an offset
    {
      arguments->op1 = memory;
      for (int i = 0; input_string[offset] != ')'; ++offset)
	{
	  op1_mnemonic[i] = input_string[offset]; // will be changed later to point at right one 
	}
    }
  // Otherwise it should be an immediate
  else
    {
      arguments->op1 = immediate; // Now we need to loop until the space is found
      for (int i = 0; input_string[offset] != ' '; ++offset)
	{
	  op1_mnemonic[i] = input_string[offset]; // Will be changed later
	}
      
    }
  // Add the word to the above contrainsts, make the struct point at them 
  arguments->op1_mnemonic = op1_mnemonic;
  

  // THE FIRST ARG should be processed, now onto the second

  for (; input_string[offset] == ' '; ++offset);

  if (input_string[offset] != ',') // it should always be some type of comma to separate the operands
    {
      fprintf(stderr, "Unrecognized arguments");
      assert(1 == 0);
    }

  offset++;

  for (; input_string[offset] == ' '; ++offset); // loop until the next argument

  if (input_string[offset] == '(') // Thsi is a memory operand, probably does need some type of special loop until the next parentheses
    {
      arguments->op2 = memory;
      for (int i = 0; input_string[offset] != ')'; ++offset)
	{
	  op2_mnemonic[i] = input_string[offset];
	}
    }

  else if (input_string[offset] == '%') // this is a register, does not need a special loop
    {arguments->op2 = reg;
      for (int i = 0; input_string[offset] != ' '; ++offset)
	{
	  op2_mnemonic[i] = input_string[offset]; // wil point at right one later
	}
    }

  else if (input_string[offset] > 48 && input_string[offset]  < 58) // should be an integer or a 0 which would signify an offset
    {
      arguments->op2 = memory;
      for (int i = 0; input_string[offset] != ')'; ++offset)
	{
	  op2_mnemonic[i] = input_string[offset]; // will be changed later to point at right one 
	}
    }


  else
    {
      arguments->op2 = immediate; // Now we need to loop until the space is found
      for (int i = 0; input_string[offset] != ' '; ++offset)
	{
	  op2_mnemonic[i] = input_string[offset]; // Will be changed later
	}
      
    }

  arguments->op2_mnemonic = op2_mnemonic;

  // Now this function should be done 


}
  // NOT DONE
  
  // TODO: Make the array of instructions from the table and the structs of instructions
  // Along with the IDs of the instructions
int binary_lookup(int in, int* array_in)
{
  int high = 1073;
  int low = 0;
  int mid = 0; // returned
  int counter = 12; // pretty close to log 2 1074 

  while (counter-- &&  array_in[mid] != in)
    {
      mid = (high + low)/2;
      if (array_in[mid] < in) // need to make the bottom move up search higher range
	low = mid;
      else // move the top down to search the smaller numbers
	high = mid;

    }
  if (counter == 0)  // failed
    return -1;

  else
    return mid;
}

int rip_suffix(char *instruction_mnemonic)
{
  //  suffixes
  int iterator = 0;
  while (instruction_mnemonic[iterator++]);
  iterator--;
  switch (instruction_mnemonic[iterator])
    {
    case 'q': // quadword
      instruction_mnemonic[iterator] = 0;
      return 0;
    case 'd':
      instruction_mnemonic[iterator] = 0;
      return 0;
    case 'w':
      instruction_mnemonic[iterator] = 0;
      return 0;
    case 'b':
      instruction_mnemonic[iterator] = 0;
      return 0;
    case 'h':
      instruction_mnemonic[iterator] = 0;
      return 0;
    default:
      return -1;
      
      
    }


}

  
int look_for_mnemonic(char *instr_mnemonic, int* shorter_mnemonics, int* longer_mnemonics)
{
  // The string should be converted to an int after the % register
  // Will be compared against the other ints, but in a struct array?
  // Note: should I make an array of structs then search through or make an array
  // of ints and have them point to the proper struct?
  // There are 1074 arguments --> 0-1073
  unsigned long int name_id;
  int stripped  = -1; 
  name_id = name_to_id(instr_mnemonic);
  int index = -1;
  
  if (!name_id)
    index = binary_lookup(name_id, longer_mnemonics);

  else
    index = binary_lookup(name_id, longer_mnemonics);

  if (index != -1) // found
    return index;

  else // look again wi8th the stripped prefix
    {
      char copy[16]; int iterator = 0;
      for (; instr_mnemonic[iterator] != 0; ++iterator )
	{
	  copy[iterator] = instr_mnemonic[iterator];
	}
      
      stripped = rip_suffix(copy);
      
      if (!stripped)
	{
	  name_id = name_to_id(copy);
	  if (!name_id)
	    index = binary_lookup(name_id, longer_mnemonics);
	  else
	    index = binary_lookup(name_id, shorter_mnemonics);

	  if (index != -1)
	    return index;
	  else
	    {
	      fprintf(stderr, "Failure to find any instruction for the instruction");
	      assert(0 == 1);
	    }
	}

      else
	    {
          fprintf(stderr, "No mnemonic could be found with the mnemonic on this line");
          assert(0 == 1);
	    }
    }
    


}

int look_for_reg(char *reg_in, int *reg_array)
{
  // start with the percent symbol % and move forward one
  int reg_no = name_to_id(reg_in+1);
  int index = binary_lookup(reg_no, reg_array);

  if (index != -1)
    return index;

  else
    {
      fprintf(stderr, "Failure to find the register for the given ");
      assert(0 == 1);
    }

}

 void check_memory_operand(struct instruction_pieces* in)
 {
   // Needs to check for the type
 }



void assert_dependencies(struct instruction_pieces *in); // TODO

int write_modrm(struct instruction_pieces *in);
 



 
  

void _text_checker(FILE * in);
  // Need to look for the text or the other sections in the beginning
  // For now there needs to be some type of variable that when this thing is run it keeps
  // track of the current section
  // should have some types of variable as well as some read only stuff
  // also there needs to be a .text section for this
  // First look for the first instruction and then the two registers

  /* Instruction format: 
     movq %rax, %rbx \n */
