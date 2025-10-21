# 可变参数模板

> C++ 的**可变参数模板**（Variadic Templates）是 C++11 引入的重要特性，允许模板参数接受任意数量、任意类型的参数，极大增强了模板的灵活性。它广泛用于泛型编程中需要处理不确定数量参数的场景（如容器初始化、函数参数转发等）

## 参数包

可变数目的参数被称为**参数包**，存在两种参数包：

- 模板参数包，表示零或多个模板参数。(如 `class ...Args`)，在模板参数列表中，`class...`或

  `typename...`指出接下来的参数表示零或多个类型列表
- 函数参数包：表示零或多个函数参数。(如 `Args... args`)，在函数参数列表中，类型名后面跟 `...`指出接下来表示零或多个形参对象列表

```cpp
template<class ...Args>
void func(Args... args){ }

template<class ...Args>
void func(Args&... args) {}

template<class ...Args>
void func(Args&&... args) {}
```

**函数参数包**可以用**左值引用**或**右值引用**表示，跟前面普通模板一样，每个参数实例化时遵循引用折叠规则。

可变参数模板的原理跟模板类似，本质还是去实例化对应类型和个数的多个函数。

下面用 `sizeof...`运算符配合可变参数模板来计算参数的个数:

```cpp
template<class ...Args>
void Print(Args&&... args)
{
    cout << sizeof...(args) << endl;
}

int main()
{
    double x = 2.2;
    Print();                        // 包里有0个参数
    Print(1);                       // 包里有1个参数
    Print(1, string("xxxxx"));      // 包里有2个参数
    Print(1.1, string("xxxxx"), x); // 包里有3个参数

    return 0;
}
```

程序运行如下:

```bash
0
1
2
3
```

编译器编译时会看有没有**可变参数模板**,通过实现多个函数模板来实现上述功能,最终实例化成下述四个函数模板.

```cpp
void Print();

template <class T1>
void Print(T1&& arg1);

template <class T1, class T2>
void Print(T1&& arg1, T2&& arg2);

template <class T1, class T2, class T3>
void Print(T1&& arg1, T2&& arg2, T3&& arg3);
```

## 包的展开方式(递归展开和包扩展)

参数包不能直接使用,必须通过展开操作(`...`),将其分为独立的参数.

### 递归展开

最常见的用法是通过**递归函数模板**展开参数包:

1. 定义一个**递归终止函数**(处理参数包为空的情况).
2. 定义一个**可变参数模板**,每次处理参数包的第一个元素,剩余元素继续递归.

下面是一个打印任意数量、任意类型参数的例子:

```cpp
// 1. 递归终止函数（参数包为空时调用） 
void Print()
{
    cout << "参数打印完毕!" << endl;
}

// 2. 可变参数函数模板（递归展开）
// 每次处理第一个参数t，剩余参数包Args... args继续递归
template<class T, class ...Args >
void Print(T t, Args... args)
{
    cout << "参数: " << t << "(剩余" << sizeof...(args) << "个参数)" << endl;
    Print(args...); // 展开剩余参数包，继续递归
}

int main() {
    Print(10, 3.14, string("hello"), 'A'); // 传入4个不同类型的参数
    return 0;
}
```

`main`函数中调用 `Print`函数,调用参数包,参数包第一个参数会传递给 `t`,剩余的参数传递给 `args`.

之后继续递归,直至无参数传递给 `Print`,此时调用**递归终止函数**,函数调用完毕,参数包展开完毕.

程序运行结果如下:

```bash
参数: 10(剩余3个参数)
参数: 3.14(剩余2个参数)
参数: hello(剩余1个参数)
参数: A(剩余0个参数)
参数打印完毕!
```

具体函数模板实例化后调用过程如下图:

![](image/%E5%8F%AF%E5%8F%98%E5%8F%82%E6%95%B0%E6%A8%A1%E6%9D%BF,lambda,function%E5%8C%85%E8%A3%85%E5%99%A8/image.png)

### 包扩展

