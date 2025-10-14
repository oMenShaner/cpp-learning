#include <iostream>
#include <string>
using namespace std;

int main()
{
    // 左值:可以取地址
    // 以下的p、b、c、*p、s、s[0]就是常⻅的左值
    int* p = new int(0);
    int b = 1;
    const int c = b;
    *p = 10;
    string s("111111");
    s[0] = 'x';

    // 右值:不能取地址
    double x = 1.1, y = 2.2;
    // 以下的10、x + y、fmin(x, y)、string("11111")都是常⻅的右值
    10;
    x + y;
    fmin(x, y);
    string("11111");

    // error:表达式必须是左值或函数指示符
    // cout << &10 << endl;
    // cout << &(x+y) << endl;
    // cout << &(fmin(x, y)) << endl;
    // cout << &string("11111") << endl;

    // 左值引⽤给左值取别名
    int& r1 = b;
    int*& r2 = p;
    int& r3 = *p;
    string& r4 = s;
    char& r5 = s[0];

    // 右值引⽤给右值取别名
    int&& rr1 = 10;
    double&& rr2 = x + y;
    double&& rr3 = fmin(x, y);
    string&& rr4 = string("11111");

    // 左值引用不能直接引用右值, 但是const左值引用可以引用右值
    const int& rx1 = 10;
    const double& rx2 = x + y;
    const double& rx3 = fmin(x, y);
    const string& rx4 = string("11111");

    // 右值引用不能直接引用左值,但是右值引用可以引用move(左值)
    int&& rrx1 = move(b);
    int*&& rrx2 = move(p);
    int&& rrx3 = move(*p);
    string&& rrx4 = move(s);
    string&& rrx5 = (string&&)s;

    // b、r1、rr1都是变量表达式,都是左值,都可以取地址
    cout << &b << endl;
    cout << &r1 << endl;
    cout << &rr1 << endl;

    int& r6 = r1;
    // int&& rrx6 = rr1; error
    int&& rrx6 = move(rr1);
}