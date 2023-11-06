#include<iostream>

using namespace std;

//class Date
//{
//public:
//  Date(int year, int month, int day)
//  : _year(year)
//  , _month(month)
//  , _day(day)
//  , x(_year)
//  , y(month)
//  , _year(month)
//  {}
//
//private:
//  int _year;
//  int _month;
//  int _day;
//
//  int& x;         // 引用成员变量
//  const int y;    // const 成员变量
//};
//
//int main()
//{
//  Date d1(2023, 11, 2);   //定义加初始化
//
//  return 0;
//}
//class A       // A类 没有默认构造函数
//{
//public:
//  A(int a)  
//  : _a(a)
//  {}
//
//  void Print()
//  {
//    cout << "_a: " << _a << endl;
//  }
//private:
//  int _a;
//};
//
//class B
//{
//public:
//  B(int x, int a, int ref, int n)
//  : _x(x)
//  , _ref(ref)   // 引用成员初始化
//  , _n(n)       // const 成员初始化
//  {}
//
//  void Print()
//  {
//    cout << "_x: " << _x << endl;
//    _aobj.Print();
//    cout << "_ref: " << _ref << endl;
//    cout << "_n: " << _n << endl;
//  }
//private:
//  int _x;
//  A _aobj;      // 没有默认构造函数
//  int& _ref;    // 引用
//  const int _n; // const
//};
//
//int main()
//{
//  int x, a, ref, n;
//  cout << "_x: "; cin >> x;
//  cout << "_a: "; cin >> a;
//  cout << "_ref: "; cin >> ref;
//  cout << "_n:"; cin >> n;
// 
//  cout << endl;
//
//  B b(x, a, ref, n);
//  b.Print();
//
//  return 0;
//}
class Date
{
public:
  Date(int year, int month, int day)
  : _year(2)        // 初始化列表也定义了值
  , _month(month)
  , _day(day)
  {}
  
  void Print()
  {
    cout << "_year: " << _year << endl;
    cout << "_month: " << _month << endl;
    cout << "_day: " << _day << endl;
  }
private:
  int _year = 1;    // 缺省值
  int _month;
  int _day;
};

int main()
{
  int year, month, day;
  cout << "_year: "; cin >> year;
  cout << "_month: "; cin >> month;
  cout << "_day: "; cin >> day;

  cout << endl;

  Date d(year, month, day);
  d.Print();

  return 0;
}
