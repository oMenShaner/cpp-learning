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

// �����ࣺ��״
class Shape{
public:
    // ���麯��������������ӿڣ�
    virtual double getArea() const = 0;
    // ��������������Ҫ����
    virtual ~Shape() { cout << "~Shape()" << endl; }
};

// �����ࣺԲ��
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r)
        :radius(r)
    {}

    // ������д��������г��󷽷�
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
};

// �����ࣺ����
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h)
        :width(w)
        ,height(h)
    {}

    double getArea() const override {
        return width * height;
    }
};

int main()
{
    // Shape s; // ���󣡲��ܴ���������Ķ���

    Shape* s1 = new Circle(5.0);    // ��̬������ָ��ָ��������ָ��
    Shape* s2 = new Rectangle(3.0, 4.0);

    // ͨ��ͳһ�ӿڲ�����ͬ����
    Shape* shapes[] = { s1, s2 };
    for (Shape* s : shapes) {
        cout << "Area:" << s->getArea() << endl;
    }

    delete s1;
    delete s2;

    return 0;
}