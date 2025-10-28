#include <iostream>
#include <exception>
#include <memory>
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

int main()
{
    // 创建 shared_ptr, 引用计数初始为1
    shared_ptr<int> ptr1(new int(20));
    cout << "引用计数: " << ptr1.use_count() << endl;

    // 复制 ptr1, 引用计数变为2
    shared_ptr<int> ptr2 = ptr1;
    cout << "引用计数: " << ptr1.use_count() << endl;

    // 重置ptr1(不再指向对象),引用计数变为1
    ptr1.reset();
    cout << "引用计数: " << ptr2.use_count() << endl;

    return 0;
}