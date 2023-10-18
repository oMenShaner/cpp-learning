**c++的简单介绍**
> C语言是结构化和模块化的语言，适合处理较小规模的程序。对于复杂的问题，规模较大的程序，需要高度的抽象和建模时，C语言则不合适。为了解决软件危机， 20世纪80年代， 计算机界提出了**OOP**(object oriented programming：面向对象)思想，支持面向对象的程序设计语言应运而生。
 
> 1982年，Bjarne Stroustrup博士在C语言的基础上引入并扩充了面向对象的概念，发明了一种新的程序语言。为了表达该语言与C语言的渊源关系，命名为C++。因此：C++是基于C语言而产生的，它既可以进行C语言的过程化程序设计，可以进行以抽象数据类型为特点的基于对象的程序设计，还可以进行面向对象的程序设计。

![1697633474902](image/c++入门/1697633474902.png)


c++几乎兼容了98%的c语言的特性, 同时添加了面向对象,泛型以及c的不足弥补.
本章主要简单讲解c++对C语言的不足弥补的一些语法特性.

# 1. 命名空间
> 在C/C++中, 变量,函数和我们之后要学的类都是大量存在的, 这些变量,函数和类的名称都将存在全局作用域中, 可能会导致很多冲突.

> 使用命名空间的目的就是**对标识符的名称进行本地化**,**以避免命名冲突或者名字污染**, `namespace`关键字的出现就是针对这种问题的.

```cpp
#include <stdio.h>
#include <stdlib.h>

int rand = 10;

int main()
{
    //c语言没法解决这样的命名冲突, namespace就是用来解决这个问题的
    printf("%d\n", rand);
    return 0;
}
```

![1697635140476](image/c++入门/1697635140476.png)
编译器直接提示 `rand` 重定义了, 原来是一个函数, 在 `<stdlib.h>`库函数中.

C语言无法解决命名冲突, 比如我们定义的名称和库里的有冲突, 又比如团队中不同成员的互相之间有命名冲突. 

如果在c语言遇到上面的问题, 是解决不了的, 解决方法只有改名.

而在c++, 提供了 `namespace` 关键字用来解决命名冲突

***
> 命名空间用关键字 `namespace` 定义, 后面跟着命名空间的名字, 然后跟着一对 `{}`, 在 `{}` 里面即命名空间的成员. 

注意: `{}` 后面不需要跟着 `;`

**正确的命名定义**
```cpp
#include <stdio.h>
#include <stdlib.h>

// 正确的命名定义
namespace wr
{
    int rand = 10;
}

void fun()
{
    printf("%d\n", rand);
}

int main()
{
    fun();
    printf("%d\n", rand);
    return 0;
}
```
程序运行结果如下
![1697637428333](image/c++入门/1697637428333.png)

我们发现, 程序并没有得到我们想要的结果.

> 编译器先从局部空间寻找有没有使用这个名字的变量, 如果局部空间没有, 那么就在全局空间来寻找. <font color='red'> 全局空间找不到并不会在命名空间内寻找, 会直接报错 </font>

上述程序就是打印了库中 `rand函数` 的地址, 按整数打印.

*** 
> **一个命名空间就定义了一个新的作用域**, 命名空间中的所有内容都限定在这个作用域内.

下面的程序可以更加直观的观察到, 在命名空间的成员不会被直接当成全局变量的.
```cpp
#include <stdio.h>
#include <stdlib.h>

namespace wr
{
    int rand = 10;
    int x = 1;
}

int main()
{
    printf("%d\n", x);
    return 0;
}
```
![1697637746403](image/c++入门/1697637746403.png)
编译器还没有编译就直接报错: `x`未定义

命名定义相当于一堵墙, 将变量围了起来, 我们使用它们需要指定的字符.

***
那么应该怎么样正确使用命名空间的成员呢?

一种方法就是用`::`域作用限定符, 来使用命名空间的成员.

