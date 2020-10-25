#include <stdio.h>
#include "../include/convert_instruction.h"
#include <assert.h>

int main()
{
  // Try to match the binary for the first few and see if it works
  struct instruction_definition def;

  struct instruction_format test_format;


  char * test_pool = malloc(250);
  pool_memory(&test_format, test_pool);
  test_format.ID = name_to_id("PUNPCKHDQ");
  test_format.mnemonic = "PUNPCKHDQ";
  test_format.primary_opcode = 106;
  test_format.op1 = "xmm";
  test_format.op2 = "xmm/m128";
  test_format.prefix = 0x66;
  test_format.prefix_OF = 0x0F;
  test_format.fields = 0; // 'r'
  test_format.ring_level = 3;

  convert_instruction(&def, &test_format);
  
  assert(def.mnemonic == 0);
  assert(def.opcode == 0x6A);
  assert(def.prefix == 0x66);
  assert(def.prefix_OF == 0x0F);
  assert(def.requirements.highest_ring == 3 ); // not privileged by default
  assert(def.requirements.lockable == 0);
  assert(def.requirements.max_size == 16);
  assert(def.requirements.one == xmm);
  assert(def.requirements.two == xmm_or_mem);

  printf("Test passed for PUNPCKHDQ");
  
  


  
}
