#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/get_instructions.h"
#include "../include/syntax_checker.h"
#include <stdbool.h>
#include "../include/sib.h"
#include <math.h>

// This file needs to go through line by line and check for tokens. It will just look for whitespace and endlines


// text holds the actual instructions and registers
// the other sections have to look through the declared variables and stuff

void init_op_info(struct memory_op_info *in)
{
  in->disp_length = 0;
  in->disp_offset = -1;
  in->reg1_off = -1;
  in->reg2_off = -1;
  in->sib = 0;
  in->sib_scale = 0;
}



  
int ascii_to_int( char * in, int *returned_index)
{
  int temp = 0;
  int sum = 0;

  while (in[temp] != '(' )
    {
      sum *= 10;
      sum += (in[temp]-48);
      ++temp;
    }
  *returned_index = temp; // The last one will be the parentheses
  return sum;
}

void search_line(FILE * in, struct instruction_pieces *arguments)
{
  // The fp has information on where in the file we are, this assumes that we
  // are at the beginning of the line and that the file is opened already
  // If the beginning of the line is not a space then it should be a label
  char input_string[250] = {0};// Allocate 250 bytes for the string
  size_t line_length;
  int offset = 0;
  // Hopefully whoever wrote the assembly makes good use of endlines
  line_length  = getline(&input_string, &line_length, in); // Should not be able to distinguish between these when called
  char label[100] = {0};
  char mnemonic[16] = {0};
  char op1_mnemonic[16] = {0};
  char op2_mnemonic[16] = {0};
  if (input_string[0] != ' ') // This should be a label
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

  // First check if this is asking for a lock. I think that is the only prefix we can have
  // Slow but probably rare 
  if (input_string[offset] == 'l' && input_string[offset + 1] == 'o' &&
      input_string[offset + 2] == 'c' && input_string[offset] == 'k')
  {
      arguments->wants_lock = 1;
  }



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
int binary_lookup(unsigned long int in, unsigned long int* array_in)
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

  
int look_for_mnemonic(char *instr_mnemonic, unsigned long int* shorter_mnemonics, unsigned long int* longer_mnemonics)
{
  // The string should be converted to an int after the % register
  // Will be compared against the other ints, but in a struct array?
  // Note: should I make an array of structs then search through or make an array
  // of ints and have them point to the proper struct?
  // There are 1074 arguments --> 0-1073
  unsigned long int name_id;
  int stripped  = -1; 
  name_id = name_to_id(instr_mnemonic); // eval to 0 if this is too long
  int index = -1;
  
  if (!name_id)
    index = binary_lookup(name_id, longer_mnemonics);

  else
    index = binary_lookup(name_id, shorter_mnemonics);

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

int look_for_reg(char *reg_in, unsigned long int *reg_array)
{
  // start with the percent symbol % and move forward one
  unsigned long int reg_no = name_to_id(reg_in+1);
  int index = binary_lookup(reg_no, reg_array);

  if (index != -1)
    return index;

  else
    {
      fprintf(stderr, "Failure to find the register for the given ");
      assert(0 == 1);
    }

}

static inline int check_for_offset(char * string, int *start_parentheses, int *disp_value)
{
  // Should return the number of bytes for the offset
  int length_counter = 2;
  int total = 0;
  if (string[0] == '0' && string[1] == 'x') // Hexadecimal number
    {
      // Hexadecimal offset or a number
      for (; string[length_counter] >= 48 && string[length_counter] < 58; ++length_counter)
	{
	  char temp = string[length_counter] - 48;
	  total |= temp;
	  total <<= 4;
	}

      *start_parentheses = length_counter;

      if (length_counter - 2 > 8) // Too big
	{
	  fprintf(stderr, "Disp is greater than 8 bytes");
	  assert(0 == 1);
	}
      
      if ((length_counter -2) > 2) // Need more than one byte to process this
	return 4;
      else
	return 1;
    }

  else if  (string[0] >= 48 && string[0] < 58)
    {
      // This is just a decimal offset
      if (ascii_to_int(string, start_parentheses)  > 255)
	{
	  return 1;
	}

      else
	return 4;    
    }
  
  else
    return 0;
}

      
// Don't write yet, we need to know whether it is an sib,etc
struct memory_op_info check_memory_operand(char * memory_instruction_in) // Should be a given that this is a memroy type
 {
   // Needs to check for an offset first
   struct memory_op_info info;
   init_op_info(&info);
   int length_counter = 0;
   int disp_value = 0;
   info.disp_length = check_for_offset(memory_instruction_in, &length_counter, &disp_value);
   info.disp_offset = length_counter;
   info.disp = disp_value;

   // Make a loop to look for the next thing other than a space
   length_counter++;
   for (; memory_instruction_in[length_counter] == ' '; ++length_counter);
   // Now the length counter should be at the right spot for the register mnemonic
   if (memory_instruction_in[length_counter] != '%') // Not a register
     {
       fprintf(stderr, "Improper usage with the op1_mnemonic and memory");
       fprintf(stderr, "The op1_mnemonic needs a register after the parentheses");
       assert(0 == 1);
     }

   
   info.reg1_off = length_counter;
   // Now need to look for the next non whitespace
   for (; memory_instruction_in[length_counter] != ','; ++length_counter); // should be at the comma
   for (; memory_instruction_in[length_counter] == ' '; ++length_counter); // should be at next non whitespace character

   if (memory_instruction_in[length_counter] == ')') // we do not have more coming
     {
       return info;
     }

   else if (memory_instruction_in[length_counter] == ',')
     {
       for (; memory_instruction_in[length_counter] == ' '; ++length_counter);
       info.sib =  1;
       if (memory_instruction_in[length_counter] == '%') // the next thing that comes is a reg
	 {
	   info.reg2_off = length_counter;
	 }
       else
	 {
	   fprintf(stderr, "The second operand of the sib was not a register, like it should be");
	   assert(0 == 1);
	 }

        for (; memory_instruction_in[length_counter] != ','; ++length_counter); // should be at the comma
	for (; memory_instruction_in[length_counter] == ' '; ++length_counter); // should be at next non whitespace character

	info.sib_scale = memory_instruction_in[length_counter] - 48;

	if (info.sib_scale != 1 && info.sib_scale != 2 && info.sib_scale != 4 && info.sib_scale != 8)
	  {
	    fprintf(stderr, "The scale for the sib is not 1,2,4, or 8");
	    assert(1 == 0);
	  }
	
	for (; memory_instruction_in[length_counter] == ' '; ++length_counter);

	assert(memory_instruction_in[length_counter] == ')');
     }

   return info;
 }



void assert_dependencies(struct instruction_pieces *in, unsigned long int *shorter_mnemonics, unsigned long int *longer_mnemonics, struct dependencies *dep)
{
  /* Now some requirements for instructions will be listed
     - < 2 memory operands 
     - No direction in ModRM, rather in the instruction 
     - < 2 immediates
     - If a dependency check fails for a mnemonic, try one of the nearest ones. Likely, lots of them will fail as of now
   */

  // Walk through this, 
  int index = look_for_mnemonic(in->instruction_mnemonic, shorter_mnemonics,  longer_mnemonics);


  if (index == -1)
    {
      printf("Mnemonic not found for the instruction");
      assert(1 == 0);
    }
  int name_id = name_to_id(in->instruction_mnemonic);
  // If the name_id comes out to 0 then we know that it was found in the longer ones, otherwsie it was found in the shorter ones
  if (name_id)
    {

      // Found in the shorter ones, look at the dependencies for this one and its neighbors
      int valid_neighbors[16] = { 0 };
      int valid_neighbors_number = 0;
      // Check below
      for (int i = 0; shorter_mnemonics[index - i] == name_id; ++i)
      {
          valid_neighbors[i] = index - i;
          valid_neighbors_number++;
      }
      
      for (int i = 0; shorter_mnemonics[index + i] == name_id; ++i)
      {
          valid_neighbors[i] = index + i;
          valid_neighbors_number++;
      }
      
    }

  else
    {
      // Found in the longer ones, look at the dependencies for this one and its neighbors
      int valid_neighbors[16] = { 0 };
      int valid_neighbors_number = 0;
      // Check below
      for (int i = 0; longer_mnemonics[index - i] == name_id; ++i)
      {
          valid_neighbors[valid_neighbors_number++] = index - i;
          
      }
      // Check above 
      for (int i = 0; longer_mnemonics[index + i] == name_id; ++i)
      {
          valid_neighbors[valid_neighbors_number++] = index + i;
      }
      // Now to make a note about the direction and field bits
      /* 
      
      
      
      
      
      
      */





    }
  
  
}

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
