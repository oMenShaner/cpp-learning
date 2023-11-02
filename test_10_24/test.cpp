#include "Date.h"

using namespace std;

void Test1()
{
  Date d1;
  cout << "d1: "; d1.Print();
  Date d2(2000, 1, 1);
  cout << "d2: "; d2.Print();
  Date d3(2000, 13, 1);
  Date d4(2000, 2, 30);
}

void Test2()
{
  Date d1;
  cout << "d1: "; d1.Print();
  Date d2(2000, 1, 1);
  cout << "d2: "; d2.Print();

  cout << "d1 == d2: " << (d1 == d2) << endl;
  cout << "d1 >= d2: " << (d1 >= d2) << endl;
  cout << "d1 > d2: " << (d1 > d2) << endl;
  cout << "d1 < d2: " << (d1 < d2) << endl;
  cout << "d1 <= d2: " << (d1 <= d2) << endl;
  cout << "d1 != d2: " << (d1 != d2) << endl;

}

void Test3()
{
  Date d1(2023, 11, 1);
  Date d2;
  cout << "d1:"; d1.Print();
  cout << "d2:"; d2.Print();
  d2 = d1; 
  cout << "d2:"; d2.Print();

  cout << "d1 + 100:\t"; (d1 + 100).Print();
  cout << "d1 + 10000:\t"; (d1 + 10000).Print();
  cout << "d1 - 100:\t"; (d1 - 100).Print();
  cout << "d1 - 10000:\t"; (d1 - 10000).Print();

}

int main()
{
  //Test1();
  //Test2();
  Test3();

  return 0;
}
