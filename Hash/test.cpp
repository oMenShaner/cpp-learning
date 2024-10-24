#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;

#include "Hash.h"
using namespace hashbucket;
void Test1()
{
  HashTable<int, int> ht;
  int arr[] = {81, 36, 91, 46, 71, 56};
  for (auto e : arr)
  {
    ht.Insert(make_pair(e, e));
  }

  ht.Insert(make_pair(61, 61));
  ht.Insert(make_pair(66, 66));
  ht.Erase(61);
  ht.Erase(60);
}

void Test2()
{
  int a[] = {1, 4, 24, 34, 7, 44, 17, 37};
  HashTable<int, int> ht;
  for (auto e : a)
  {
    ht.Insert(make_pair(e, e));
  }

  for (auto e : a)
  {
    auto ret = ht.Find(e);
    if (ret)
    {
      cout << ret->_kv.first << ":E" << endl;
    }
    else
    {
      cout << ret->_kv.first << ":D" << endl;
    }
  }
  cout << endl;

  ht.Erase(34);
  ht.Erase(4);

  for (auto e : a)
  {
    auto ret = ht.Find(e);
    if (ret)
    {
      cout << ret->_kv.first << ":E" << endl;
    }
    else
    {
      cout << e << ":D" << endl;
    }
  }
  cout << endl;
}

void Test3()
{
  HashTable<string, string> ht;
  ht.Insert(make_pair("abcd", "abcd"));
  ht.Insert(make_pair("acbd", "acbd"));
  ht.Insert(make_pair("aadd", "aadd"));
}

void Test4()
{
  const size_t N = 30000;

  unordered_set<int> us;
  set<int> s;
  HashTable<int, int> ht;

  vector<int> v;
  v.reserve(N);
  srand(time(0));
  for (size_t i = 0; i < N; ++i)
  {
    // v.push_back(rand()); // N比较大时，重复值比较多
    v.push_back(rand() + i); // 重复值相对少
                             // v.push_back(i); // 没有重复，有序
  }

  size_t begin1 = clock();
  for (auto e : v)
  {
    s.insert(e);
  }
  size_t end1 = clock();
  cout << "set insert:" << end1 - begin1 << endl;

  size_t begin2 = clock();
  for (auto e : v)
  {
    us.insert(e);
  }
  size_t end2 = clock();
  cout << "unordered_set insert:" << end2 - begin2 << endl;

  size_t begin10 = clock();
  for (auto e : v)
  {
    ht.Insert(make_pair(e, e));
  }
  size_t end10 = clock();
  cout << "HashTbale insert:" << end10 - begin10 << endl
       << endl;

  size_t begin3 = clock();
  for (auto e : v)
  {
    s.find(e);
  }
  size_t end3 = clock();
  cout << "set find:" << end3 - begin3 << endl;

  size_t begin4 = clock();
  for (auto e : v)
  {
    us.find(e);
  }
  size_t end4 = clock();
  cout << "unordered_set find:" << end4 - begin4 << endl;

  size_t begin11 = clock();
  for (auto e : v)
  {
    ht.Find(e);
  }
  size_t end11 = clock();
  cout << "HashTable find:" << end11 - begin11 << endl
       << endl;

  cout << "插入数据个数：" << us.size() << endl
       << endl;
  ht.Some();

  size_t begin5 = clock();
  for (auto e : v)
  {
    s.erase(e);
  }
  size_t end5 = clock();
  cout << "set erase:" << end5 - begin5 << endl;

  size_t begin6 = clock();
  for (auto e : v)
  {
    us.erase(e);
  }
  size_t end6 = clock();
  cout << "unordered_set erase:" << end6 - begin6 << endl;

  size_t begin12 = clock();
  for (auto e : v)
  {
    ht.Erase(e);
  }
  size_t end12 = clock();
  cout << "HashTable Erase:" << end12 - begin12 << endl
       << endl;
}

int main()
{
  HashTable<int, int> ht;
  // Test2();
  // Test1();
  // Test3();
  Test4();
  return 0;
}