#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

//// �����׳��쳣�ĺ���
//int divide(int a, int b) {
//    if (b == 0) {
//        // �׳���׼�쳣
//        throw std::runtime_error("��������Ϊ��");
//    }
//    return a / b;
//}
//
//int main() {
//    int x = 10, y = 0;
//
//    // try��:���������׳��쳣�Ĵ���
//    try {
//        int result = divide(x, y);
//        cout << "���: " << result << endl;
//    }
//    // catch��: ���񲢴����ض������쳣
//    catch (const std::runtime_error& e){
//        cout << "�����쳣: " << e.what() << endl;
//    }
//    // �����ж��catch�飬����ͬ���͵��쳣
//    catch (...) { // ��������δ��ǰ��catch������쳣��ͨ�����
//        std::cout << "����δ֪�쳣" << std::endl;
//    }
//
//    std::cout << "�������ִ��" << std::endl; // �쳣����󣬳����������
//
//    return 0;
//}

//class Myclass {
//public:
//    ~Myclass() { cout << "MyClass����" << endl; }
//};
//
//void func() {
//    Myclass obj;    // �ֲ�����
//    throw 1;        // �׳��쳣, obj�ᱻ����
//}
//
//int main() {
//    try {
//        func();
//    }
//    catch (int) {
//        cout << "����int�쳣" << endl;
//    }
//
//    return 0;
//}

//// �Զ����쳣��
//class FileError : public std::exception {
//private:
//    std::string msg;
//public:
//    FileError(const std::string& filename) : msg("�ļ�����" + filename) {}
//    const char* what() const noexcept override {
//        return msg.c_str();
//    }
//};
//
//// �׳��Զ����쳣
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