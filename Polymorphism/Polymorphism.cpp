#include <iostream>
#include <cmath>

using namespace std;

//class Person {
//public:
//    // 添加virtual关键字
//    virtual void BuyTicket()
//    {
//        cout << "全价买票" << endl;
//    }
//};
//class Student : public Person {
//public:
//    // 派生类保持返回值类型，函数名及参数列表完全相同，才可以达到重写
//    virtual void BuyTicket()
//    {
//        cout << "半价买票" << endl;
//    }
//};
//class Soldier : public Person {
//public:
//    virtual void BuyTicket()
//    {
//        cout << "优先买票" << endl;
//    }
//};
//
//// 调用虚函数必须通过指针或引用
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
//    Base* p = new Derived();    // 用基类指针指向一个派生类对象
//    delete p;                   // 关键在这里！通过基类指针删除对象
//}

//// 抽象类：形状
//class Shape{
//public:
//    // 纯虚函数：计算面积（接口）
//    virtual double getArea() const = 0;
//    // 虚析构函数（重要！）
//    virtual ~Shape() { cout << "~Shape()" << endl; }
//};
//
//// 派生类：圆形
//class Circle : public Shape {
//private:
//    double radius;
//public:
//    Circle(double r)
//        :radius(r)
//    {}
//
//    // 必须重写基类的所有抽象方法
//    double getArea() const override {
//        return 3.14159 * radius * radius;
//    }
//};
//
//// 派生类：矩形
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
//    // Shape s; // 错误！不能创建抽象类的对象
//
//    Shape* s1 = new Circle(5.0);    // 多态：基类指针指向派生类指针
//    Shape* s2 = new Rectangle(3.0, 4.0);
//
//    // 通过统一接口操作不同对象
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
//    void func1() { cout << "Derived::func1" << endl; }  // 重写func1
//    virtual void func3() { cout << "Derived::func2" << endl; } // 派生类新建一个虚函数func3
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
//    void func3() { cout << "Base::func3" << endl; }     // 基类成员函数func3
//    virtual ~Base() { cout << "~Base()" << endl; }
//};
//
//class Derived : public Base {
//public:
//    void func1() { cout << "Derived::func1" << endl; }  // 重写func1，继承基类func3
//    ~Derived() { cout << "~Derived()" << endl; }        
//};
//
//int main()
//{
//    Derived d;
//
//    Base* ptr = &d; // ptr指向派生类对象
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
    // 重写基类的func1
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
    printf("栈: % p\n", &i);
    printf("静态区: % p\n", &j);
    printf("堆: % p\n", p1);
    printf("常量区: % p\n", p2);
    Base b;
    Derive d;
    Base * p3 = &b;
    Derive * p4 = &d;
    printf("Person 虚表地址: % p\n", *(int*)p3);
    printf("Student 虚表地址: % p\n", *(int*)p4);
    printf("虚函数地址: % p\n", &Base::func1);
    printf("普通函数地址: % p\n", &Base::func5);

    return 0;
}
