#include<iostream>
#include<string>

using namespace std;

// int main()
// {
//   try
//   {
//     string s1;
//     s1.reserve(s1.max_size());
//   }
//   catch(const std::exception& e)
//   {
//     std::cerr << e.what() << '\n';
//   }
//   
//   return 0;
// }

// int main()
// {
//   string s1("Hello,world");
//   cout << "size: " << s1.size() << endl;
//   cout << "begin: " << s1.capacity() << endl;
// 
//   s1.reserve(13);
//   cout << "s1.reserve(13): " << s1.capacity() << endl;
// 
//   s1.reserve(1);
//   cout << "s1.reserve(1): " << s1.capacity() << endl;
// 
//   return 0;
// }

// int main()
// {
//   string s1 = "1234567890";
//   cout << "begin\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl << endl;
// 
//   // n > capacity
//   // s1.resize(40);
//   // cout << "after s1.resize(40)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;
// 
//   // n <= capacity && n >= size
//   // s1.resize(13);
//   // cout << "after s1.resize(13)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;
// 
//   // n < size
//   s1.resize(5);
//   cout << "after s1.resize(5)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;
// 
// }

// int main()
// {
//   string s = "abcde";
//   s.append("fg"); // 尾插c格式串
//   cout << s << endl;
// 
//   string s1 = "hijklm";
//   s.append(s1); // 尾插string类对象
//   cout << s << endl;
// 
//   return 0;
// }

// int main()
// {
//   string s = "abcdef";
//   s.append(1, 'g');
//   cout << s << endl;
//   
//   return 0;
// }

// int main()
// {
//   string s = "12345";
//   s += '6';             // 尾插字符
//   s += "789";           // 尾插字符串
//   s += string("0000");  // 尾插string类对象
// 
//   cout << s << endl;
//   return 0;
// }

// int main()
// {
//   string file = "hello.c";
//   size_t pos = file.find('.', 0); // 找到 . 的位置
// 
//   if (pos != string::npos){
//     cout << file.substr(pos) << endl; // 截取 . 位置之后的字符串
//   }
// 
//   return 0;
// }

int main()
{
  string str("https://legacy.cplusplus.com/reference/string/string/substr/");

  size_t pos1 = str.find(':');
  cout << str.substr(0, pos1 - 0) << endl;

  size_t pos2 = str.find('/', pos1 + 3);
  cout << str.substr(pos1 + 3, pos2 - pos1 - 3) << endl;

  cout << str.substr(pos2 + 1) << endl;

  return 0;
}