#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned long int   Elf64_Addr;
typedef unsigned int        Elf64_Word;
typedef unsigned long int   Elf64_Off;
typedef unsigned short int  Elf64_Half;
typedef int                 Elf64_Sword;
typedef unsigned long int   Elf64_Xword;
typedef long int            Elf64_Sxword;
// Defines structs and functions for reading an ELF file 

typedef unsigned int        Elf32_Addr;
typedef unsigned int        Elf32_Word;
typedef unsigned int        Elf32_Off;
typedef unsigned short int  Elf32_Half;
typedef int                 Elf32_Sword;


struct Elf64_Ehdr
{
  unsigned char e_ident[16]; /* ELF identification */
  Elf64_Half e_type; /* Object file type */
  Elf64_Half e_machine; /* Machine type */
  Elf64_Word e_version; /* Object file version */
  Elf64_Addr e_entry; /* Entry point address */
  Elf64_Off e_phoff; /* Program header offset */
  Elf64_Off e_shoff; /* Section header offset */
  Elf64_Word e_flags; /* Processor-specific flags */
  Elf64_Half e_ehsize; /* ELF header size */
  Elf64_Half e_phentsize; /* Size of program header entry */
  Elf64_Half e_phnum; /* Number of program header entries */
  Elf64_Half e_shentsize; /* Size of section header entry */
  Elf64_Half e_shnum; /* Number of section header entries */
  Elf64_Half e_shstrndx; /* Section name string table index */
};

struct Elf32_Ehdr
{
  unsigned char e_ident[16]; /* ELF Identification */
  Elf32_Half    e_type; /* Object file type */
  Elf32_Half    e_machine; /* Machine type */
  Elf32_Word    e_version; /* Object file version */
  Elf32_Addr    e_entry; /* Entry point address */
  Elf32_Off     e_phoff; /* Program header offset */
  Elf32_Off     e_shoff; /* Section header offset */
  Elf32_Word    e_flags; /* Processor-specific flags */
  Elf32_Half    e_ehsize; /* ELF header size */
  Elf32_Half    e_phentsize; /* Size of program header entry */
  Elf32_Half    e_phnum; /* Number of program header entries */
  Elf32_Half    e_shentsize; /* Size of section header entry */
  Elf32_Half    e_shnum; /* Number of section header entries */
  Elf32_Half    e_shstrndx; /* Section name string table index */
  
};


struct Elf_ph_32
{
  Elf32_Word p_type;
  Elf32_Word p_offset;
  Elf32_Word p_vaddr;
  Elf32_Word p_filesz;
  Elf32_Word p_memsz;
  Elf32_Word p_flags;
  Elf32_Word p_align;
};

struct Elf_ph_64
{
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Xword p_offset;
  Elf64_Xword p_vaddr;
  Elf64_Xword p_paddr;
  Elf64_Xword p_filesz;
  Elf64_Xword p_memsz;
  Elf64_Xword p_align;
}


void print_e_type(Elf64_Half *input);
void print_e_machine(Elf64_Half *input);
void print_e_version();
void print_buffer(unsigned char * array);
void print_e_os_abi(unsigned char input);
int print_elf_header(const char * input_string);

