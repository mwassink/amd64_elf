#include <stdio.h>
#include <stdlib.h>

// This file needs to go through line by line and check for tokens. It will just look for whitespace and endlines

enum Sections { _text, _bss, data};
enum Basic_Operands {immediate, memory, reg};

// text holds the actual instructions and registers
// the other sections have to look through the declared variables and stuff


struct instruction_pieces
{
  char * instruction_mnemonic;
  long unsigned int instruction; // This will match the table which allows for a quick search
  enum Basic_Operands op1;
  int op1_size;
  char * op1_mnemonic;
  enum Basic_Operands op2;
  int op2_size;
  char * op2_mnemonic;
};



void search_line(FILE * in, struct instruction_pieces *arguments)
{
  // The fp has information on where in the file we are, this assumes that we
  // are at the beginning of the line and that the file is opened already
  // If the beginning of the line is not a space then it should be a label
  char input_string[250]; // Allocate 250 bytes for the string
  size_t line_length;
  int offset = 0;
  // Hopefully whoever wrote the assembly makes good use of endlines
  line_length  = getline(&input_string, &line_length, in);
  char label[100];
  char mnemonic[16];
  char suffix;
  char op1_mnemonic[16];
  char op2_mnemonic[16];
  if (input_string[0] != '\n') // This should be a label
    {
      for (; input_string[offset] != ' '; ++offset)\
	{
	  label[offset] = input_string[offset];
	}
    }

  for (; input_string[offset] == ' '; ++offset); // Need to keep looking until the end of a line is found
  // Regardless we can keep going until we find the mnemonic for the instruction
  // NOTE: that this will be put into the checker and search the array for the right insdtr
  // If the instr does not exist then this will die
  for (int i = 0; input_string[offset] != ' '; ++offset, ++i)
    {
      mnemonic[i] = input_string[offset];
      suffix=input_string[offset]; // The last thing will be put into the suffix, overwriting every time
    }

  for (; input_string[offset] == ' '; ++offset);

  // $ denotes immediate, number will denote offset, ( will denote a mem, % just reg

  if (input_string[offset] == '(')
    {
      arguments->op1 = memory;
    }

  else if (input_string[offset] == '%') // this is a register
      arguments->op1 = reg;

  else if (input_string[offset] > 48 && input_string[offset]  < 58) // should be an integer 
    arguments->op1 = memory;

  else
    arguments->op1 = immediate;
  
  for (int i = 0; input_string[offset] != ' '; ++offset)
	{
	  op1_mnemonic[i] = input_string[offset];
	}

  // NOT DONE
  
  // TODO: Make the array of instructions from the table and the structs of instructions
  // Along with the IDs of the instructions

  

void _text_checker(FILE * in);
  // Need to look for the text or the other sections in the beginning
  // For now there needs to be some type of variable that when this thing is run it keeps
  // track of the current section
  // should have some types of variable as well as some read only stuff
  // also there needs to be a .text section for this
  // First look for the first instruction and then the two registers

  /* Instruction format: 
     movq %rax, %rbx \n */
