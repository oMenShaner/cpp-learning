#include "string.h"

using std::cin, std::cout, std::endl;
using namespace wr;

void Test1()
{
  string s1;
  string s2("abcdef");
  cout << s2 << endl;

  string s3(s2);
  string s4 = s2;
  string s5 = "hello";

  cout << s3 << endl;
  cout << s4 << endl;
  cout << s5 << endl;

  for (auto &e: s2){
    ++e;
  }
  cout << s2 << endl;
}

int main()
{
  Test1();

  return 0;
}