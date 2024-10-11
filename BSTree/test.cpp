#include <iostream>

using namespace std;

#include "BSTree.h"

// int main()
// {
//   BSTree<int> t;
//   int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};

//   for (auto e : a)
//     t.Insert(e);

//   t.InOrder();

//   t.Erase(8);
//   t.InOrder();

//   t.Erase(14);
//   t.InOrder();

//   t.Erase(4);
//   t.InOrder();

//   t.Erase(6);
//   t.InOrder();

//   for (auto e : a)
//   {
//     t.Erase(e);
//     t.InOrder();
//   }

//   t.InOrder();
//   return 0;
// }

// int main()
// {
//   BSTree<int> t;
//   int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};

//   for (auto e : a)
//     t.InsertR(e);

//   t.InOrder();

//   t.EraseR(8);
//   t.InOrder();

//   t.EraseR(14);
//   t.InOrder();

//   t.EraseR(4);
//   t.InOrder();

//   t.EraseR(6);
//   t.InOrder();

//   for (auto e : a)
//   {
//     t.EraseR(e);
//     t.InOrder();
//   }

//   t.InOrder();
//   return 0;
// }

int main()
{
  BSTree<int> t;
  int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
  for (auto e : a)
  {
    t.InsertR(e);
  }
  t.InOrder();

  BSTree<int> t1(t);
  t1.InOrder();

  BSTree<int> t2;
  t2 = t1;
  t2.InOrder();

  return 0;
}