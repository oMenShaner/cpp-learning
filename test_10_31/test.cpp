#include "Date.h"

using namespace std;

void Test1()
{
  Date d1(2001, 1, 1);
  const Date d2;

  //cout << d1 << endl;
  //cin >> d2;
  //cout << d2 << endl;
  
  cout << &d1 << endl;
  cout << &d2 << endl;
}

int main()
{
  Test1();


  return 0;
}