比如我要使用名为`wr`命名空间的成员`rand`, 就需要这样 `wr::rand`(命名空间名 :: 命名空间成员)

```cpp
#include <stdio.h>
#include <stdlib.h>

namespace wr
{
    int rand = 10;
    int x = 1;
}

void fun()
{
    int rand = 100;
    printf("%d\n", wr::rand);
}

int main()
{
    fun();
    printf("%d\n", wr::rand);
    printf("%d\n", wr::x);
    return 0;
}
```
![1697638363675](image/c++入门/1697638363675.png)
这样就可以正确使用命名空间的成员了, 如果变量名前限定了命名空间, 会直接使用命名空间内的变量, 而不会再在局部空间和全局空间内找.

***
同样, 函数和结构体成员也是可以当作命名空间的成员的, 使用方式也是一样用域作用限定符

```c
#include <stdio.h>
#include <stdlib.h>

namespace wr
{
    int rand = 10;
    
    int Add(int a, int b)
    {
        return a+b;
    }

    struct Node
    {
        int val;
        struct Node* next;
    };
}


int main()
{
    struct wr::Node n1 = {100, NULL};
    
    printf("%d\n", wr::Add(1, 2));
    printf("%d\n", n1.val);
    return 0;
}
```
程序运行结果如下: 
![1697639126460](image/c++入门/1697639126460.png)

注意域作用限定符是直接作用在名称上的, 例如`struct wr::Node` 而不是`wr::struct Node`

*** 
> 命名空间的好处就是防止发生命名冲突, 即使名称一样通过命名空间可以很好的解决这个冲突

```cpp
#include <stdio.h>
#include <stdlib.h>

namespace wr
{
    int rand = 10;
    
    int Add(int a, int b)
    {
        return a+b;
    }
}

namespace wht
{
    int rand = 100;

    int Add(int a, int b)
    {
        return 10*(a+b);
    }
}

int main()
{
    printf("wr::Add(1, 2):%d\n", wr::Add(1, 2));
    printf("wr::rand:%d\n", wr::rand);

    printf("wht::Add(1, 2):%d\n", wht::Add(1, 2));
    printf("wht::rand:%d\n", wht::rand);
    return 0;
}
```
![1697639799265](image/c++入门/1697639799265.png)

***
> 命名空间是可以嵌套的
```cpp
#include <stdio.h>
#include <stdlib.h>

namespace N1
{
    int a = 10;
    int b = 11;

    int Add (int a, int b)
    {
        return a+b;
    }

    namespace N2
    {
        int c = 12;
        int d = 13;

        int Mul (int a, int b)
        {
            return a*b;
        }
    }
}

int main()
{
    printf("N1::a\t\t%d\n", N1::a);
    printf("N1::b\t\t%d\n", N1::b);
    printf("N1::N2::c\t\t%d\n", N1::N2::c);
    printf("N1::N2::d\t\t%d\n", N1::N2::d);
    printf("N1::Add(1,2)\t\t%d\n", N1::Add(1,2));
    printf("N1::N2::Mul(3,4)\t\t%d\n", N1::N2::Mul(3,4));

    return 0;
}
```
***
> 同一工程允许存在多个相同名称的命名空间, 编译器最后会合成一个命名空间
> 同一文件中的多个相同名称的命名空间, 也会合成一个命名空间

- `Stack.h`
```cpp
#include <stdio.h>
#include <stdlib.h>

namespace wr 
{
  typedef struct Stack
  {
    int* a;
    int capacity;
    int top;
  }ST;

  void StackInit(ST* ps);
}
```
- `Stack.cpp`
```cpp
#include "Stack.h"

namespace wr 
{
  void StackInit(ST* ps)
  {
    ps->a = NULL;
    ps->capacity = ps->top = 0;
  }
}
```

- `test.cpp`
```cpp
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
```

程序运行没有任何问题, `test.cpp` 使用到了同工程其他文件的同名命名空间的成员.

***