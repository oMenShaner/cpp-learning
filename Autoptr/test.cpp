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
//    // ���������, �ṩָ������ӿ�
//    T& operator*() const { return *_ptr; }
//    T* operator->() const { return _ptr; }
//private:
//    T* _ptr;
//};
//
//void test_smart_ptr()
//{
//    cout << "\n----- ��������ָ�� -----\n";
//    SmartPtr<int> a = new int(0);
//
//    // ģ���쳣
//    throw std::runtime_error("ģ���쳣");
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
//    // ���� unique_ptr��ָ�� int ���͵Ķ�̬�ڴ棨ֵΪ 10��
//    unique_ptr<int> ptr1(new int(10));
//    cout << *ptr1 << endl;   // ���:10
//
//    // ����Ȩת�ƣ�ptr1 ����ӵ���ڴ棬��Ϊ�գ�
//    unique_ptr<int> ptr2(move(ptr1));
//    if (ptr1 == nullptr) {
//        cout << "ptr1Ϊ��" << endl;
//    }
//
//    unique_ptr<int[]> arr(new int[3] {1, 2, 3});    // ָ������
//    cout << arr[0] << arr[1] << arr[2] << endl;     // ���123
//    return 0;
//}

int main()
{
    // ���� shared_ptr, ���ü�����ʼΪ1
    shared_ptr<int> ptr1(new int(20));
    cout << "���ü���: " << ptr1.use_count() << endl;

    // ���� ptr1, ���ü�����Ϊ2
    shared_ptr<int> ptr2 = ptr1;
    cout << "���ü���: " << ptr1.use_count() << endl;

    // ����ptr1(����ָ�����),���ü�����Ϊ1
    ptr1.reset();
    cout << "���ü���: " << ptr2.use_count() << endl;

    return 0;
}