#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/elf.h"





void print_p_type(int in)
{
  switch (in)
    {
    case 0:
      printf("0x00000000 PT_NULL. ENtry Unused");
      break;
    case 1:
      printf("0x00000001 PT_LOAD. Loadable segment");
      break;
    case 2:
      printf("0x00000002 PT_DYNAMIC Dynamic Linking information");
      break;
    case 3:
      printf("0x00000003 PT_INTERP Interpreter Information");
      break;
    case 4:
      printf("0x00000004 PT_NOTE Auxiliary Information");
      break;
    case 5:
      printf("0x00000005 PT_SHLIB reserved ");
      break;
    case 6:
      printf("0x00000006 PT_PHDR segment containing program header table itself ");
      break;
    case 7:
      printf("0x00000007 PT_TLS thread-Local storage template ");
      break;
    case 0x60000000:
      printf("0x60000000 PT_LOOS inclusive reserved ranges for operating system semantics ");
      break;
    case 0x6FFFFFFF:
      printf("0x6FFFFFFF PT_HIOS  inclusive reserved ranges for operating system semantics ");
      break;
    case 0x70000000:
      printf("0x70000000 PT_LOPROC  inclusive reserved ranges for operating system semantics ");
      break;
    case 0x7FFFFFFF:
      printf("0x7FFFFFFF PT_HIPROC  inclusive reserved ranges for operating system semantics");
      break;

    default:
      printf("unknown p_type ");

    }
}

void print_sh_type(int in )
{
  switch (in)
    {
    case 0:
      printf("0x00000000 SHT NULL \n");
      break;
    case 1:
      printf("0x00000001 SHT_PROGBITS Program data\n");
      break;
    case 2:
      printf("0x00000002 SHT_SYMTAB Symbol table\n");
      break;
    case 3:
      printf("0x00000003 SHT_STRTAB String table \n");
      break;
    case 4:
      printf("0x00000004 SHT_RELA Relocation entries with addends \n");
      break;
    case 5:
      printf("0x00000005 SHT_HASH Symbol hash table \n");
      break;
    case 6:
      printf("0x00000006 SHT_DYNAMIC Dynamic linking informaiton \n");
      break;
    case 7:
      printf("0x00000007 SHT_NOTE Notes \n");
      break;
    case 8:
      printf("0x00000008 SHT_NOBITS Program space with no data \n");
      break;
    case 9:
      printf("0x00000009 SHT_REL Relocation entrien no addends \n");
    case 0x0a:
      printf("0x0000000a SHT_SHLIB reserved \n");
      break;
    case 0x0b:
      printf("0x0000000b SHT_DYNSYM Dynamic linker symbol table \n");
      break;
    case 0x0e:
      printf("0x0000000e SHT_INIT_ARRAY Array of constructors \n");
      break;
    case 0x0f:
      printf("0x0000000f SHT_FINI_ARRAY Array of destrcutors \n");
      break;
    case 0x10:
      printf("0x00000010 SHT_PREINIT_ARRAY Array of preconstructors \n");
    case 0x11:
      printf("0x00000011 SHT_GROUP Section group \n");
      break;
    case 0x12:
      printf("0x00000012 SHT_SYMTAB_INDEX Extended section indices \n");
      break;
    case 0x13:
      printf("0x00000013 SHT_NUM Number of defined types \n");
      break;

    case 0x60000000:
      printf("0x60000000 SHT_LOOS OS Specific");

    default:
      printf("No matching type for the given value");






      
    }
}







void print_e_type(Elf64_Half * input)
{
    switch (*input)
    {
        case 0:
        printf("ET_NONE, No file type");
        break;
        case 1:
        printf("ET_REL, Relocatable file");
        break;
        case 2:
        printf("ET_EXEC, Executable File");
        break;
        case 3:
        printf("ET_DYN, Shared object file");
        break;
        case 4:
        printf("ET_CORE, Core file");
        break;
        case 0xff00:
        printf("ET_LOPROC, Processor-specific");
        case 0xffff:
        printf("ET_HIPROC, Processor-specific");
        default:
        printf("Not a valid value");
        break;
    }
}

void print_e_machine(Elf64_Half * input)
{
    switch (*input)
    {
        case 0:
        printf("No machine");
        break;
        
        break;
        case 2:
        printf("SPARC");
        break;
        case 3:
        printf("x86");
        break;
        case 0x28:
        printf("ARM");
        break;
        case 0x3e:
        printf("AMD64");
        break;
        case 0xf3:
        printf("RISC-V");
        default:
        printf("Something unusual");
        
    }
}



