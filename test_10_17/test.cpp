#include<iostream>
#include<typeinfo>
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

//int TestAuto()
//{
//    return 10;
//}
//
//int main()
//{
//    int a = 10;
//    auto b = a;
//    auto c = 'a';
//    auto d = &c;
//    auto e = TestAuto();
//    auto& f = a;
//    f++;
//
//    cout << typeid(b).name() << endl;
//    cout << typeid(c).name() << endl;
//    cout << typeid(d).name() << endl;
//    cout << typeid(e).name() << endl;
//    cout << typeid(f).name() << endl;
//
//    return 0;
//}
//int main()
//{
//    int x = 10;
//    auto a = &x;
//    auto* b = &x;
//    auto& c = x;
//
//    cout << typeid(a).name() << endl;
//    cout << typeid(b).name() << endl;
//    cout << typeid(c).name() << endl;
//
//    *a = 30;
//    cout << x << endl;
//
//    *b = 40;
//    cout << x << endl;
//
//    c = 50;
//    cout << x << endl;
//
//    return 0;
//}
//void TestAuto()
//{
//    auto a = 1, b = 2;
//    auto c = 3, d = 4.0;    //改行会编译失败, c 和 d 的初始化表达式类型不同
//}
//
//void TestAuto(auto x)
//{
//
//}
//void TestAuto()
//{
//    int a[] = {1, 2, 3};
//    auto b[] = {4, 5, 6};
//}
//void TestFor()
//{
//  int array[] = {1, 2, 3, 4, 5};
//
//  for (int i = 0; i < sizeof(array)/sizeof(int); i++)
//    array[i] *= 2;
//
//  for (int* p = array; p < array + sizeof(array)/sizeof(int); p++)
//    cout << *p << endl;
//}

//void TestFor()
//{
//    int array[] = {1, 2, 3, 4, 5};
//
//    for (auto& e : array)
//        e *= 2;
//
//    for (auto e : array)
//        cout << e << endl;
//}
//
//int main()
//{
//  TestFor();
//
//  return 0;
//}
//void f(int)
//{
//    cout << "f(int)" << endl;
//}
//
//void f(int*)
//{
//    cout << "f(int*)" << endl;
//}
//
//int main()
//{
//    f(0);
//    f(NULL);
//    f((int*)NULL);
//
//    return 0;
//}
//typedef int STDataType;
//struct Stack
//{
//    void Init(size_t capacity)
//    {
//        _array = (STDataType*)malloc(sizeof(STDataType) * capacity);
//        if (nullptr == _array)
//        {
//            perror("malloc fail");
//            return;
//        }
//
//        _capacity = capacity;
//        _top = 0;
//    }
//
//    void Push(const STDataType& data)
//    {
//        _array[_top] = data;
//        _top++;
//    }
//
//    void Destroy()
//    {
//        if (_array)
//        {
//            free(_array);
//            _array = nullptr;
//            _capacity = _top = 0;
//        }
//    }
//    STDataType* _array;
//    int _capacity;
//    int _top;
//};
//
//int main()
//{
//    Stack s;
//    s.Init(10);
//    s.Push(1);
//    s.Push(2);
//    s.Push(3);
//    s.Push(4);
//    s.Push(5);
//
//    s.Destroy();
//
//    return 0;
//}
class Date
{
  public:
    void Init(int year, int month, int day)
    {
      _year = year;
      _month = month;
      _day = day;
    }
    void Print()
    {
      cout << _year << '-' << _month << '-' << _day << endl;
    }
  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  Date d;
  d.Init(2020, 1, 1);
  d.Print();

  return 0;
}
















