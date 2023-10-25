#include<iostream>
#include<typeinfo>

using namespace std;

int TestAuto()
{
    return 10;
}

int main()
{
    int a = 10;
    auto b = a;
    auto c = 'a';
    auto d = &c;
    auto e = TestAuto();
    auto& f = a;
    f++;

    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(e).name() << endl;
    cout << typeid(f).name() << endl;

    return 0;
}
