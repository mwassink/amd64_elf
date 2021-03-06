
#include <stdio.h>
#include <stdlib.h>
#include "../include/get_instructions.h"
#include <string.h>
#include "../include/utilities.h"



//static int prefixes[30] = {0x26, 0x2e, 0x36, 0x3e, 0x40, 0x41, 0x42, 0x43,
//                         0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d,
//                         0x4e, 0x4f, 0x64, 0x65, 0x66, 0x67, 0x9b, 0xf0, 0xf2, 0xf3};

int string_restrict(char * input)
{
  int length = 0;

  while (input )
    {
      input++;
      if (9 == ++length)
        return 1;
    }

  return 0;
}

void pool_memory(struct instruction_format *instr_ptr, char * char_pool_begin)
{
    
    instr_ptr->prefix = 0;
    instr_ptr->prefix_OF = 0;
    instr_ptr->primary_opcode = 0;
    instr_ptr->secondary_opcode = 0;
    instr_ptr->reg_opcode_field = 0;
    instr_ptr->documentation = 0;
    instr_ptr->mode = 0;
    instr_ptr->ring_level = 3; // let it be used by all by default
    instr_ptr->lock_prefix = 0;
    instr_ptr->mnemonic = char_pool_begin + 16;
    instr_ptr->op1 = char_pool_begin + 32;
    instr_ptr->op2 = char_pool_begin + 48;
    instr_ptr->op3 = char_pool_begin + 64;
    instr_ptr->op4 = char_pool_begin + 80;
    instr_ptr->iext = char_pool_begin + 96;
    instr_ptr->tested_flags = char_pool_begin + 112;
    instr_ptr->modif_flags = char_pool_begin + 128;
    instr_ptr->def_flags = char_pool_begin + 144;
    instr_ptr->undef_flags = char_pool_begin + 160;
    instr_ptr->flag_values = char_pool_begin + 176; // up to 176
    instr_ptr->pooled = -1;
    instr_ptr->fields = char_pool_begin + 192;
    
    memset(instr_ptr->mnemonic - 16, 0, 208);
    
     // so that the pointer does not get lost and leaked
}  
  



unsigned char byte_hexstring_to_int(char * input)
{
    unsigned short int offset = 0;
    unsigned char total = 0;
    int debug_flag = 0;
get_value:
    switch (*input)
        {
        case '0':
            total += 0;
            break;
        case '1':
            total += 1;
            break;
        case '2':
            total += 2;
            break;
        case '3':
            total += 3;
            break;
        case '4':
            total += 4;
            break;
        case '5':
            total += 5;
            break;
        case '6':
            total += 6;
            break;
        case '7':
            total += 7;
            break;
        case '8':
            total += 8;
            break;
        case '9':
            total += 9;
            break;
        case 'A':
            total += 10;
            break;
        case 'B':
            total += 11;
            break;
        case 'C':
            total += 12;
            break;
        case 'D':
            total += 13;
            break;
        case 'E':
            total += 14;
            break;
        case 'F':
            total += 15;
            break;
        default:
            printf("Error in function byte_hexstring_to_int converting ascii\n");
            ++debug_flag;
            return -1;
        }
    input++;
    if (0 == offset++)
        {
            total =  total<<4;
            goto get_value;
        }

    return total;
}

  







