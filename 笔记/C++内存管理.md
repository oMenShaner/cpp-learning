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

---

`new` 一块连续的空间, 有几个元素就要调用几次构造函数和析构函数, 同时会按照先构造后析构的顺序进行.

```cpp
// new[] / delete[]
  A* ptr3 = new A[3]{1, 2, 3};  // C++11 使用列表初始化
  delete[](ptr3);
```

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-7.png)

---

下面有一个更为复杂一点的栈自定义类型

```cpp
class Stack
{
  public:
    Stack(int capacity = 4)
    :_capacity(capacity)
    ,_top(0)
    {
      cout << "Stack(int capacity = 4)" << endl;
      _array = new int[_capacity];
    }

    ~Stack()
    {
      cout << "~Stack()" << endl;
      delete[](_array);
      _array = nullptr;
      _capacity = _top = 0;
    }

  private:
    int* _array;
    int _capacity;
    int _top;
};

int main()
{
  Stack* p1 = new Stack(5);
  delete(p1);

  return 0;
}
```

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-8.png)

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-9.png)

对于自定义类型, `new/delete` 和 `malloc/free` 的区别就是 `new/delete` 会分别调用构造函数和析构函数.

在这里, 直接 `free(p1)` 肯定是有问题的, `free` 在释放自定义类型对象空间前不会调用该自定义类型的析构函数, 那么 `_array` 指向的空间没有被释放, 造成了内存泄漏.

---

对于 `new` 操作, 如果 `new` 失败怎么处理呢?
在 C++ 中是使用捕捉异常来处理的, 之后会详细讲解, 这里简单展示以下用法.

```cpp
void Test()
{
  char* p1 = new char[1024*1024*1024];
  cout << (void*)p1 << endl;              // char*类型不能直接使用cout, 会被自动识别成字符串

  char* p2 = new char[1024*1024*1024];
  cout << (void*)p2 << endl;
}

int main()
{
  try
  {
    Test();
  }
  catch(const std::exception& e)
  {
    cout << "1" << endl;
    std::cerr << e.what() << '\n';
  }

  return 0;
}
```

第二次开辟空间失败, 会直接捕捉到异常并打印出异常, 程序并不会崩.
![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-10.png)

# 四. operator new 与 operator delete 函数

> **`new` 和 `delete`** 是用户进行 **动态内存申请和释放的操作符**, **`operator new` 和 `operator delete`** 是系统提供的**全局函数**.
> `new` **在底层通过调用** `operator new` 全局函数来申请空间, `delete` **在底层通过调用** `operator delete` 全局函数来释放空间.

`operator new` 与 `operator delete` 函数就是库全局函数, 是 `malloc` 和 `free` 的封装, 不调用构造函数和析构函数.

如果申请空间失败则会直接抛异常, 而原来的 `malloc` 只能返回 0.

```cpp
/*
operator new：该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间
失败，尝试执行空间不足应对措施，如果改应对措施用户设置了，则继续申请，否则抛异常。
*/
void *__CRTDECL operator new(size_t size) __THROW1(__STD bad_alloc)
{
  // try to allocate size bytes
  void *p;
  while ((p = malloc(size)) == 0)
    if (_callnewh(size) == 0)
    {
      // report no memory
      // 如果内存申请失败了, 这里会抛出bad_alloc 类型异常
      static const std::bad_alloc nomem;
      _RAISE(nomem);
    }

  return (p);
}

/*
operator delete: 该函数最终是通过free来释放空间的
*/
void operator delete(void *pUserData)
{
     _CrtMemBlockHeader * pHead;
     RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
     if (pUserData == NULL)
         return;
     _mlock(_HEAP_LOCK);  /* block other threads */
     __TRY
         /* get a pointer to memory block header */
         pHead = pHdr(pUserData);
          /* verify block type */
         _ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
         _free_dbg( pUserData, pHead->nBlockUse );
     __FINALLY
         _munlock(_HEAP_LOCK);  /* release other threads */
     __END_TRY_FINALLY
     return;
}
/*
free的实现
*/
#define   free(p)               _free_dbg(p, _NORMAL_BLOCK)
```

---

以下三种对于内置类型的动态开辟内存空间的操作是一样的.

```cpp
int main()
{
  int* p1 = (int*)malloc(sizeof(int));
  free(p1);

  int* p2 = new int;
  delete(p2);

  int* p3 = (int*)operator new(sizeof(int));
  operator delete(p3);

  return 0;
}
```

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-11.png)

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-12.png)

---

那么下面的代码也能知道底层是怎么调用的了.

```cpp
Stact* p1 = new Stack[10];
delete[](p1);
```

