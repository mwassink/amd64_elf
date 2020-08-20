#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H
#include <stdbool.h>

enum Basic_Operands {immediate, memory, reg, sib, mem_or_reg, mm, xmm, stack_reg, segment, implied_reg,
		     flag, empty, rflags, memory_offset, relative_offset, push_or_pop, xmm_or_mem};

enum section_types {text, bss};
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

struct instruction_format {
    // might have alignment issues, be careful
  int pooled;
    unsigned char prefix; /* 0 if there is no prefix */
    int prefix_OF;
    unsigned char primary_opcode; /* 0 if this is a prefix or does not have one */
    unsigned char secondary_opcode; /* 0 if this does not exist */
    char reg_opcode_field; /* 0 if this is not specified	*/
    unsigned char documentation; // below this should all be 1 normal letter so a signed char should be fine
    unsigned char mode;
    char ring_level;
    unsigned char lock_prefix;
 
    char *mnemonic; //16

    char *op1; //16
    char *op2; //16
    char *op3; //16
    char *op4; //16
    char *iext; //16
    char *tested_flags; //16
    char *modif_flags; //16
    char *def_flags; //16
    char *undef_flags; //16
    char *flag_values; //16
    char *fields; //5
    unsigned long int ID;
};

struct ID_instr_pair
{
  struct instruction_format * instr_ptr;
  unsigned long int ID;
};

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


struct sib
{
    // The first thing needed is the scale
    // Next thing needed is the base register
    int mod_prev;
    int scale;
    char* base; // cannot be rbp
    char* index;
};

struct sib_byte
{
    int ss : 2;
    int index : 3;
    int base : 3;
};

struct sib_return_info
{
    int displacement;
    struct sib_byte sib_returned;
};




struct instruction_pieces
{
  char * instruction_mnemonic;
  long unsigned int instruction; // This will match the table which allows for a quick search
  enum Basic_Operands op1;
  int op1_size;
  char * op1_mnemonic;
  enum Basic_Operands op2;
  int op2_size;
  char * op2_mnemonic;
  int size;
  bool wants_lock;
};


struct memory_op_info
{
  int disp_offset;
  int disp_length;
  int disp;
  int sib_scale; // -1 if not available
  int reg1_off, reg2_off; // -1 if the register does not exist
  bool sib; // Good easy way to check for the sib byte 
};



#endif
