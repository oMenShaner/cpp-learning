//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;

//int main()
//{
//    // 左值:可以取地址
//    // 以下的p、b、c、*p、s、s[0]就是常⻅的左值
//    int* p = new int(0);
//    int b = 1;
//    const int c = b;
//    *p = 10;
//    string s("111111");
//    s[0] = 'x';
//
//    // 右值:不能取地址
//    double x = 1.1, y = 2.2;
//    // 以下的10、x + y、fmin(x, y)、string("11111")都是常⻅的右值
//    10;
//    x + y;
//    fmin(x, y);
//    string("11111");
//
//    // error:表达式必须是左值或函数指示符
//    // cout << &10 << endl;
//    // cout << &(x+y) << endl;
//    // cout << &(fmin(x, y)) << endl;
//    // cout << &string("11111") << endl;
//
//    // 左值引⽤给左值取别名
//    int& r1 = b;
//    int*& r2 = p;
//    int& r3 = *p;
//    string& r4 = s;
//    char& r5 = s[0];
//
//    // 右值引⽤给右值取别名
//    int&& rr1 = 10;
//    double&& rr2 = x + y;
//    double&& rr3 = fmin(x, y);
//    string&& rr4 = string("11111");
//
//    // 左值引用不能直接引用右值, 但是const左值引用可以引用右值
//    const int& rx1 = 10;
//    const double& rx2 = x + y;
//    const double& rx3 = fmin(x, y);
//    const string& rx4 = string("11111");
//
//    // 右值引用不能直接引用左值,但是右值引用可以引用move(左值)
//    int&& rrx1 = move(b);
//    int*&& rrx2 = move(p);
//    int&& rrx3 = move(*p);
//    string&& rrx4 = move(s);
//    string&& rrx5 = (string&&)s;
//
//    // b、r1、rr1都是变量表达式,都是左值,都可以取地址
//    cout << &b << endl;
//    cout << &r1 << endl;
//    cout << &rr1 << endl;
//
//    int& r6 = r1;
//    // int&& rrx6 = rr1; error
//    int&& rrx6 = move(rr1);
//}

//void f(int& x)
//{
//    cout << "左值引用重载" << endl;
//}
//
//void f(const int& x)
//{
//    cout << "const左值引用重载" << endl;
//}
//
//void f(int&& x)
//{
//    cout << "右值引用重载" << endl;
//}
//
//int main()
//{
//    int i = 1;
//    const int ci = 2;
//
//    f(i);   // 调用f(int&)
//    f(ci);  // 调用f(const int&)
//    f(3);   // 调用f(int&&), 如果没有f(int&&)重载则会调用f(const int&)
//    f(move(i)); // 调用f(int&&)
//}

//class Myclass {
//public:
//    Myclass(int data = 10) : _data(data)
//    {
//        cout << "默认构造Myclass(int data = 10)" << endl;
//    }
//
//    Myclass(const Myclass& tmp) : _data(tmp._data)
//    {
//        cout << "拷贝构造Myclass(const Myclass& tmp)" << endl;
//    }
//
//    Myclass& Add(int val)
//    {
//        _data += val;
//        return *this;
//    }
//private:
//    int _data;
//};
//
//int main()
//{
//    Myclass m1;
//    Myclass m2(m1.Add(10));
//}

//class MyString {
//private:
//    char* _data;
//    size_t _size;
//public:
//    void swap(MyString& s)
//    {
//        ::swap(_data, s._data);
//        ::swap(_size, s._size);
//    }
//    // 默认构造函数
//    MyString(const char* str = "")
//        :_size(strlen(str))
//    {
//        _data = new char[_size + 1];
//        std::memcpy(_data, str, _size + 1);
//        cout << "默认构造函数MyString(const char* str = "")" << endl;
//    }
//    // 传统的拷贝构造函数(深拷贝,成本高)
//    MyString(const MyString& other) : _size(other._size)
//    {
//        _data = new char[_size + 1];
//        std::memcpy(_data, other._data, _size + 1);
//        cout << "拷贝构造函数MyString(const MyString& other)" << endl;
//    }
//
//    // 移动构造函数("窃取"资源,成本极低)
//    MyString(MyString&& other) noexcept
//        :_data(other._data), _size(other._size)
//    {
//        // 直接复制指针和大小
//
//        // 将源对象置于可安全析构的状态
//        other._data = nullptr;
//        other._size = 0;
//        std::cout << "移动构造函数MyString(MyString&& other)" << std::endl;
//    }
//    // 移动赋值
//    MyString& operator=(MyString&& s)
//    {
//        swap(s);
//        std::cout << "移动赋值MyString& operator=(MyString&& s)" << std::endl;
//        _data = nullptr;
//    }
//};
//
//// 使用场景
//MyString createString() {
//    MyString temp("Hello");
//    return temp; // 这里编译器通常会进行RVO，但即使不优化，也会优先选择移动构造函数
//}
//
//int main()
//{
//    MyString s1 = createString(); // 如果没有移动构造，这里会调用拷贝构造。有移动构造则调用移动构造。
//    MyString s2 = std::move(s1);  // 使用 std::move 将左值 s1 强制转换为右值，触发移动构造
//}

