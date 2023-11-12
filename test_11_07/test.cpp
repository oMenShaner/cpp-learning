#include<iostream>
#include<stdlib.h>
using namespace std;

//void Test()
//{
//  int* p1 = (int*)malloc(sizeof(int));
//  free(p1);
//
//  int* p2 = (int*)calloc(4, sizeof(int));
//  int* p3 = (int*)realloc(p2, sizeof(int) * 10);
//
//  //free(p2);  // 这里需要free(p2)吗?
//  free(p3);
//}

//void Test()
//{
//  // 动态申请一个 int 类型的空间, 不会初始化
//  int* ptr1 = new int;          
//
//  // 动态申请一个 int 类型的空间, 并初始化为 10
//  int* ptr2 = new int(10);
//
//  // 动态申请十个 int 类型的空间, 不会初始化
//  int* ptr3 = new int[10];
//
//  // 动态申请十个 int 类型的空间, 并按照列表初始化
//  int* ptr4 = new int[10]{1, 2, 3};       //第四个元素开始被默认初始化为 0
//
//  delete(ptr1);
//  delete(ptr2);
//  delete[](ptr3);
//  delete[](ptr4);
//}

class A
{
  public: 
    A(int a = 0)
      :_a(a)
    {
      cout << "A(int a): " << this << endl;
    }

    ~A()
    {
      cout << "~A(): " << this << endl;
    }

  private:
    int _a;
};

int main()
{
  // new/delete 和 malloc/free 的最大区别就是 new/delete 对于自定义类型出了开空间还会调用构造函数和析构函数
  A *ptr1 = (A*)malloc(sizeof(A));
  A *ptr2 = new A(1);
  free(ptr1);
  delete(ptr2);

  // new[] / delete[]
  A* ptr3 = new A[3]{1, 2, 3};
  delete[](ptr3);

  return 0;
}
