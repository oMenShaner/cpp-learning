#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

using namespace std;
typedef int STDataType;

class Stack
{
  public:
    void Init(int capacity); 
  private:
    STDataType* _array;
    int _capacity;
    int _top;
};
