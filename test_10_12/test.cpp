//#include <iostream>
//using namespace std;
//
//int Add(int left, int right)
//{
//  return left + right;
//}
//
//double Add(double left, double right)
//{
//  return left + right;
//}
//void f()
//{
//    cout << "f()" << endl; 
//}
//
//void f(int a = 1)
//{
//    cout << "f(int a)" << endl; 
//}
//
//int main()
//{
//  cout << Add(1, 2) << endl;
//  cout << Add(1.1, 2.2) << endl;
//  f();
//}

//#include "Func.h"
//
//int main()
//{
//    A a = {1};
//    f(1, 'x');
//    f('y', 2);
//    f(a);
//
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    int a = 10;  
//    int &b = a;     // b是a的别名
//    int &c = b;     // c是b的别名, 也是a的别名
//    int d = a;      // 将a的值赋给d, 新开辟了一块内存空间
//
//    return 0;
//}
#include <iostream>
using namespace std;

int main()
{
  int val1 = 1024;
  int val2 = 100;
  int& refVal = val1;
  int i = 0, &r1 = i;
  double d = 0, &r2 = d;
  
  r2 = 4.33;
  r2 = r1;
  i = r2;
  r1 = d;
}

