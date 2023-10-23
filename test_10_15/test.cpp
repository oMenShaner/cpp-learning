//#include <iostream>
//using namespace std;
//
//int& count()
//{
//    int n = 0;
//    n++;
//    //...
//
//    return n;
//}
//
//int main()
//{
//    int ret = count();
//    cout << ret << endl;
//    cout << ret << endl;
//
//    return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//int& count()
//{
//    static int n = 0;
//    n++;
//    //...
//
//    return n;
//}
//
//int main()
//{
//    int& ret = count();
//    cout << ret << endl;
//    cout << ret << endl;
//    count();
//    cout << ret << endl;
//
//    return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//int& Add(int a, int b)
//{
//    int c = a + b;
//
//    return c;
//}
//
//int main()
//{
//    int& ret = Add(1, 2);
//    Add(3, 4);
//    cout << "Add(1, 2) is " << ret << endl;
//
//    return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//void fun1()
//{
//    int a = 0;
//    cout << &a << endl;
//}
//
//void fun2()
//{
//    int b = 0;
//    cout << &b << endl;
//}
//
//int main()
//{
//    fun1();
//    fun2();
//    fun1();
//
//    return 0;
//}
#include <time.h>
#include <iostream>
using namespace std;

struct A{ int a[10000]; };
void TestFunc1(A a){}
void TestFunc2(A& a){}
void TestRefAndValue()
{
 A a;
 // 以值作为函数参数
 size_t begin1 = clock();
 for (size_t i = 0; i < 10000; ++i)
 TestFunc1(a);
 size_t end1 = clock();
 // 以引用作为函数参数
 size_t begin2 = clock();
 for (size_t i = 0; i < 10000; ++i)
 TestFunc2(a);
 size_t end2 = clock();
// 分别计算两个函数运行结束后的时间
 cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;
 cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;
}

A a;
// 值返回
A TestFunc1() { return a;}
// 引用返回
A& TestFunc2(){ return a;}
void TestReturnByRefOrValue()
{
 // 以值作为函数的返回值类型
 size_t begin1 = clock();
 for (size_t i = 0; i < 100000; ++i)
 TestFunc1();
 size_t end1 = clock();
 // 以引用作为函数的返回值类型
 size_t begin2 = clock();
 for (size_t i = 0; i < 100000; ++i)
 TestFunc2();
 size_t end2 = clock();
 // 计算两个函数运算完成之后的时间
 cout << "TestFunc1 time:" << end1 - begin1 << endl;
 cout << "TestFunc2 time:" << end2 - begin2 << endl;
}

int main()
{
  TestRefAndValue();
  TestReturnByRefOrValue();

  return 0;
}