void gather_instruction(struct instruction_format *instr, FILE * fileptr, int * catches)
{
    // parse the small flags first
    if (instr->pooled != -1)
      return;

    int counter = 0;
    int offset = 0;

    char temp[17];

    char full_instruction[255] = { 0 };
    
    int full_instruction_counter = 0;
    char out;

    for (; counter < 10; )
        {
        
            out = fgetc(fileptr);
            if (out == '\n')
            {
                printf("big problem");
		(*catches) = *catches + 1;
            }
            full_instruction[full_instruction_counter++] = out;
            if (out == ',')
                {
                    counter += 1;
                    offset = 0;
                    continue;
                handle_po_plus:
                    out = fgetc(fileptr);
                    out = fgetc(fileptr);
                    counter += 1;
                    continue;

                }
            switch (counter)
                {
                case 0:
                    if (offset == 0) //expecting another number
                        {
                            temp[0] = out;
                            offset++;
                        }
                    else
                        {
                            temp[1] = out;
                            offset = 0;
                            instr->prefix = byte_hexstring_to_int(temp);

                        }
                    break;
                case 1:
                    instr->prefix_OF = 0x0F;
                    break;
                case 2:
                    if (offset == 0)
                        {
                        if (out == '+')
                        {
                            goto handle_po_plus;
                        }
                          temp[0] = out;
                          offset++;
                        }
                    else
                        {
                          temp[1] = out;
                          offset = 0;
                          
                          instr->primary_opcode = byte_hexstring_to_int(temp);
                          
                        }
                      break;
                case 3:
                    if (offset == 0)
                        {
                            temp[0] = out;
                            offset++;
                        }
                    else
                        {
                            temp[1] = out;
                            offset = 0;
                            instr->secondary_opcode = byte_hexstring_to_int(temp);
                        }
                    break;
                case 4:
		  if (out == 'r')
		    break;
		  else
		    {
		      instr->reg_opcode_field = atoi(&out);
		      break;
		    }
                case 5:
                    //printf("There are no codes introduced with the processor for this one");
                    break;
                case 6:
                    instr->documentation = out;
                    break;
                case 7:
                    instr->mode = out;
                    break;
                case 8:
                    instr->ring_level = out;
                    break;
                case 9:
                    instr->lock_prefix = out;
                    break;
                }
        }
        char * current = NULL;
        offset = 0;
        for (; counter < 21;)
            {
            
            char out = fgetc(fileptr);
            if (out == '\n')
            {
                printf("big problem");
                (*catches) = *catches + 1;
            }
            full_instruction[full_instruction_counter++] = out;
                if (out == ',')
                    {
                        if (current)
                            current[offset] = 0;
                        counter++;
                        offset = 0;
                        current = NULL;
                        continue;
                    }
                switch (counter)
                    {
                    case 10:
                        instr->mnemonic[offset] = out;
                        current = instr->mnemonic;
                        ++offset;
                        break;
                    case 11:
                        instr->op1[offset] = out;
                        current = instr->op1;
                        offset++;
                        break;
                    case 12:
                        instr->op2[offset] = out;
                        current = instr->op2;
                        offset++;
                        break;
                    case 13:
                        instr->op3[offset] = out;
                        current = instr->op3;
                        offset++;
                        break;
                    case 14:
                        instr->op4[offset] = out;
                        current = instr->op4;
                        offset++;
                        break;
                    case 15:
                        instr->iext[offset] = out;
                        current = instr->iext;
                        offset++;
                        break;
                    case 16:
                        instr->tested_flags[offset] = out;
                        current = instr->tested_flags;
                        offset++;
                        break;
                    case 17:
                        instr->modif_flags[offset] = out;
                        current = instr->modif_flags;
                        offset++;
                        break;
                    case 18:
                        instr->def_flags[offset] =out;
                        current = instr->def_flags;
                        offset++;
                        break;
                    case 19:
                        instr->undef_flags[offset] = out;
                        current = instr->undef_flags;
                        offset++;
                        break;
                    case 20:
                        instr->flag_values[offset] = out;
                        current = instr->flag_values;
                        offset++;
                        break;

                    }
            }

            if (instr->prefix_OF == 0)
              instr->ID = name_to_id(instr->mnemonic); // this is a single byte opcode

            else if (!string_restrict(instr->mnemonic)) // == 0 which means it passed the check
              instr->ID = name_to_id(instr->mnemonic);

            else
              instr->ID = 0;

            
            while (out != '\n')
            {
                out = fgetc(fileptr);
            }
            *catches = *catches + 1;

}

