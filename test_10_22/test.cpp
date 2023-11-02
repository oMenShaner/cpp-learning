#include <iostream>
#include <string.h>

using namespace std;
//typedef int STDataType;
//class Stack
//{
//private:
//    STDataType* _array;
//    int _capacity;
//    int _top;
//public:
//    Stack(int capacity = 4)
//    {
//        cout << "Stack()" << endl; 
//        _array = (STDataType*)malloc(sizeof(STDataType) * capacity);
//
//        if (nullptr == _array)
//        {
//            perror("malloc fail");
//            exit(-1);
//        }
//
//        _capacity = 4;
//        _top = 0;
//    }
//    
//    ~Stack()
//    {
//        cout << "~Stack()" << endl;
//        free(_array);
//        _array = nullptr;
//        _capacity = _top = 0;
//    }
//    
//    void Print()
//    {
//      cout << "_array: " << _array << endl;
//      cout << "_capacity: " << _capacity << endl;
//      cout << "_top: " << _top << endl << endl;
//    }
//};
//
//// 写一个函数, 将 Stack 类类型的变量传值操作当作参数
//void func(Stack st)
//{
//    cout << "func方法中的st:" << endl; 
//    st.Print();    
//}
//
//int main()
//{
//    Stack st;
//    cout << "main方法中的stack:" << endl;
//    st.Print();
//
//    func(st);   //传值操作
//
//    return 0;
//}
//typedef int STDataType;
//class Stack
//{
//private:
//    STDataType* _array;
//    int _capacity;
//    int _top;
//public:
//    void Print()
//    {
//        cout << "_array: " << _array << endl;
//        cout << "_capacity: " << _capacity << endl;
//        cout << "_top: " << _top << endl << endl;
//    }
//
//    // 构造函数
//    Stack(int capacity = 4)
//    {
//        cout << "Stack()" << endl; 
//        _array = (STDataType*)malloc(sizeof(STDataType) * capacity);
//
//        if (nullptr == _array)
//        {
//            perror("malloc fail");
//            exit(-1);
//        }
//
//        _capacity = 4;
//        _top = 0;
//    }
//
//    // 拷贝构造函数
//    Stack(const Stack& st)
//    {
//        cout << "Stack(const Stack& st)" << endl;
//
//        _array = (STDataType*)malloc(sizeof(STDataType) * st._capacity);
//        if (_array == nullptr)
//        {
//            perror("malloc fail");
//            exit(-1);
//        }
//        memcpy(_array, st._array, sizeof(STDataType) * st._top);
//        _top = st._top;
//        _capacity = st._capacity;
//    }
//
//    // 析构函数
//    ~Stack()
//    {
//        cout << "~Stack()" << endl;
//        free(_array);
//        _array = nullptr;
//        _capacity = _top = 0;
//    }
//};
//
//// 写一个函数, 将 Stack 类类型的变量传值操作当作参数
//void func(Stack st)
//{
//    cout << "func方法中的st:" << endl; 
//    st.Print();
//}
//
//int main()
//{
//    Stack stack;
//    cout << "main方法中的stack:" << endl; 
//    stack.Print();
//    func(stack);   //传值操作
//
//    return 0;
//}
//class Time
//{
//private:
//    int _hour;
//    int _minute;
//    int _second;
//public:
//    // 构造函数
//    Time()
//    {
//        _hour = 1;
//        _minute = 1;
//        _second = 1;
//    }
//
//    // 拷贝构造函数
//    Time(const Time& t)
//    {
//        _hour = t._hour;
//        _minute = t._minute;
//        _second = t._second;
//    }
//
//    void Print()
//    {
//        cout << _hour << ": " << _minute << ": " << _second << endl;
//    }
//};
//
//class Date
//{
//private:
//    // 内置类型
//    int _year = 1970;
//    int _month = 1;
//    int _day = 1;
//
//    // 自定义类型
//    Time _t;
//public:
//    void Print()
//    {
//      cout << _year << '-' << _month << '-' << _day << ' ';
//      _t.Print();
//    }
//
//};
//
//int main()
//{
//    Date d1;
//    d1.Print();
//
//    Date d2(d1);
//    d2.Print();
//    return 0;
//}
//class Date
//{
//public:
//    // 构造函数
//    Date(int year, int minute, int day)
//    {
//        cout << "Date(int, int, int)"<< this << endl;
//    }
//
//    // 拷贝构造函数
//    Date(const Date& d)
//    {
//        cout << "Date(const Date& d)" << this << endl;
//    }
//
//    // 析构函数
//    ~Date()
//    {
//        cout << "~Date()" << this << endl;
//    }
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//Date Test(Date d)
//{
//    Date temp(d);
//    return temp; 
//}
//
//int main()
//{
//    Date d1(2000, 1, 1);
//    Test(d1);
//
//    return 0;
//}
class Date
{
public:
    // 获取某年某月的天数
    int getMonthDay(int year, int month)
    {
        int day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

        // 如果是二月且是闰年
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        {
            return 29;
        }

        return day[month];
    }