void print_e_version()
{
    printf("Version 1, the original");
}


void print_buffer(unsigned char * array)
{
    if (array[5] == 1)
    {
        int offset = 0;
        printf("Little Endian Format");
        
        for (int i = 0; i < 64; ++i)
        {
            if (offset++ % 16 == 0)
                printf("\n");
            if (array[i] < 0x10)
	      {
		printf("0%x ", array[i]);
		
	      }
	    else
	      {
		printf("%x ", array[i]);
	      }
        }
    }
    else 
    {
        int offset = 0;
        printf("Big Endian");

        for (int i = 0; i < 64; ++i)
        {
            if (offset++ % 16 == 0)
                printf("\n");
            if (array[i] < 0x10)
	      {
		printf("0%x ", array[i]);
		
	      }
	    else
	      {
		printf("%x ", array[i]);
	      }
        }
    }
}

void print_e_os_abi(unsigned char input)
{
    switch (input)
    {
    case 0x0:
    printf("0x00 : System V UNIX");
    break;
    case 0x01:
    printf("0x01 : HP-UX ");
    break;
    case 0x02:
    printf("0x02 : NetBSD");
    break;
    case 0x03:
    printf(" 0x03: Linux");
    break;
    case 0x04:
    printf(" 0x04 : GNU Hurd");
    break;
    
    break;
    case 0x06:
    printf(" 0x06: Solaris     ");
    break;
    case 0x07:
    printf(" 0x07 : AIX     ");
    break;
    case 0x08:
    printf(" 0x08 : IRIX ");
    break;
    case 0x09:
    printf(" 0x09: FreeBSD     ");
    break;
    case 0x0a:
    printf(" 0x0A: Tru64     ");
    break;
    case 0x0b:
    printf(" 0x0B: Novell Modesto     ");
    break;
    case 0x0c:
    printf(" 0x0C: OpenBSD     ");
    break;
    case 0xd:
    printf(" 0x0D: OpenVMS     ");
    break;
    case 0xe:
    printf(" 0x0E: NonStop Kernel ");
    break;
    case 0xf:
    printf(" 0x0F: AROS     ");
    break;
    case 0x10:
    printf(" 0x10: Fenix OS    ");
    break;
    case 0x11:
    printf(" 0x11: CloudABI     ");
    break;
    case 0x12:
    printf(" 0x12: OpenVos     ");
    break;
    default:
        break;
    }
}



