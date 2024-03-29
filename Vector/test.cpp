//#include "vector.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
//using namespace wr;

#define SHOW(v)                                                         \
  cout << "capacity: " << v.capacity() << " size: " << v.size() << endl; \
  for (auto e : v)                                                      \
  {                                                                     \
    cout << e << " ";                                                   \
  }                                                                     \
  cout << endl;

void Test1()
{
  vector<int> v;
  SHOW(v);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  SHOW(v);
  vector<int>::iterator it = v.begin();
  while (it != v.end())
  {
    cout << *it << " ";
    ++it;
  }
  cout << endl;

  v[0] = 10;
  for (auto e : v)
  {
    cout << e << " ";
  }
  cout << endl;
  SHOW(v);

}

void Test2()
{
  vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  v.push_back(40);
  v.push_back(50);
  SHOW(v);

  v.insert(v.begin(), 100);
  v.insert(v.begin(), 200);
  SHOW(v);
  
  v.insert(v.end(), 300);
  cout << *v.insert(v.begin(), 400) << endl;
  SHOW(v);

  v.pop_back();
  v.pop_back();
  SHOW(v);

  v.erase(v.end() - 1);
  cout << *v.erase(v.begin()) << endl;
  SHOW(v);
}

void Test3()
{
  vector<int> v1;
  v1.push_back(1);
  v1.push_back(1);
  v1.push_back(1);
  v1.push_back(1);
  v1.push_back(1);
  SHOW(v1);

  vector<int> v2;
  v2.push_back(2);
  v2.push_back(2);
  v2.push_back(2);
  v2.push_back(2);
  v2.push_back(2);
  v2.push_back(2);
  v2.push_back(2);
  v2.push_back(2);
  SHOW(v2);

  v1.swap(v2);
  cout << "v1:" << endl;
  SHOW(v1);

  cout << "v2:" << endl;
  SHOW(v2);

  v1.resize(1);
  SHOW(v1);

  v1.resize(10);
  SHOW(v1);

  v1.resize(21, 6);
  SHOW(v1);
}

void Test4()
{
  vector<int> v1(10, 3);
  SHOW(v1);

  vector<char> v2(20, 'a');
  SHOW(v2);

  vector<int> v3(v1.begin(), v1.end());
  SHOW(v3);

  vector<char> v4(v2);
  SHOW(v4);

  vector<int> v5;
  v5 = v3;
  SHOW(v5);
}

void Test5()
{
  vector<int> vi;
  vi.push_back(1);
  vi.push_back(1);
  vi.push_back(1);
  vi.push_back(1);
  vi.push_back(1);
  SHOW(vi);

  vector<string> vstr;
  vstr.push_back("1111");
  vstr.push_back("2222");
  vstr.push_back("3333");
  vstr.push_back("4444");
  vstr.push_back("5555");

  SHOW(vstr);
}

void Test6()
{
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(2);
  v.push_back(3);
  v.push_back(5);
  v.push_back(6);
  v.push_back(8);
  v.push_back(10);
  v.push_back(11);

  vector<int>::iterator it = v.begin();
  while (it != v.end())
  {
    if (*it % 2 == 0)
    {
      it = v.erase(it);
    }
    else
    {
      ++it;
    }
  }

  SHOW(v);
}

void Test7()
{
  int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> v(a, a + 10); // 用 int数组 构造 vector<int>对象

  vector<int>::iterator ret = find(v.begin(), v.end(), 11); // 使用通用find()方法进行查找

  if (ret != v.end())
  {
    cout << "找到了" << endl;
  }
  else
  {
    cout << "没找到" << endl;
  }
}

void Test8()
{
  vector<int> v{1, 2, 3, 4, 5, 6};
  auto it = v.begin();
  v.reserve(100);
  it = v.begin(); // 更新
  while (it != v.end())
  {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
}

void Test9()
{
  int a[] = {1, 2, 2, 4, 5, 6, 6, 8, 9};
  vector<int> v(a, a + sizeof(a) / sizeof(int));

  vector<int>::iterator it = v.begin();
  while (it != v.end())
  {
    if (*it % 2 == 0)
    {
      it = v.erase(it);
    }
    else
    {
      ++it;
    }
  }

  for (auto e: v)
  {
    cout << e << " ";
  }
  cout << endl;
}
int main()
{
  //Test1();
  //Test2();
  //Test3();
  //Test4();
  //Test5();
  //Test6();
  //Test7();
  //Test8();
  Test9();

  return 0;
}