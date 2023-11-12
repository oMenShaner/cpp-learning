#include<iostream>

using std::cout;
using std::cin;
using std::endl;
using std::nullptr_t;

//void Test()
//{
//  char* p1 = new char[1024*1024*1024];
//  cout << (void*)p1 << endl;              // char*类型不能直接使用cout, 会被自动识别成字符串
//
//  char* p2 = new char[1024*1024*1024];
//  cout << (void*)p2 << endl;
//
//}

//int main()
//{
//  try
//  {
//    Test();
//  }
//  catch(const std::exception& e)
//  {
//    cout << "1" << endl;
//    std::cerr << e.what() << '\n';
//  }
//  
//  return 0;
//}

// class Stack
// {
//   public:
//     Stack(int capacity = 4)
//     :_capacity(capacity)
//     ,_top(0)
//     {
//       _array = new int[_capacity]; 
//     }
// 
//     ~Stack()
//     {
//       delete[](_array);
//       _array = nullptr;
//       _capacity = _top = 0;
//     }
// 
//   private: 
//     int* _array;
//     int _capacity;
//     int _top;
// };

//void *__CRTDECL operator new(size_t size) __THROW1(__STD bad_alloc)
//{
//  // try to allocate size bytes
//  void *p;
//  while ((p = malloc(size)) == 0)
//    if (_callnewh(size) == 0)
//    {
//      // report no memory
//      // 如果内存申请失败了, 这里会抛出bad_alloc 类型异常
//      static const std::bad_alloc nomem;
//      _RAISE(nomem);
//    }
//
//  return (p);
//}

// int main()
// {
//   int* p1 = (int*)malloc(sizeof(int));
//   free(p1);

//   int* p2 = new int;
//   delete(p2);

//   int* p3 = (int*)operator new(sizeof(int));
//   operator delete(p3);

//   return 0;
// }

// int main()
// {
//   Stack* p1 = new Stack[8];
//   delete[](p1);
// 
//   int* p2 = new int[10];
//   delete(p2);
//   return 0;
// }

class A
{
  public:
    A(int a = 0)
      :_a(a)
    {
      cout << "A():" << this << endl;
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
  A* p1 = (A*)malloc(sizeof(A));          // 此时p1所指向的空间并没有被初始化, malloc只有申请空间的作用
  new(p1)A;   // 使用定位new进行p1对象的构造
  p1->~A();   // 可以显示调用析构函数
  free(p1);

  A* p2 = (A*)operator new(sizeof(A));    // operator new 同样只申请空间 并不初始化空间
  new(p2)A(2);  // 使用列表进行初始化
  p2->~A();
  operator delete(p2);

  return 0;
}