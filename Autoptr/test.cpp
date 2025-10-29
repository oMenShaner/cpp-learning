#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <memory>
#include <string>
#include <cstdio>
#include <functional>
using namespace std;

//template<class T>
//class SmartPtr {
//public:
//    // RAII
//    SmartPtr(T* p) : _ptr(p)
//    {
//        cout << "new" << endl;
//    }
//    ~SmartPtr() 
//    {
//        cout << "delete" << endl;
//        delete _ptr;
//    }
//
//    // 运算符重载, 提供指针操作接口
//    T& operator*() const { return *_ptr; }
//    T* operator->() const { return _ptr; }
//private:
//    T* _ptr;
//};
//
//void test_smart_ptr()
//{
//    cout << "\n----- 测试智能指针 -----\n";
//    SmartPtr<int> a = new int(0);
//
//    // 模拟异常
//    throw std::runtime_error("模拟异常");
//}
//
//int main() {
//    try {
//        test_smart_ptr();
//    }
//    catch (const std::runtime_error& e) {
//        cout << e.what() << endl;
//    }
//    return 0;
//}

//class Date {
//private:
//    int _year;
//    int _month;
//    int _day;
//public:
//    Date(int year = 1, int month = 1, int day = 1)
//        :_year(year), _month(month), _day(day)
//    { }
//
//    ~Date()
//    {
//        cout << "~Date" << endl;
//    }
//};
//
//int main() {
//    // 创建 unique_ptr，指向 int 类型的动态内存（值为 10）
//    unique_ptr<int> ptr1(new int(10));
//    cout << *ptr1 << endl;   // 输出:10
//
//    // 所有权转移（ptr1 不再拥有内存，变为空）
//    unique_ptr<int> ptr2(move(ptr1));
//    if (ptr1 == nullptr) {
//        cout << "ptr1为空" << endl;
//    }
//
//    unique_ptr<int[]> arr(new int[3] {1, 2, 3});    // 指向数组
//    cout << arr[0] << arr[1] << arr[2] << endl;     // 输出123
//    return 0;
//}

//int main()
//{
//    // 创建 shared_ptr, 引用计数初始为1
//    shared_ptr<int> ptr1(new int(20));
//    cout << "引用计数: " << ptr1.use_count() << endl;
//
//    // 复制 ptr1, 引用计数变为2
//    shared_ptr<int> ptr2 = ptr1;
//    cout << "引用计数: " << ptr1.use_count() << endl;
//
//    // 重置ptr1(不再指向对象),引用计数变为1
//    ptr1.reset();
//    cout << "引用计数: " << ptr2.use_count() << endl;
//
//    return 0;
//}

//template<class T>
//class MyUniquePtr {
//private:
//    T* _ptr;    // 管理的原始指针
//public:
//    // 构造函数：接管原始指针的所有权
//    MyUniquePtr(T* ptr = nullptr) : _ptr(ptr) {}
//
//    // 禁止拷贝构造(独占所有权,不能复制)
//    MyUniquePtr<T>(const MyUniquePtr<T>&) = delete;
//
//    // 禁止复制赋值
//    MyUniquePtr<T>& operator=(const MyUniquePtr<T>&) = delete;
//
//    // 允许移动构造(转移所有权),浅拷贝即可
//    MyUniquePtr(MyUniquePtr<T>&& other) noexcept
//        :_ptr(other._ptr)
//    {
//        other._ptr = nullptr;
//    }
//
//    // 允许移动赋值
//    MyUniquePtr<T>& operator=(MyUniquePtr<T>&& other) noexcept
//    {
//        if (this != &other)
//        {
//            delete _ptr;        // 释放当前资源
//            _ptr = other._ptr;  // 接管对方资源
//            other._ptr = nullptr;// 对方放弃所有权
//        }
//        return *this;
//    }
//
//    // 析构函数:释放资源
//    ~MyUniquePtr()
//    {
//        delete _ptr;
//    }
//
//    // 重载运算符
//    T& operator*() const
//    {
//        return *_ptr;
//    }
//
//    T* operator->() const
//    {
//        return _ptr;
//    }
//
//    // 检查是否持有资源
//    bool is_null() const
//    {
//        return _ptr == nullptr;
//    }
//};
//
//int main()
//{
//    MyUniquePtr<int> ptr1(new int(10));
//    cout << *ptr1 << endl;  // 输出10
//
//    //MyUniquePtr<int> ptr2(ptr1);    // 错误:禁止拷贝构造
//    //MyUniquePtr<int> ptr2 = ptr1;   // 错误:禁止赋值
//
//    MyUniquePtr<int> ptr2 = move(ptr1); // 移动赋值,转移资源
//    cout << ptr1.is_null() << endl;     // 输出1,ptr1已空
//    cout << *ptr2 << endl;              // 输出10
//
//    return 0;
//}