//// 由于引用折叠限定,f1实例化以后总是左值引用
//template<class T>
//void f1(T& x)
//{ }
//
//// 由于引用折叠限定,f2实例化以后可以是左值引用,也可以是右值引用
//template<class T>
//void f2(T&& x)
//{ }
//
//int main()
//{
//    typedef int& lref;
//    typedef int&& rref;
//    int n = 0;
//
//    lref& r1 = n;   // r1 的类型是 int&
//    lref&& r2 = n;  // r2 的类型是 int&
//    rref& r3 = n;   // r3 的类型是 int&
//    rref&& r4 = 1;  // r4 的类型是 int&&
//
//    // 没有折叠->实例化为void f1(int& x)
//    f1<int>(n); 
//    f1<int>(0);     // 报错
//
//    // 折叠->实例化为void f1(int& x)
//    f1<int&>(n);
//    f1<int&>(0);    // 报错
//
//    // 折叠->实例化为void f1(int& x)
//    f1<int&&>(n);
//    f1<int&&>(0);   // 报错
//
//    // 折叠->实例化为void f1(const int& x)
//    f1<const int&>(n);
//    f1<const int&>(0);  
//
//    // 折叠->实例化为void f1(const int& x)
//    f1<const int&&>(n);
//    f1<const int&&>(0);
//
//    // 没有折叠->实例化为void f2(int&& x)
//    f2<int>(n);     // 报错
//    f2<int>(0);
//    
//    // 折叠->实例化为void f2(int& x)
//    f2<int&>(n);
//    f2<int&>(0);   // 报错
//
//    // 折叠->实例化为void f2(int&& x)
//    f2<int&&>(n);   // 报错
//    f2<int&&>(0);   
//}

//// 手动模拟模板推导和引用折叠
//template<class T>
//struct myClass {
//    using Type = T&&;   // 这里会发生引用折叠
//};
//
//int main()
//{
//    int val = 42;
//
//    // int&
//    using Result1 = myClass<int&>::Type;    // int& && -> int&
//
//    // int&&
//    using Result2 = myClass<int&&>::Type;   // int&& && -> int&&
//
//    // const int&
//    using Result3 = myClass<const int&>::Type;  // const int& && -> const int &
//
//    return 0;
//}

//// 目标函数 - 重载版本
//void process(int& x) {
//    cout << "处理左值: " << x << endl;
//}
//
//void process(int&& x) {
//    cout << "处理右值: " << x << endl;
//}
//
//void process(const int& x) {
//    cout << "处理 const 左值: " << x << endl;
//}
//
//// 简单的转发函数 - 有问题！
//template<class T>
//void forward_bad(T arg) {   // 按值传递,总是拷贝
//    process(arg);           // arg 总是左值！
//}
//
//template<typename T>
//void forward_bad2(T& arg) {    // 只能接受非const左值
//    process(arg);              // 总是调用左值版本
//}
//
//int main() {
//    int x = 10;
//    const int y = 20;
//
//    cout << "直接调用:" << endl;
//    process(x);        // 左值版本 ✓
//    process(30);       // 右值版本 ✓
//    process(y);        // const左值版本 ✓
//
//    cout << "\n错误转发:" << endl;
//    forward_bad(x);    // 左值版本 ✓ (但有不必要的拷贝)
//    forward_bad(30);   // 左值版本 ✗ (应该是右值！)
//    forward_bad(y);    // 左值版本 ✗ (应该是const左值！)
//
//    // forward_bad2(30);  // 编译错误！不能绑定右值到非const左值引用
//}

#include <iostream>
#include <utility>

using namespace std;

// 调试工具
template<class T>
void debug_forward(const char* scenario, T&& arg) {
    cout << scenario << ":" << endl;

    if (is_lvalue_reference<T>::value) {
        cout << "  T 是左值引用" << endl;
    }
    else if (is_rvalue_reference<T>::value) {
        cout << "  T 是右值引用" << endl;
    }
    else {
        cout << "  T 是非引用类型" << endl;
    }

    cout << "  转发前 arg 是: ";
    if (is_lvalue_reference<decltype(arg)>::value) cout << "左值引用" << endl;
    else if (is_rvalue_reference<decltype(arg)>::value) cout << "右值引用" << endl;

    cout << "  转发后结果是: ";
    if (is_lvalue_reference<decltype(std::forward<T>(arg))>::value)
        cout << "左值引用" << endl;
    else if (is_rvalue_reference<decltype(std::forward<T>(arg))>::value)
        cout << "右值引用" << endl;

    cout << endl;
}

// 目标函数
void target(int&) { cout << "  调用: 左值版本" << endl; }
void target(int&&) { cout << "  调用: 右值版本" << endl; }
void target(const int&) { cout << "  调用: const左值版本" << endl; }

// 完美转发函数
template<class T>
void perfect_forward(T&& arg){
    debug_forward("在 perfect_forward 中", arg);
    target(std::forward<T>(arg));
}

int main() {
    int x = 10;
    const int y = 20;

    cout << "=== 完美转发演示 ===" << endl;
    perfect_forward(x);             // 左值
    perfect_forward(30);            // 右值
    perfect_forward(y);             // const 左值
    perfect_forward(std::move(x));  // 右值

    return 0;
}