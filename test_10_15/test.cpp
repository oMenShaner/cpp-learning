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
//#include <time.h>
//#include <iostream>
//using namespace std;
//
//struct A{ int a[10000]; };
//void TestFunc1(A a){}
//void TestFunc2(A& a){}
//void TestRefAndValue()
//{
// A a;
// // 以值作为函数参数
// size_t begin1 = clock();
// for (size_t i = 0; i < 10000; ++i)
// TestFunc1(a);
// size_t end1 = clock();
// // 以引用作为函数参数
// size_t begin2 = clock();
// for (size_t i = 0; i < 10000; ++i)
// TestFunc2(a);
// size_t end2 = clock();
//// 分别计算两个函数运行结束后的时间
// cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;
// cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;
//}
//
//A a;
//// 值返回
//A TestFunc1() { return a;}
//// 引用返回
//A& TestFunc2(){ return a;}
//void TestReturnByRefOrValue()
//{
// // 以值作为函数的返回值类型
// size_t begin1 = clock();
// for (size_t i = 0; i < 100000; ++i)
// TestFunc1();
// size_t end1 = clock();
// // 以引用作为函数的返回值类型
// size_t begin2 = clock();
// for (size_t i = 0; i < 100000; ++i)
// TestFunc2();
// size_t end2 = clock();
// // 计算两个函数运算完成之后的时间
// cout << "TestFunc1 time:" << end1 - begin1 << endl;
// cout << "TestFunc2 time:" << end2 - begin2 << endl;
//}
//
//int main()
//{
//  TestRefAndValue();
//  TestReturnByRefOrValue();
//
//  return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//  // 权限不变
//  int a = 0;
//  int& ra = a;
//  
//  const int b = 100;
//  const int& rb = b;
//  //rb = 200;           //错误  rb是常变量的别名  不能修改
//  const int c = 1000; 
//  //int& rc = c;        //错误  试图让一个非常量引用指向一个常量对象
//  
// // 权限缩小是可以的  比如试图让一个常量引用指向一个非常量对象
//  const int& rra = a;
//
// // 追根究底  虽然引用类型规定需要与其所指向的对象一致
// // 但其实就和类型转换一样  只要指向表达式的类型能够转换成引用类型即可
//  int i = 42;
//  const int& r1 = i;      //虽然类型不一样  但是int->const int 
//  const int& r2 = 42;     //字面量本来就是const int类型的
//  const int& r3 = r1 * 2; //r3也是个常量引用 直接将r1*2的结果让r3指向
//
//  // 原因
//  double dval = 3.14;
//  //int& ri = dval;         //err
//  const int& ri = dval; 
//  // 为了确保让ri绑定一个整数 编译器将上一代码变成了如下如下形式
//  // const int temp = dval; //隐式类型转换成一个临时量整形对象
//  // const int& ri = temp;  //让ri绑定这个临时量
//  
//
//  return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//  int i = 42;
//  int& r1 = i;          //引用r1绑定对象i        
//  const int& r2 = i;    //r2也绑定对象i, 但是不允许通过r2修改i的值
//  r1 = 50;              //可以通过r1修改i的值
//  //r2 = 49;            //不可以通过r2修改i的值
//
//  return 0;
//}
#include<iostream>

using namespace std;

//int main()
//{
//  int a = 0;
//  int& ra = a;
//
//  cout << "&a = " << &a << endl;
//  cout << "&ra = " << &ra << endl;
//
//  return 0;
//}
int main()
{
    int a = 0;

    int& ra = a;
    ra = 20;

    int* pa = &a;
    *pa = 20;

    return 0;
}