//struct Person {
//    string _name;
//    int _age;
//    Person(string n, int a) : _name(n), _age(a) {}
//};
//
//int main()
//{
//    // 用make_shared创建shared_ptr
//    auto ptr1 = make_shared<Person>("Tom", 20);
//    // 传递new结果创造
//    shared_ptr<Person> ptr2(new Person("Jerry", 20));
//}

//// 引用计数管理类（单独管理计数，方便共享）
//template<class T>
//struct RefCount {
//    T* _ptr;        // 指向管理的资源
//    size_t _count;  // 强引用计数
//
//    RefCount(T* p): _ptr(p), _count(1) {}
//    ~RefCount() { delete _ptr; }
//};
//
//// 简化版shared_ptr
//template <class T>
//class MySharedPtr {
//private:
//    RefCount<T>* _ref;   // 指向引用计数对象
//
//public:
//    // 构造函数:创建引用计数对象
//    explicit MySharedPtr(T* p = nullptr)
//    {
//        if (p)
//        {
//            _ref = new RefCount<T>(p);
//        }
//        else
//        {
//            _ref = nullptr;
//        }
//    }
//
//    // 拷贝构造:共享资源,计数+1(浅拷贝)
//    MySharedPtr(const MySharedPtr<T>& other)
//    {
//        _ref = other._ref;
//        if (_ref)
//        {
//            _ref->_count++;  // 计数增加
//        }
//    }
//
//    // 计数-1，若为0则释放资源
//    void release()
//    {
//        if (_ref && --_ref->_count == 0)
//        {
//            delete _ref;
//            _ref = nullptr;
//        }
//    }
//
//    // 复制赋值:先减当前计数(若为0则释放0),再共享新资源
//    MySharedPtr& operator=(MySharedPtr<T>& other)
//    {
//        if (this != &other)
//        {
//            release();
//            // 共享新资源
//            _ref = other._ref;
//            if (_ref)
//            {
//                _ref->_count++;
//            }
//        }
//        return *this;
//    }
//
//    // 析构函数
//    ~MySharedPtr()
//    {
//        release();
//    }
//
//    // 重载*和->
//    T& operator*() const
//    {
//        return *_ref->_ptr;
//    }
//
//    T* operator->() const
//    {
//        return _ref->_ptr;
//    }
//
//    // 获取当前引用计数
//    size_t use_count() const
//    {
//        return _ref ? _ref->_count : 0;
//    }
//};
//
//int main()
//{
//    MySharedPtr<int> ptr1(new int(10));
//    cout << "计数1: " << ptr1.use_count() << endl;
//
//    MySharedPtr<int> ptr2 = ptr1;   // 复制构造,计数+1
//    cout << "计数2: " << ptr1.use_count() << endl;
//
//    {
//        MySharedPtr<int> ptr3(ptr2);    // 拷贝构造,计数+1
//        std::cout << "计数3：" << ptr3.use_count() << std::endl; // 输出：3
//    }// ptr3 析构，计数-1 → 2
//
//    std::cout << "计数4：" << ptr1.use_count() << std::endl; // 输出：2
//
//    return 0;
//}

