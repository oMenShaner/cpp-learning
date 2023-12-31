**c++的简单介绍**

> C 语言是结构化和模块化的语言，适合处理较小规模的程序。对于复杂的问题，规模较大的程序，需要高度的抽象和建模时，C 语言则不合适。为了解决软件危机， 20 世纪 80 年代， 计算机界提出了**OOP**(object oriented programming：面向对象)思想，支持面向对象的程序设计语言应运而生。

> 1982 年，Bjarne Stroustrup 博士在 C 语言的基础上引入并扩充了面向对象的概念，发明了一种新的程序语言。为了表达该语言与 C 语言的渊源关系，命名为 C++。因此：C++是基于 C 语言而产生的，它既可以进行 C 语言的过程化程序设计，可以进行以抽象数据类型为特点的基于对象的程序设计，还可以进行面向对象的程序设计。

![1697633474902](image/c++入门/1697633474902.png)

c++几乎兼容了 98%的 c 语言的特性, 同时添加了面向对象,泛型以及 c 的不足弥补.
下面主要简单讲解 c++对 C 语言的不足弥补的一些语法特性.

# 1. 命名空间

> 在 C/C++中, 变量,函数和我们之后要学的类都是大量存在的, 这些变量,函数和类的名称都将存在全局作用域中, 可能会导致很多冲突.

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

C 语言无法解决命名冲突, 比如我们定义的名称和库里的有冲突, 又比如团队中不同成员的互相之间有命名冲突.

如果在 c 语言遇到上面的问题, 是解决不了的, 解决方法只有改名.

而在 c++, 提供了 `namespace` 关键字用来解决命名冲突

---

> 命名空间用关键字 `namespace` 定义, 后面跟着命名空间的名字, 然后跟着一对 `{}`, 在 `{}` 里面即命名空间的成员.

注意: `{}` 后面不需要跟着 `;`

## 正确的命名定义

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

---

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

---

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

---

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
![1697719571753](image/c++入门/1697719571753.png)

注意域作用限定符是直接作用在名称上的, 例如`struct wr::Node` 而不是`wr::struct Node`

---

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

---

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
    printf("N1::N2::c\t%d\n", N1::N2::c);
    printf("N1::N2::d\t%d\n", N1::N2::d);
    printf("N1::Add(1,2)\t%d\n", N1::Add(1,2));
    printf("N1::N2::Mul(3,4)\t%d\n", N1::N2::Mul(3,4));

    return 0;
}
```

![1697718461250](image/c++入门/1697718461250.png)

---

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
  void StackPush(ST* ps, int x);
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

  void StackPush(ST* ps, int x)
  {
    //...
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

---

## 命名空间的使用

还是使用上面栈的数据结构, 如果我想一次性将 1,2,3,4,5 压入栈, 需要如下操作

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
  wr::StackPush(&s, 1);
  wr::StackPush(&s, 2);
  wr::StackPush(&s, 3);
  wr::StackPush(&s, 4);
  wr::StackPush(&s, 5);

  return 0;
}
```

在每个 `StackPush` 前面都要**加上命名空间和域作用限定符**, 这显然造成代码冗长.

有一种方法可以避免这种情况, **直接使用 `using` 指示**, 将整个命名空间名称引入:

```cpp
#include "Stack.h"
namespace wr
{
  int x = 100;
}
using namespace wr;

int main()
{
  ST s;
  StackInit(&s);
  StackPush(&s, 1);
  StackPush(&s, 2);
  StackPush(&s, 3);
  StackPush(&s, 4);
  StackPush(&s, 5);

  return 0;
}
```

> `using`指示使得某个特定的命名空间中所有的名字都可见, 这样我们就无需再为它们添加任何前缀限定符了.

> 简写的名字从 `using` 指示开始, 一直到 `using` 指示所在的作用域结束都能使用.

---

还有一种最安全的方法, 也就是**使用 `using` 声明**

```cpp
#include <iostream>
using std::cin;

int main()
{
    int i;
    cin >> i;       //正确: cin和std::cin含义相同
    cout << i;      //错误: 没有对应的using声明, 必须使用完整的名字
    std::cout << i; //正确: 显示地从std中使用cout

    return 0;
}
```

![1697719981668](image/c++入门/1697719981668.png)
这也是 c++特有的输入输出代码, 马上就会讲解这个知识点, 首先中心放在 `using` 声明里.

第 232 行, 编译器直接提示我没有对应的 using 声明.

当然, 我是可以直接用 `using` 指示: `using namespace std`
但是, 库中的命名空间 `std` 显然有很多成员, 如果一次性全部展开, 这是不安全的, **最好最安全的方式就是使用 `using` 声明**. 我需要用到什么成员, 我就声明什么成员.

