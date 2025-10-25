#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

//// 可能抛出异常的函数
//int divide(int a, int b) {
//    if (b == 0) {
//        // 抛出标准异常
//        throw std::runtime_error("除数不能为零");
//    }
//    return a / b;
//}
//
//int main() {
//    int x = 10, y = 0;
//
//    // try块:包裹可能抛出异常的代码
//    try {
//        int result = divide(x, y);
//        cout << "结果: " << result << endl;
//    }
//    // catch块: 捕获并处理特定类型异常
//    catch (const std::runtime_error& e){
//        cout << "捕获到异常: " << e.what() << endl;
//    }
//    // 可以有多个catch块，捕获不同类型的异常
//    catch (...) { // 捕获所有未被前面catch处理的异常（通配符）
//        std::cout << "捕获到未知异常" << std::endl;
//    }
//
//    std::cout << "程序继续执行" << std::endl; // 异常处理后，程序继续运行
//
//    return 0;
//}

//class Myclass {
//public:
//    ~Myclass() { cout << "MyClass析构" << endl; }
//};
//
//void func() {
//    Myclass obj;    // 局部对象
//    throw 1;        // 抛出异常, obj会被析构
//}
//
//int main() {
//    try {
//        func();
//    }
//    catch (int) {
//        cout << "捕获到int异常" << endl;
//    }
//
//    return 0;
//}

//// 自定义异常类
//class FileError : public std::exception {
//private:
//    std::string msg;
//public:
//    FileError(const std::string& filename) : msg("文件错误" + filename) {}
//    const char* what() const noexcept override {
//        return msg.c_str();
//    }
//};
//
//// 抛出自定义异常
//void openFile(const std::string& filename) {
//    throw FileError(filename);
//}
//
//int main() {
//    try {
//        openFile("text.txt");
//    }
//    catch (const FileError& e) {
//        cout << e.what() << endl;
//    }
//    return 0;
//}

class A { public: A() {} A(int) = delete; };