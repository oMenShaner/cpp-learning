#include<iostream>

using namespace std;

//class Date
//{
//private:
//    int _year;
//    int _month;
//    int _day;
//
//public:
//    void Init(int year, int month, int day)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//
//    void Print()
//    {
//        cout << _year << '-' << _month << '-' << _day << endl;
//    }
//};
//
//int main()
//{
//  Date d;
//  d.Print();
//
//  return 0;
//}
//class Date
//{
//private:
//    int _year;
//    int _month;
//    int _day;
//public:
//    Date(int year, int month, int day)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//
//    void Print()
//    {
//      cout << _year << '-' << _month << '-' << _day << endl;
//    }
//};
//
//int main()
//{
//    Date d1;       
//  
//    return 0;
//}
//class Date
//{
//private:
//    int _year;
//    int _month;
//    int _day;
//public:
//    void Print()
//    {
//      cout << _year << '-' << _month << '-' << _day << endl;
//    }
//};
//
//int main()
//{
//  Date d1;
//
//  d1.Print();
//
//  return 0;
//}
//typedef int STDataType;
//class Stack
//{
//private:
//    STDataType* _array;
//    int _capacity;
//    int _top;
//public:
//    //Stack(int capacity = 4)
//    //{
//    //    _array = (STDataType*)malloc(sizeof(STDataType) * capacity);
//
//    //    if (nullptr == _array)
//    //    {
//    //        perror("malloc fail");
//    //        exit(-1);
//    //    }
//
//    //    _capacity = 4;
//    //    _top = 0;
//    //}
//
//    void Print()
//    {
//      cout << "_array: " << _array << endl;
//      cout << "_capacity: " << _capacity << endl;
//      cout << "_top: " << _top << endl << endl;
//    }
//};
//
//class MyQueue
//{
//private:
//    Stack _pushst;
//    Stack _popst;
//    int _size;
//public:
//    void Print()
//    {
//      _pushst.Print();
//      _popst.Print();
//      cout << "_size:" << _size << endl << endl;
//    }
//};
//
//int main()
//{
//    Stack st;
//    MyQueue mq;
//
//    cout << "st:" << endl;
//    st.Print();
//
//    cout << "mq: " << endl;
//    mq.Print();
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
//    Time()
//    {
//        _hour = 0;
//        _minute = 0;
//        _second = 0;
//    }
//
//    void Print()
//    {
//      cout << _hour << ": " << _minute << ": " << _second << endl;
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
//    Date(int year = 2000, int month = 4, int day = 1)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//    void Print()
//    {
//      cout << _year << '-' << _month << '-' << _day << ' ';
//      _t.Print();
//    }
//};
//
//int main()
//{
//    Date d1;
//    d1.Print();
//    
//    Date d2(1999, 1, 1);
//    d2.Print();
//    return 0;
//}
//class Date
//{
//private:
//    int _year = 1970;
//    int _month = 1;
//    int _day = 1;
//public: 
//    ~Date()
//    {//严格来说, Date类不需要析构函数
//        cout << "~Date()" << endl;
//    }
//};
//
//int main()
//{
//    Date d1;
//
//    return 0;
//}
typedef int STDataType;
class Stack
{
private:
    STDataType* _array;
    int _capacity;
    int _top;
public:
    void Print()
    {
      cout << "_array: " << _array << endl;
      cout << "_capacity: " << _capacity << endl;
      cout << "_top: " << _top << endl << endl;
    }
    
		Stack(int capacity = 4)
    {//Stack的构造函数
        _array = (STDataType*)malloc(sizeof(STDataType) * capacity);

        if (nullptr == _array)
        {
            perror("malloc fail");
            exit(-1);
        }

        _capacity = 4;
        _top = 0;
    }

    ~Stack()
    {//Stack的析构函数
        cout << "~Stack()" << endl; 
        free(_array);
        _array = nullptr;
        _capacity = _top = 0;
   	
				Print(); 
		}

};

class MyQueue
{
private:
    //自定义类型
    Stack _pushst;
    Stack _popst;

    //内置类型
    int _size = 0;
public: 
    void Print()
    {
      _pushst.Print();
      _popst.Print();
      cout << "_size:" << _size << endl << endl;
    }
};

int main()
{
    Stack st;
    MyQueue mq;
		
    return 0;
}
