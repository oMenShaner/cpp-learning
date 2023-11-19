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
// 用 str 从 $[pos, pos+len)$ 来拷贝构造.
// 如果范围超过了 pos位置到字符串末尾的长度, 拷贝到字符串结尾就停止了.
```
这里的 `npos` 是最大的 `size_t`, 在 64 位下就是 $2^{64}-1 = 9223372036854775808$
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
`capacity()` 得到当前 `string` 对象的容量大小, 和当前对象的有效字符长度没有必然联系, 取决于编译器底层扩容机制

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


## 3. string 类对象的访问及遍历操作

函数名称|功能说明
---|---
[operator[]](https://legacy.cplusplus.com/reference/string/string/operator[]/)| 返回 `pos` 位置的字符, `const string` 类对象调用
[begin](https://legacy.cplusplus.com/reference/string/string/begin/) + [end](https://legacy.cplusplus.com/reference/string/string/end/)| `begin` 获取第一个字符的迭代器 + `end` 获取最后一个字符下一个位置的迭代器
[rbegin](https://legacy.cplusplus.com/reference/string/string/rbegin/) + [rend](https://legacy.cplusplus.com/reference/string/string/rend/)| `rbegin` 获取最后一个字符的迭代器 + `rend` 获取第一个字符前一个位置的迭代器
范围 `for`| C++11支持更简洁的范围 `for` 的新遍历方式

### operator[] 和 at() 