//struct B;  
//struct A {
//    shared_ptr<B> b_ptr;    // A 持有 B 的 shared_ptr
//    ~A() { cout << "A 被销毁\n"; }
//};
//struct B {
//    weak_ptr<A> a_ptr;    // B 持有 A 的 weak_ptr(不增加计数)
//    ~B() { cout << "B 被销毁\n"; } 
//};
//
//int main()
//{
//    {
//        shared_ptr<A> a(new A());   // a的计数=1
//        shared_ptr<B> b(new B());   // b的计数=1
//
//        a->b_ptr = b; // b 的计数变为 2
//        b->a_ptr = a; // a 的计数仍为 1(weak_ptr不增加计数)
//        cout << a.use_count() << endl;
//        cout << b.use_count() << endl;
//    }   // 离开作用域
//
//    // 此时：
//    // a 销毁 → 计数从 1 减为 0 → A 被析构 → a->b_ptr 销毁 → b 计数从 2 减为 1
//    // b 销毁 → 计数从 1 减为 0 → B 被析构
//
//    cout << "程序结束" << endl;
//    return 0;
//}

//int main()
//{
//    shared_ptr<int> sp1(new int(10));
//    weak_ptr<int> wp1(sp1);      // 从 shared_ptr 构造
//    weak_ptr<int> wp2 = wp1;    // 从 weak_ptr 赋值
//
//    std::shared_ptr<int> sp2 = wp1.lock();
//    if (sp2) { // 检查资源是否有效
//        std::cout << *sp2 << std::endl;
//        cout << sp2.use_count() << endl;
//    }
//    else {
//        std::cout << "资源已释放\n";
//    }
//    return 0;
//}

//int main()
//{
//    // 自定义删除器:用delete[]释放数组
//    auto arr_deleter = [](int* p) {
//        cout << "释放数组" << endl;
//        delete[] p;
//    };
//
//    // unique_ptr 绑定删除器（模板参数需指定删除器类型）
//    unique_ptr<int, decltype(arr_deleter)> arr_ptr(new int[3] {1, 2, 3}, arr_deleter);
//
//    return 0; // 离开作用域时，自动调用 arr_deleter 释放数组
//}

//// 自定义删除器:关闭文件 通过仿函数实现
//class Fclose
//{
//public:
//    void operator()(FILE* ptr)
//    {
//        cout << "fclose:" << ptr << endl;
//        fclose(ptr);
//    }
//};
//
//int main()
//{
//    // 打开文件
//    FILE* fp = fopen("test.txt", "w+");
//    if (!fp)
//    {
//        return 1;
//    }
//
//    // shared_ptr 管理文件句柄，绑定删除器
//    shared_ptr<FILE> file_ptr(fp, Fclose());
//
//    return 0; // 自动调用 file_deleter 关闭文件
//}


//// 引用计数控制块（包含删除器）
//template<class T, class Deleter>
//struct SharedControlBlock {
//    T* _ptr;
//    size_t _count;
//    Deleter _deleter;    // 存储删除器
//
//    SharedControlBlock(T* ptr, Deleter d)
//        :_ptr(ptr), _count(1), deleter(move(d)) { }
//
//    ~SharedControlBlock()
//    {
//        _deleter(_ptr); // 调用删除器释放资源
//    }
//};

template<class T>
class SmartPtr {
private:
    T* _ptr;
    std::function<void(T*)> _del = [](T* p) {delete p; };    // 默认为普通delete
public:
    // 默认构造函数
    SmartPtr(T* ptr = nullptr)
        :_ptr(ptr)
    { }

    // 带删除器的构造函数
    template<class Deleter>
    SmartPtr(T* ptr, Deleter del)
        : _ptr(ptr), _del(move(del))
    { }

    // ...

    // 析构函数
    ~SmartPtr()
    {
        _del(_ptr); // 调用删除器进行释放资源
        cout << "释放资源" << endl;
        _ptr = nullptr;
    }
};

int main()
{
    SmartPtr<int> ptri(new int(10));
    auto arr_deleter = [](int* arr) {
        delete[] arr;
        cout << "释放数组" << endl;
    };
    SmartPtr<int> ptrarr(new int[3] {1, 2, 3}, arr_deleter);

    return 0;
}