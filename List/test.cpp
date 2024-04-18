#include <iostream>
#include <utility>
#include <string>
#include "list.h"

using namespace std;
using namespace wr;

#define SHOW(x)       \
  for (auto e : x)    \
    cout << e << " "; \
  cout << endl;

void Test1()
{
  list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);

  list<int>::iterator lt = l.begin();
  while (lt != l.end())
  {
    cout << *lt << " ";
    lt++;
  }
  cout << endl;
}

void Test2()
{
  list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);
  l.push_back(6);
  SHOW(l);

  l.push_front(0);
  SHOW(l);
  l.pop_back();
  SHOW(l);
  l.pop_front();
  SHOW(l);
  l.clear();
  SHOW(l);
}

void Test3()
{
  list<string> l1;
  l1.push_back("1111");
  l1.push_back("2222");
  l1.push_back("3333");
  l1.push_back("4444");
  l1.push_back("5555");
  l1.push_back("6666");
  SHOW(l1);

  list<string> l2;
  l2.push_back("aaaa");
  l2.push_back("bbbb");
  l2.push_back("cccc");
  l2.push_back("dddd");
  l2.push_back("eeee");
  SHOW(l2);

  l1.swap(l2);
  SHOW(l1);

  l1.front() = "1111";
  l1.back() = "9999";
  cout << l1.front() << endl;
  cout << l1.back() << endl;
  SHOW(l1);
}

void Test4()
{
  list<int> l;
  cout << l.empty() << endl;
  cout << l.size() << endl;

  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  cout << l.empty() << endl;
  cout << l.size() << endl;
}

void Test5()
{
  char a[] = "abcdeftg";
  list<char> l1(a, a + sizeof(a) / sizeof(char));
  SHOW(l1);
  cout << l1.size() << endl;

  list<char> l2(l1);
  SHOW(l2);

  list<char> l3;
  l3.push_back('1');
  l2.swap(l3);
  SHOW(l2);
  SHOW(l3);
}

void Test6()
{
  list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);

  list<int>::reverse_iterator rlt = l.rbegin();
  while (rlt != l.rend())
  {
    cout << *rlt << ' ';
    rlt++;
  }

  cout << endl;
}
int main()
{
  // Test1();
  // Test2();
  // Test3();
  // Test4();
  // Test5();
  Test6();

  return 0;
}