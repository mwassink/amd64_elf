#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/sib.h"
#include <math.h>
#include "../include/customtypes.h"
#include "../include/get_instructions.h"
#include "../include/syntax_checker.h"
#include "../include/utilities.h"
// This file needs to go through line by line and check for tokens. It will just look for whitespace and endlines
// text holds the actual instructions and registers
// the other sections have to look through the declared variables and stuff




enum section_types check_for_section_label(const char * input_string, int * iterator_in)
{
  int start_iterator = 0;
  char temp_string[30] = {0};
  for (; input_string[start_iterator] == ' ' || input_string[start_iterator] == 9; start_iterator++);

  if (input_string[start_iterator] != '.') //start iterator may be 0
    {
      *iterator_in = 0; // Just start from the beginning
      return -1;
    }

  int string_iterator = 0;
  for (; input_string[start_iterator] != ' '; ++start_iterator, ++string_iterator)
    {
      temp_string[string_iterator]= input_string[start_iterator];
    }

  if (compare_strings(temp_string, ".text"))
    {
      *iterator_in = start_iterator;
      return text;
    }

  else if (compare_strings(temp_string, ".bss"))
    {
      *iterator_in = start_iterator;
      return bss;
    }

  else if (compare_strings(temp_string, ".data"))
    {
      *iterator_in = start_iterator;
      return data;
    }
  else
    {
      *iterator_in = 0;
      return invalid_section_label;
    }
  
}


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

void search_line(FILE * file_in, struct instruction_pieces *arguments, enum section_types current_type)
{
  // The fp has information on where in the file we are, this assumes that we
  // are at the beginning of the line and that the file is opened already
  // If the beginning of the line is not a space then it should be a label
  int line_iterator = 0;
  char input_string[250] = {0};// Allocate 250 bytes for the string
  size_t line_length = fill_string_with_line(250, input_string, file_in);
  enum section_types type = check_for_section_label(input_string);

  if (type == invalid_section_label)
    {
      fprintf(stderr, "Invalid section label");
    }

  

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
      *disp_value = total;
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
      *disp_value = ascii_to_int(string, start_parentheses);
      if (*disp_value> 255)
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



void check_instruction(struct instruction_pieces *in, unsigned long int *shorter_mnemonics, unsigned long int *longer_mnemonics, struct dependencies *dep)
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
  unsigned long int name_id = name_to_id(in->instruction_mnemonic);
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
         - The direction and field buts may not be there for all of them
         - While many have d and w bits, others may have a different one in one of theirs
      */

      // Calling the assert deps on all of these
      // Declare a match variable on this to make sure that it works

      bool match_found = 0;
      for (int iterator = 0; iterator < valid_neighbors_number; ++iterator)
        {
          // NOT DONE YET
          if ()
        }



    }
  
  
} 
bool assert_dependencies(struct instruction_pieces *user_in, struct dependencies *table_in)
{
  /*
    - Pass the same enum operands
    - Pass the lock check 
    - Pass the size check 
 
   */
  if (user_in->wants_lock && !(table_in->lockable)) // Failure, return a zero
    {
      return 0;
    }

  if (user_in->op1 != table_in->one)
    {
      return 0;
    }

  if (user_in->op2 != table_in->two)
    {
      return 0;
    }
  
  if (user_in->size > table_in->max_size)
    {
      return 0;
    }
  return 1;
}

 
  

void _text_checker(FILE * in);
  // Need to look for the text or the other sections in the beginning
  // For now there needs to be some type of variable that when this thing is run it keeps
  // track of the current section
  // should have some types of variable as well as some read only stuff
  // also there needs to be a .text section for this
  // First look for the first instruction and then the two registers

  /* Instruction format: 
     movq %rax, %rbx \n */