除了递归，C++11 后还可以通过包扩展直接展开参数包（无需递归），例如初始化容器:

```cpp
// 可变参数模板函数：用参数包初始化vector
template<class ...Args>
vector<int> make_vector(Args... args)
{
    // 将参数包args...展开为独立参数，初始化vector
    return { args... };
}

int main()
{
    auto vec = make_vector(1, 2, 3, 4, 5);
    for (int num : vec)
    {
        cout << num << " ";
    }

    return 0;
}
```

当调用 `make_vector(1,2,3,4,5)`时,编译器会做一下几件事:

1. **推导模板参数包**

   函数调用的实参是 `1,2,3,4,5`,都是 `int`类型.因此编译器会推导模板参数包 `Args...`为 `int,int,int,int,int`
2. **实例化具体函数**

   编译器会根据推导结果,生成一个针对 `Args={int, int, int, int, int}`的具体函数,相当于:

   ```cpp
   std::vector<int> make_vector(int arg1, int arg2, int arg3, int arg4, int arg5) {
       return {arg1, arg2, arg3, arg4, arg5}; // 包扩展后的值
   }
   ```
3. **调用实例化的函数**

   `main`函数中的调用会直接匹配这个实例化的函数,传入 `1,2,3,4,5`作为实参,最终用这 5 个值初始化 `std::vector<int>`.

## empalce系列接口

> 在 C++ 标准库中，`emplace`系列接口（如 `emplace_back`、`emplace`、`emplace_front`等）是 C++11 引入的高效插入元素的方法，主要用于容器（如 `std::vector`、`std::list`、`std::map`等）。它们的核心优势是直接在容器内部构造元素，避免了不必要的临时对象复制或移动，从而提升性能。

`emplace`系统接口依赖**可变参数模板**和**完美转发**实现

- 通过可变参数模板接收任意数量,任意类型的参数
- 通过 `std::forward`将参数完美转发给元素的构造函数,确保参数的左值/右值属性被正确传递

移动语义的开销本身就不大,故 `emplace_back`与 `push_back`在传右值时开销差不多,但是在传递左值时,`push_back`无法使用移动语义,此时必须**调用对应的拷贝构造函数进行深拷贝**.

而 `emplace_back`可以直接传递其可变参数包,使得传递的参数直接在已经分配好的内存空间上**直接构造**.

```cpp
struct MyString {
    char* _data;
    size_t _size;

    // 构造函数（分配内存）
    MyString(const char* str = "")
        :_size(strlen(str)) {
        _data = new char[_size + 1];
        memcpy(_data, str, _size+1);
        cout << "构造函数：分配" << _size + 1 << "字节\n";
    }

    // 移动构造函数（转移资源，不分配新内存）
    MyString(MyString&& other) noexcept
        :_data(other._data), _size(other._size) {
        other._data = nullptr;
        other._size = 0;
        cout << "移动构造：资源转移\n";
    }

    // 禁止复制（突出移动的作用）
    MyString(const MyString&) = delete;
    MyString& operator=(const MyString&) = delete;

    ~MyString() {
        if (_data) {
            cout << "析构函数：释放" << _size + 1 << "字节\n";
            delete[] _data;
        }
    }
};

int main()
{
    vector<MyString> vec;
    vec.reserve(2);
    cout << "emplace_back" << endl;
    vec.emplace_back("hello");
    cout << "emplace_back" << endl;

    cout << "push_back" << endl;
    vec.push_back("world");
    cout << "push_back" << endl;
    return 0;
}

```

`reverse(2)`确保 `vector`有足够空间,.

`emplace_back`直接在容器的内存中调用 `MyString`的构造函数,**没有临时对象**,不会触发移动构造.

`push_back`即使在容器内存足够的情况下,还是先调用 `MyString`的构造函数,**创建临时对象**,之后触发移动构造,将已有元素移动到容器内存中.

程序运行结果如下:

