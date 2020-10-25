
#include <stdio.h>
#include "../include/modrm.h"
#include <assert.h>
#include "../include/sib.h"
#include <stdbool.h>
#include "../include/utilities.h"
#include <stdlib.h>
// Example with the sib indexing

// This is used for addressing between registers
// Ex. leaq 4(%rsi, %rdi, 8), %rsi
// Need rex prefix because this is by default a 32 bit operation
// Rex = 0100 + WRXB
// w = 1 because we need 64 bits
// r = 0 because we do not need anything in  modrm 
// x = 0 because rdi is not one of the new ones
// b = 0 because rsi is not one of the new ones
// 01001000 = 0x40 + 0x8 = 0x48
// Need the actual instruction 8d
// need the ModRM to specify the target operands
// ModRM: 01 memory and an 8 bit displacement follows 100 Sib Follows 110 rsi is the target
// 01110100 = 0x74
// 48 8d 74 fe 04
// ss = 11 (scale) 101 (rsi) 111 (rdi) = base
// 1111 -> ss + scale first two (base is less significant than the scale) 1110 ->
// The last bit of the scale + the base (the base in this case is the first to come)
// the base is rsi
// offset is 4 (the immediate)

// BASE comes first
// the INDEX comes second
// the third thing to come is the SCALE


// In terms of the byte itself there is
// ss  | index | base 
// 7 6 | 5 4 3 | 2 1 0  in terms of signifuicance where the more significant is a higher number



// The sib is called upon when there is a special displacement used for the indexing, like movq -4(%rax, 4, %rbx)
// We have 4 scales of interest: 1, 2, 4, 8
// The mod before impacts how the sib is done, specically with the displacement
// Mod 00:
// Most of these have no displacement, but they allow for indexing
// Not all of them do though
// rbp, specifally, does not exist as a base for the sib, neither does r13. This is just a disp32 for mod 00 along with the disp
// rsp is fake for the index
int switch_on_sib_scale(int scale )
{
  // could use log but that will have doubles and stuff
  switch(scale)
    {
    case 1:
      return 0;
    case 2:
      return 1;
    case 4:
      return 2;
    case 8:
      return 3;
    default:
      printf("Improper scale used for the SIB. 1,2,4,8 are allowed");
      exit(1);
    }
}
 
int get_mod_from_disp(int disp)
{
  switch(disp)
    {
    case 0:
      return 0;
    case 1:
      return 1;
    case 4:
      return 2;
    default:
      printf("Invalid displacement");
      exit(1);
    }
}


unsigned char make_sib_byte(struct sib sib_operand)
{
  unsigned char to_be_returned = 0;

  if (sib_operand.scale > 8)
    sib_operand.scale -= 48;

  
  
  to_be_returned = switch_on_sib_scale(sib_operand.scale);
  to_be_returned <<= 3; // make space for the next one

  if (needs_rex_r(sib_operand.operand + sib_operand.index_index))
    to_be_returned |= sib_rexr_table_index(sib_operand.operand + sib_operand.index_index) ;

  else
    to_be_returned |= sib_regular_table_index(sib_operand.operand + sib_operand.index_index );

  to_be_returned <<= 3;
  
  if (needs_rex_r(sib_operand.operand + sib_operand.base_index))
    to_be_returned |= sib_rexr_table_base(sib_operand.operand + sib_operand.base_index, sib_operand.disp_length_in_bytes);

  else
    to_be_returned |= sib_regular_table_base(sib_operand.operand + sib_operand.base_index, sib_operand.disp_length_in_bytes);
  
  return to_be_returned;
}






bool sib_reg_string_compare (char  * in, char  * in2, bool long_check) // before, just cast the address to one of type int, compiler will know what to do 
{
    int* lhs = (int*)in;
    int* rhs = (int*)in2;
    // Mask the last bit if it is a ), this would mean it would have length 3
    // By masking the last bit, I know that a comparison against a null character will work
    // However, other ones might need this
    if (long_check)
    {
      for (int i = 0; i <3; ++i)
	{
	  if (in[i] != in2[i])
	    return false;
	}
      return true;
    }
    else
      return (*lhs == *rhs);
}

// NOTE: I have to decide whether to process the whole instruction at once or to put it into a struct and operate on it 
// Another note: There does not need to be a table for 01 and 10
// The mod 00 is unique in that it will allow for there to be no base register AND no index register

