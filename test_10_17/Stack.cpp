#include"Stack.h"

void Stack::Init(int capacity)
{
  _array = (STDataType*)malloc(sizeof(STDataType) * capacity);
  if (nullptr == _array)
  {
    perror("malloc fail");
    return;
  }

  _capacity = capacity;
  _top = 0;
}

