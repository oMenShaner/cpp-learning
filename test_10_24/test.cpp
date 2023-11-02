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

void Test4()
{
  Date d1(2023, 11, 1);

  cout << "d1++.Print(): "; (d1++).Print();
  cout << "++d1.Print(): "; (++d1).Print();
  cout << "d1--.Print(): "; d1--.Print();
  cout << "--d1.Print(): "; (--d1).Print(); 
}

void Test5()
{
  Date d1(2023, 11, 2);
  Date d2(2024, 12, 25);
  Date d3(2024, 5, 5);
  Date d4(2100, 1, 1);

  cout << d2 - d1 << endl;
  cout << d3 - d1 << endl;
  cout << d4 - d1 << endl;
}

int main()
{
  //Test1();
  //Test2();
  //Test3();
  //Test4();
  Test5();

  return 0;
}
