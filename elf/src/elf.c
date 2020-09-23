// Writes a 64 bit elf header for amd64 unix
#include <stdio.h>
typedef unsigned char uchar;
typedef unsigned char BYTE;
#define MAX_LABELS 200


typedef struct 
{
  unsigned int st_name; // the index into the o files string table
  // for main.foo would have 0 and then 6
  unsigned char st_info;
  unsigned char st_other;
  short unsigned int st_shndx; // holds the relevant section header table index 
  long unsigned int st_value; // where does this start?
  long unsigned int st_size; // how big is this?

} Elf64_Sym;


typedef struct
{
  
  int current_label_index;
  int corresponding_starts_for_labels[MAX_LABELS]; // same thing as start
  char string_for_jumps[MAX_LABELS][50]; // Must correspond to the jump table exactly
  BYTE *instructions;
  int bytes_written;
  



}  symbols_information;

void write_elf_magic(FILE *fp)
{
  unsigned char arr[4] = {0x7F, 0x45, 0X4c, 0x46 };
  fwrite(arr, 1, 4, fp);
  return;
}

void write_bits_endianness_ver(FILE *fp)
{
  uchar arr[3] = {2,1, 1};
  fwrite(arr,1,3,fp);
  return;
}

void write_e_ident(FILE *fp)
{
  uchar arr[9] = {0};
  fwrite(arr,1,9,fp);
  return;
}

void write_type_machine(FILE *fp)
{
  short arr[2] = {1,3};
  fwrite(arr,2,2, fp);
  return;
}

void write_version(FILE *fp)
{
  int i = 1;
  fwrite(&i, 4, 1, fp);
  return;
}

void write_entry(FILE *fp, int entry)
{
  fwrite(&entry, 4, 1, fp);
}

void write_phoff(FILE *fp, long int phoff)
{
  fwrite(&phoff, 8, 1, fp);
}

void write_shoff(FILE *fp, long int shoff)
{
  fwrite(&shoff, 8, 1, fp);
}

void write_flags(FILE *fp, int flags)
{
  fwrite(&flags, 4, 1, fp);
}

void write_header_size(FILE *fp, short header_size)
{
  fwrite(&header_size, 2, 1, fp);
}

void write_program_header_entry_size(FILE *fp, short header_size)
{
  fwrite(&header_size, 2, 1, fp);
}

void write_num_pheaders(FILE *fp, short num_entries)
{
  fwrite(&num_entries, 2, 1, fp);
}

void write_section_header_size(FILE *fp, short shentsize)
{
  fwrite(&shentsize, 2, 1, fp);
}

void write_num_sheaders(FILE *fp, short num_entries)
{
  fwrite(&num_entries, 2, 1, fp);
}

void write_index_shentry(FILE *fp, short index)
{
  fwrite(&index, 2, 1, fp);
}

void extract_symbol(Elf64_Sym *target, symbols_information *src, int current_index, int last_index)
{
  if (current_index == 0)
    {
      target->st_value = 0;
    }

  else
    {
      target->st_value = src->corresponding_starts_for_labels[current_index];
    }
  
  if (current_index != last_index)
    target->st_size = src->corresponding_starts_for_labels[current_index + 1] - target->st_value;
  else
    target->st_size = src->bytes_written - src->corresponding_starts_for_labels[current_index];
}

// Returns the number of entries in the table for now 
// Should probably return a little more than that as this probabky needs more
// Need a string table that corresponds to the symbol table for the linker to link off of 
int initialize_sym(Elf64_Sym **ptr_to_symbol_array, symbols_information *info, char * strtab  )
{
  // The string table will have to be continuous in a pool
  // The number of symbols to be written should be in the info, but with one less than the current index
  int num_entries = info->current_label_index;
  Elf64_Sym * table = (Elf64_Sym *)malloc(num_entries * sizeof(Elf64_Sym));
  *ptr_to_symbol_array = table;
  
  
  
}
