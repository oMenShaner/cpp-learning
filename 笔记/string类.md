本章开始, 进入学习 C++ STL 的阶段, 现简单了解一下什么是 STL
# STL简介
STL(standard template libraru -标准模板库): **是C++标准库的重要组成部分**, 不仅是一个可复用的组建爱你哭, 而且是**一个包罗数据结构与算法的软件框架**.

**STL的版本**
市面上最常用的是 **P.J.版本**(被Windows Visual C++ 采用)和 **SGI版本**(被GCC采用)

**STL六大组件**
![Alt text](image/string%E7%B1%BB/image.png)

# 一. 为什么要有string类
在C语言中, 已经学习过字符串了.

C语言中, 字符串是以 `\0` 为结尾的一些字符的集合. 
为了操作方便, C标准库 <string.h> 提供了一些处理字符串的库函数. 
但是这些库函数是与字符串分开的, **不符合 OOP 的思想,** 而且底层空间需要用户自己管理, 稍不留神就可能出现越界访问.

string类比STL出现的要早, 原因就是 string 的使用太常见了, 最后将 string 归入 STL 中.

# 二. STL 中的 string 类介绍
## 1. string 类描述
在 STL 中最常用的一个数据结构就是 `string` .

> - 字符串是表示字符序列的对象.
> - 标准 `string` 类提供的借口类似与 `standard container` 所提供的字符接口, 同时专门增加了操作 `single-byte` 字符串的设计特性
> - `string` 类是 `basic_string<char>` 模板的实例, 并用 `char_traits` 和 `allocator` 作为 `basic_string` 的默认参数
> - `string` 类独立于所使用的编码来处理字节, 如果用来处理多字节或者变长字符(如 UTF-8) 的系列, `string` 类仍然按照字节来操作, 而不是按照实际编码的字符来操作.

<font size=4 color=red>总结</font>
1. `string` 是表示字符串的字符串类.
2. 该类的接口与常规容器的接口基本相同, 再添加了一些专门操作 `string` (例如单字节字符串)的常规操作.
3. `string` 在底层实际是: <font style="background: red">basic string</font> 模板类的别名.
```cpp
typedef basic_string<char, char_traits, allocator> string;
```
4. 不能操作多字节或者变长字符的序列.

**使用 `string` 类, 需要**:
```cpp
#include<string>    // 使用 string 类需要引入头文件
using std::string   // string 标识在命名空间 std 中
```

## 2. 关于 basic_string
通过查看文档,可以看到 `basic_string` 是一个模板
```cpp
template < class charT, 
class traits = char_traits<charT>,    // basic_string::traits_type           
class Alloc = allocator<charT>        // basic_string::allocator_type           
> class basic_string;
```
这里的 `charT` 表示实例化后的类需要按照 `charT` 类的字符处理字符串.

根据不同的 `charT` 类, 可以生成四种字符串类
![Alt text](image/string%E7%B1%BB/image-1.png)

UTF-8 就是一个字符有 8bit, 众所周知 `char` 类型的一个数据有 `8` bit.  
`wstring` 常用来处理 Unicode 类型的字符
还有UTF-16, UTF-32字节编码类型.

对于 `string` 是 `basic_string` 模板实例化的一个类就可以很好理解了
```cpp
typedef basic_string<char, char_traits, allocator> string;
```
`string` 就是用来处理 单字节字符的字符串, 不适用于用来处理变长字符或者多字节字符串.
其他字符串有 `basic_string` 模板实例化的其他类来处理.

# 三. string 类的常用接口
## 1. string 类的常见构造
官方文档 C++98 下的所有 `string` 类构造函数:
![Alt text](image/string%E7%B1%BB/image-2.png)

**重点掌握:**
```cpp
string()                  //构造空的 string 类对象, 即空字符串
string(const char* s)       //使用 C-string 来构造 string 对象
string(size_t n, char c)  //string 类对象中包含 n个字符c
string(const string &c)   //拷贝构造函数
```

