#include <stdio.h>
#include <unistd.h>
unsigned char byte_hexstring_to_int(char * input);

int main()
{
  sleep(5);
  printf("FF: %d", (byte_hexstring_to_int("FF")));
  return 0;
}
