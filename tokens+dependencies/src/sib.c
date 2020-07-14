
#include <stdio.h>
#include "../include/modrm.h"
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
struct sib
{
  // The first thing needed is the scale
  // Next thing needed is the base register
  int mod_prev;
  int scale;
  char * base; // cannot be rbp
  char * index; 
};

inline bool sib_reg_string_compare (char  * in, char  * in2) // before, just cast the address to one of type int, compiler will know what to do 
{
    int* lhs = (int*)in;
    int* rhs = (int*)in2;
    // Mask the last bit if it is a ), this would mean it would have length 3
    // By masking the last bit, I know that a comparison against a null character will work
    // However, other ones might need this
    if (((*in) & 0x000000FF) == ')')
    {
        *lhs &= 0xFFFFFF00; // Not a big deal if the memory is altered 
        return *lhs = *rhs;
    }
    else
        return *lhs = *rhs;
}

// NOTE: I have to decide whether to process the whole instruction at once or to put it into a struct and operate on it 
// Another note: There does not need to be a table for 01 and 10
// The mod 00 is unique in that it will allow for there to be no base register AND no index register

// Another note: stack pointer as an index does not work, cannot be done
// bp and r13 are unique for not existing on a mod 00. They should NOT BE CALLED WITH NO DISPLACEMENT, even if there is none
// Instead of bp and r13 on mod 00, there is simply just an index and a 32 bit displacement


int sib_rexr_table(char * in)
{
  if ( sib_reg_string_compare(in, "%r8") || sib_reg_string_compare(in, "%r8d"))
    return 0;

  else
    return 1;
}
int sib_regular_table(char * in);
/*
int table_base_and_index(char * in) // argument of the form %rax
{
  // Look for one of the newer GPRs first
  if (needs_rex_r(in))
    sib_rexr_table(in);

  else
    sib_regular_table(in);
    
    
}
*/



/*
int sib_from_knowns(char * base, char * index, int scale)
{
  // somewhere down the line, if the user uses a scale other than 1 2 4 or 8 then the assembler has to  throw a fit
  // This function will not as it expects processed arguments


  
}
*/	      