代码演示:
```cpp
int main()
{
  // string()
  string s1 = string(); // 无参构造

  // string(const char *s)
  string s2 = string("Hello string"); // 使用C格式字符串构造

  // string(size_t n, char c)
  string s3 = string(4, 'c'); // 使用 4个c字符 构造

  // string(const string& s)
  string s4 = string(s3); // 拷贝构造
}
```

![Alt text](image/string%E7%B1%BB/image-3.png)

***

```cpp
string(const string& str, size_t pos, size_t len = npos)
// 用 str 从 [pos, pos+len) 来拷贝构造.
// 如果范围超过了 pos位置到字符串末尾的长度, 拷贝到字符串结尾就停止了.
```
这里的 `npos` 是最大的 `size_t`, 在 64 位下就是 $2^{64}-1 = 9223372036854775808$, 它是 `string` 类的静态成员, 使用 `string::npos`
![Alt text](image/string%E7%B1%BB/image-4.png)

代码演示:
```cpp
int main()
{
  string s1 = string("12345678");
  string s2 = string(s1, 1, 5);     // [1, 6)
  string s3 = string(s1, 0);        // [0, s1.size()) 第三个参数不写默认用缺省值 npos
}
```
![Alt text](image/string%E7%B1%BB/image-5.png)

***
<font size=4 color=green>补充</font>

`string` 类同样重载了 `=` , 可以直接按照下面的格式, 编译器会直接优化成用该C格式字符串进行构造.
```cpp
string s1 = "Hello string";
```

## 2. string 类的容量操作

