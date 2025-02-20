#include <iostream>
#include <string>

using namespace std;

//// 基类 Person
//class Person 
//{
//public:
//    friend void Display(Person& p, Student& s);
//protected:
//    string _name = "张三";
//    int _age = 20;
//};
//
//// 派生类 Student
//class Student : public Person
//{
//public:
//    void Print()
//    {
//        cout << _name << endl;
//        cout << _age << endl;
//        cout << _id << endl;
//    }
//protected:
//    int _id = 0000;
//    string _name = "李四";
//};
//
//void Display(Person& p, Student& s)
//{
//    cout << p._name << endl;
//    cout << s._id << endl;
//}
//
//int main()
//{
//    Person p;
//    Student s;
//    Display(p, s);
//}
//int main()
//{
//    Student s;
//    s.Print();
//
//    return 0;
//}

//class A {
//public:
//    void func() 
//    {
//        cout << "func" << endl;
//    }
//};
//
//class B :public A{
//public:
//    void func(int i)
//    {
//        A::func();
//        cout << "func(int i)" << endl;
//    }
//};

//int main()
//{
//    B b;
//    // b.func();
//    b.func(10);
//
//    return 0;
//}
//int main()
//{    
//    Person p;
//    Student s;
//    
//    s.Print();
//    // 派生类对象可以切片/赋值转换给基类对象、指针及引用，中间不会默认生成常量
//    Person p1 = s;
//    Person* p2 = &s;
//    Person& p3 = s;
//
//    // 基类对象不可以赋值给派生类对象
//    // Student s1 = p;        // ERROR
//
//    return 0;
//}

//class A {
//public:
//    A(){ _cnt++;}
//public:
//    static int _cnt;
//};
//
//int A::_cnt = 0;
//
//class B : public A {
//protected:
//    int _num;
//};
//
//int main()
//{
//    A a1, a2, a3;
//    B b1;
//
//    cout << "静态成员该继承体系下只有一份:" << endl;
//    cout << a1._cnt << endl;
//    cout << a2._cnt << endl;
//    cout << b1._cnt << endl;
//
//    cout << "一旦被修改，其他对象进行访问的数据也是被修改后的同一数据:" << endl;
//    a3._cnt = 0;
//    cout << a1._cnt << endl;
//    cout << b1._cnt << endl;
//
//    cout << "根据地址可以再次验证，该继承体系下实际就只有一份静态成员：" << endl;
//    cout << &a1._cnt << endl;
//    cout << &a2._cnt << endl;
//    cout << &b1._cnt << endl;
//}

//class Person {
//public:
//    Person(string name = "张三", int age = 20)
//        :_name(name)
//        ,_age(age)
//    {
//        cout << "Person()" << endl;
//    }
//    Person(const Person& p)
//        :_name(p._name)
//        ,_age(p._age)
//    {
//        cout << "Person(const Person& p)" << endl;
//    }
//    Person& operator=(const Person& p)
//    {
//        cout << "Person& operator=(const Person& p)" << endl;
//        if (this != &p)
//        {
//            _name = p._name;
//            _age = p._age;
//        }
//        return *this;
//    }
//    ~Person()
//    {
//        cout << "~Person()" << endl;
//    }
//protected:
//    string _name;
//    int _age;
//};
//
//class Student : public Person {
//public:
//    Student(int sid = 1001) // 构造函数1
//        :_sid(sid)
//    {
//        cout << "Student(sid)" << endl;
//    }
//    Student(string name, int age, int sid)  // 构造函数2
//        :Person(name, age)
//        , _sid(sid)
//    {
//        cout << "Student(name,age,sid)" << endl;
//    }
//    //Student(string name, int age, int sid)  // 构造函数3
//    //    :_name(name)
//    //    ,_age(age)
//    //    , _sid(sid)
//    //{
//    //    cout << "Student(name,age,sid)" << endl;
//    //}
//    Student(const Student& s)
//        :Person(s)      // 派生类必须调用基类的拷贝构造
//        , _sid(s._sid)
//    {
//        cout << "Student(const Student& s)" << endl;
//    }
//    Student& operator=(const Student& s)
//    {
//        cout << "Student& operator=(const Student& s)" << endl;
//        if (this != &s) 
//        {
//            Person::operator=(s);   // 显式调用基类赋值重载
//            _sid = s._sid;
//        }
//        return *this;
//    }
//    ~Student()
//    {
//        // Person::~Person();
//        cout << "~Student()" << endl;
//    }
//protected:
//    int _sid;
//};
//
//int main()
//{   
//    Student s1;
//}

//class Person {
//public:
//    string _name;   // 姓名
//};
//
//// 虚拟继承
//class Student : virtual public Person {
//protected:
//    int _num;   // 学号
//};
//
//// 虚拟继承
//class Teacher : virtual public Person {
//protected:
//    int _id;    // 职工编号
//};
//
//class Assistant : public Student, public Teacher {
//public:
//    string _majorCourse;    // 主修课程
//};
//
//int main()
//{
//    Assistant a;
//    a._name = "Peter"; 
//
//    a.Student::_name = "xxx";
//    a.Teacher::_name = "yyy";
//}

class A{
public:
    int _a;
};

class B :virtual public A {
public:
    int _b;
};

class C :virtual public A {
public:
    int _c;
};

class D :public B, public C {
public :
    int _d;
};

int main()
{
    D d;
    d.B::_a = 1;
    d.C::_a = 2;
    d._b = 3;
    d._c = 4;
    d._d = 5;
    return 0;
}