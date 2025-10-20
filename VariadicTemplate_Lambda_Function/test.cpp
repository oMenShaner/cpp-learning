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
//    Print();                        // ������0������
//    Print(1);                       // ������1������
//    Print(1, string("xxxxx"));      // ������2������
//    Print(1.1, string("xxxxx"), x); // ������3������
//
//    return 0;
//}


//// 1. �ݹ���ֹ������������Ϊ��ʱ���ã� 
//void Print()
//{
//    cout << "������ӡ���!" << endl;
//}
//
//// 2. �ɱ��������ģ�壨�ݹ�չ����
//// ÿ�δ����һ������t��ʣ�������Args... args�����ݹ�
//template<class T, class ...Args >
//void Print(T t, Args... args)
//{
//    cout << "����: " << t << "(ʣ��" << sizeof...(args) << "������)" << endl;
//    Print(args...); // չ��ʣ��������������ݹ�
//}
//
//int main() {
//    Print(10, 3.14, string("hello"), 'A'); // ����4����ͬ���͵Ĳ���
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

//// �ɱ����ģ�庯�����ò�������ʼ��vector
//template<class ...Args>
//vector<int> make_vector(Args... args)
//{
//    // ��������args...չ��Ϊ������������ʼ��vector
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
//    // ���캯���������ڴ棩
//    MyString(const char* str = "")
//        :_size(strlen(str)) {
//        _data = new char[_size + 1];
//        memcpy(_data, str, _size+1);
//        cout << "���캯��������" << _size + 1 << "�ֽ�\n";
//    }
//
//    // �ƶ����캯����ת����Դ�����������ڴ棩
//    MyString(MyString&& other) noexcept
//        :_data(other._data), _size(other._size) {
//        other._data = nullptr;
//        other._size = 0;
//        cout << "�ƶ����죺��Դת��\n";
//    }
//
//    // ��ֹ���ƣ�ͻ���ƶ������ã�
//    MyString(const MyString&) = delete;
//    MyString& operator=(const MyString&) = delete;
//
//    ~MyString() {
//        if (_data) {
//            cout << "�����������ͷ�" << _size + 1 << "�ֽ�\n";
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
//    // ֱ�Ӷ��岢�ҵ���
//    []{cout << "��Lambda" << endl; }();
//
//    // �������ͷ���ֵ
//    auto add = [](int a, int b)->int {
//        return a + b;
//        };
//    cout << add(1, 2) << endl;
//
//    // ��ֵ�����ⲿ����
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
    // f1:�ղ����޷�����x
    int x = 10;
    auto f1 = [] {
        // cout << x; // ����δ����x
        cout << "���ⲿ����\n";
    };
    f1();

    // f2,f3:��ֵ�����Ĭ�ϰ�ֵ[=]
    int a = 10, b = 20;
    // ����a��b�ĸ�������ʽָ����
    auto f2 = [a, b]() {
        cout << a + b << endl;
        };
    // Ĭ�ϰ�ֵ���������ⲿ�������ȼ��ڲ���a��b��
    auto f3 = [=]() {
        cout << a * b << endl;
        };
    f2();
    f3();

    // f4:���mutable�޸ĸ���
    auto f4 = [x]() mutable {
        x = 5; // �����޸ĸ��������ڲ���Ч��
        std::cout << "�ڲ�x=" << x; // ���5
        };
    f4();
    std::cout << "�ⲿx=" << x << endl; // ���10��ԭ�������䣩

    // f5,f6:�����ò��� [&������] ��Ĭ�ϰ����� [&]
    int c = 30, d = 40;
    // ��ʽ�����ò���c��d
    auto f5 = [&c, &d]() {
        c = 35;
        d = 50; // ֱ���޸�
        };
    // Ĭ�ϰ����ò��������ⲿ����
    auto f6 = [&] {
        cout << c + d << endl;
        };

    f5();
    f6();

    // f7,f8:��ϲ���
    x = 1;
    int y = 2, z = 3;
    // Ĭ�ϰ�ֵ�������У���y�����ò���
    auto f7 = [=, &y] {
        // x = 10; // ����x��ֵ���񣬲����޸�
        y = 20;   // ��ȷ��y�����ò��񣬿��޸�
        cout << x + y + z << endl; // 1+20+3=24
        };
    // Ĭ�ϰ����ò������У���z��ֵ����
    auto f8 = [&, z] {
        x = 10;   // ��ȷ��x�����ò���
        // z = 30; // ����z��ֵ���񣬲����޸�
        };
    f7();
    f8();

    // f9:����thisָ�� [this]������ʹ�ã�
    class MyClass {
    private:
        int num = 100;
    public:
        void test() {
            // ��ʽ����this
            auto f8 = [this] {
                num = 200; // ���ʲ��޸ĳ�Ա����
                cout << num << endl;
                };
            f8(); // ���200
        }
    };
    MyClass obj;
    obj.test();

    return 0;
}