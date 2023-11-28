#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include "String.h"

using namespace wr;

void Test1()
{
  string s1;
  string s2("abcdef");
  cout << s2 << endl;

  string s3(s2);
  string s4 = s2;
  string s5 = "hello";

  s4 = s3;
  cout << s3 << endl;
  cout << s4 << endl;
  cout << s5 << endl;

  for (auto &e : s2)
  {
    ++e;
  }
  cout << s2 << endl;
}

void Test2()
{
  string s1 = "abcdef";
  cout << s1.capacity() << endl;
  cout << s1.size() << endl;
  cout << s1.empty() << endl;

  // 	s1.reserve(30);
  // 	cout << s1.capacity() << endl;
  // 	s1.reserve(20);
  // 	cout << s1.capacity() << endl;
  //
  s1.push_back('a');
  cout << s1.capacity() << endl;
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  cout << s1.capacity() << endl;
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  s1.push_back('a');
  cout << s1.capacity() << endl;
}

void Test3()
{
  string s1 = "abcdef";
  cout << s1.capacity() << endl;
  cout << s1.size() << endl;

  s1.resize(2);
  cout << s1 << endl;
  cout << s1.capacity() << endl;
  cout << s1.size() << endl;

  s1.resize(10, 'c');
  cout << s1 << endl;
  cout << s1.capacity() << endl;
  cout << s1.size() << endl;

  //	s1.resize(20);
  //	cout << s1 << endl;
  //	cout << s1.capacity() << endl;
  //	cout << s1.size() << endl;

  s1.resize(30, 'b');
  cout << s1 << endl;
  cout << s1.capacity() << endl;
  cout << s1.size() << endl;
}

void Test4()
{
  string s1("abcdef");

  for (int i = 0; i < s1.size(); ++i)
  {
    cout << s1[i];
  }
  cout << endl;

  s1 += 'b';
  cout << s1 << endl;
  cout << s1.size() << endl;
  cout << s1.capacity() << endl;

  s1.append("aaaaaa");
  cout << s1 << endl;
  cout << s1.size() << endl;
  cout << s1.capacity() << endl;

  s1 += "cccccc";
  cout << s1 << endl;
  cout << s1.size() << endl;
  cout << s1.capacity() << endl;

  string s2 = "a";
  s1.swap(s2);
  cout << "s1: " << s1 << endl;
  cout << "s2: " << s2 << endl;

  cout << s1.c_str() << endl;
  cout << s2.c_str() << endl;

}

void Test5()
{
  string s1 = "aaaab";
  string s2 = "aaaac";

  cout << (s1 < s2) << endl;

  string s3 = s2;
  cout << (s3 == s2) << endl;
  cout << (s3 == s1) << endl;

  cout << s1.find('b', 0) << endl;
  cout << s1.find("aab") << endl;
  cout << s1.find("ab") << endl;
  cout << s1.find("aac") << endl;

}

void Test6()
{
  string s1 = "123456";
  s1.insert(0, 'a');
  cout << s1 << endl;

  s1.insert(0, "cdef");
  cout << s1 << endl;

  s1.erase(6);
  cout << s1 << endl;

  s1.erase(2, 3);
  cout << s1 << endl;

  string s2 = "123456789";
  cout << s1.substr() << endl;
  cout << s2.substr(3, 10) << endl;
  cout << s2.substr(2, 4) << endl;
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
