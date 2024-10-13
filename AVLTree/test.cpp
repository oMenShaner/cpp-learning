#include <iostream>
#include <utility>
#include <assert.h>
using namespace std;

#include "AVLTree.h"

int main()
{
  AVLTree<int, int> t;

  // t.Insert(make_pair(30, 30));
  // t.Insert(make_pair(60, 60));
  // t.Insert(make_pair(90, 90));
  // t.Insert(make_pair(20, 20));
  // t.Insert(make_pair(10, 10));
  // t.Insert(make_pair(110, 110));
  // t.Insert(make_pair(120, 120));
  // t.Insert(make_pair(5, 5));
  // t.Insert(make_pair(40, 40));
  // t.Insert(make_pair(25, 25));
  // t.Insert(make_pair(23, 23));

  // t.IsBalance();
  // t.InOrder();

  TestAVLTree1();
  return 0;
}