```bash
emplace_back
构造函数：分配6字节
emplace_back
push_back
构造函数：分配6字节
移动构造：资源转移
push_back
析构函数：释放6字节
析构函数：释放6字节
```

由此可以看到,在有移动构造的情况下,参数为左值时,`emplace_back`相比 `push_back`的性能提升在**构造需要深拷贝的对象**.如果是需要构造仅需浅拷贝的对象,此时性能提升就明显了,没有了移动构造,`push_back`需要构造和拷贝构造两次,比 `emplace_back`要多一次.

# Lambda

> C++11 引入的 Lambda 表达式（匿名函数）是一种便捷的函数定义方式，可在需要函数对象的地方直接编写代码，无需单独定义函数或函数对象类。它广泛用于算法（如 `std::for_each`）、回调函数、多线程等场景，极大简化了代码。

## Lambda表达式的基本语法

Lambda 的完整语法结构如下：

```bash
[capture-list] (parameter-list) mutable noexcept -> return-type {
	// 函数体
}
```

各部分含义:

1. **捕获列表（****`capture-list`** **capture-list****）** ：用于捕获 Lambda 外部的变量（在函数体中使用），是 Lambda 与外部作用域交互的关键。常见形式：`[],[=],[&],[x,&y],[this]`
2. **参数列表（****`parameter-list`** **parameter-list****）** ：与普通函数的参数列表一致，可省略（无参数时）。
3. **`mutable`** **mutable****（可选）** ：允许修改按值捕获的变量（默认按值捕获的变量是 `const`的）。
4. **`noexcept`** **noexcept****（可选）** ：声明 Lambda 不会抛出异常。
5. **返回类型（****`return-type`** **return-type****）** ：通常可省略，由编译器自动推导（若函数体只有 `return`语句）。
6. **函数体** ：Lambda 的执行逻辑。

下面是简单的Lambda示例:

```cpp
int main()
{
    // 直接定义并且调用
    []{cout << "简单Lambda" << endl; }();

    // 带参数和返回值
    auto add = [](int a, int b)-> int {
        return a + b;
        };
    cout << add(1, 2) << endl;

    // 按值捕获外部变量
    int x = 10;
    auto printX = [x] { cout << x << endl; };
    printX();

    return 0;
}
```

程序运行结果如下:

```bash
简单Lambda
3
10
```

直接调用时, 此时 `[]{cout << "简单Lambda" << endl; }`为一个对象,由于该Lambda表达式没有参数,所以调用时最后加 `()`即可.

`auto`用于接收Lambda表达式(其类型是编译器生成的**匿名类型**，无法显式写出).

```cpp
// 在Linux下做测试
// 打印上述printX的名称
cout << typeid(printX).name() << endl;
```

```bash
root:~/learning# ./test 
Z4mainEUlvE_
```

## 捕获列表

> Lambda 的**捕获列表（capture list）** 是 Lambda 表达式与外部作用域变量交互的核心机制，用于指定如何捕获外部变量供 Lambda 内部使用。捕获列表位于 Lambda 表达式的最开头（`[]`内），决定了外部变量的访问方式（按值 / 按引用）和范围。

**捕获列表的基本规则:**

- 捕获列表仅能捕获 Lambda**定义时所在作用域**的局部变量（全局变量无需捕获即可直接使用）。
- 捕获方式分为**按值捕获**和 **按引用捕获** ，行为差异显著。
- 可显式指定捕获特定变量，或使用默认捕获模式。

**常见形式:**

- `[]`：不捕获任何变量。
- `[=]`：按值捕获所有外部变量（只读）。
- `[&]`：按引用捕获所有外部变量（可修改）。
- `[x, &y]`：按值捕获 `x`，按引用捕获 `y`。
- `[this]`：捕获当前类的 `this`指针（用于类成员函数中访问成员变量）。

下面是常用捕获方式及示例:

```cpp
#include <iostream>

using namespace std;

int main()
{
    // f1:空捕获：无法访问x
    int x = 10;
    auto f1 = [] {
        // cout << x; // 错误：未捕获x
        cout << "无外部变量\n";
    };
    f1();

    // f2,f3:按值捕获或默认按值[=]
    int a = 10, b = 20;
    // 捕获a和b的副本（显式指定）
    auto f2 = [a, b]() {
        cout << a + b << endl;
        };
    // 默认按值捕获所有外部变量（等价于捕获a和b）
    auto f3 = [=]() {
        cout << a * b << endl;
        };
    f2();
    f3();

    // f4:配合mutable修改副本
    auto f4 = [x]() mutable {
        x = 5; // 允许修改副本（仅内部有效）
        std::cout << "内部x=" << x; // 输出5
        };
    f4();
    std::cout << "外部x=" << x << endl; // 输出10（原变量不变）

    // f5,f6:按引用捕获 [&变量名] 或默认按引用 [&]
    int c = 30, d = 40;
    // 显式按引用捕获c和d
    auto f5 = [&c, &d]() {
        c = 35;
        d = 50; // 直接修改
        };
    // 默认按引用捕获所有外部变量
    auto f6 = [&] {
        cout << c + d << endl;
        };

    f5();
    f6();

    // f7,f8:混合捕获
    x = 1;
    int y = 2, z = 3;
    // 默认按值捕获所有，仅y按引用捕获
    auto f7 = [=, &y] {
        // x = 10; // 错误：x按值捕获，不可修改
        y = 20;   // 正确：y按引用捕获，可修改
        cout << x + y + z << endl; // 1+20+3=24
        };
    // 默认按引用捕获所有，仅z按值捕获
    auto f8 = [&, z] {
        x = 10;   // 正确：x按引用捕获
        // z = 30; // 错误：z按值捕获，不可修改
        };
    f7();
    f8();

    // f9:捕获this指针 [this]（类内使用）
    class MyClass {
    private:
        int num = 100;
    public:
        void test() {
            // 显式捕获this
            auto f8 = [this] {
                num = 200; // 访问并修改成员变量
                cout << num << endl;
                };
            f8(); // 输出200
        }
    };
    MyClass obj;
    obj.test();

    return 0;
}
```

程序运行如下:

```bash
无外部变量
30
200
内部x=5外部x=10
85
24
200
```

需要注意的是:

1. 当使用混合捕捉时，第一个元素必须是 `&`或 `=`，并且 `&`混合捕捉时，后面的捕捉变量必须是值捕捉，同理 `=`混合捕捉时，后面的捕捉变量必须是引用捕捉。
2. lambda 表达式如果在函数局部域中，他可以捕捉 lambda 位置之前定义的变量，不能捕捉静态局部变量和全局变量，静态局部变量和全局变量也不需要捕捉， lambda 表达式中可以直接使用。这也意味着 lambda 表达式如果定义在全局位置，捕捉列表必须为空。

# function包装器

> `std::function` 是 C++11 引入的函数包装器（位于 `<functional>` 头文件中），用于 **包装各种可调用对象** （函数、Lambda 表达式、函数指针、函数对象、成员函数指针等），将它们统一为一种类型，方便存储、传递和使用。

**核心作用**

C++ 中 “可调用对象” 的类型千差万别（如普通函数的类型、Lambda 的匿名类型、函数对象的自定义类型等），`std::function` 可以将这些不同类型的可调用对象 **包装成同一种类型** ，解决了 “类型不统一” 的问题。

**基本语法**

```cpp
std::function<返回值类型(参数类型列表)> 变量名;
```

* 包装普通函数

```cpp
// 普通函数
int add(int a, int b) {
    return a + b;
}

int main() {
    // 包装普通函数
    function<int(int, int)> func = add;
    cout << func(3, 5) << endl; // 输出
    return 0;
}
```

* 包装lambda表达式

  ```cpp
  int main(){
      auto mul = [](int a, int b) { return a * b; };

      // 包装lambda表达式
      function<int(int, int)> func = mul;
      cout << func(3, 5) << endl; // 输出15
      return 0;
  }

  ```