---

综上:

> 命名空间的使用有三种方式:
>
> - 加命名空间名称及作用域限定符 `::`
> - `using` 声明: 使用`using`将命名空间中某个成员引入
> - `using` 指示: 使用`using namespace 命名空间名称` 引入

注意: **头文件不应包含 `using` 声明**. 如果头文件有某个 `using` 声明, 那么每个使用的该头文件的文件就都会有这个圣经. 对于某些程序来说, 由于不经意间包含了一些名字, 反而可能产生始料未及的名字冲突.

---

# 2. c++输入与输出

> c++并未定义任何输入输出(**IO**)语句, 取而代之, 包含了一个全面的**标准库(standard library)** 来提供 **IO**机制(以及很多其他设施)

> `iostream` 库包含两个基础类型 `istream` 和 `ostream`, 分别表示输入流和输出流.

> 一个流就是一个字符序列, 随着时间的推移, 字符是顺序生成或消耗的.

## 标准输入输出对象

标准库定义了 4 个 **IO** 对象.

> `cin` : 标准输入(键盘)
> `cout` : 标准输出(控制台)
> `cerr` : 标准错误
> `clog` : 输出程序运行时的一般性信息

实际上 `cin` 和 `cout` 分别是 `istream` 和 `ostream` 类型的对象, 后序会详细讲解

## 向流写入 读取数据

```cpp
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    int n1, n2;

    cout << "请输入两个数字: " << endl;
    cin >> n1 >> n2;
    cout << n1 << 'x' << n2 << '=' << n1*n2 << endl;

    return 0;
}
```

![1697722160864](image/c++入门/1697722160864.png)

---

**向流写入数据**

```cpp
cout << "请输入两个数字: " << endl;
```

这句表达式使用了**输出运算符(`<<`)**在标准输出上打印信息.

`<<` 接受两个运算对象: 左侧的运算对象必须是一个 `ostream` 对象, 右侧的运算对象是要打印的值.

`endl` 是一个被称为 **操纵符** 的特殊值. 写入 `endl` 的效果是结束当前行, 相当于`\n`.

---

**从流中读取数据**
`cin >> n1 >> n2;`用于读入输入数据

**输入运算符(`>>`)** 与输出运算符类似, 它接受一个 `istream` 作为其左侧运算对象, 接受一个对象为其右侧运算对象.

---

> 使用 c++输入输出更方便, 不需要像 `printf/scanf` 那样, 需要手动输入格式. c++的输入输入可以自动识别格式.

```cpp
#include <iostream>

using namespace std;

int main()
{
    int a;
    double b;
    char c;

    cin >> a >> b >> c;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}
```

![1697723154504](image/c++入门/1697723154504.png)

若有打印精度的需求, 可以输入输出流和`printf/scanf`函数结合使用, 当然官方库也提供了一些方法, 如果需要用可以自查.

# 3. 缺省参数

> 缺省参数是**在声明或定义函数时**为函数**参数指定一个缺省值**.

> 在调用该函数时, 如果没有指定实参则使用该形参的缺省值, 否则则使用该实参.

```cpp
void Func(int a = 0)
{
    cout<<a<<endl;
}

int main()
{
    Func();     // 没有传参时，使用参数的默认值
    Func(10);   // 传参时，使用指定的实参

    return 0;
}

```

程序运行如下:
![1697808038544](image/c++入门/1697808038544.png)

---

> 缺省参数让函数调用非常灵活

## 缺省参数分类

- **全缺省参数**
  > 函数的所有形参都提供了默认实参

```cpp
void Func(int a = 1, int b = 2, int c = 3)
{
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << endl;
}

int main()
{
    Func();
    Func(20);           // a = 20;
    Func(20, 30);       // a = 20; b = 30;
    Func(20, 30, 40);   // a = 20; b = 30; c = 40;

    return 0;
}
```

![1697808582963](image/c++入门/1697808582963.png)

> 若函数有多个形参有默认实参, 如果函数指定了实参, 默认从第一个有默认实参的形参开始指定实参.

> 只能省略尾部的实参, 而不能省略前面的实参.

例如下面的函数调用就是错误的

```cpp
Func(, 20, );
```

---

- **半缺省参数**
  > 至少有一个形参没有默认实参

```cpp
void Func(int a, int b = 2, int c = 3)
{
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << endl;
}

int main()
{
    Func();             // err
    Func(20);           // a = 20;
    Func(20, 30);       // a = 20; b = 30;
    Func(20, 30, 40);   // a = 20; b = 30; c = 40;

    return 0;
}
```

