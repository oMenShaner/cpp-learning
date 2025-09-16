#include <iostream>

using namespace std;

class Person {
public:
    // ���virtual�ؼ���
    virtual void BuyTicket()
    {
        cout << "ȫ����Ʊ" << endl;
    }
};
class Student : public Person {
public:
    // �����ౣ�ַ���ֵ���ͣ��������������б���ȫ��ͬ���ſ��Դﵽ��д
    virtual void BuyTicket()
    {
        cout << "�����Ʊ" << endl;
    }
};
class Soldier : public Person {
public:
    virtual void BuyTicket()
    {
        cout << "������Ʊ" << endl;
    }
};

// �����麯������ͨ��ָ�������
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