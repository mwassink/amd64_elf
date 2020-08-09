#ifndef INTRUCTION_DEFINITION_H
#define INTRUCTION_DEFINITION_H
#include "dependencies.h"

// Look at this to make sure that it is packed properly
struct instruction_definition
{
  // This will act as the definitioon for the function, given the one earlier from get_instructions.h
  // These are not unique and do not change with user input
  struct dependencies requirements;
  unsigned long int mnemonic; // Useful for finding the instruction
  char prefix; // Useful for writing this, whether it has a prerfix or not
  char opcode; // necessary for writing the opcode into the file
  char secondary_opcode; // Necessary if this is included
  char prefix_OF; // Don't do a bool just the prefix


};



#endif // INTRUCTION_DEFINITION_H