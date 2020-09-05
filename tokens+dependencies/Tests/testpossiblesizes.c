#include  "../include/utilities.h"
#include "../include/customtypes.h"
#include <assert.h>
int main()
{
  struct available_sizes available;

  fill_possible_sizes(&available, "r/m16/32/64");

  assert(available.byte_2 == 1);
  assert(available.byte_4 == 1);
  assert(available.byte_8 == 1);

  
  return 0;
}