根据我们上面得到的结论

> 拥有半缺省参数的函数, 对于没有默认实参的形参, 都需要在函数调用的时候指定实参.

> 半缺省参数必须**从右向左依次来给出**, 不能间隔着给

```cpp
void Func(int a = 1, int b, int c);         //err
void Func(int a = 1, int b, int c = 3);     //err
void Func(int a, int b = 2, int c);         //err
void Func(int a, int b, int c = 3);         //正确
```

总结: <font color='red'>缺省参数后面都应为缺省参数.</font>

> 合理设置形参的顺序, 尽量让不怎么使用默认值的形参出现在前面, 而让哪些经常使用默认值的形参出现在后面.

---

## 缺省参数声明

对于函数的声明来说, 通常的习惯是将其放在头文件中, 并且一个函数只声明依次, <font color='red'> 但是多次声明同一个函数也是合法的!</font>

> 不过需要注意的是, **函数的后序声明只能为之前那些没有默认值的形参添加默认实参, 而且该形参的右侧的所有形参必须都有默认值.**

例如已经声明了一个函数:

```cpp
void Func(int a, int b, int c = 3);
```

是不可以在这个声明后面对已经有默认值的形参进行修改默认值的:

```cpp
void Func(int a, int b, int c = 4);     //错误 在上面已经对 c 赋值过默认值, 不可再进行修改
```

同样,如果该形参的右边不全是缺省参数也是不可以的:

```cpp
void Func(int a = 1, int b, int c = 3);   //错误 形参 a 右侧不全是缺省参数
```

下面这样是正确的

```cpp
void Func(int a = 1, int b = 2, int c = 3);
```

> <font color='red'>通常来说, 应该在函数声明中指定缺省参数, 不可在函数声明和函数定义同时指定缺省参数</font>

---

## 缺省参数初始值

> 缺省值必须是常量或全局变量.不可以是局部变量

```cpp
int i = 10;
int j = 20;

void Func(int a = i; int b = j; int c = 3)
{
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << endl;
}

int main()
{
    Func();         //a = 10; b = 20; c = 3;

    i = 100;        //改变了默认实参的值
    int j = 200;    //没有改变默认实参的值
    Func();         //a = 100; b = 20; c = 3;

    return 0;
}
```

![1697810823350](image/c++入门/1697810823350.png)
如果缺省参数的缺省值是全局变量, 那么他们的缺省值是在函数调用后才真正开始计算.
这也就是为什么在修改了全部变量后, 形参的默认值也发生了改变.

# 4. 函数重载

自然语言中, 一个词可以有多重含义, 这就是我们所说的二义性. 人们可以根据不同上下语境得到不同的意思, 这个词就被重载了.

## 函数重载概念

> **函数重载**: 同一作用于的几个**函数名字相同**但**形参列表(参数个数 或 类型 或 类型顺序)不同**.

```cpp
int Add(int left, int right)
{
	return left + right;
}

double Add(double left, double right)
{
	return left + right;
}

int main()
{
    cout << Add(1, 2) << endl;
    cout << Add(1.1, 2.2) << endl;

    return 0;
}
```

![1698059487248](image/c++入门/1698059487248.png)
函数接受的形参类型不一样, 但是执行的操作非常类似. 当调用这些函数的时候, 编译器会根据实际传递的实参类型来判断想要的是哪个函数.

---

下面的两个函数:

```cpp
void f()
{
    cout << "f()" << endl;
}

void f(int a = 1)
{
    cout << "f(int a)" << endl;
}
```

虽然构成了重载关系, 但是不能实际存在, 对于编译器来说无法判断传入的实参类型, 判断不了程序需要哪个函数.
![1698059779578](image/c++入门/1698059779578.png)

---

再次强调一遍, 重载与返回值是否一样无关, 编译器只会检查函数名和形参列表.
像下面的两个函数就会造成重定义:

```cpp
double Add(double left, double right)
{
    return left + right;
}

int Add (double left, double right)
{
    return left + right;
}
```

---

## c++支持函数重载的原理--名字修饰(name Mangling)

