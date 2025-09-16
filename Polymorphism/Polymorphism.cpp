#include <iostream>

using namespace std;

class Person {
public:
    // 添加virtual关键字
    virtual void BuyTicket()
    {
        cout << "全价买票" << endl;
    }
};
class Student : public Person {
public:
    // 派生类保持返回值类型，函数名及参数列表完全相同，才可以达到重写
    virtual void BuyTicket()
    {
        cout << "半价买票" << endl;
    }
};
class Soldier : public Person {
public:
    virtual void BuyTicket()
    {
        cout << "优先买票" << endl;
    }
};

// 调用虚函数必须通过指针或引用
void Pay(Person* ptr)
{
    ptr->BuyTicket();
}

int main()
{
    Person p;
    Student st;
    Soldier so;

    Pay(&p);
    Pay(&st);
    Pay(&so);

    return 0;
}