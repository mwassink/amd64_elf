#ifndef MODRM_H
#define MODRM_H

#include <stdbool.h>
// The ModR/M byte depends on several factors and input registers
// The Rex determines the registers that will get chosen
// This is supposed to assemble instructions, so I only need the input registers

struct __instruction
{
  // This is an instruction as a bunch of bytes
  int length;
  unsigned char * instruction;
};


struct temprm
{
  unsigned int first : 3;
  unsigned int second : 3;
  unsigned int mod : 2;
};

// It is up to the instruction to decide whether it needs to be encoded with this
// It should not need to know which rex is needed as an input, but rather it should figure it out
struct __instruction encode_registers_rm( char * op1,  char * op2, bool op1_rm );

#endif