// Another note: stack pointer as an index does not work, cannot be done
// bp and r13 are unique for not existing on a mod 00. They should NOT BE CALLED WITH NO DISPLACEMENT, even if there is none
// Instead of bp and r13 on mod 00, there is simply just an index and a 32 bit displacement


int sib_rexr_table_base(char * in, int mod) // THe mod should be known for the r13 
{
  if (sib_reg_string_compare(in, "%r8", 1) || sib_reg_string_compare(in, "%r8d", 0))
        return 0;

  else if (sib_reg_string_compare(in, "%r9", 1) || sib_reg_string_compare(in, "%r9d", 0))
        return 1;

  else if (sib_reg_string_compare(in, "%r10", 0))
        return 2;

  else if (sib_reg_string_compare(in, "%r11", 0))
        return 3;

  else if (sib_reg_string_compare(in, "%r12", 0))
        return 4;

  else if (sib_reg_string_compare(in, "%r13", 0))
    {
      if (mod == 0)
        {
	  fprintf(stderr, "R13 cannot be used as a base with 0 displacement");
	  assert(0 == 1);

        }
        else
            return 5;
    }
  else if (sib_reg_string_compare(in, "%r14", 0))
        return 6;

  else if (sib_reg_string_compare(in, "%r15", 0))
        return 7;

    else
    {
        fprintf(stderr, "End of control for sib_regular_table_index(char* in, int mod), no reg found");
        assert(0 == 1);
    }

}
int sib_regular_table_base(char* in, int mod)
{
  if (sib_reg_string_compare(in, "%rax", 0))
        return 0;

  else if (sib_reg_string_compare(in, "%rcx", 0))
        return 1;

  else if (sib_reg_string_compare(in, "%rdx", 0))
        return 2;

  else if (sib_reg_string_compare(in, "%rbx", 0))
        return 3;

  else if (sib_reg_string_compare(in, "%rsp", 0))
        return 4;

  else if (sib_reg_string_compare(in, "%rbp", 0))
    {
        if (mod == 0)
        {
            fprintf(stderr, "rbp cannot be used as a base with 0 displacement");
            assert(0 == 1);

        }
        else
            return 5;
    }

  else if (sib_reg_string_compare(in, "%rsi", 0))
        return 6;

  else if (sib_reg_string_compare(in, "%rdi", 0))
        return 7;
 
    else
    {
        fprintf(stderr, "End of control for sib_regular_table_index(char* in, int mod), no reg found");
        assert(0 == 1);
    }
}

int sib_rexr_table_index(char* in)
{
  if (sib_reg_string_compare(in, "%r8", 1) || sib_reg_string_compare(in, "%r8d", 0))
        return 0;

  else if (sib_reg_string_compare(in, "%r9", 1) || sib_reg_string_compare(in, "%r9d", 0))
        return 1;

  else if (sib_reg_string_compare(in, "%r10", 0))
        return 2;

  else if (sib_reg_string_compare(in, "%r11", 0))
        return 3;

  else if (sib_reg_string_compare(in, "%r12", 0))
        return 4;

  else if (sib_reg_string_compare(in, "%r13", 0))
        return 5;

  else if (sib_reg_string_compare(in, "%r14", 0))
        return 6;

  else if (sib_reg_string_compare(in, "%r15", 0))
        return 7;

    else
    {
        fprintf(stderr, "End of control for sib_regular_table_index(char* in, int mod), no reg found");
        assert(0 == 1);
    }
}

int sib_regular_table_index(char* in)
{
  if (sib_reg_string_compare(in, "%rax", 0))
        return 0;

  else if (sib_reg_string_compare(in, "%rcx", 0))
        return 1;

  else if (sib_reg_string_compare(in, "%rdx", 0))
        return 2;

  else if (sib_reg_string_compare(in, "%rbx", 0))
        return 3;

  else if (sib_reg_string_compare(in, "%rbp", 0))
        return 5;

  else if (sib_reg_string_compare(in, "%rsi", 0))
        return 6;

  else if (sib_reg_string_compare(in, "%rdi", 0))
        return 7;

    else
    {
        fprintf(stderr, "End of control for sib_regular_table_index(char* in, int mod), no reg found");
        assert(0 == 1);
    }
}




