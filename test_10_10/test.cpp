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
//#pragma once 
//#include "Stack.h"
//namespace wr 
//{
//  int x = 100;
//}
//
//int main()
//{
//  wr::ST s;
//  wr::StackInit(&s);
//
//  return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//
//namespace N1
//{
//    int a = 10;
//    int b = 11;
//
//    int Add (int a, int b)
//    {
//        return a+b;
//    }
//
//    namespace N2
//    {
//        int c = 12;
//        int d = 13;
//
//        int Mul (int a, int b)
//        {
//            return a*b;
//        }
//    }
//}
//
//int main()
//{
//    printf("N1::a\t\t%d\n", N1::a);
//    printf("N1::b\t\t%d\n", N1::b);
//    printf("N1::N2::c\t%d\n", N1::N2::c);
//    printf("N1::N2::d\t%d\n", N1::N2::d);
//    printf("N1::Add(1,2)\t%d\n", N1::Add(1,2));
//    printf("N1::N2::Mul(3,4)\t%d\n", N1::N2::Mul(3,4));
//
//    return 0;
//}
//#include "Stack.h"
//namespace wr 
//{
//  int x = 100;
//}
//using namespace wr;
//
//int main()
//{
//  ST s;
//  StackInit(&s);
//  StackPush(&s, 1);
//  StackPush(&s, 2);
//  StackPush(&s, 3);
//  StackPush(&s, 4);
//  StackPush(&s, 5);
//
//  return 0;
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
//#include <iostream>
//using std::cin;
//
//int main()
//{
//    int i;
//    cin >> i;       //正确: cin和std::cin含义相同
//    cout << i;      //错误: 没有对应的using声明, 必须使用完整的名字
//    std::cout << i; //正确: 显示地从std中使用cout
//
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//namespace wr 
//{
//  int rand = 100;
//}
//using wr::rand;
//
//int main()
//{
//  cout << rand << endl;
//}
//#include <iostream>
//using std::cout;
//using std::cin;
//using std::endl;
//
//int main()
//{
//    int n1, n2;
//
//    cout << "请输入两个数字: " << endl;
//    cin >> n1 >> n2;
//    cout << n1 << 'x' << n2 << '=' << n1*n2 << endl;
//
//    return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//    int a;
//    double b;
//    char c;
//
//    cin >> a >> b >> c;
//    cout << a << endl;
//    cout << b << endl;
//    cout << c << endl;
//
//    return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//void Func(int a = 0)
//{
//  cout << a << endl;
//}
//
//int main()
//{
//  Func();   // 没有指定实参, 默认使用缺省值
//  Func(10); // 指定了实参, 则使用指定的实参
//
//  return 0;
//}
//#include <iostream>
//
//using namespace std;
//
//void Func(int a = 1, int b = 2, int c = 3)
//{
//    cout << a << endl;
//    cout << b << endl;
//    cout << c << endl;
//    cout << endl;
//}
//
//int main()
//{
//    Func();
//    Func(20);
//    Func(20, 30);
//    Func(20, 30, 40);
//
//    return 0;
//}
#include <iostream>

using namespace std;
int i = 10;
int j = 20;

void Func(int a = i, int b = j, int c = 3)
{
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << endl;
}

int main()
{
    Func();     //a = 10; b = 20; c = 3;
    
    i = 100;
    int j = 200;
    Func();     //a = 100; b = 20; c = 3;

    return 0;
}
