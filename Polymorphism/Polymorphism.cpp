#include <iostream>
#include <cmath>

using namespace std;

//class Person {
//public:
//    // ���virtual�ؼ���
//    virtual void BuyTicket()
//    {
//        cout << "ȫ����Ʊ" << endl;
//    }
//};
//class Student : public Person {
//public:
//    // �����ౣ�ַ���ֵ���ͣ��������������б���ȫ��ͬ���ſ��Դﵽ��д
//    virtual void BuyTicket()
//    {
//        cout << "�����Ʊ" << endl;
//    }
//};
//class Soldier : public Person {
//public:
//    virtual void BuyTicket()
//    {
//        cout << "������Ʊ" << endl;
//    }
//};
//
//// �����麯������ͨ��ָ�������
//void Pay(Person* ptr)
//{
//    ptr->BuyTicket();
//}
//
//int main()
//{
//    Person p;
//    Student st;
//    Soldier so;
//
//    Pay(&p);
//    Pay(&st);
//    Pay(&so);
//
//    return 0;
//}

//class A
//{
//public:
//    virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//    virtual void test() { func(); }
//};
//
//class B : public A
//{
//public:
//    void func(int val = 0) { std::cout << "B->" << val << std::endl; }
//};
//
//int main(int argc, char* argv[])
//{
//    B* p = new B; 
//    p->func();
//    return 0;
//}
//

//class Base {
//public:
//    Base() { cout << "Base()" << endl; }
//    virtual ~Base() { cout << "~Base()" << endl; }
//};
//
//class Derived : public Base {
//public:
//    Derived() { cout << "Derived()" << endl; }
//    ~Derived() { cout << "~Derived()" << endl; }
//};
//
//int main()
//{
//    Base* p = new Derived();    // �û���ָ��ָ��һ�����������
//    delete p;                   // �ؼ������ͨ������ָ��ɾ������
//}

//// �����ࣺ��״
//class Shape{
//public:
//    // ���麯��������������ӿڣ�
//    virtual double getArea() const = 0;
//    // ��������������Ҫ����
//    virtual ~Shape() { cout << "~Shape()" << endl; }
//};
//
//// �����ࣺԲ��
//class Circle : public Shape {
//private:
//    double radius;
//public:
//    Circle(double r)
//        :radius(r)
//    {}
//
//    // ������д��������г��󷽷�
//    double getArea() const override {
//        return 3.14159 * radius * radius;
//    }
//};
//
//// �����ࣺ����
//class Rectangle : public Shape {
//private:
//    double width, height;
//public:
//    Rectangle(double w, double h)
//        :width(w)
//        ,height(h)
//    {}
//
//    double getArea() const override {
//        return width * height;
//    }
//};
//
//int main()
//{
//    // Shape s; // ���󣡲��ܴ���������Ķ���
//
//    Shape* s1 = new Circle(5.0);    // ��̬������ָ��ָ��������ָ��
//    Shape* s2 = new Rectangle(3.0, 4.0);
//
//    // ͨ��ͳһ�ӿڲ�����ͬ����
//    Shape* shapes[] = { s1, s2 };
//    for (Shape* s : shapes) {
//        cout << "Area:" << s->getArea() << endl;
//    }
//
//    delete s1;
//    delete s2;
//
//    return 0;
//}

//class Base {
//public:
//    virtual void func1()
//    {
//        cout << "func1" << endl;
//    }
//    virtual void func2()
//    {
//        cout << "func2" << endl;
//    }
//    void func3()
//    {
//        cout << "func3" << endl;
//    }
//private:
//    int _b;
//};
//
//int main()
//{
//    Base b;
//    cout << sizeof(b) << endl;
//    return 0;
//}

//class Base {
//public:
//    virtual void func1() { cout << "Base::func1" << endl; }
//    virtual void func2() { cout << "Base::func2" << endl; }
//    virtual ~Base() { cout << "~Base()" << endl; }
//};
//
//class Derived : public Base {
//public:
//    void func1() { cout << "Derived::func1" << endl; }  // ��дfunc1
//    virtual void func3() { cout << "Derived::func2" << endl; } // �������½�һ���麯��func3
//    ~Derived() { cout << "~Derived()" << endl; }
//};
//
//void Func(Base *ptr)
//{
//    ptr->func1();
//}
//
//int main()
//{
//    Base b;
//    Derived d;
//
//    Func(&b);
//    Func(&d);
//}

//class Base {
//public:
//    virtual void func1() { cout << "Base::func1" << endl; }
//    void func3() { cout << "Base::func3" << endl; }     // �����Ա����func3
//    virtual ~Base() { cout << "~Base()" << endl; }
//};
//
//class Derived : public Base {
//public:
//    void func1() { cout << "Derived::func1" << endl; }  // ��дfunc1���̳л���func3
//    ~Derived() { cout << "~Derived()" << endl; }        
//};
//
//int main()
//{
//    Derived d;
//
//    Base* ptr = &d; // ptrָ�����������
//    ptr->func1();
//    ptr->func3();
//
//    return 0;
//}


class Base {
public:
    virtual void func1() { cout << "Base::func1" << endl; }
    virtual void func2() { cout << "Base::func2" << endl; }
    void func5() { cout << "Base::func5" << endl; }
protected:
    int a = 1;
};
class Derive : public Base
{
public:
    // ��д�����func1
    virtual void func1() { cout << "Derive::func1" << endl; }
    virtual void func3() { cout << "Derive::func1" << endl; }
    void func4() { cout << "Derive::func4" << endl; }
protected:
    int b = 2;
};

int main()
{
    int i = 0;
    static int j = 1;
    int* p1 = new int;
    const char* p2 = "xxxxxxxx";
    printf("ջ: % p\n", &i);
    printf("��̬��: % p\n", &j);
    printf("��: % p\n", p1);
    printf("������: % p\n", p2);
    Base b;
    Derive d;
    Base * p3 = &b;
    Derive * p4 = &d;
    printf("Person ����ַ: % p\n", *(int*)p3);
    printf("Student ����ַ: % p\n", *(int*)p4);
    printf("�麯����ַ: % p\n", &Base::func1);
    printf("��ͨ������ַ: % p\n", &Base::func5);

    return 0;
}
