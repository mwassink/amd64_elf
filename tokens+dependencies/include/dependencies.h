#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H
#include <stdbool.h>
enum Basic_Operands {immediate, memory, reg, sib, mem_or_reg, mm, xmm, stack_reg, segment, implied_reg,
		     flag, empty, rflags, memory_offset, relative_offset, push_or_pop, xmm_or_mem};

// These are necessary for the instruction, given the mnemonic or the ID
struct dependencies
{
  // NEEDS INIT FUNCTION
  bool lockable; // Easy one to see. If there calls for a lock prefix, then look if a lock is allowed
  enum Basic_Operands one;
  enum Basic_Operands two;
  int highest_ring; // User space would be the highest, 3
  int max_size; // In BYTES
};
  














#endif
