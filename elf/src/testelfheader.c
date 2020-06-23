#include <stdio.h>
#include "../include/elf.h"





int main()
{


  int returned = print_elf_header("../objects/addmov.o");
  printf("Returned with exit status %d", returned);
}

