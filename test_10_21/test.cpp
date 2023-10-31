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
class Date
{
public:
    // 构造函数
    Date(int year, int minute, int day)
    {
        cout << "Date(int, int, int)"<< this << endl;
    }

    // 拷贝构造函数
    Date(const Date& d)
    {
        cout << "Date(const Date& d)" << this << endl;
    }

    // 析构函数
    ~Date()
    {
        cout << "~Date()" << this << endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

Date Test(Date d)
{
    Date temp(d);
    return temp; 
}

int main()
{
    Date d1(2000, 1, 1);
    Test(d1);

    return 0;
}