void write_instruction_stdout(struct instruction_format *instr)
{
  printf("Prefix: %c \n", instr->prefix);
  printf("OF?%x \n", instr->prefix_OF);
  printf("Primary opcode: %X \n", instr->primary_opcode);
  printf("Secondary opcode %X \n", instr->secondary_opcode);
  printf("Reg Opcode Field: %c \n", instr->reg_opcode_field);
  printf("Documentation: %c \n", instr->documentation);
  printf("Mode: %c \n", instr->mode);
  printf("Ring Level %c \n", instr->ring_level);
  printf("Lock Prefix: %c\n", instr->lock_prefix);

  printf("Mnemonic: %s \n", instr->mnemonic);
  printf("op1 %s \n", instr->op1);
  printf("op2 %s \n", instr->op2);
  printf("op3 %s \n", instr->op3);
  printf("op4 %s \n", instr->op4);
  printf("iext %s \n", instr->iext);
  printf("tested_flags %s \n", instr->tested_flags);
  printf("modif flags %s \n", instr->modif_flags);
  printf("def_flags %s \n", instr->def_flags);
  printf("undef_flags %s \n", instr->undef_flags);
  printf("flag_value %s \n", instr->flag_values);
  printf("fields (currently not finished)%s \n",instr->fields );
}


void bubble_sort_instructions(struct ID_instr_pair * pair_array, int size)
{
  

  struct ID_instr_pair temp;
  temp.instr_ptr = NULL;
  temp.ID = 0;

  for (int i = 0; i < size; ++i)
    {
      while(pair_array[i].ID > pair_array[i-1].ID)
	{
	  temp = pair_array[i];
	  pair_array[i] = pair_array[i-1];
	  pair_array[i-1] = temp;
	  i -= 1;
	}
    }
  
}



struct instruction_format*  pool_struct_memory(int instructions)
{
  // This will return a pointer to a pool of roughly 1000 instructions
  struct instruction_format sample;
  struct instruction_format* pool_ptr = (struct instruction_format*)malloc(instructions*sizeof(sample));
  return pool_ptr;
}


char * pool_character_memory(int instructions)
{
  char * char_ptr = (char *)malloc(instructions*16*11);
  return char_ptr;
}

unsigned int map_register_to_ID(char * reg)
{
  // Unsigned char and char will look the same as long as it is not negative
  // Stored in 2's complement
  unsigned int returned_value = 0;

  returned_value |= reg[0];
  returned_value <<=4;
  returned_value |= reg[1];
  returned_value <<=4;
  returned_value |= reg[2];
  returned_value <<=4;
  returned_value |= reg[3];

  return returned_value;
}




void pull_instructions_and_rewrite()
{
  // The first thing that needs to be done is to give space for the structs and the characters
  char * memory_pool = pool_character_memory(1000);
  struct instruction_format* instructions = pool_struct_memory(1000);
  struct ID_instr_pair* pair_array_ptr  = malloc(16000);
  /* Available memory
     
     memory_pool = 176000
     instructions = 112000
   */
  //int char_step = 176;
  FILE * fptr;

  fptr = fopen("instructions.csv", "r");
  for (int i = 0; i < 1000; ++i)
    {
      struct instruction_format *current_ptr = instructions+i; // change this later
      pool_memory(current_ptr, memory_pool+176*i);
      gather_instruction(current_ptr, fptr, NULL);
      write_instruction_stdout(current_ptr);
    }

  //Make the instruction, ID pairs
  for (int k = 0; k < 1000 ; k++)
    {
      pair_array_ptr[k].ID = instructions[k].ID;
      pair_array_ptr[k].instr_ptr = instructions+k;
    }

  bubble_sort_instructions(pair_array_ptr, 1000);


  free(memory_pool);
  free(instructions);
  free(pair_array_ptr);
  // After the data structures are formed
}

















