#pragma once 
#include <iostream>
using namespace std;

typedef struct A
{
  int i;
}A;

void f(int a, char b);
void f(char a, int b);
void f(A a);