* 包装函数对象(仿函数)

  ```cpp
  // 函数对象,重载operator
  struct Divide {
      int operator()(int a, int b) const {
          return a / b;
      }
  };

  int main() {
      // 包装函数对象
      function<int(int, int)> func = Divide();
      cout << func(10, 2) << endl;    // 输出5
      return 0;
  }
  ```
* 包装类的成员函数

  ```cpp
  class Calculator {
  public:
      int sub(int a, int b) {
          return a - b;
      }
  };

  int main()
  {
      Calculator calc;
      // 包装成员函数,成员函数第一个参数为this指针
      function<int(Calculator*, int, int)> func1 = &Calculator::sub;
      function<int(Calculator, int, int)> func2 = &Calculator::sub;
      function<int(Calculator&&, int, int)> func3 = &Calculator::sub;

      // 调用,输出为8
      cout << func1(&calc, 10, 2) << endl;
      cout << func2(calc, 10, 2) << endl;
      cout << func3(move(calc), 10, 2) << endl;
      cout << func3(Calculator(), 10, 2) << endl;

      return 0;
  }
  ```

  由于成员函数第一个参数隐含this指针,使用 `function`进行包装时,要注意第一个参数不要落下,以上三种方式都可以作为参数.

## bind

> `std::bind` 是 C++11 引入的函数绑定工具（位于 `<functional>` 头文件），用于 **将可调用对象与部分参数预先绑定** ，生成一个新的可调用对象（“绑定器”）。它的核心作用是灵活调整函数的参数列表（如固定部分参数、调整参数顺序），适配不同场景的调用需求。

**基本语法**

```cpp
std::bind(可调用对象, 参数列表);
```

* **可调用对象** ：可以是普通函数、Lambda、函数对象、成员函数指针等。
* **参数列表** ：包含具体值或占位符（`std::placeholders::_1, _2, ...`），用于指定新函数的参数如何传递给原对象。

`std::bind`的关键是通过**通过占位符**控制参数传递, `_1`表示第一个未固定参数,`_2` `_3`等同理

通过下列形式引入占位符：

```cpp
using namespace std::placeholders; // 引入占位符 _1, _2...
```

```cpp
using std::placeholders::_1;
using std::placeholders::_2;
```

1. 固定参数

   将函数的部分参数预先固定，新生成的函数只需传入剩余参数。

```cpp
// 原函数:计算a-b
int sub(int a, int b) {
    return a - b;
}

int main() {
    // 绑定第二个参数为 5，新函数签名变为 int(int)（仅需传入 a）
    auto minus5 = bind(sub, _1, 5);
    cout << minus5(10) << endl; // 输出10

    // 绑定第一个参数为 20，新函数签名变为 int(int)（仅需传入 b）
    auto minusFrom20 = bind(sub, 20, _1);
    cout << minusFrom20(7) << endl; // 输出13
    return 0;
}
```

2. 调整参数顺序

   通过占位符重新排列参数传递的顺序。

```cpp
// 原函数:a/b
double divide(double a, double b) {
    return a / b;
}

int main() {
    // 交换参数顺序：新函数的 _1 传给原函数的 b，_2 传给原函数的 a
    auto invert_divide = bind(divide, _2, _1);
    cout << invert_divide(2, 10) << endl;   // 相当于mul(10, 2)
    return 0;
}
```

3. 绑定成员函数（需绑定 `this`指针）

    非静态成员函数隐含`this` 指针作为第一个参数，`std::bind` 需显式绑定对象（或对象指针 / 引用）。

```cpp
class Math {
public:
    // 成员函数：计算 a * b
    int multiply(int a, int b) {
        return a * b;
    }
};

int main() {
    Math math;
    // 绑定对象指针 &math 和成员函数，新函数签名为 int(int, int)
    auto bound_multiply = bind(&Math::multiply, &math, _1, _2);
    cout << bound_multiply(3, 4) << endl;   // 等价于 math.multiply(3,4)
}
```
