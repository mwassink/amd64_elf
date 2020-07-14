#ifndef MACHINE_INSTRUCTION_H
#define MACHINE_INSTRUCTION_H
#include <stdbool.h>






enum modes { Real, Protected, bit64, smm};

struct instruction_attributes
{
  int ring;
  bool lockable;
  int mode;
  enum 
  enum operand_types  operand2_allowed[64];
  enum modes allowed_modes[4];
};


struct machine_instruction{

  unsigned char legacy[4];
  bool  legacy_exists;
  unsigned char opcode[4];
  int opcode_length;
  unsigned char rex; // Includes MODRM and SIB
  bool rex_not_needed;
  bool modrm_not_needed;
  bool sib_not_needed;
  int displacement;
  unsigned char immediate[8];
  int immediate_length;
  char * identifier;
  struct instruction_attributes attributes;
  
};


struct rex
{
  int fixed : 4; // 0100
  int w : 1; // necessary for the 64 bit if not default
  int r : 1; // mod r/m second sib first
  int x : 1; // sib second
  int b : 1; // sib second
};

struct modrm
{
  int mod : 2;
  int reg : 3;
  int rm : 3;
  
};

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
struct sib
{
  int scale : 2; // Indicates the register to use
  int index : 3;
  int base : 3;
};




#endif
