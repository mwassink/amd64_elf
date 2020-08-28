 #ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H
#include <stdbool.h>

enum Basic_Operands {none, immediate, memory, reg, sib, mem_or_reg, mm, xmm, stack_reg, segment, implied_reg,
		     flag, empty, rflags, memory_offset, relative_offset, push_or_pop, xmm_or_mem, rax,
                     eflags, rel, not_found};

enum section_types {none, text, bss, data, invalid_section_label};
// These are necessary for the instruction, given the mnemonic or the ID

enum Sections {_text, _bss, data};


struct available_sizes
{
  bool one_byte;
  bool byte_high;
  bool byte_2;
  bool byte_4;
  bool byte_8;
  bool byte_16;
};

struct dependencies
{
  // NEEDS INIT FUNCTION
  bool lockable; // Easy one to see. If there calls for a lock prefix, then look if a lock is allowed
  enum Basic_Operands one;
  enum Basic_Operands two;
  int highest_ring; // User space would be the highest, 3
  struct available_sizes allowed_sizes;
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
  int disp_length_in_bytes;
  int disp_value;
  int scale;
  char *operand; // cannot be rbp. This denotes the start of the operand. Could be "-64(%rbp, rax, 2 )"
  int start_parentheses_index; // relative to the start of the string for the operand
  int base_index;  // relative to the start of the string for the operand
  int index_index;  // relative to the start of the string for the operand
};

// This is for when this actually gets written in binary 
struct sib_byte
{
  
    int ss : 2;
    int index : 3;
    int base : 3;
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
  // Regular memory 
  int first_paren_offset; // This tells how far along the operand string (like 10(%rax)) ther first parenthese is
  int disp_length;
  unsigned int disp;
  bool is_mem;
};

struct symbols_information
{
  int current_line;
  int current_label;
  int current_instruction_number;
  int * jump_instructions; // lines that have labels
  char ** string_for_jumps; // Must correspond to the jump table exactly
  int * lengths_labels;
  bool _start_found; // entry into the program
  // NOT COMPLETE


};

struct Elf64_Sym
{
  unsigned int st_name;
  unsigned char st_info;
  unsigned char st_other;
  short unsigned int st_shndx;
  long unsigned int st_value; // where does this start?
  long unsigned int st_size; // how big is this?


  
};

struct label_info
{
  int bytes;
  int written_before;
  char *string_name; // For linking later
  // visibility??
  // function info??
  
  
};


#endif
