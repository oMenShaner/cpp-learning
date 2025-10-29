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

//int main()
//{
//    // ���� shared_ptr, ���ü�����ʼΪ1
//    shared_ptr<int> ptr1(new int(20));
//    cout << "���ü���: " << ptr1.use_count() << endl;
//
//    // ���� ptr1, ���ü�����Ϊ2
//    shared_ptr<int> ptr2 = ptr1;
//    cout << "���ü���: " << ptr1.use_count() << endl;
//
//    // ����ptr1(����ָ�����),���ü�����Ϊ1
//    ptr1.reset();
//    cout << "���ü���: " << ptr2.use_count() << endl;
//
//    return 0;
//}

//template<class T>
//class MyUniquePtr {
//private:
//    T* _ptr;    // �����ԭʼָ��
//public:
//    // ���캯�����ӹ�ԭʼָ�������Ȩ
//    MyUniquePtr(T* ptr = nullptr) : _ptr(ptr) {}
//
//    // ��ֹ��������(��ռ����Ȩ,���ܸ���)
//    MyUniquePtr<T>(const MyUniquePtr<T>&) = delete;
//
//    // ��ֹ���Ƹ�ֵ
//    MyUniquePtr<T>& operator=(const MyUniquePtr<T>&) = delete;
//
//    // �����ƶ�����(ת������Ȩ),ǳ��������
//    MyUniquePtr(MyUniquePtr<T>&& other) noexcept
//        :_ptr(other._ptr)
//    {
//        other._ptr = nullptr;
//    }
//
//    // �����ƶ���ֵ
//    MyUniquePtr<T>& operator=(MyUniquePtr<T>&& other) noexcept
//    {
//        if (this != &other)
//        {
//            delete _ptr;        // �ͷŵ�ǰ��Դ
//            _ptr = other._ptr;  // �ӹܶԷ���Դ
//            other._ptr = nullptr;// �Է���������Ȩ
//        }
//        return *this;
//    }
//
//    // ��������:�ͷ���Դ
//    ~MyUniquePtr()
//    {
//        delete _ptr;
//    }
//
//    // ���������
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
//    // ����Ƿ������Դ
//    bool is_null() const
//    {
//        return _ptr == nullptr;
//    }
//};
//
//int main()
//{
//    MyUniquePtr<int> ptr1(new int(10));
//    cout << *ptr1 << endl;  // ���10
//
//    //MyUniquePtr<int> ptr2(ptr1);    // ����:��ֹ��������
//    //MyUniquePtr<int> ptr2 = ptr1;   // ����:��ֹ��ֵ
//
//    MyUniquePtr<int> ptr2 = move(ptr1); // �ƶ���ֵ,ת����Դ
//    cout << ptr1.is_null() << endl;     // ���1,ptr1�ѿ�
//    cout << *ptr2 << endl;              // ���10
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
//    // ��make_shared����shared_ptr
//    auto ptr1 = make_shared<Person>("Tom", 20);
//    // ����new�������
//    shared_ptr<Person> ptr2(new Person("Jerry", 20));
//}

//// ���ü��������ࣨ����������������㹲��
//template<class T>
//struct RefCount {
//    T* _ptr;        // ָ��������Դ
//    size_t _count;  // ǿ���ü���
//
//    RefCount(T* p): _ptr(p), _count(1) {}
//    ~RefCount() { delete _ptr; }
//};
//
//// �򻯰�shared_ptr
//template <class T>
//class MySharedPtr {
//private:
//    RefCount<T>* _ref;   // ָ�����ü�������
//
//public:
//    // ���캯��:�������ü�������
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
//    // ��������:������Դ,����+1(ǳ����)
//    MySharedPtr(const MySharedPtr<T>& other)
//    {
//        _ref = other._ref;
//        if (_ref)
//        {
//            _ref->_count++;  // ��������
//        }
//    }
//
//    // ����-1����Ϊ0���ͷ���Դ
//    void release()
//    {
//        if (_ref && --_ref->_count == 0)
//        {
//            delete _ref;
//            _ref = nullptr;
//        }
//    }
//
//    // ���Ƹ�ֵ:�ȼ���ǰ����(��Ϊ0���ͷ�0),�ٹ�������Դ
//    MySharedPtr& operator=(MySharedPtr<T>& other)
//    {
//        if (this != &other)
//        {
//            release();
//            // ��������Դ
//            _ref = other._ref;
//            if (_ref)
//            {
//                _ref->_count++;
//            }
//        }
//        return *this;
//    }
//
//    // ��������
//    ~MySharedPtr()
//    {
//        release();
//    }
//
//    // ����*��->
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
//    // ��ȡ��ǰ���ü���
//    size_t use_count() const
//    {
//        return _ref ? _ref->_count : 0;
//    }
//};
//
//int main()
//{
//    MySharedPtr<int> ptr1(new int(10));
//    cout << "����1: " << ptr1.use_count() << endl;
//
//    MySharedPtr<int> ptr2 = ptr1;   // ���ƹ���,����+1
//    cout << "����2: " << ptr1.use_count() << endl;
//
//    {
//        MySharedPtr<int> ptr3(ptr2);    // ��������,����+1
//        std::cout << "����3��" << ptr3.use_count() << std::endl; // �����3
//    }// ptr3 ����������-1 �� 2
//
//    std::cout << "����4��" << ptr1.use_count() << std::endl; // �����2
//
//    return 0;
//}

