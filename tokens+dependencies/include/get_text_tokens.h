#ifndef GET_TEXT_TOKENS_H
#define GET_TEXT_TOKENS_H

struct Register
{
  int ID;
  unsigned short size;
};

void init_32_64_bit_old_register_from_string(char * input_string, struct  Register * input_register );

void init_16_bit_old_register_from_string(char * input_string, struct Register * input_register);

int init_new_register_from_string(char * input_string, struct Register * input_register, int register_name_length);

int initialize_register_ID( char * null_term_reg);

int * init_register_tokens();

char * other_strings();






















#endif