    // 打印
    void Print()
    {
      cout << _year << '-' << _month << '-' << _day << endl;
    }

    // 全缺省的构造函数
    Date(int year = 1900, int month = 1, int day = 1)
    {
        _year = year;
        _month = month;
        _day = day;
    }
  
    // 拷贝构造函数
    Date(const Date& d)
    {
      _year = d._year;
      _month = d._month;
      _day = d._day;
    }

    // 析构函数
    ~Date()
    {
      _year = _month = _day = 0;
    }

    // 赋值运算符重载
    Date& operator=(const Date& d)
    {
      if (this != &d)
      {
        _year = d._year;
        _month = d._month;
        _day = d._day;
      }
      return *this;
    }
    
    // 日期 += 天数
    Date& operator+=(int day)
    {
      _day += day;
      // 如果日超了
      if (_day > getMonthDay(_year, _month))
      {
        _day -= getMonthDay(_year, _month);
        _month++;
        // 如果月超了
        if (_month == 13)
        {
          _year++;
          _month = 1;
        }
      }
      
      return *this;
    }

    // 日期 + 天数
    Date operator+(int day) 
    {
      Date temp(*this); // 用 *this 拷贝构造 temp 
      temp += day;      // 直接调用运算符重载 +=
      
      return temp;
    }

    // 日期 -= 天数
    Date& operator-=(int day)
    {
      _day -= day;
      // 如果天数不够，用前一个月的天数补
      while (_day <= 0)
      {
        _month--;
        if (_month == 0)
        {
          _year--;
          _month = 12;
        }
        _day += getMonthDay(_year, _month);
      }
      return *this;
    }
    
    // 日期 - 天数
    Date operator-(int day)
    {
      Date temp(*this);
      temp -= day;

      return temp;
    }

    // > 运算符重载
    bool operator>(const Date& d)
    {
        if (_year > d._year)
            return true;
        if (_month > d._month)
            return true;
        if (_day > d._month)
            return true;
        return false;
    }
    
    // 前置++
    Date& operator++()
    {
      *this += 1;

      return *this;
    }

    // 后置++
    Date operator++(int)
    {
      Date temp(*this);
      *this += 1;
      
      return temp;
    }
    // 后置--
    Date operator--(int)
    {
      Date temp(*this);
      *this -= 1;

      return temp;
    }

    // 前置--
    Date& operator--()
    {
      *this -= 1;

      return *this;
    }

    // == 运算符重载
    bool operator==(const Date& d)
    {
      return _year == d._year
        && _month == d._month
        && _day == d._day;
    }
    
    // >= 运算符重载
    bool operator>=(const Date& d)
    {
      return (*this > d) || (*this == d);
    }

    // < 运算符重载
    bool operator<(const Date& d)
    {
      return !(*this >= d);
    }
  
    // <= 运算符重载
    bool operator<=(const Date& d)
    {
      return (*this < d) || (*this == d);
    }

    // != 运算符重载
    bool operator!=(const Date& d)
    {
      return !(*this == d);
    }

    // 日期 - 日期 返回天数
    int operator-(const Date& d);
private:
    int _year;
    int _month;
    int _day;
};

//bool operator==(const Date& d1, const Date& d2)
//{
//    return d1._year == d2._year
//    && d1._month == d2._month
//    && d1._day == d2._day;
//}

int main()
{
    Date d1;
    Date d2(2023, 1, 1);
    Date d3(1900, 1, 1);

    // 可以写成函数调用的形式
    //cout << d1.operator==(d2) << endl;

    // 最好写成正常运算符的形式, 编译器会自己转化成运算符重载函数
    //cout << (d1 == d3) << endl;
    
    //cout << (d1 > d2) << endl; 
    //cout << (d2 > d3) << endl;
  
    cout << "d2 += 40前:"; d2.Print();
    d2 += 40;
    cout << "d2 += 40后:"; d2.Print();

    cout << "d1 + 10前:"; d1.Print();
    d1 + 10;
    cout << "d1 + 10后:"; d1.Print();

    d2 = d1;
    d2.Print();

    (d2 - 40).Print();
    (d2 - 50).Print();
    d2.Print();

    cout << (d1 != d3) << endl;
    cout << (d1 >= d3) << endl;
    cout << (d1 <= d3) << endl;

    return 0;
}

