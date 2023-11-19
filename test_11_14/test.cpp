#include<string>
#include<iostream>

using namespace std;

int main()
{
  string s1("");
  int size = s1.capacity();

  int i = 0;
  for (i = 0; i < 500; i++)
  {
    s1.push_back('x');
    if (size != s1.capacity())
    {
      size = s1.capacity();
      cout << size << endl;
    }
  }
}