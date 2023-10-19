#include <stdio.h>
#include <stdlib.h>

namespace wr 
{
  typedef struct Stack
  {
    int* a;
    int capacity;
    int top;
  }ST;

  void StackInit(ST* ps);
}