int print_elf_header(const char * input_string)
{
    FILE * file_pointer = fopen(input_string, "rb");

    unsigned char buffer[65];

    if (!file_pointer)
        {
            return -1;
        }


    fread(buffer, 64, 1, file_pointer);

    print_buffer(buffer);
    
    unsigned char elf_magic[5];

    for (int i = 0; i < 4; ++i)
    {
        elf_magic[i] = buffer[i];
    }
    elf_magic[4] = 0;
    printf("\nOffset Range 0x0 - 0x4: \n");
    printf("Elf magic: %s", elf_magic);

    printf("\nOffset 0x04: \n");
    if (buffer[4] == 0x1)
    {
        printf("0x1: 32 bit system \n");
    }

    else if (buffer[4] == 0x2)
    {
        printf("0x2: 64 bit system \n");
    }

    else
    {
        printf("Bit size not found \n");
    }

    printf("Offset 0x05: \n");
    if (buffer[5] == 1)
    {
        printf("0x1: Little Endianness \n");
    }

    else if (buffer[5] == 2)
    {
        printf("0x2: Big Endianness \n");
    }

    else
    {
        printf("Endianness not identified \n");
    }

    printf("Offset 0x6: \n");
    print_e_version(); printf("\n");

    printf("Offset 0x7: OS_ABI \n");
    print_e_os_abi(buffer[7]); printf("\n");

    printf("Offset 0x8: ABIVERSION \n");
    printf("ABI VERSION: %d \n", buffer[8]);

    printf("Offset 0x09: EI_PAD \n");
    printf("0x00000000000000 \n");

    printf("Offset 0x10: e_type \n");
    print_e_type((Elf64_Half*)(buffer+0x10)); printf("\n"); /* 16 */

    printf("Offset 0x12: e_machine \n");
    print_e_machine((Elf64_Half*)(buffer+0x12)); printf("\n"); /* 18 */

    printf("Offset 0x14: e_version \n");
    printf("0x00000001"); printf("\n");
   
    int current_address = 24; //0x18
    if (buffer[4] == 1)
    {   printf("Offset 0x%x: entry point \n", current_address);
        int *temp1 = ( int *)(buffer + current_address + 4);     
        printf("0x%x \n", *temp1);
        current_address += 4;
        printf("Offset 0x%x: e_phoff \n", current_address + 4);
        temp1 = (int *)(buffer + current_address);
        printf("0x%x \n",  *temp1);
        current_address += 4;
        printf("Offset 0x%x: e_shoff \n", current_address + 4);
        temp1 = (int *)(buffer + current_address);
        printf("0x%x, \n", *temp1);
        current_address += 4;

    }
    else
    {
        printf("Offset 0x%x: entry point \n", current_address);
        long int *temp1 = ( long int *)(buffer + current_address );
        printf("0x%lx \n", *temp1);
        current_address += 8;
        printf("Offset 0x%x: e_phoff \n", current_address);
        temp1 = ( long int *)(buffer + current_address );
        printf("0x%lx \n",  *temp1);
        current_address += 8;
        printf("Offset 0x%x: e_shoff \n", current_address);
        temp1 = (long int *)(buffer + current_address );
        printf("0x%lx, \n", *temp1);
        current_address += 8;
    }

    printf("Offset 0x%x: e_flags\n", current_address);
    int * temp2 = (int *)(buffer + current_address);
    printf("0x%x \n", *temp2); 
    current_address += 4;

    printf("Offset 0x%x: e_ehsize \n", current_address);
    short int * temp3 = (short int *)(buffer + current_address);
    printf("0x%hx \n", *temp3);
    current_address += 2;

    printf("Offset 0x%x, e_phentsize \n", current_address);
    short int * temp4 = (short int * )(buffer +current_address);
    printf("0x%hx \n", *temp4);
    current_address += 2;

    printf("Offset 0x%x, e_phnum \n", current_address );
    short int * temp5 = (short int *)(buffer + current_address);
    printf("0x%hx \n", *temp5);
    current_address += 2;

    printf("Offset 0x%x: e_shentsize \n", current_address);
    short int * temp6 = (short int *)(buffer + current_address);
    printf("0x%hx \n", *temp6);
    current_address += 2;

    printf("Offset 0x%x: e_shnum \n", current_address);
    short int * temp7 = (short int *)(buffer + current_address);
    printf("0x%hx \n", *temp7);
    current_address += 2;

    printf("Offset 0x%x, e_shstrndx \n", current_address);
    short int * temp8 = (short int *)(buffer + current_address);
    printf("0x%hx \n", *temp8);


    return 0;
}



int populate_elf_header_64(const char * input_file, struct Elf64_Ehdr *elf_header64)
{
  struct Elf64_Ehdr * elf_header = elf_header64;

  
  FILE * file_pointer = fopen(input_file, "rb");

  if(!file_pointer)
    return -1;

  unsigned char buffer[64];


  fread(buffer, 64, 1, file_pointer);

  for (int k = 0; k < 16; ++k)
    {
      elf_header->e_ident[k] = buffer[k];
    }

  unsigned short int * small_ptr = (unsigned short int *)(buffer + 16);
  elf_header->e_type = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 18);
  elf_header->e_machine = *small_ptr;

  unsigned int * medium_ptr = (unsigned int *)(buffer + 20);
  elf_header->e_version = *medium_ptr;

  unsigned long int * long_ptr = (unsigned long int *)(buffer + 24);
  elf_header->e_entry = *long_ptr;
  long_ptr = (unsigned long int *)(buffer + 32);
  elf_header->e_phoff = *long_ptr;
  long_ptr = (unsigned long int *)(buffer + 40);
  elf_header->e_shoff = *long_ptr;

  medium_ptr = (unsigned int *)(buffer + 48);
  elf_header->e_flags = *medium_ptr;

  small_ptr = (unsigned short int *)(buffer + 52);
  elf_header->e_ehsize = *small_ptr;


  small_ptr = (unsigned short int *)(buffer + 54);
  elf_header->e_phentsize = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 56);
  elf_header->e_phnum = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 58);
  elf_header->e_shentsize = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 60);
  elf_header->e_shnum = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 62);
  elf_header->e_shstrndx = *small_ptr;
  
  return 0;


}


