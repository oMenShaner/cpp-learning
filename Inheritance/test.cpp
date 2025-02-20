#include <iostream>
#include <string>

using namespace std;

// 基类 Person
class Person 
{
public:
	void Print()
	{
		cout << _name << endl;
		cout << _age << endl;
	}
protected:
	string _name = "张三";
	int _age = 20;
};

// 派生类 Student
class Student : public Person
{
protected:
	int _id = 0000;
	string _name = "李四";
};

int main()
{	
	Person p;
	Student s;
	
	s.Print();
	// 派生类对象可以切片/赋值转换给基类对象、指针及引用，中间不会默认生成常量
	Person p1 = s;
	Person* p2 = &s;
	Person& p3 = s;

	// 基类对象不可以赋值给派生类对象
	// Student s1 = p;		// ERROR

	return 0;
}r