函数名称|功能说明
---|---
[size](https://legacy.cplusplus.com/reference/string/string/size/)|返回字符串有效字符长度
[length](https://legacy.cplusplus.com/reference/string/string/length/)|返回字符串有效字符长度
[capacity](https://legacy.cplusplus.com/reference/string/string/capacity/)|返回空间总大小
[empty](https://legacy.cplusplus.com/reference/string/string/empty/)|检测字符串是否位空串, 是返回 `true`, 否则返回 `false`
[max_size](https://legacy.cplusplus.com/reference/string/string/max_size/)|返回字符串可取的最大有效字符长度
[clear](https://legacy.cplusplus.com/reference/string/string/clear/)|清空有效字符
[reserve](https://legacy.cplusplus.com/reference/string/string/reserve/)|为字符串预留空间
[resize](https://legacy.cplusplus.com/reference/string/string/resize/)|将有效字符的个数改成n个, 多出的空间用字符c填充

### size() 和 length()
```cpp
size_t size() const;
size_t length() const;
```
`size()` 和 `length()`都是得到字符串的有效长度, 两者没有区别.
```cpp
int main()
{
  string s1;
  cout << "Please input a string: ";
  cin >> s1;

  cout << "Your input: " << s1;
  cout << "s1.size(): " << s1.size() << endl;
  cout << "s1.length(): " << s1.length() << endl;

  return 0;
}
```

程序运行结果:  
![Alt text](image/string%E7%B1%BB/image-6.png)

<font size=4 color=red>注意:</font>
`size()` 和 `length()` 不包括 `\0` , `\0` 是结尾标识符, 不被算作字符串的长度.

`length()`的出现是要比 `size()` 要早的. 一开始 `string` 类出现的时候并没有 STL, STL 其他很多容器计算大小都是使用 `size()`
为了将 `string` 放入 STL, 也让 `string` 类拥有了 `size()` 方法, 两者在底层是一模一样的.

`size()` 和 `length()` 的底层源码: 甚至 `length()` 底层是直接调用 `size()` 的
```cpp
size_type size() const { return _M_finish - _M_start; } //有效字符的个数，finish永远指向\0

size_type length() const { return size(); }
```

***
### capacity()
```cpp
size_t capacity() const;
```
`capacity()` 得到当前 `string` 对象的**可存放有效字符的**容量值, `capacity >= size`, 如何扩容取决于编译器底层扩容机制

下面写一个程序用来测试 `g++(Linux)` 的扩容机制
```cpp
int main()
{
  string s1 = string();
  size_t old_capacity = s1.capacity();
  cout << old_capacity << endl;

  for (int i = 0; i < 500; i++)
  {
    s1.push_back('x');
    if (old_capacity != s1.capacity())
    {
      old_capacity = s1.capacity();
      cout << old_capacity << endl;
    }
  }

  return 0;
}
```
发现在<font color=green>Linux下 g++编译器</font>的扩容机制是这样的: **第一次直接开 15 个字符的空间, 之后每次扩容为当前容量的两倍.**
![Alt text](image/string%E7%B1%BB/image-7.png)

### max_size()
```cpp
size_t max_size() const;
```
`max_size()` 可以返回字符串的最大长度

```cpp
int main()
{
  string s1;
  cout << s1.max_size() << endl;
  
  return 0;
}
```
程序运行结果如下:  ![Alt text](image/string%E7%B1%BB/image-19.png), 转换为 16进制: `0x3FFFFFFFFFFFFFFF`, 结果是 `int` 类型可取最大正整数 `2^63-1` 的一半.

`max_size()` 所返回的数不能保证真的能创建一个这么大容量的 `string` 类对象, 程序很有很有可能报异常.

![Alt text](image/string%E7%B1%BB/image-20.png)

`max_size()` 的主要作用就是通过得到的返回值可以得到**系统或者库中实现的限制**, 提醒不能超过这么大的容量, 实践中参考和使用价值并不大.

### reserve()
```cpp
void reserve(size_t n = 0);
```
`reserve()` 可以申请为 `string` 类扩容, 使得扩容后的 `capacity` 可以存放**输入参数**长度的字符串. 不一定就会扩容**输入参数**, `capacity` >= `n` 即可(例如输入500, 不一定会只开500)

- 如果 `n > capacity`, 编译器会将 `capacity` 扩容至 `n`(可能大于`n`)

```cpp
int main()
{
  string s1("Hello,world");
  cout << "size: " << s1.size() << endl;
  cout << "begin: " << s1.capacity() << endl;

  // n > size
  s1.reserve(300);
  cout << "n > size: " << s1.capacity() << endl;

  return 0;
}
```
程序运行如下: 在 Linux g++ 下, `s1` 的 `capacity` 被扩容至了 `n`
![Alt text](image/string%E7%B1%BB/image-21.png)

- 如果 `n < capacity`, `capacity` 不会被改变
```cpp
int main()
{
  string s1("Hello,world");
  cout << "size: " << s1.size() << endl;
  cout << "begin: " << s1.capacity() << endl;

  s1.reserve(13);
  cout << "s1.reserve(13): " << s1.capacity() << endl;

  s1.reserve(1);
  cout << "s1.reserve(1): " << s1.capacity() << endl;

  return 0;
}
```
程序运行结果如下: `n` < `capacity` 时, 无论 `n` 是比 `size` 大还是小, 都不会对 `capacity` 进行改变
![Alt text](image/string%E7%B1%BB/image-22.png)

<font size=4 color=red>总结:</font>`reserve` 只提供扩容功能, 不会对原本的数据进行修改.

### resize()
```cpp
void resize(size_t n);
void resize(size_t n, char c);
```
`resize()` 会修改 `string` 类对象的 `size` 为 `n`
- 如果 `n > capacity`, 将 `capacity` 扩容至少到 `n`, 同时插入字符(默认是`'\0'`)至 `size` 为 `n`
- 如果 `n <= capacity && n >= size` , 直接尾插字符, 容量不变
- 如果 `n < size`, 将 `n` 位置字符替换为 `0`, 容量不变

- `n > capacity`
```cpp
int main()
{
  string s1 = "1234567890";
  cout << "begin\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl << endl;

  // n > capacity
  s1.resize(40);
  cout << "after s1.resize(40)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;
}
```
程序运行结果:
<font color=red>注意: 只有字符串中最后一个`'\0'`会被认为是结尾标识符, 前面的`'\0'`都是有效字符</font>
![Alt text](image/string%E7%B1%BB/image-23.png)

- `n <= capacity && n >= size`
```cpp
s1.resize(13);
cout << "after s1.resize(13)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;
```
程序运行结果:  
![Alt text](image/string%E7%B1%BB/image-24.png)

- `n < size`
```cpp
s1.resize(5);
cout << "after s1.resize(5)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;
```
程序运行结果为:  
![Alt text](image/string%E7%B1%BB/image-25.png)

<font color=red>`resize()` 常用作在知道需要开很大空间的前提下, 提前开空间进行初始化, 避免重复扩容, 扩容消耗很大.</font>
## 3. string 类对象的访问及遍历操作

函数名称|功能说明
---|---
[operator[]](https://legacy.cplusplus.com/reference/string/string/operator[]/)| 返回 `pos` 位置的字符, `const string` 类对象调用
[begin](https://legacy.cplusplus.com/reference/string/string/begin/) + [end](https://legacy.cplusplus.com/reference/string/string/end/)| `begin` 获取第一个字符的迭代器 + `end` 获取最后一个字符下一个位置的迭代器
[rbegin](https://legacy.cplusplus.com/reference/string/string/rbegin/) + [rend](https://legacy.cplusplus.com/reference/string/string/rend/)| `rbegin` 获取最后一个字符的迭代器 + `rend` 获取第一个字符前一个位置的迭代器
范围 `for`| C++11支持更简洁的范围 `for` 的新遍历方式

### operator[] 和 at() 
如果想要访问字符串的元素, 可以使用`[]` 来访问, 并使用 `for` 循环来遍历字符串
```cpp
int main()
{
  string s1 = "hello world!";

  for (size_t i = 0; i < s1.size(); i++)
  {
    cout << s1[i]; // 使用 operator[] 访问每个字符
  }

  cout << endl;
}
```
就像使用 `for` 循环遍历数组一样, 通过 `[]` 解引用访问每一个数组元素.

这里的 `[]` 是**运算符重载**, 同等于下面的形式, 即 `operator[]`, `s1` 通过调用运算符重载来达到访问该位置元素的效果, 传入参数为元素的下标序号(index position)

```cpp
cout << s1[i];   
cout << s1.operator[](i) <<;  // 返回下标为 i 的元素的引用
```
如果想要修改该位置的元素, 也是可以通过 `[]` 进行修改的
```cpp
int main()
{
  string s1("helloworld");

  for (size_t i = 0; i < s1.size(); i++)
  {
    ++s1[i];    // 对 s1 的每个字符都加1
  }

  cout << s1 << endl;
}
```
程序结果为: ![Alt text](image/string%E7%B1%BB/image-8.png)


`operator[]` 运算符重载有两种形式
```cpp
char& operator[] (size_t pos);              // 可读可写
const char& operator[] (size_t pos) const;  // 只读不可写
```
为了让运算符重载支持对原位置元素的修改, 需要返回 `char&` 对原位置元素的引用.
同时也提供 `cosnt` 版本, 调用运算符重载的对象是一个 `const` 对象时, 通过对原位置的 `const` 引用, 以达到不可修改的作用.

***
`at()` 和 `[]` 起到的作用都是一样的, 取到下标为 `i` 的元素, 可以对其进行修改.

唯一的区别是两者对越界的处理.
- `[]` 可以访问 $[0, size]$ 的元素, 如果越界直接**断言**, 程序停止.
- `at()` 可以访问 $[0, size)$ 的元素, 如果越界会**报异常**, 处理相对温和.

![Alt text](image/string%E7%B1%BB/image-9.png)

![Alt text](image/string%E7%B1%BB/image-10.png)

但一般情况还是 `[]` 用的比较多. 

<font color=red size=4>还有一个需要注意的点</font>: 
下标的是一个 `size_t` 类型, 即 `string::size_type`. 但一般写 `int` 类型的就可以了. 64位机器下, 对于小于 $2^{63}-1$的下标, `int` 和 `size_t` 是一样的, 如果为了规范, 当然是更推荐写 `size_t` 类型.

***

### 使用迭代器进行遍历
迭代器(iterator)是 C++ STL的组件之一, 作用是**用来遍历容器**

```cpp
int main()
{
  string s1 = "Hello,world!";

  string::iterator it = s1.begin();
  while (it != s1.end()){
    cout << *it << " ";
    ++it;
  }

  cout << endl;
}
```
程序运行结果:![Alt text](image/string%E7%B1%BB/image-11.png) 

`iterator` 的用法是指针, 但是不一定是指针, 目前使用它只要像使用指针一样. 

![Alt text](image/string%E7%B1%BB/image-12.png)

`it` 的类型是 `string::iterator`, `iterator` 是 `string` 类的成员变量.

`iterator` 遍历对于像 `string` 这样底层连续的容器看起来不如使用 `[]` 来的直接简便.
但是对于物理结构非线性的结构却十分高效, 例如链式结构, 树形结构, 哈希结构这样的容器, 是不可以用 `[]` 的形式来遍历访问到每一个元素的. 
因为 `[]` 在底层本质是通过相对于首元素的偏移量来访问到对应元素的. 而上述结构在物理结构上并不是连续的, 不可以通过偏移量来访问到每个元素. 

<font style="background: red">iterator不用关心底层是怎么实现的, 通用性更强</font>. 上述用来 `iterator` 遍历同样适用于非线性结构.

如果想要反向遍历, 也有对应的 `rbegin` 和 `rend` 使用, 要使用反向迭代器类 `reverse_iterator`

```cpp
int main()
{
  string s1("Hello,world!");

  string::reverse_iterator it = s1.rbegin();
  while (it != s1.rend()){
    cout << *it;
    ++it;
  }

  cout << endl;
}
```
程序运行结果是:  ![Alt text](image/string%E7%B1%BB/image-14.png)
![Alt text](image/string%E7%B1%BB/image-15.png)
***
下面是 `string` 类的所有迭代器类成员变量 
![Alt text](image/string%E7%B1%BB/image-13.png)
如果容器对象是 `const` 对象, 也有对应的 `const_iterator`. 
<font color=red>不同于 `const iterator` </font>, `const_iterator` 限制的是不可以通过对指向容器的元素进行修改, 而 `const iterator` 则是限定了 `it` 不可以修改, 这显然是不对的.

同样的, `begin` 和 `end`, `rbegin` 和 `rend` 也重载了 `const` 修饰的成员函数  
![Alt text](image/string%E7%B1%BB/image-16.png)

如果不想让迭代器对原数据进行修改, 可以这样定义 `it`
```cpp
string::const_iterator it = s1.begin();
```
编译器会自动使用 `begin()` 的 `const`形式.


C++11 新增了 `cbegin`, `cend`, `crbegin`, `crend`; 这些仅有 `const` 版本, 但是并不实用.

### 范围 for (C++11)
C++11添加了范围 `for` 的语法, 配合 `auto` 关键字, 可以更为简洁地进行遍历

```cpp
int main()
{
  string s1 = "Hello,world";

  // 编译器将 auto 推导为 string::iterator
  for (auto e: s1){
    cout << e;
  }
  cout << endl;
}
```
程序运行结果为:  ![Alt text](image/string%E7%B1%BB/image-17.png)

其实底层仍然是使用迭代器进行遍历, 只是看起来更为简洁. 配合 `auto` 可以使整个代码大大缩短, 但是降低了程序可读性.

配合引用, 也可以进行原数据上的修改
```cpp
int main()
{
  string s1 = "Hello,world";

  for (auto& e: s1){
    ++e;
  }
  cout << s1 << endl;
}
```
程序运行结果为:  ![Alt text](image/string%E7%B1%BB/image-18.png)