//struct B;  
//struct A {
//    shared_ptr<B> b_ptr;    // A ���� B �� shared_ptr
//    ~A() { cout << "A ������\n"; }
//};
//struct B {
//    weak_ptr<A> a_ptr;    // B ���� A �� weak_ptr(�����Ӽ���)
//    ~B() { cout << "B ������\n"; } 
//};
//
//int main()
//{
//    {
//        shared_ptr<A> a(new A());   // a�ļ���=1
//        shared_ptr<B> b(new B());   // b�ļ���=1
//
//        a->b_ptr = b; // b �ļ�����Ϊ 2
//        b->a_ptr = a; // a �ļ�����Ϊ 1(weak_ptr�����Ӽ���)
//        cout << a.use_count() << endl;
//        cout << b.use_count() << endl;
//    }   // �뿪������
//
//    // ��ʱ��
//    // a ���� �� ������ 1 ��Ϊ 0 �� A ������ �� a->b_ptr ���� �� b ������ 2 ��Ϊ 1
//    // b ���� �� ������ 1 ��Ϊ 0 �� B ������
//
//    cout << "�������" << endl;
//    return 0;
//}

//int main()
//{
//    shared_ptr<int> sp1(new int(10));
//    weak_ptr<int> wp1(sp1);      // �� shared_ptr ����
//    weak_ptr<int> wp2 = wp1;    // �� weak_ptr ��ֵ
//
//    std::shared_ptr<int> sp2 = wp1.lock();
//    if (sp2) { // �����Դ�Ƿ���Ч
//        std::cout << *sp2 << std::endl;
//        cout << sp2.use_count() << endl;
//    }
//    else {
//        std::cout << "��Դ���ͷ�\n";
//    }
//    return 0;
//}

//int main()
//{
//    // �Զ���ɾ����:��delete[]�ͷ�����
//    auto arr_deleter = [](int* p) {
//        cout << "�ͷ�����" << endl;
//        delete[] p;
//    };
//
//    // unique_ptr ��ɾ������ģ�������ָ��ɾ�������ͣ�
//    unique_ptr<int, decltype(arr_deleter)> arr_ptr(new int[3] {1, 2, 3}, arr_deleter);
//
//    return 0; // �뿪������ʱ���Զ����� arr_deleter �ͷ�����
//}

//// �Զ���ɾ����:�ر��ļ� ͨ���º���ʵ��
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
//    // ���ļ�
//    FILE* fp = fopen("test.txt", "w+");
//    if (!fp)
//    {
//        return 1;
//    }
//
//    // shared_ptr �����ļ��������ɾ����
//    shared_ptr<FILE> file_ptr(fp, Fclose());
//
//    return 0; // �Զ����� file_deleter �ر��ļ�
//}


//// ���ü������ƿ飨����ɾ������
//template<class T, class Deleter>
//struct SharedControlBlock {
//    T* _ptr;
//    size_t _count;
//    Deleter _deleter;    // �洢ɾ����
//
//    SharedControlBlock(T* ptr, Deleter d)
//        :_ptr(ptr), _count(1), deleter(move(d)) { }
//
//    ~SharedControlBlock()
//    {
//        _deleter(_ptr); // ����ɾ�����ͷ���Դ
//    }
//};

template<class T>
class SmartPtr {
private:
    T* _ptr;
    std::function<void(T*)> _del = [](T* p) {delete p; };    // Ĭ��Ϊ��ͨdelete
public:
    // Ĭ�Ϲ��캯��
    SmartPtr(T* ptr = nullptr)
        :_ptr(ptr)
    { }

    // ��ɾ�����Ĺ��캯��
    template<class Deleter>
    SmartPtr(T* ptr, Deleter del)
        : _ptr(ptr), _del(move(del))
    { }

    // ...

    // ��������
    ~SmartPtr()
    {
        _del(_ptr); // ����ɾ���������ͷ���Դ
        cout << "�ͷ���Դ" << endl;
        _ptr = nullptr;
    }
};

int main()
{
    SmartPtr<int> ptri(new int(10));
    auto arr_deleter = [](int* arr) {
        delete[] arr;
        cout << "�ͷ�����" << endl;
    };
    SmartPtr<int> ptrarr(new int[3] {1, 2, 3}, arr_deleter);

    return 0;
}