在之前学习的关于 c 语言程序从代码成为一个程序一共经历四个阶段: **预处理 编译 汇编 链接** . 具体移步[c 语言:程序环境和预处理](https://blog.csdn.net/Kuzuba/article/details/131898839?spm=1001.2014.3001.5502)

实际项目通常分为多个文件, 这里我创建了两个文件

- `Func.h`

```cpp
#pragma once
#include <iostream>
using namespace std;

void f(int a, char b);
void f(char a, int b);
```

- `Func.c`

```cpp
#include "Func.h"

void f(int a, char b)
{
    cout << "f(int a, char b)" << endl;
}

void f(char a, int b)
{
    cout << "f(char a, int b)" << endl;
}
```

- `test.cpp`

```cpp
#include "Func.h"

int main()
{
    f(1, 'x');
    f('y', 2);

    return 0;
}
```

---

生成可执行程序后, 使用`objdump -S`来查看程序的汇编代码, 观察到在程序中两个重载函数所在的地址不是一样的, 同时所对应的函数名也是不一样的

![1698061457095](image/c++入门/1698061457095.png)

首先在编译阶段就已经将两个函数分别命名, 接着在汇编阶段形成符号表, 最后在链接阶段, 进行符号表中函数的重定位.
![1698061577813](image/c++入门/1698061577813.png)

最终, 在主函数呈现出函数重载的效果.
![1698061550846](image/c++入门/1698061550846.png)

---

在 Linux 中 g++ 编译器的名称修饰规则是这样的:
`_Z[长度][原始函数名][参数类型]`
例如
`void f(char a, int b)` 修饰为 `_Z1fci`
`void f(int a, char b)` 修饰为 `_Z1fic`

而在 c 语言中不会有名称修饰, 所以 C 语言中不能重载.
这也是为什么返回值不同不构成重载, 编译器不会将函数的返回值作为要素来命名.

# 5. 引用

> 引用(reference)不是定义一个新对象, 而是给已存在对象**取了个别名**, 引用类型引用另一种类型.

> 通常将声明符写成 `&d` 的形式来定义引用类型, 其中 `d` 是声明的变量名

```cpp
int val = 1024;
int &refVal = val;      //refVal 指向 val (是 val 的别名)
int &refVal2;           //报错: 引用必须被初始化

```

一般在初始化变量的时候, 初始值会被拷贝到新建的对象中. 然而定义引用时, 程序**把引用和它的初始值绑定在一起, 而不是将初始值拷贝给引用.** 一旦初始化完成, 引用将永远和它的初始值绑定在一起, 不能将该引用绑定到另一个对象上, 所以**引用必须初始化**.

```cpp
int val1 = 1024;
int val2 = 100;
int &refVal = val1;
&refVal = val2;             //报错: 引用不能被改变
refVal = val2;              //正确, 将val1 的值改为100
```

![1698064869176](image/c++入门/1698064869176.png)

## 引用即别名

> 引用并非对象, 相反的, 它指示为一个已经存在的对象所起的另外一个名字.

```cpp
int main()
{
    int a = 10;
    int &b = a;     // b是a的别名
    int &c = b;     // c是b的别名, 也是a的别名
    int d = a;      // 将a的值赋给d, 新开辟了一块内存空间

    return 0;
}
```

程序中很明显, a,b,c 都是指向同一块空间.而 d 不是
![1698064424573](image/c++入门/1698064424573.png)

> 注意: <font color='red'> 引用类型必须和应用实体是同一类型的.</font>

## 引用的作用

> 减少拷贝  
> 修改返回值
> 引用作参数

## 引用作参数或返回值

### 引用作参数

之前写过指针版本的交换函数

```cpp
void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

引用作参数也可以这样写:

```cpp
void Swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
```

> 这样交换的时候更方便, 不用解引用了

---

在学习数据结构的时候, 对于单链表尾插的函数, 有些教科书会这样写:

```cpp
typedef int SLDataType;
typedef struct SListNode
{
    SLDataType val;
    struct SListNode* next;
}SLTNode, *PLTNode;

void SListPushBack(PLTNode& phead, SLDataType x);
```

这里的 `PLTNode& phead` 相当于 `SLTNode*& phead`. 也就是说, 直接将主函数中创建的单链表头结点的引用传过来了. 本来我们需要 `void SListPushBack(SLTNode** phead, SLDataType x);`使用二级指针, 这样就只需要一级指针加引用了, 使之看起来更方便.

> 引用使代码看起来更简洁

### 引用作返回值

关于指针我们学过, 不能用函数不能返回一个局部变量的指针, 同样引用也是不可以的.

如果将局部变量引用返回赋值给一个普通变量, 不会出现问题.

```cpp
int& count()
{
    int n = 0;
    n++;
    //...

    return n;
}

int main()
{
    int ret = count();
    cout << ret << endl;
    cout << ret << endl;

    return 0;
}
```

![1698068057601](image/c++入门/1698068057601.png)

---

但如果将引用变量与函数中的局部变量进行绑定, 就会出现不可预料的后果:

```cpp
int& count()
{
    int n = 0;
    n++;
    //...

    return n;
}

int main()
{
    int& ret = count();
    cout << ret << endl;
    cout << ret << endl;
    cout << ret << endl;

    return 0;
}
```

![1698068192857](image/c++入门/1698068192857.png)
将 `ret` 与 函数中局部变量 `n` 进行绑定, 此时 `ret` 是 `n` 的别名.
但是函数调用完毕后, 已经将变量 `n` 所处的这块内存空间归还给操作系统了, 此时打印 `ret` 的值相当于打印这块内存空间的值.

我们都知道, 函数调用首先将当前栈顶指针压入栈顶, 接着开辟需要用到的栈帧空间.此时 `n` 就在这块临时开辟的栈帧空间里. 当函数调用完毕后, 执行 `ret`指令, 先将栈帧空间归还给操作系统, 再将原来的栈顶指针和栈底指针恢复.

这个时候, `n` 所在内存空间已经不确定究竟存放了什么, 后序如果调用了其他函数, 这块空间就更不知道会存放什么了.

> 所以, 不能将一个局部对象用引用返回, 会出现不可预料的后果.

---

那么, 什么样的对象可以在函数用引用返回呢?

自然是函数调用完毕后, 不会被销毁的对象.

例如: `static`, 全局变量等

```cpp
int& count()
{
    static int n = 0;
    n++;
    //...

    return n;
}

int main()
{
    int& ret = count();
    cout << ret << endl;
    cout << ret << endl;
    count();
    cout << ret << endl;

    return 0;
}
```

![1698068901734](image/c++入门/1698068901734.png)
第二次调用 `count()`, 修改了静态变量 `n` 的值, 那么 `n` 的别名 `ret` 必然也被修改了. 因为它们所指的内存空间是一样的.

---

下面这段代码的错误输出也就很好理解了, 这也是对于局部对象的错误引用导致的错误:

```cpp
int& Add(int a, int b)
{
    int c = a + b;

    return c;
}

int main()
{
    int& ret = Add(1, 2);
    Add(3, 4);
    cout << "Add(1, 2) is " << ret << endl;

    return 0;
}
```

![1698069174202](image/c++入门/1698069174202.png)
两次调用 `Add` 函数所开辟的栈帧空间是一样的, 恰好局部变量 `c` 一直在那一块内存空间中, 这样 `c` 的别名 `ret` 的值自然是第二次调用后 `c` 的值 : 7

可以如此验证:

```cpp
void fun1()
{
    int a = 0;
    cout << &a << endl;
}

void fun2()
{
    int b = 0;
    cout << &b << endl;
}

int main()
{
    fun1();
    fun2();
    fun1();

    return 0;
}
```

可以看到地址都是一样的.
![1698069662768](image/c++入门/1698069662768.png)

> 综上: <font color='red'> 如果函数返回时, 出了函数作用域, 如果返回对象还在(没归还给操作系统), 那么可以用引用返回. 如果已经销毁还给操作系统了, 只能传值返回</font>

---

## 传值、传引用效率比较

> 以值作为参数或者返回值类型, 在传参和返回期间, 函数不会直接传递实参或者变量本身返回, 而是传递实参或者返回变量的一份临时拷贝, 因此值作为参数或者返回值类型, 效率是十分低效的.

> 之前学过传址操作可以解决这个问题, 现在多了一个方法: 传引用

下面可以看出传引用的效率比传值高多了

```cpp
#include <time.h>
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
```

![1698070508162](image/c++入门/1698070508162.png)
传引用几乎不耗时间.

## 常引用 (const 与 引用)

> 可以把引用绑定到 `const` 对象上, 就像绑定到其他对象一样, 称之为 **对常量的引用(reference to const)**

> 与普通引用不同的是, 对常量的引用不能被用作修改它所绑定的对象

```cpp
const int b = 100;
const int& rb = b;      //正确  引用及其对象都是常量
rb = 200;               //错误  rb是常变量的别名  不能修改
int& rrb = b;           //错误  试图让一个非常量引用指向一个常量对象
```

`b` 是一个常变量, 不允许修改 `b` 的值. 那么其引用也不能修改, 引用就是其所指向对象的别名, 所以 `rb` 的类型是 `const int&` 的.

而 `rbb` 不是常量引用, 是不可以指向一个常量对象的.

---

> 允许为一个常量引用绑定一个非常量的对象, 字面值, 甚至是一般表达式

```cpp
int i = 42;
const int& r1 = i;      //虽然类型不一样  但是int可以转换为const int
const int& r2 = 42;     //字面量本来就是const int类型的
const int& r3 = r1 * 2; //r3也是个常量引用 直接让r3指向 r1*2 的结果
```

初始化常量引用时允许任意表达式作为初始值, 只要该表达式的结果能够转换成引用的类型.

要理解这种情况的发生, 搞懂一个常量引用被绑定到另外一个类型上发生了什么就行了:

```cpp
double dval = 3.14;
//int& ri = dval;         //err
const int& ri = dval;
```

此时 `ri` 应该引用了一个 `int` 类型的数据, 但是 `dval` 却是一个 `double` 类型的数据.

为了确保让 `ri` 绑定一个整数, 编译器将上述代码变成了如下形式:

```cpp
const int temp = dval;      //发生了隐式类型转换
const int& ri = temp;       //使 ri 指向一个临时量
```

在发生隐式/显示类型转换时候, 通常会先生成一个**临时量**, 这个临时量是一个常量对象, 再将左表达式来接收这个临时量.

如果要让 `ri` 指向 `dval`, 肯定是希望通过 `ri` 实现对 `dval` 的修改, 但实际上 `ri` 绑定的是一个临时量, 没有人会想通过 `ri` 实现对临时量的修改, 所以`c++` 直接规定 `int& ri = 3.14` 这样的操作是非法的.

---

> 常量引用指向的对象可以是个非常量对象

```cpp
int i = 42;
int& r1 = i;          //引用r1绑定对象i
const int& r2 = i;    //r2也绑定对象i, 但是不允许通过r2修改i的值
r1 = 50;              //可以通过r1修改i的值
//r2 = 49;            //不可以通过r2修改i的值
```

虽然通过常变量引用 `r2` 指向了 `i`, 但是 `i` 的值仍然可以被修改, 只是不允许通过 `r2` 进行修改.

## 引用和指针的区别

> 在**语法概念**上, 引用就是一个别名, 没有独立空间, 和其引用实体共用同一块空间.

```cpp
int main()
{
    int a = 0;
    int& ra = a;

    cout << "&a = " << &a << endl;
    cout << "&ra = " << &ra << endl;

    return 0;
}
```

![1698215260680](image/c++入门/1698215260680.png)

> 在**底层实现**上, 实际上是有空间的, 因为**引用是按照指针方式来实现的**

```cpp
int main()
{
    int a = 0;

    int& ra = a;
    ra = 20;

    int* pa = &a;
    *pa = 20;

    return 0;
}
```

引用和指针在底层无异, 都是先将被指向变量的地址存入寄存器中, 随后将寄存器中的值存入对应引用或者指针对象所在的内存中.
![1698215661543](image/c++入门/1698215661543.png)

引用和指针的不同点:

> 1. 引用概念上定义一个变量的别名, 指针存储一个变量地址
> 2. **引用**在定义时必须初始化, 指针没有要求
> 3. **引用**在初始化时引用一个实体后, 就**不能再引用其他实体**, 而指针可以在任何时候指向任何一个同类型实体
> 4. **没有 NULL 引用**, 但有 NULL 指针
> 5. **在`sizeof`中含义不同: 引用**结果为**引用类型的大小**, 但**指针**始终是**地址空间所占字节个数**(32 位平台下占 4 个字节)
> 6. 引用自加即引用指向的对象增加 1, 指针自加即指针向后偏移一个类型的大小
> 7. **有多级指针, 但是没有多级引用**
> 8. 访问实体不同, **指针需要解引用, 引用编译器自己处理**
> 9. **引用用起来比指针相对更安全**

# 6. 内联函数

## 内联函数的概念

> 以`inline`修饰的函数叫做内联函数, **编译时**c++编译器会在调用**内联函数的地方展开**, 没有函数调用建立栈帧的开销, 内联函数提升了程序运行的效率

这是不使用内联函数的代码

```cpp
int Add(int left, int right)
{
    return left + right;
}

int main()
{
    int ret = 0;
    ret = Add(1, 2);

    return 0;
}
```

它的汇编代码如下:
![1698217947634](image/c++入门/1698217947634.png)

如果使用了内联函数:

```cpp
inline int Add(int left, int right)
{
    return left + right;
}

int main()
{
    int ret = 0;
    ret = Add(1, 2);

    return 0;
}
```

需要在函数名前加上`__attribute__((always_inline))`, 否则不会展开.
![1698219010120](image/c++入门/1698219010120.png)

汇编代码缩短了很多:
![1698218918745](image/c++入门/1698218918745.png)

---

在学习 c 语言期间, **宏** 也有这个作用, 比如 `#define Add(left, right) ((left) + (right))`

虽然宏有以下优点

> 1. 提高代码复用性
> 2. 提高性能 (不用像函数一样有栈帧的开销)

但是宏的缺点却有更多不便

> 1. 不方便调试宏 (预处理阶段就已经进行了替换)
> 2. 导致代码可读性差, 可维护性差, 容易误用
> 3. 没有类型检查

**c++针对宏的缺点, 有以下技术替代宏**

> 1. 常量定义 换用 `const` 和 `enum`
> 2. 短小函数定义 换用 内联函数

---

## 内联函数的特性

> - `inline`是一种**空间换时间**的做法, 如果编译器将函数当作内联函数处理, 在**编译阶段, 会用函数体替换函数调用**, 缺陷: 可能会使目标文件变大, 优势: 少了调用开销, 提高程序运行效率.

如果我有一个 100 行指令的函数, 在程序中需要调用其 10000 次, 那么我肯定不会使用内联函数, 同时编译器也不可能将该函数展开.
![1698219869472](image/c++入门/1698219869472.png)

---

> - `inline对于编译器而言只是一个建议, 不同编译器关于inline实现机制不同`, 一般建议: 将**函数规模较小**(即函数不是很长, 具体没有准确的说法, 取决于编译器内部实现), **不是递归, 且频繁调用**的函数采用 `inline` 修饰, 否则编译器会忽略 `inline` 特性.

![1698220099046](image/c++入门/1698220099046.png)

---

> - `inline` 不建议声明和定义分离, 分离会导致链接错误. 因为 `inline` 在编译阶段被展开, 就没有函数地址了, 在链接的时候找不到该函数地址.

> 直接去头文件定义即可.

# 7. auto 关键字(c++11)

编程时常常需要把表达式的值赋给变量, 这就要求在声明变量的时候清楚地知道表达式的类型. 然而要做到这一点并非那么容易, 有时候甚至根本做不到.

> 为了解决这个问题, **c++11**新标准引入了 `auto` 类型说明符, 用它就能让编译器替我们去分析表达式所属的类型.

## auto 关键字的概念

> `auto` 让编译器通过初始值来推算变量的类型. **显然, `auto` 定义的变量必须有初始值**

> 使用 `auto` 定义变量必须对其进行初始化, 在编译阶段编译器需要根据初始化表达式来推导 `auto` 的实际类型.

> 因此 `auto` 并非是一种"类型"的声明, 而是一个类型声明时的**占位符**, 编译器在编译期间会将 `auto` 替换为变量实际的类型.

```cpp
int TestAuto()
{
    return 10;
}

int main()
{
    int a = 10;
    auto b = a;
    auto c = 'a';
    auto d = &c;
    auto e = TestAuto();
    auto& f = a;
    f++;

    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(e).name() << endl;
    cout << typeid(f).name() << endl;

    return 0;
}
```

结果是: ![1698236320934](image/c++入门/1698236320934.png)

---

鉴于 `auto` 可以通过初始化表达式的类型推导出来, 可以利用这个特性简写一些复杂的类型

```cpp
#include<vector>
#include<string>

int main()
{
    vector<string> v;
    //vector<string>::iterator it = v.begin();    //定义容器的迭代器
    auto it = v.begin();    //可以用 auto 替换这么长的类型
}
```

---

## auto 的使用细则

**auto 与指针和引用结合起来用**

> 用 `auto` 声明指针类型时, 用 `auto` 和 `auto*` 没有任何区别, 只要右值是一个地址即可; 但是 `auto` 声明引用类型时必须加 `&`

```cpp
int main()
{
    int x = 10;
    auto a = &x;
    auto* b = &x;
    auto& c = x;

    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;

    *a = 30;
    cout << x << endl;

    *b = 40;
    cout << x << endl;

    c = 50;
    cout << x << endl;

    return 0;
}
```

![1698239112173](image/c++入门/1698239112173.png)

---

**在同一行定义多个变量**

> 当在同一行声明多个变量时, 这些变量必须时相同的类型, 否则编译器将会报错, 因为编译器实际只对第一个类型进行推导, 然后用推导出来的类型定义其他变量.

```cpp
void TestAuto()
{
    auto a = 1, b = 2;
    auto c = 3, d = 4.0;    //改行会编译失败, c 和 d 的初始化表达式类型不同
}
```

![1698239339310](image/c++入门/1698239339310.png)

## auto 不能推导的场景

**1. auto 不能作为函数的参数**

```cpp
void TestAuto(auto x)
{}
```

编译器直接报错
![1698239741699](image/c++入门/1698239741699.png)

---

**2. auto 不能用来声明数组**

```cpp
void TestAuto()
{
    int a[] = {1, 2, 3};
    auto b[] = {4, 5, 6};
}
```

![1698239822788](image/c++入门/1698239822788.png)

---

**3. 最好不要用 `auto` 用作返回值**

就像 Python 一样, 如果用 `auto` 作函数返回值, 想用一个对象用来接受函数返回值的时候就会很苦恼, 谨慎使用.

**4. 为了避免与 c++98 的 `auto` 混淆, c++11 只保留了 `auto` 作为类型指示符的用法**

**5. auto 在实际中最常见的优势用法就是以后会讲到的 c++11 提供的新式 for 循环和 在 lambda 表达式中使用**

# 8. 基于范围的 for 循环 (c++11)

## 范围 for 的语法

在 c++98 如果要遍历一个数组, 可以按照以下方式进行:

```cpp
void TestFor()
{
    int array[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
        array[i] *= 2;
    for (int* p = array; p < array + sizeof(array)/ sizeof(array[0]); ++p)
        cout << *p << endl;
}
```

对于一个**有范围的集合**而言, 由程序员来说明循环的范围是多余的, 有时候还会容易犯错误.

因此 c++11 中引入了基于范围的 `for` 循环.  
**for 循环后的括号由冒号`:`分为两部分: 第一部分是范围内用于迭代的变量, 第二部分则表示被迭代的范围**

```cpp
void TestFor()
{
    int array[] = {1, 2, 3, 4, 5};

    for (auto e : array)
        cout << e << endl;
}
```

依次去数组中的数据赋值给给 `e`, 自动判断结束, 自动 `++` 向后走
![1698240905018](image/c++入门/1698240905018.png)

但是如果我想要修改数组中的元素该怎么办呢? 如果只是修改局部变量 `e` 是修改不了数组本身的数据的.

可以使用引用, 让 引用对象`e` 依次指向数组的每个元素, 并进行修改.

```cpp
void TestFor()
{
    int array[] = {1, 2, 3, 4, 5};

    for (auto& e : array)
        e *= 2;

    for (auto e : array)
        cout << e << endl;
}
```

如果使用指针, 则会很麻烦.
![1698241139140](image/c++入门/1698241139140.png)

> 注意: <font color='red'>与普通循环类似, 可以用 `continue` 来结束本次循环, 也可以用 `break` 来跳出整个循环</font>

## 范围 for 的使用条件

**1. for 循环迭代的范围必须是确定的**

**对于数组而言, 就是数组中第一个元素和最后一个元素的范围;**
对于类而言, 应该提供 begin 和 end 的方法, begin 和 end 就是 for 循环迭代的范围.

注意: 以下代码就有问题, 因为 for 的范围不确定, 传递的参数只是一个指针.

```cpp
void TestFor(int array[])
{
    for(auto& e : array)
        cout << e << endl;
}
```

**2. 迭代的对象要实现++和==的操作**

# 10. 指针空值--nullptr(c++11)

## c++98 中的指针空值

> 在良好的 C/C++编程习惯中, 声明一个变量最好给该变量一个合适的初始值, 否则可能会出现不可预料的错误.

比如未初始化的指针, 如果一个指针没有合法的指向, 我们基本都是按照如下的方式对其进行初始化:

```cpp
void TestPtr()
{
    int* p1 = NULL;
    int* p2 = 0;

    //...
}

```

`NULL` 实际上是一个宏, 在传统的 C 头文件(stddef.h)中, 可以看到如下代码:

```cpp
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif
```

我们可以看到, `NULL`可能被定义为字面量 0, 或者被定义为无类型指针`(void*)`的常量.
无论采取何种定义, 在使用空值的指针, 都不可避免的会遇到一些麻烦, 比如:

```cpp
void (int)
{
    cout << "f(int)" << endl;
}

void (int*)
{
    cout << "f(int*)" << endl;
}

int main()
{
    f(0);
    f(NULL);
    f((int*)NULL);

    return 0;
}
```

![1698243616911](image/c++入门/1698243616911.png)
程序本意是想通过`f(NULL)`调用指针版本的`f(int*)`函数, 但是由于 `NULL` 被定义成 0, 因此与程序的初衷相悖.

> 在 c++98 中, 字面常量 0 既可以时一个整型数字, 也可以是无类型的指针 `(void*)` 常量, 但是编译器默认情况下将其看成一个整型常量, 如果要将其按照指针方式来使用, 必须对其进行强转 `(void*)0`

<font color='red'>注意:</font>

1. 在使用 `nullptr` 表示指针空值时, 不需要包含头文件, 因为 `nullptr` 是 c++11 作为新关键字引入的.
2. 在 c++11 中, `sizeof(nullptr)` 与 `sizeof((void*)0)` 所占字节数相同.
3. 为了提高代码的健壮性, 在后续表示指针控制时建议最好使用 `nullptr`.

本章完.
