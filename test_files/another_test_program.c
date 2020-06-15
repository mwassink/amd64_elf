#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void test()
{
  sleep(5);
  int POINTER[3];

  POINTER[0] = 1;


  int x = POINTER[0];

  sleep(10);
  
}

int main()
{

  int x = 3;

  int * ptr = &x;

  test();


  int * ptr2 = malloc(6 * sizeof(int));

  *ptr2 = 3;
  *(ptr2 + 1) = 4;

  int sample = *(ptr2 + 1);
  int sample2 = ptr2[1];


  x = sample2;
  free(ptr2);
  return 0;
}
