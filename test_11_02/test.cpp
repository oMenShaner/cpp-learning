#include <iostream>

using namespace std;

// class Date
//{
// public:
//   Date(int year, int month, int day)
//   : _year(year)
//   , _month(month)
//   , _day(day)
//   , x(_year)
//   , y(month)
//   , _year(month)
//   {}
//
// private:
//   int _year;
//   int _month;
//   int _day;
//
//   int& x;         // 引用成员变量
//   const int y;    // const 成员变量
// };
//
// int main()
//{
//   Date d1(2023, 11, 2);   //定义加初始化
//
//   return 0;
// }
// class A       // A类 没有默认构造函数
//{
// public:
//   A(int a)
//   : _a(a)
//   {}
//
//   void Print()
//   {
//     cout << "_a: " << _a << endl;
//   }
// private:
//   int _a;
// };
//
// class B
//{
// public:
//   B(int x, int a, int ref, int n)
//   : _x(x)
//   , _ref(ref)   // 引用成员初始化
//   , _n(n)       // const 成员初始化
//   {}
//
//   void Print()
//   {
//     cout << "_x: " << _x << endl;
//     _aobj.Print();
//     cout << "_ref: " << _ref << endl;
//     cout << "_n: " << _n << endl;
//   }
// private:
//   int _x;
//   A _aobj;      // 没有默认构造函数
//   int& _ref;    // 引用
//   const int _n; // const
// };
//
// int main()
//{
//   int x, a, ref, n;
//   cout << "_x: "; cin >> x;
//   cout << "_a: "; cin >> a;
//   cout << "_ref: "; cin >> ref;
//   cout << "_n:"; cin >> n;
//
//   cout << endl;
//
//   B b(x, a, ref, n);
//   b.Print();
//
//   return 0;
// }
// class Date
//{
// public:
//   Date(int year, int month, int day)
//   : _year(2)        // 初始化列表也定义了值
//   , _month(month)
//   , _day(day)
//   {}
//
//   void Print()
//   {
//     cout << "_year: " << _year << endl;
//     cout << "_month: " << _month << endl;
//     cout << "_day: " << _day << endl;
//   }
// private:
//   int _year = 1;    // 缺省值
//   int _month;
//   int _day;
// };
//
// int main()
//{
//   int year, month, day;
//   cout << "_year: "; cin >> year;
//   cout << "_month: "; cin >> month;
//   cout << "_day: "; cin >> day;
//
//   cout << endl;
//
//   Date d(year, month, day);
//   d.Print();
//
//   return 0;
// }
//class Time
//{
//public:
//  Time(int t = 4)
//  {
//    cout << "Time(int t = 4)" << endl;
//    _t = t;
//  }
//
//private:
//  int _t;
//};
//
//class Date
//{
//public:
//  Date()
//  {
//  }
//
//private:
//  int _day;
//  Time _t;
//};
//
//int main()
//{
//  Date d1;
//
//  return 0;
//}
//class A
//{
//public:
//  A(int a)
//    :_a1(a)
//    ,_a2(_a1)
//  {}
//
//  void Print()
//  {
//    cout << _a1 << ' ' << _a2 << endl;
//  }
//
//private:
//  int _a2;
//  int _a1;
//};
//
//int main()
//{
//  A aa(1);
//  aa.Print();
//
//  return 0;
//}
//class A
//{
//public:
//  A(int a)
//  :_a(a)
//  {
//    cout << "A(int a)" << endl; 
//  }
//
//  A(const A& aa)
//  {
//    _a = aa._a;
//    cout << "A(const A aa)" << endl; 
//  }
//private:
//  int _a;  
//};
//
//int main()
//{
//  A aa1 = 1;  //会发生隐式类型转换
//
//  return 0;
//}
//class A // 默认构造函数不只一个参数
//{
//public:
//  A(int a, int b)
//    :_a(a)
//    ,_b(b)
//  {}
//
//private:
//  int _a;
//  int _b;
//};
//
//class B //  右值不能隐式转换为构造函数参数的类型
//{
//public:
//  B(A a)
//    :_a(a)
//  {}
//
//private:
//  A _a;
//};
//
//int main()
//{
//  A aa = 1; //no viable conversion from 'int' to A 
//  B bb = 0; //no viable conversion from 'int' to B
//
//  return 0;
//}
//class A
//{
//public:
//  explicit A(int a)
//  :_a(a)
//  {
//    cout << "A(int a)" << endl; 
//  }
//
//  A(const A& aa)
//  {
//    _a = aa._a;
//    cout << "A(const A aa)" << endl; 
//  }
//private:
//  int _a;  
//};
//
//int main()
//{
//  A aa1 = 1;  // 使用explicit关键字可以防止隐式类型转换
//
//  return 0;
//}
//class A
//{
//public:
//  A() { ++_scount; }
//  A(const A& a) { ++_scount; }
//  ~A() { --_scount; }
//  static int getCount() { return _scount; } // 只有静态方法可以访问静态成员
//
//private:
//  static int _scount; // 声明静态成员
//};
//
//int A::_scount = 0; // 初始化静态成员
//
//int main()
//{
//  cout << A::getCount() << endl;
//  A a1, a2;
//  A a3(a1);
//  cout << A::getCount() << endl;
//
//  return 0;
//}
//class Time
//{
//  friend class Date; //声明 Date 类为 Time 类的友元类, 则在 Date 类中可以直接访问 Time 类的私有成员变量
//  public:
//    Time (int hour = 0, int minute = 0, int second = 0)
//      :_hour(hour)
//      ,_minute(minute)
//      ,_second(second)
//    {}
//
//  private:
//    int _hour;
//    int _minute;
//    int _second;
//};
//
//class Date
//{
//  public:
//    Date (int year = 1970, int month = 1, int day = 1)
//      :_year(year)
//      ,_month(month)
//      ,_day(day)
//    {}
//
//    void SetTimeOfDate(int hour, int minute, int second)
//    {
//      // 直接访问 Time 类的私有成员变量
//      _t._hour = hour;
//      _t._minute = minute;
//      _t._second = second;
//    }
//
//private:
//  int _year;
//  int _month;
//  int _day;
//  Time _t;
//};
//class A
//{
//  private:
//    static int _k;
//    int _h;
//  public:
//    class B // B 天生是 A 的友元
//    {
//      public:
//        void func(const A& a)
//        {
//          cout << _k << endl;   // ok
//          cout << a._h << endl; // ok
//        }
//    };
//};
//
//int A::_k = 1;
//
//int main()
//{
//  A::B b;
//  b.func(A());
//
//  cout << sizeof(A) << endl;
//  cout << sizeof(A::B) << endl;
//
//  return 0;
//}
//class A
//{
//  public:
//    A(int a = 0)
//      :_a(a)
//    {
//      cout << "A(int a)" << endl;
//    }
//
//    ~A()
//    {
//      cout << "~A()" << endl;
//    }
//
//  private:
//    int _a;
//};
//
//class Solution
//{
//  public:
//    int Sum_Solution(int n)
//    {
//      //..
//      return n;
//    }
//};
//
//int main()
//{
//  A();    // 定义匿名对象, 生命周期只有这一行, 下一行就会自动调用析构函数
//
//  A aa1(2); // 先用 2 构造匿名对象, 再用匿名对象拷贝构造 aa1
//
//  // 匿名对象在这样的场景下就很好用
//  Solution().Sum_Solution(10);
//
//  return 0;
//}
class A
{
  public:
    A(int a = 0) 
      :_a(a)
    { 
      cout << "A()" << endl; 
    }
    
    A(const A& a) 
      :_a(a._a)
    { 
      cout << "A(const A& a)" << endl; 
    }

    A& operator=(const A& a) 
    { 
      cout << "A& operator=(const A& a)" << endl; 
      
      if (this != &a)
      {
        _a = a._a;
      }

      return *this;
    }

    ~A() 
    { 
      cout << "~A()" << endl; 
    }
  private:
    int _a;
};

void f1(A aa) 
{}

A f2() 
{ 
  A aa; 
  return aa; 
}

int main()
{
  // 传值传参, 不能优化, 已经创建出来了
  A aa1;
  f1(aa1);
  cout << endl; 

  // 传值返回
  f2();
  cout << endl;

  // 隐式类型转换 连续构造 + 拷贝构造 -> 直接构造
  f1(1);
  cout << endl;
  
  f1(A(2));
  cout << endl;

  A aa2 = f2();
  cout << endl;

  aa1 = f2();
  cout << endl;

  return 0;
}
