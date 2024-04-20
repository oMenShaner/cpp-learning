# stack 和 queue(priority_queue)

## 1. 容器适配器

> 适配器(Adapter)：一种用来修饰**容器**(Containers)或**仿函数**(Functors)或**迭代器**(Iterator)接口的东西。

**适配器是一种设计模式**，该模式将一个类的接口转换成客户希望的另外一个接口。

现实中拿插座来说，一个插座可以适配不同的插头，以适应不同电器的电压或者其他要求。

![image-20240420220120184](<.\stack和queue(priority_queue).assets\image-20240420220120184.png>)

`STL`中的适配器相当于一个插座，以适应不同容器，可以"插入"`vector`, 也可以插入 `list`，等等。

---

> 虽然`stack`和`queue`也可以存放元素，但在`STL`中并没有将其划分在容器的行列，而是将其称为**容器适配器**。

例如`stack`只提供**LIFO**（先进先出）的概念，对其他容器的接口进行了包装，并没有完全重新创建了一个容器。在`STL`中，`stack`和`queue`默认使用`deque`，而`priority_queue`默认使用`vector`。

![image-20240420221010149](<.\stack和queue(priority_queue).assets\image-20240420221010149.png>)

类似于`list`中`iterator`的实现，实际上是更高一层的封装。`__list_iterator`是对`Node*`的封装，以支持运算符重载；相对应的，`stack`是对其`Container`的封装，以支持**LIFO**的环境。

## 2. stack 的介绍和实现

### 2.1 stack 的介绍

[stack 文档介绍](https://cplusplus.com/reference/stack/stack/?kw=stack)

> 1. `stack` 是一种容器适配器，设计用于在具有**后进先出**操作的上下文环境中，其删除和插入只能从容器的末尾进行操作。
>
> 2. `stack`是作为容器适配器被实现的，**容器适配器**即是对特定类封装作为其底层的容器，并提供一组特定的成员函数来访问其元素，元素特定从容器的尾部（即栈顶）被压入和弹出。
>
> 3. `stack`的底层容器可以是任何标准的容器类模板或者一些特殊设计的容器类。这些容器应该支持如下操作：
>
>    ```cpp
>    empty()			// 判空操作
>    size()  		// 得到元素个数操作
>    back()  		// 得到容器尾部元素操作
>    push_back()		// 尾插操作
>    pop_back()		// 尾删操作
>    ```
>
> 4. 标准容器`list`,`vector`和`deque`均满足这些要求。**默认情况下**，如果没有为`stack`指定特定的底层容器，默认使用`deque`作为底层容器。

![image-20240420222803451](<.\stack和queue(priority_queue).assets\image-20240420222803451.png>)

### 2.2 stack 的实现

`stack` 有如下成员函数（不包括 C++11)

![image-20240420222654994](<.\stack和queue(priority_queue).assets\image-20240420222654994.png>)

利用**适配器**概念进行实现：

```cpp
#pragma once
#include <deque>

namespace wr
{
  template <class T, class Con = deque<T>>
  class stack
  {
  public:
    void push(const T &x)
    {
      _con.push_back(x);
    }

    void pop()
    {
      _con.pop_back();
    }

    T &top()
    {
      return _con.back();
    }

    T &top() const
    {
      return _con.back();
    }

    size_t size()
    {
      return _con.size();
    }

    bool empty()
    {
      return _con.empty();
    }

  private:
    Con _con;	// 底层的容器类对象作为成员变量
  };
}
```

可以看到，适配器模式下设计的`stack`十分简洁，相比用 C 语言实现的`stack`,完全体现了适配器模式的优势。

<font color = red>总结</font>：从使用者角度来看，不需要知道`stack`底层使用的是什么容器实现，只需要知道其可以实现对应适合 LIFO 的操作。无论是`STL`中的容器，还是自定义类容器，只要拥有对应的接口，就可以作为`stack`的底层容器。

---

## 2. queue 的介绍和实现

### 2.1 queue 的介绍

[queue 文档介绍](https://cplusplus.com/reference/queue/queue/)

> 1. `queue` 是一种容器适配器，专门用于在 FIFO（先进先出）的环境中操作，其中从容器一端插入元素，另一端提取元素。
>
> 2. `queue`作为容器适配器实现，用一个底层是特定容器类的封装类来实现，`queue`提供了特定了成员函数来访问它的元素。元素队尾入队列，从队头出队列。
>
> 3. `queue`的底层容器可以是标准容器中的一种，或者是经过特别设计的容器类。底层容器应该至少指出如下操作：
>
>    ```c++
>    empty()				// 判空操作
>    size()				// 得到元素个数操作
>    front()				// 得到容器头部元素
>    back()				// 得到容器尾部元素
>    push_back()			// 容器尾插元素操作
>    pop_back()			// 容器头删元素操作
>    ```
>
> 4. `STL`中`deque`和`list`可以满足这些需求。默认情况下，如果没有容器类被指定，默认使用`deque`作为`queue`的底层容器。

![image-20240420231255575](<./stack和queue(priority_queue).assets/image-20240420231255575.png>)

### 2.2 queue 的实现

`queue`有如下成员函数：

![image-20240420231447136](<./stack和queue(priority_queue).assets/image-20240420231447136.png>)

实现如下：

```cpp
#pragma once

#include <deque>

namespace wr
{
  template <class T, class Con = deque<T>>
  class queue
  {
  public:
    void push(const T &x)
    {
      _con.push_back(x);
    }

    void pop()
    {
      _con.pop_front();
    }

    T &back()
    {
      return _con.back();
    }

    const T &back() const
    {
      return _con.back();
    }

    T &front()
    {
      return _con.front();
    }

    const T &front() const
    {
      return _con.front();
    }

    size_t size() const
    {
      return _con.size();
    }

    bool empty() const
    {
      return _con.empty();
    }

  private:
    Con _con;
  };
}
```

和`stack`的实现差不多，<font color = red>唯一需要注意的是 </font>：`queue`的底层容器不能是`vector`，因为`vector`类根本不支持`pop_front()`的操作。并且`vector`的头删效率太低，需要挪动后面的所有元素。

## 3. priority_queue 的介绍和使用