int populate_elf_header_32(const char * input_file, struct Elf32_Ehdr *elf_header32)
{
  struct Elf32_Ehdr * elf_header = elf_header32;

  
  FILE * file_pointer = fopen(input_file, "rb");

  if(!file_pointer)
    return -1;

  unsigned char buffer[64];



  fread(buffer, 64, 1, file_pointer);

  for (int k = 0; k < 16; ++k)
    {
      elf_header->e_ident[k] = buffer[k];
    }

  unsigned short int * small_ptr = (unsigned short int *)(buffer + 16);
  elf_header->e_type = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 18);
  elf_header->e_machine = *small_ptr;

  unsigned int * medium_ptr = (unsigned int *)(buffer + 20);
  elf_header->e_version = *medium_ptr;

  medium_ptr = (unsigned  int *)(buffer + 24);
  elf_header->e_entry = *medium_ptr;
  medium_ptr  = (unsigned  int *)(buffer + 28);
  elf_header->e_phoff = *medium_ptr;
  medium_ptr = (unsigned  int *)(buffer + 32);
  elf_header->e_shoff = *medium_ptr;

  medium_ptr = (unsigned int *)(buffer + 36);
  elf_header->e_flags = *medium_ptr;

  small_ptr = (unsigned short int *)(buffer + 40);
  elf_header->e_ehsize = *small_ptr;


  small_ptr = (unsigned short int *)(buffer + 42);
  elf_header->e_phentsize = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 44);
  elf_header->e_phnum = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 46);
  elf_header->e_shentsize = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 48);
  elf_header->e_shnum = *small_ptr;
  small_ptr = (unsigned short int *)(buffer + 50);
  elf_header->e_shstrndx = *small_ptr;
  
  return 0;


}

int write_elf_header_64(const char * output_file_name, struct Elf64_Ehdr *elf_header)
{
  FILE * fileptr = fopen(output_file_name, "wb");

  
  if (!fileptr)
    return -1;
  /* 0x00 - 0x10 */
  fwrite(elf_header->e_ident, 16, 1,fileptr);
  fwrite(&elf_header->e_type, 1, sizeof(elf_header->e_type), fileptr);
  fwrite(&elf_header->e_machine, 1, sizeof(elf_header->e_machine), fileptr);
  fwrite(&elf_header->e_version, 1, sizeof(elf_header->e_version), fileptr);
  fwrite(&elf_header->e_entry,1, sizeof(elf_header->e_entry), fileptr);
  fwrite(&elf_header->e_phoff,1, sizeof(elf_header->e_phoff), fileptr);
  fwrite(&elf_header->e_shoff, 1, sizeof(elf_header->e_shoff), fileptr);
  fwrite(&elf_header->e_flags, 1, sizeof(elf_header->e_flags), fileptr);
  fwrite(&elf_header->e_ehsize, 1, sizeof(elf_header->e_ehsize), fileptr);
  fwrite(&elf_header->e_phentsize, 1, sizeof(elf_header->e_phentsize), fileptr);
  fwrite(&elf_header->e_phnum, 1, sizeof(elf_header->e_phnum), fileptr);
  fwrite(&elf_header->e_shentsize, 1, sizeof(elf_header->e_shentsize), fileptr);
  fwrite(&elf_header->e_shnum, 1, sizeof(elf_header->e_shnum), fileptr);
  fwrite(&elf_header->e_shstrndx, 1, sizeof(elf_header->e_shstrndx), fileptr);
  
  return 0;
}

int write_elf_header_32(const char * output_file_name, struct Elf32_Ehdr *elf_header)
{
  FILE * fileptr = fopen(output_file_name, "wb");

  
  if (!fileptr)
    return -1;
  /* 0x00 - 0x10 */
  fwrite(elf_header->e_ident, 16, 1,fileptr);
  fwrite(&elf_header->e_type, 1, sizeof(elf_header->e_type), fileptr);
  fwrite(&elf_header->e_machine, 1, sizeof(elf_header->e_machine), fileptr);
  fwrite(&elf_header->e_version, 1, sizeof(elf_header->e_version), fileptr);
  fwrite(&elf_header->e_entry,1, sizeof(elf_header->e_entry), fileptr);
  fwrite(&elf_header->e_phoff,1, sizeof(elf_header->e_phoff), fileptr);
  fwrite(&elf_header->e_shoff, 1, sizeof(elf_header->e_shoff), fileptr);
  fwrite(&elf_header->e_flags, 1, sizeof(elf_header->e_flags), fileptr);
  fwrite(&elf_header->e_ehsize, 1, sizeof(elf_header->e_ehsize), fileptr);
  fwrite(&elf_header->e_phentsize, 1, sizeof(elf_header->e_phentsize), fileptr);
  fwrite(&elf_header->e_phnum, 1, sizeof(elf_header->e_phnum), fileptr);
  fwrite(&elf_header->e_shentsize, 1, sizeof(elf_header->e_shentsize), fileptr);
  fwrite(&elf_header->e_shnum, 1, sizeof(elf_header->e_shnum), fileptr);
  fwrite(&elf_header->e_shstrndx, 1, sizeof(elf_header->e_shstrndx), fileptr);
  
  return 0;
}


