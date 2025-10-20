//#include <iostream>
//#include <vector>
//#include <string.h>
//using namespace std;
//template<class ...Args>
//void func(Args... args){ }
//
//template<class ...Args>
//void func(Args&... args) {}
//
//template<class ...Args>
//void func(Args&&... args) {}

//template<class ...Args>
//void Print(Args&&... args)
//{
//    cout << sizeof...(args) << endl;
//}
//
//int main()
//{
//    double x = 2.2;
//    Print();                        // 包里有0个参数
//    Print(1);                       // 包里有1个参数
//    Print(1, string("xxxxx"));      // 包里有2个参数
//    Print(1.1, string("xxxxx"), x); // 包里有3个参数
//
//    return 0;
//}


//// 1. 递归终止函数（参数包为空时调用） 
//void Print()
//{
//    cout << "参数打印完毕!" << endl;
//}
//
//// 2. 可变参数函数模板（递归展开）
//// 每次处理第一个参数t，剩余参数包Args... args继续递归
//template<class T, class ...Args >
//void Print(T t, Args... args)
//{
//    cout << "参数: " << t << "(剩余" << sizeof...(args) << "个参数)" << endl;
//    Print(args...); // 展开剩余参数包，继续递归
//}
//
//int main() {
//    Print(10, 3.14, string("hello"), 'A'); // 传入4个不同类型的参数
//    return 0;
//}
//
//
//void Print()
//{
//    //...
//
//}
//
//void Print(char d)
//{
//    //...
//    Print();
//}
//
//void Print(string c, char d)
//{
//    //...
//    Print(d);
//}
//
//void Print(double b, string c, char d) 
//{ 
//    //...
//    Print(c, d);
//}
//
//void Print(int a, double b, string c, char d) 
//{ 
//    //...
//    Print(b, c, d);
//}

//// 可变参数模板函数：用参数包初始化vector
//template<class ...Args>
//vector<int> make_vector(Args... args)
//{
//    // 将参数包args...展开为独立参数，初始化vector
//    return { args... };
//}
//
//int main()
//{
//    auto vec = make_vector(1, 2, 3, 4, 5);
//    for (int num : vec)
//    {
//        cout << num << " ";
//    }
//
//    return 0;
//}

//struct MyString {
//    char* _data;
//    size_t _size;
//
//    // 构造函数（分配内存）
//    MyString(const char* str = "")
//        :_size(strlen(str)) {
//        _data = new char[_size + 1];
//        memcpy(_data, str, _size+1);
//        cout << "构造函数：分配" << _size + 1 << "字节\n";
//    }
//
//    // 移动构造函数（转移资源，不分配新内存）
//    MyString(MyString&& other) noexcept
//        :_data(other._data), _size(other._size) {
//        other._data = nullptr;
//        other._size = 0;
//        cout << "移动构造：资源转移\n";
//    }
//
//    // 禁止复制（突出移动的作用）
//    MyString(const MyString&) = delete;
//    MyString& operator=(const MyString&) = delete;
//
//    ~MyString() {
//        if (_data) {
//            cout << "析构函数：释放" << _size + 1 << "字节\n";
//            delete[] _data;
//        }
//    }
//};
//
//int main()
//{
//    vector<MyString> vec;
//    vec.reserve(2);
//    cout << "emplace_back" << endl;
//    vec.emplace_back("hello");
//    cout << "emplace_back" << endl;
//
//    cout << "push_back" << endl;
//    vec.push_back("world");
//    cout << "push_back" << endl;
//    return 0;
//}

//int main()
//{
//    // 直接定义并且调用
//    []{cout << "简单Lambda" << endl; }();
//
//    // 带参数和返回值
//    auto add = [](int a, int b)->int {
//        return a + b;
//        };
//    cout << add(1, 2) << endl;
//
//    // 按值捕获外部变量
//    int x = 10;
//    auto printX = [x] { cout << x << endl; };
//    printX();
//
//    return 0;
//}

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