# 一. C/C++ 内存分布

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-1.png)

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image.png)

下面来看一段代码和相关内存分布问题

```cpp
#define _CRT_SECURE_NO_WARNINGS   1
#include<iostream>
#include<string.h>
int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
	static int staticVar = 1;
	int localVar = 1;
	int num1[10] = { 1, 2, 3, 4 };
	char char2[] = "abcd";
	char* pChar3 = "abcd";

	int* ptr1 = (int*)malloc(sizeof (int)* 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int)* 4);
	free(ptr1);
	free(ptr3);

	std::cout << "sizeof(num1):" <<sizeof(num1) << std::endl;
	std::cout << "sizeof(char2):"<<sizeof(char2) << std::endl;
	std::cout << "strlen(char2):" << strlen(char2) << std::endl;
	std::cout << "sizeof(pChar3):" << sizeof(pChar3) << std::endl;
	std::cout << "strlen(pChar4):" << strlen(pChar3) << std::endl;
	std::cout << "sizeof(ptr1):" << sizeof(ptr1) << std::endl;
}

int main()
{
	Test();
	return 0;
}

```

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-2.png)

- `globaVar` 是全局变量, 所有文件都可以访问, **存放在数据段**.
- `staticGlobalVar` 是静态全局变量, 只有当前文件可以访问, **存放在数据段**.
- `staticVar` 是静态局部变量, 只有当前函数可以访问, **存放在数据段**.
- `localVar` 是局部变量, **存放在栈**.
- `num1` 是局部变量, **存放在栈**.

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-3.png)

- `char2` 是数组名, 字符串`"abcd"`存放在常量区, 在创建数组的时候, 会拷贝一份 `"abcd\0"` 在栈空间, 首元素`'a'`的地址就是数组名的地址.**在栈空间**.
- `*char2` 是对数组首元素地址的解引用, `*char2` 相当于数组首元素 `a` , **在栈空间**.
- `pChar3` 是一个指针变量, 指向了存放在数据区的常量字符串 `"abcd"`, `const` 限定的是 `*pChar3`, **存放在栈**.
- `*pChar3` 是对`pChar3` 的解引用, 实际上就是数据区中的 `a`, **在数据段**
- `ptr1` 指向了是通过 `malloc` 后返回的空间的首地址, 但是 `ptr1` 本身是 `main` 函数临时创建的, **存放在栈空间**
- `*ptr1` 是动态开辟空间的第一块四字节大小的空间的数据, **存放在堆空间**

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-4.png)

# 二. C 语言中动态内存管理方式: malloc/calloc/realloc/free

```cpp
void Test()
{
  int* p1 = (int*)malloc(sizeof(int));
  free(p1);

  int* p2 = (int*)calloc(4, sizeof(int));
  int* p3 = (int*)realloc(p2, sizeof(int) * 10);

  //free(p2);  // 这里需要free(p2)吗?
  free(p3);
}
```

<font size=5 color=red>这里 `p2` 不需要自己手动释放, `realloc` 如果申请空间成功, 会自动释放原来的空间.</font>

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-5.png)

- `malloc` 和 `calloc` 的唯一区别就是 `calloc` 会将申请空间初始化为 0, 而 `malloc` 则不会对申请到的空间进行初始化处理.
- `realloc`: 如果原地址可以存放新开辟的空间, 则直接原地址进行扩容; 如果原地址没有那么大的空间, 则会新找到一块空间, 同时将原来的空间自动释放, 返回新空间的起始地址.

# 三. C++内存管理方式

> C 语言内存管理方式可以在 C++继续使用, 但有些地方就无能为力, 而且使用起来比较麻烦, 因此 C++又提出了自己的内存管理方式: **通过 `new` 和 `delete` 操作符进行动态内存管理**.

## 1. new / delete 操作内置类型

```cpp
void Test()
{
  // 动态申请一个 int 类型的空间, 不会初始化
  int* ptr1 = new int;          

  // 动态申请一个 int 类型的空间, 并初始化为 10
  int* ptr2 = new int(10);

  // 动态申请十个 int 类型的空间, 不会初始化
  int* ptr3 = new int[10];

  // 动态申请十个 int 类型的空间, 并按照列表初始化
  int* ptr4 = new int[10]{1, 2, 3};       //第四个元素开始被默认初始化为 0

  delete(ptr1);
  delete(ptr2);
  delete[](ptr3);
  delete[](ptr4);
}
``` 
<font size=4 color=red>注意:</font> 
**申请和释放单个元素的空间, 使用 `new` 和 `delete` 操作符**.
**申请和释放连续的空间, 使用 `new[]` 和 `delete[]` 操作符**.
`new` 和 `malloc` 在用法上没有区别, 区别就是 `new` **可以在申请空间的时候同时对那一块空间进行初始**化, 而 `malloc` 只可以申请空间.

## 2. new / delete 操作自定义类型

```cpp
class A
{
  public: 
    A(int a)
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
  // new/delete 和 malloc/free 的最大区别就是 new/delete 对于自定义类型出了开空间和释放空间还会调用构造函数和析构函数
  A *ptr1 = (A*)malloc(sizeof(A));
  A *ptr2 = new A(1);
  free(ptr1);
  delete(ptr2);

  return 0;
}
```
结果如下:  
![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-6.png)
`new` 和 `delete` 会调用自定义类型的构造函数和析构函数.
而 `malloc` 和 `free` 不会, 它们只会申请空间和释放空间.

***
`new` 一块连续的空间, 有几个元素就要调用几次构造函数和析构函数, 同时会按照先构造后析构的顺序进行.

```cpp
// new[] / delete[]
  A* ptr3 = new A[3]{1, 2, 3};  // C++11 使用列表初始化
  delete[](ptr3);
```

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-7.png)

***