#include "Stack.h"

namespace wr 
{
  void StackInit(ST* ps)
  {
    ps->a = NULL;
    ps->capacity = ps->top = 0;
  }
}
