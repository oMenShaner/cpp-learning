//#include <stdio.h>
//#include <stdlib.h>
//
//int rand = 100;
//int main()
//{
//
//  // C语言没法解决这样的命名冲突, namespace就是解决这个问题的
//  printf("%d\n", rand);
//
//  return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//
//namespace wr
//{
//    int rand = 10;
//}
//
//void fun()
//{
//    printf("%d\n", rand);
//}
//
//int main()
//{
//    fun();
//    printf("%d\n", rand);
//    return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//
//namespace wr
//{
//    int rand = 10;
//    int x = 10;
//}
//
//int main()
//{
//    printf("%d\n", x);
//    return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//
//namespace wr
//{
//    int rand = 10;
//    int x = 1;
//}
//
//void fun()
//{
//    int rand = 100;
//    printf("%d\n", wr::rand);
//}
//
//int main()
//{
//    fun();
//    printf("%d\n", wr::rand);
//    printf("%d\n", wr::x);
//    return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//
//namespace wr
//{
//    int rand = 10;
//    
//    int Add(int a, int b)
//    {
//        return a+b;
//    }
//
//    struct Node
//    {
//        int val;
//        struct Node* next;
//    };
//}
//
//
//int main()
//{
//    struct wr::Node n1 = {100, NULL};
//    
//    printf("%d\n", wr::Add(1, 2));
//    printf("%d\n", n1.val);
//    return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//
//namespace wr
//{
//    int rand = 10;
//    
//    int Add(int a, int b)
//    {
//        return a+b;
//    }
//}
//
//namespace wht
//{
//    int rand = 100;
//
//    int Add(int a, int b)
//    {
//        return 10*(a+b); 
//    }
//}
//
//int main()
//{
//    printf("wr::Add(1, 2):%d\n", wr::Add(1, 2));
//    printf("wr::rand:%d\n", wr::rand);
//
//    printf("wht::Add(1, 2):%d\n", wht::Add(1, 2));
//    printf("wht::rand:%d\n", wht::rand);
//    return 0;
//}
#pragma once 
#include "Stack.h"
namespace wr 
{
  int x = 100;
}

int main()
{
  wr::ST s;
  wr::StackInit(&s);

  return 0;
}
