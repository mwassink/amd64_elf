#include <stdio.h>
#include "../include/elf.h"
#include <unistd.h>




int main()
{
  sleep(3);
  print_elf_header("addmov.o");
}

