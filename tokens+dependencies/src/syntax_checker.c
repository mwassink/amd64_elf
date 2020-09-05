#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "../include/sib.h"
#include <math.h>
#include "../include/customtypes.h"
#include "../include/get_instructions.h"
#include "../include/syntax_checker.h"
#include "../include/utilities.h"
#include "../include/symbols.h"



// This file needs to go through line by line and check for tokens. It will just look for whitespace and endlines
// text holds the actual instructions and registers
// the other sections have to look through the declared variables and stuff
 
typedef unsigned char byte;

bool check_sizes(int size_in, struct available_sizes available)
{
  switch (size_in)
    {
    case 8:
      return available.one_byte;
    case 16:
      return available.byte_2;
    case 32:
      return available.byte_4;
    case 64:
      return available.byte_8;
    case 128:
      return available.byte_16;
    default:
      return 0;
      
    }
}

enum section_types check_for_section_label(const char * input_string, int * iterator_in)
{
  int start_iterator = 0;
  char temp_string[30] = {0};
  for (; input_string[start_iterator] == ' ' || input_string[start_iterator] == 9; start_iterator++);

  if (input_string[start_iterator] != '.') //start iterator may be 0
    {
      *iterator_in = 0; // Just start from the beginning
      return none;
    }

  int string_iterator = 0;
  for (; input_string[start_iterator] != ' ' && input_string[start_iterator] != '\n'; ++start_iterator, ++string_iterator)
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

int check_for_jump_label(const char * input_string, struct symbols_information *sym_info)
{
  int start_iterator = 0;
  

  for (; input_string[start_iterator] != ' ' && input_string[start_iterator] != 9 && input_string[start_iterator] != '\n'; ++start_iterator);
 
 
  // If we started on a space or a tab
  // Need to return from the function
  if (start_iterator == 0)
    {
      return -1;
    }

  else if (input_string[start_iterator - 1] != ':')
    {
      fprintf(stderr, "Failure assembling the line. Label expected but not denoted properly");
      assert(0 ==1);
      return -1;
    }

  else
    {
      
      return start_iterator; // wil be handled in the next part 
    }

  
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

int search_line(FILE * file_in, struct instruction_pieces *arguments, struct symbols_information *symbols)
{

    
    
  // The fp has information on where in the file we are, this assumes that we
  // are at the beginning of the line and that the file is opened already
  // If the beginning of the line is not a space then it should be a label

    
  int line_iterator = 0;
  char input_string[250] = {0};// Allocate 250 bytes for the string
  char *mnemonic = (char *)malloc(15); // 15 bytes for the future mnemonic
  memset(mnemonic, 0, 15);
  
  if (fgets(input_string, 250, file_in) == NULL)
    {
      return 2;
    }
  enum section_types type = check_for_section_label(input_string, &line_iterator );

  if (type != text && type != none )
    {
      fprintf(stderr, "Invalid section label");
      assert(0 == 1);
    }
  // text assumed
  // if we get type of text then just return as nothing else will be on the line
  if (type == text)
    return 1;
  
  int start_iterator = check_for_jump_label( input_string, symbols);

  if (start_iterator) // the start iterator is not zero, label found
    {
      symbols->corresponding_starts_for_labels[symbols->current_label_index] = symbols->bytes_written;
      //fill the label starting at 0, going until start_iterator
      for (int i = 0; i < start_iterator; ++i)
        symbols->string_for_jumps[symbols->current_label_index][i] = input_string[i];
      
      
      symbols->current_label_index++;
      
    }

start_iterator = move_while_general(input_string, start_iterator, ' '); // Mnemonic comes next, hopefully

  if (input_string[start_iterator] == '\n') // this is fine we can just wait until the next non-space
      {
        start_iterator = 0;
        if (fgets(input_string, 250, file_in) == NULL)
            {
                printf("Empty label. Do not do that");
                exit(1);
            }

      }



  sscanf(input_string, "%*[\t\r \n]%s%*[\t\r \n]%s%*[\t\r\n ,]%s", arguments->instruction_mnemonic, arguments->op2_mnemonic
         , arguments->op1_mnemonic );


  
  arguments->op2 = user_string_to_operand(arguments->op2_mnemonic,0); // This does not move the start iterator

  
  arguments->op1 = user_string_to_operand(arguments->op1_mnemonic,0);



  arguments->instruction = name_to_id(arguments->instruction_mnemonic);
  
  
  return 0;
  
  // Make sure that everything is part of the text section

}
  
  
  // TODO: Make the array of instructions from the table and the structs of instructions
  // Along with the IDs of the instructions
int binary_lookup(unsigned  int in, struct instruction_definition* array_in, bool long_instruction)
{
  int high_longs = 42;
  int high_shorts = 1030; 
  int low_longs = 0;
  int low_shorts = 43;
  int mid_longs = 0; // returned
  int mid_shorts = 43;
  int counter = 14; // pretty close to log 2 1074 

  if (long_instruction)
    {
      while (counter-- &&  array_in[mid_longs].long_mnemonic != in)
	{
	  mid_longs = (high_longs + low_longs)/2;
	  if (array_in[mid_longs].mnemonic < in) // need to make the bottom move up search higher rang
	    low_longs = mid_longs;
          else if(array_in[mid_longs].mnemonic > in) // move the top down to search the smaller numbers
	    high_longs = mid_longs;
          else
              return mid_longs;
	  
	}
       // failed
	return -1;
      

    }
  else
    {
      while (counter-- &&  array_in[mid_shorts].long_mnemonic != in)
	{
          mid_shorts = (high_shorts + low_shorts)/2;
	  if (array_in[mid_shorts].mnemonic < in) // need to make the bottom move up search higher range
	    low_shorts = mid_shorts;
          else if (array_in[mid_shorts].mnemonic > in)// move the top down to search the smaller numbers
	    high_shorts = mid_shorts;
          else
              return mid_shorts;
	  
	}
       // failed
	return -1;
      


    }
}

void rip_suffix(char *instruction_mnemonic, int depth)
{
  //  suffixes
  int length = 0;
  while (instruction_mnemonic[length])
    {
      length++;
    }
  
  for (int i = 0; i < depth; ++i)
    {
      instruction_mnemonic[length - i] = 0;
    }

}

  


    



int check_for_offset(char * string, int *start_parentheses, int *disp_value)
{
  // Should return the number of bytes for the offset
  // Modified should be the index at which the parentheses start
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
	  fprintf(stderr, "Disp is greater than 4 bytes");
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
      if (*disp_value < 255)
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
regular_memory_operand construct_memory_operand(char * memory_instruction_in) // Should be a given that this is a memroy type
{
   // Needs to check for an offset first
   // SIB -----> offset(base, index, scale)
   // This does just a regular memory
   
   regular_memory_operand mem_operand;

   mem_operand.disp_length = check_for_offset(memory_instruction_in, &mem_operand.first_paren_offset, &mem_operand.disp);
   return mem_operand;
}

sib_pieces construct_sib_from_string(char *sib_instruction_in)
{
  // This just does the whole sib, knowing that it is an sib
  sib_pieces sib_returned;
  sib_returned.disp_length_in_bytes = check_for_offset(sib_instruction_in, &sib_returned.start_parentheses_index, &sib_returned.disp_value);

  int iterator = sib_returned.start_parentheses_index + 1;

  iterator = move_to_general(sib_instruction_in, iterator, '%');
  sib_returned.base_index = iterator;

  iterator = move_to_general(sib_instruction_in, iterator, '%');
  sib_returned.index_index = iterator;

  iterator = move_to_general(sib_instruction_in, iterator, ',');
  while (sib_instruction_in[iterator] == ' ')
    {
      iterator++;
    }

  if (sib_instruction_in[iterator] < 48 || sib_instruction_in[iterator] > 57)
    {
      fprintf(stderr, "Failure with the scale index base byte" );
    }
  
  sib_returned.scale = sib_instruction_in[iterator] - 48;
  sib_returned.operand = sib_instruction_in;

  return sib_returned;
  
}



int check_instruction(struct instruction_pieces *in, struct instruction_definition *defs)
{
  /* Now some requirements for instructions will be listed
     - < 2 memory operands 
    - < 2 immediates

     - If a dependency check fails for a mnemonic, try one of the nearest ones. Likely, lots of them will fail as of now
   */ 
    char * p = in->instruction_mnemonic;
  while(*p != 0) *(p++) -= 0x20;

  char copy_of_mnemonic[20] = {0};
  int length = 0;
  for (; in->instruction_mnemonic[length] != 0; ++length)
      copy_of_mnemonic[length] = in->instruction_mnemonic[length];

  int length_poststrip;

  unsigned long int ID = name_to_id(in->instruction_mnemonic);
  int index = -1;
  int strip_iterator = -1;
strip: strip_iterator++;
  if (!ID)
    {
      ID = name_to_id((in->instruction_mnemonic +8));
        for (; strip_iterator < 3; ++strip_iterator)
	  {
            rip_suffix(in->instruction_mnemonic, strip_iterator);
	    ID = name_to_id(in->instruction_mnemonic+8);
	    index = binary_lookup(ID, defs, 1);
	    if (index != -1)
                {
                    length_poststrip = length -strip_iterator;
                    break;
                }
	  }
    }

  else
    {
      for (; strip_iterator < 3; ++strip_iterator)
	  {
            rip_suffix(in->instruction_mnemonic, strip_iterator);
            ID = name_to_id(in->instruction_mnemonic);
            index = binary_lookup(ID, defs, 0 );
	    if (index != -1)
                {
                    length_poststrip = length - strip_iterator;
                    break;
                }
	  }
      
    }

  in->size = numbits_from_suffix(in->instruction_mnemonic + length_poststrip);
  ID = name_to_id(in->instruction_mnemonic);
  if (index == -1)
    {
      fprintf(stderr, "Failure to find a matching mnemonic for the opcode");
      assert(0 == 1);
    }

  else if (ID)
    {

      // Found in the shorter ones, look at the dependencies for this one and its neighbors
      int valid_neighbors[64] = { 0 };
      int valid_neighbors_number = 1;
      valid_neighbors[0] = index;
      // Check below
      for (int i = 0; defs[index - i].mnemonic == ID; ++i) // look below thje index
	{
          valid_neighbors[i] = index - i;
          valid_neighbors_number++;
	}
      
      for (int i = 0; defs[index + i].mnemonic == ID; ++i) // look above
	{
          valid_neighbors[i+valid_neighbors_number ] = index + i;
          valid_neighbors_number++;
	}


       for (int iterator = 0; iterator < valid_neighbors_number; ++iterator)
	 {
          // NOT DONE YET
	  // Will use the dependencies check function for this one
           if (assert_dependencies(in, &defs[(valid_neighbors[iterator])]))
	   {
	     return valid_neighbors_number;
	   }
	 }

       if (strip_iterator >= 2)
        return -1;
       else
           goto strip;
    }

  else
    {
      // Found in the longer ones, look at the dependencies for this one and its neighbors
      int valid_neighbors[16] = { 0 };
      int valid_neighbors_number = 0;
      
      // Check below
      for (int i = 0; defs[index - i].mnemonic == ID; ++i)
	{
	valid_neighbors[valid_neighbors_number++] = index - i;
        
	}
      // Check above 
      for (int i = 0; defs[index + i].mnemonic == ID; ++i)
	{
	valid_neighbors[valid_neighbors_number++] = index + i;
	}
      

      
      for (int iterator = 0; iterator < valid_neighbors_number; ++iterator)
        {
      
	  // Will use the dependencies check function for this one
          if (assert_dependencies(in, &defs[(valid_neighbors[valid_neighbors_number])]))
	  {
	     return valid_neighbors_number; // THE TRUTH
	  }
        }

      return -1;

    }
  
  
}


bool assert_dependencies(struct instruction_pieces *user_in, struct instruction_definition *defs)
{
  /*
    - Pass the same enum operands
    - Pass the lock check 
    - Pass the size check 
 
   */
  struct dependencies * table_in = &defs->requirements;

  bool mem_or_reg_1_changed = 0;
  bool mem_or_reg_2_changed = 0;
  bool mem_or_xmm_1_changed = 0;
  bool mem_or_xmm_2_changed = 0;

  
  if (table_in->one == mem_or_reg)
    {
      mem_or_reg_1_changed = 1;
      if (user_in->op1 == memory)
	table_in->one = memory;
      else if (user_in->op1 == reg)
	table_in->one = reg;
      else
	return 0;
    }
   if (table_in->two == mem_or_reg)
    {
      mem_or_reg_2_changed = 1;
      if (user_in->op2 == memory)
	table_in->two = memory;
      else if (user_in->op2 == reg)
	table_in->two = reg;
      else
	return 0;
    }

   if (table_in->one == xmm_or_mem)
     {
       mem_or_xmm_1_changed = 1;
       if (user_in->op1 == xmm)
	 table_in->one = xmm;
       else if (user_in->op1 == memory)
	 table_in->one = memory;
       else
	 return 0;
     }

    if (table_in->two == xmm_or_mem)
     {
       mem_or_xmm_2_changed = 1;
       if (user_in->op2 == xmm)
	 table_in->two = xmm;
       else if (user_in->op2 == memory)
	 table_in->two = memory;
       else
	 return 0;
     }
  
  
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



  
 if (!check_sizes(user_in->size, table_in->allowed_sizes))
    {
      return 0;
    }
  
  if (!check_sizes(user_in->size, table_in->allowed_sizes))
    {
      return 0;
    }

  if (mem_or_reg_1_changed)
    table_in->one = mem_or_reg;
  if (mem_or_reg_2_changed)
    table_in->two = mem_or_reg;
  if (mem_or_xmm_1_changed)
    table_in->one = xmm_or_mem;
  if (mem_or_xmm_2_changed)
    table_in->two = xmm_or_mem;
    
  
  return 1;
}

 
enum Basic_Operands user_string_to_operand(const char *string_in, int start_index)
{
  // CAN RETURN: sib, memory, register, immediate 

  
  // Needs to be called after the offset is checked for
  

  
  if (string_in[start_index] == '(')
    {
      int reg_counter = 0;
      for (; string_in[start_index] != ')'; ++start_index)
	{
	  if (string_in[start_index] == '%')
	    {
	      ++reg_counter;
	    }
	}

      if (reg_counter == 2)
	{
	  return sib;
	}

      else if (reg_counter == 1)
	{
	  return memory;
	}

      else
	{
	  fprintf(stderr, "Failure to parse the memory addressing operand");
	  assert( 0 == 1);
	}
    }

  else if (string_in[start_index] == '%')
    {
      
      return user_fallback(string_in + start_index + 1);
    }


  else if (string_in[start_index] == '$')
    {
      return immediate;
    }

  else
    {
      fprintf(stderr, "operand not found" );
      assert( 0 == 1);
    }
  
}


char * copy_until_space(char * old)
{
  char * to_be_returned = malloc(25);

  memset(to_be_returned, 0, 25);
  for (int i = 0; old[i] != 0; ++i)
    {
      to_be_returned[i] = old[i];
    }
  return to_be_returned;
}