首先调用 `operator new` 开辟了 `160` 字节大小的空间, 随后调用了 10 次构造函数, 创造了 10 个 `Stack` 类的自定义类型对象.

但是通过调试却发现, 开辟了不是 `160` 字节, 而是 `168` 字节, 传入 `operator new` 的参数 `sz` 为 `168`

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-13.png)

开辟完空间后, `p1` 的值为 `0x614c28` , 通过观察 `0x614c20`, 发现多开辟的 `8` 字节空间, 存放了数组元素个数 `10`

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-14.png)

更换代码, `Stack* p1 = new Stack[8];`
发现 `p1` 指向地址的向前 `8` 个字节确实为 `8`

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-15.png)

**这个数字存在是因为自定义类型有析构函数, 需要知道要调用多少次析构函数.**

这个时候, 如果我错误的使用了 `delete` 而非 `delete[]`, 会直接导致程序崩溃, 程序真实是在 `0x614c20` 开始申请了 `168` 个字节大小的空间. 使用 `delete[]` 会自动把该地址传入 `operator delete`, 而 `delete` 不会这么处理, 会把原来的 `0x614c28` 传入函数, 这个地址不是申请空间的首地址, 释放失败.

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-16.png)

但如果是内置类型, 则有可能不会崩溃

```cpp
int* p2 = new int[10];
delete(p2);
```

内置类型没有析构函数, 也就不需要多开一块空间用来记录需要调用多少次析构函数.这样, 程序也就不会崩溃.

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-17.png)

---

通过上面的调试, 可以得到下面的编程注意.

> `new/delete`, `new[]/delete[]`, `malloc/free`一定要配套使用, 否则结果是未确定的.

# 五. new 和 delete 的实现原理

## 1. 内置类型

> 如果申请的是内置类型的空间, `new` 和 `malloc`, `delete` 和 `free` 基本相似, 不同的地方是:
> `new/delete` 申请和释放的是单个元素的空间, `new[]/delete[]` 申请和释放的是连续空间.
> `new` 申请失败时会抛异常, `malloc` 则会返回 `NULL`

## 2. 自定义类型

- `new` 的原理

  1. 调用 `operator new` 函数构造空间
  2. 在申请的空间上执行构造函数, 完成对象的构造

- `delete` 的原理

  1. 在空间上执行析构函数, 完成对象中资源的清理工作
  2. 调用 `operator delete` 函数释放对象的空间

- `new[]` 的原理

  1. 调用 `operator new[]` 函数, 在 `operator new[]` 中实际调用 `operator new` 函数完成 N 个对象空间的申请
  2. 在申请的空间上执行 N 次构造函数

- `delete[]` 的原理
  1. 在释放的对象空间上执行 N 次析构函数, 完成 N 个对象中资源的清理
  2. 调用 `operator delete[]` 释放空间, 实际在 `operator delete[]` 中调用 `operator delete` 来释放空间

## 六. 定位 new 表达式 (placement-new)

定位 `new` 表达式是在**已分配的原始内存空间中调用构造函数初始化一个对象**

使用格式:

```cpp
new(place_address)type 或者 new(place_address)type(initializer-list)

place_address 必须是一个指针, initializer-list 是类型的初始化列表.
```

使用场景:
定位 `new` 表达式在实际中一般是配合内存池使用. 因为内存池分配出的内存没有初始化, 所以如果是自定义类型的对象, 就需要使用 `new` 的定义表达式进行显示调用构造函数进行初始化.

```cpp
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
```

最后确实使用定位 `new` 完成了对未初始化空间的初始化构造

![Alt text](image/C++%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/image-18.png)

## 七. malloc/free 和 new/delete 的区别

`malloc/free` 和 `new/delete` 的共同点是: 都是从堆上申请空间, 并且需要用户手动释放.
不同的地方是:

> 1. `malloc` 和 `free` 是函数, `new` 和 `delete` 是操作符.
> 2. `malloc` 申请的空间不会初始化, `new` 可以初始化.
> 3. `malloc` 申请空间时, 需要手动计算空间大小并传递, `new` 只需在其后跟上空间的类型即可, 如果是多个对象, `[]` 中指定对象个数即可.
> 4. `malloc` 的返回值为 `void*`, 在使用时必须强转, `new` 不需要, 因为 `new` 跟的是空间的类型.
> 5. `malloc` 申请空间失败时, 返回的是 `NULL`, 因此使用时必须判空, `new` 不需要, 但是 `new` 需要捕获异常.
> 6. 申请自定义类型对象时, `malloc/free` 只会开辟空间, 不会调用构造函数和析构函数, 而 `new` 在申请空间后会调用构造函数完成对象的初始化, `delete` 在释放空间前会调用析构函数完成空间中资源的清理.

本章完.