// Start Program Header

int print_program_header(const char * in_file)
{
  FILE * fp = fopen(in_file, "rb");

  if (!in_file)
    {
      return -1;
      printf("File does not exist or is inaccessible");
    }

  // Looks for the program header in the elf header


  unsigned char buffer[64];
  fread(buffer, 64, 1, fp);
  long int phoff = 0;
  int sphoff = 0;
  if (buffer[4] == 1)
    {
      // 32 Bit format
      int * temp = (int *)(buffer + 0x1C);
      phoff = *temp;
    }

  else if (buffer[4] == 2)
    {
      long int * temp = (long int *)(buffer + 0x20);
      phoff = *temp;

    }



  fp->_IO_read_ptr = fp->_IO_read_base + phoff;

  int * type = NULL;
  fread(type, 1, 4, fp);
  if (buffer[4] == 1)
    printf("Offset 0x%x ", sphoff);
  else
    printf("Offset 0x%lx ", phoff);
  print_p_type(*type);
  phoff += 4; //0x04

  if (buffer[4] == 2)
    {
      unsigned long int long_numbers[6];
      printf("Offset 0x%lx : p_flags ", phoff + 4);
      int * temp;
      fread(temp, 4, 1, fp);
      printf("\n %x \n", *temp);
      phoff += 4; // 0x08
      printf("Offset 0x%lx: p_offset \n", phoff);
      fread(long_numbers, 8, 6, fp);
      printf("%lx ", long_numbers[0]);
      phoff += 8;
      printf("Offset 0x%lx: p_vaddr\n", phoff);
      printf("%lx ", long_numbers[1]);
      phoff += 8;
      printf("offset 0x%lx: p_paddr \n", phoff);
      printf("%lx ", long_numbers[2]);
      phoff += 8;
      printf("Offset 0x%lx p_filesz \n", phoff);
      printf("%lx ", long_numbers[3]);
      phoff += 8;
      printf("Offset 0x%lx p_memsz \n", phoff);
      printf("%lx ", long_numbers[4]);
      phoff += 8;
      printf("Offset 0x%lx p_align \n", phoff);
      phoff += 8;
      printf("%lx ", long_numbers[5]);
      printf("Offset 0x%lx End of Program Header", phoff);

    }

  else if (buffer[4] == 1)
    {
      unsigned int long_numbers[7];
      int * temp;
      fread(temp, 4, 1, fp);
      printf("\n %x \n", *temp);
      sphoff += 4; // 0x08
      printf("Offset 0x%x: p_offset \n", sphoff);
      fread(long_numbers, 4, 7, fp);
      printf("%x ", long_numbers[0]);
      sphoff += 4;
      printf("Offset 0x%x: p_vaddr\n", sphoff);
      printf("%x ", long_numbers[1]);
      sphoff += 4;
      printf("offset 0x%x: p_paddr \n", sphoff);
      printf("%x ", long_numbers[2]);
      sphoff += 4;
      printf("Offset 0x%x p_filesz \n", sphoff);
      printf("%x ", long_numbers[3]);
      sphoff += 4;
      printf("Offset 0x%x p_memsz \n", sphoff);
      printf("%x ", long_numbers[4]);
      sphoff += 4;
      printf("Offset 0x%x p_flags \n", sphoff);
      sphoff += 4;
      printf("%x ", long_numbers[5]);
      printf("Offset 0x%x p_align \n", sphoff);
      printf("%x ", long_numbers[6]);
      printf("Offset 0x%x End of Program Header", sphoff);

    }
  
}

int  print_section_headers(const char * in_file)
{
  FILE * fp = fopen(in_file, "rb");


  if (!fp)
    {
      return -1;
    }
  
  if (fp->_IO_read_end - fp->_IO_read_base < 64)
    {
      return -2;
    }


  int * sh_name;
  fread(sh_name, 4, 1, fp);
  printf("Offset 0x00: sh_name \n");
  printf("%x", *sh_name);
  
  int * sh_type;
  fread(sh_type, 4, 1, fp);
  printf("Offset 0x04: sh_type \n");
  






}
