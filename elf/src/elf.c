#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "elf.h"


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
        
        for (int i = 0; i < 32; ++i)
        {
            if (offset++ % 8 == 0)
                printf("\n");
            printf("%d%d" ,array[2*i + 1], array[2*i] );
        }
    }
    else 
    {
        int offset = 0;
        printf("Big Endian");

        for (int i = 0; i < 32; ++i)
        {
            if (offset++ % 8 == 0)
                printf("\n");
            printf("%d%d ", array[2*i], array[2*i + 1]);
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



void print_elf_header(const char * input_string)
{
    FILE * file_pointer = fopen(input_string, "rb");

    unsigned char buffer[65];

    
    fread(buffer, 64, 1, file_pointer);

    print_buffer(buffer);
    
    unsigned char elf_magic[5];

    for (int i = 0; i < 4; ++i)
    {
        elf_magic[i] = buffer[i];
    }
    elf_magic[4] = 0;
    printf("Offset Range 0x0 - 0x4: \n");
    printf("Elf magic: %s", elf_magic);

    printf("Offset 0x04: \n");
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
    print_e_os_abi(buffer[6]); printf("\n");

    printf("Offset 0x8: ABIVERSION \n");
    printf("ABI VERSION: %d \n", buffer[8]);

    printf("Offset 0x09: EI_PAD \n");
    printf("0x00000000000000 \n");

    printf("Offset 0x10: e_type \n");
    print_e_type((Elf64_Half*)(buffer+10)); printf("\n"); /* 16 */

    printf("Offset 0x12: e_machine \n");
    print_e_machine((Elf64_Half*)(buffer+12)); printf("\n"); /* 18 */

    printf("Offset 0x14: e_version \n");
    printf("0x00000001"); printf("\n");
   
    int current_address = 24; //0x18
    if (buffer[4] == 1)
    {   printf("Offset %x: entry point \n", current_address);
        int *temp1 = ( int *)(buffer + current_address);     
        printf("%x \n", *temp1);
        current_address += 4;
        printf("Offset %x: e_phoff \n", current_address);
        temp1 = (int *)(buffer + current_address);
        printf("%x \n",  *temp1);
        current_address += 4;
        printf("Offset %x: e_shoff \n", current_address);
        temp1 = (int *)(buffer + current_address);
        printf("%x, \n", *temp1);
        current_address += 4;

    }
    else
    {
        printf("Offset %x: entry point \n", current_address);
        long int *temp1 = (long int *)(buffer + current_address);
        printf("%lx \n", *temp1);
        current_address += 8;
        printf("Offset %x: e_phoff \n", current_address);
        temp1 = (long int *)(buffer + current_address);
        printf("%lx \n",  *temp1);
        current_address += 8;
        printf("Offset %x: e_shoff \n", current_address);
        temp1 = (long int *)(buffer + current_address);
        printf("%lx, \n", *temp1);
        current_address += 8;
    }

    printf("Offset %x: e_flags\n", current_address);
    int * temp2 = (int *)(buffer + current_address);
    printf("%x \n", *temp2); 
    current_address += 4;

    printf("Offset %x: e_ehsize \n", current_address);
    short int * temp3 = (short int *)(buffer + current_address);
    printf("%hx \n", *temp3);
    current_address += 2;

    printf("Offset %x, e_phentsize \n", current_address);
    short int * temp4 = (short int * )(buffer +current_address);
    printf("%hx \n", *temp4);
    current_address += 2;

    printf("Offset %x, e_phnum \n", current_address );
    short int * temp5 = (short int *)(buffer + current_address);
    printf("%hx \n", *temp5);
    current_address += 2;

    printf("Offset %x: e_shentsize \n", current_address);
    short int * temp6 = (short int *)(buffer + current_address);
    printf("%hx \n", *temp6);
    current_address += 2;

    printf("Offset %x: e_shnum \n", current_address);
    short int * temp7 = (short int *)(buffer + current_address);
    printf("%hx \n", *temp7);
    current_address += 2;

    printf("Offset %x, e_shstrndx \n", current_address);
    short int * temp8 = (short int *)(buffer + current_address);
    printf("%hx \n", *temp8);


    
}




