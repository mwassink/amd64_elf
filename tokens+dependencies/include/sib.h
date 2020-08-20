#include <stdio.h>
#include "modrm.h"
#include <assert.h>
#include "customtypes.h"




void full_sib_instruction(struct sib sib_in, int mod);
inline bool sib_reg_string_compare(char* in, char* in2);
int sib_rexr_table_base(char* in, int mod);
int sib_regular_table_base(char* in, int mod);
int sib_rexr_table_index(char* in, int mod);
int sib_regular_table_index(char* in, int mod);

