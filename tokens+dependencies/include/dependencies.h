#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H
#include <stdbool.h>
// Look for the struct from before with the
// Make note of the different directions that we can have with the instruction
enum Operand
{
    immediate, memory, reg
};
struct dependencies
{
    bool lockable; // Easy one to see. If there calls for a lock prefix, then look if a lock is allowed
    Operand one;
    Operand two;
    int highest_ring; // User space would be the highest, 3
    int ID; // If this is long then this will be parts 8-end of the instruction, rather than the first part


};
  














#endif
