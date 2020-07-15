#include <stdio.h>
#include "./modrm.h"
#include <assert.h>



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

void full_sib_instruction(struct sib sib_in, int mod);
inline bool sib_reg_string_compare(char* in, char* in2);
int sib_rexr_table_base(char* in, int mod);
int sib_regular_table_base(char* in, int mod);
int sib_rexr_table_index(char* in, int mod);
int sib_regular_table_index(char* in, int mod);

