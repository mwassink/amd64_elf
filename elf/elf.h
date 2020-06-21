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

typedef struct
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
} Elf64_Ehdr;

void print_e_type(Elf64_Half input);

void print_e_machine(Elf64_Half input);



void print_e_version();


void print_buffer(unsigned char * array);

void print_e_ident(unsigned char input);



void print_elf_header(const char * input_string);




void init_elf_header(struct elf_header * elf_ptr, unsigned char * array);