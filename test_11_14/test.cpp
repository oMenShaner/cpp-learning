#include <iostream>
#include <string>

using namespace std;

// int main()
// {
//   string s1("");
//   int size = s1.capacity();
//
//   int i = 0;
//   for (i = 0; i < 500; i++)
//   {
//     s1.push_back('x');
//     if (size != s1.capacity())
//     {
//       size = s1.capacity();
//       cout << size << endl;
//     }
//   }
// }

// int main()
// {
//   // string()
//   string s1 = string(); // 无参构造
// 
//   // string(const char *s)
//   string s2 = string("Hello string"); // 使用C格式字符串构造
// 
//   // string(size_t n, char c)
//   string s3 = string(4, 'c'); // 使用 4个c字符
// 
//   // string(const string& s)
//   string s4 = string(s3);
// 
//   cout << string::npos << endl;
// }

// int main()
// {
//   string s1 = string("12345678");
//   string s2 = string(s1, 1, 5);     // [1, 6)
//   string s3 = string(s1, 0);        // [0, s1.size())
// }

// int main()
// {
//   string s1;
//   cout << "Please input a string: ";
//   cin >> s1;
// 
//   cout << "Your input: " << s1 << endl;
//   cout << "s1.size(): " << s1.size() << endl;
//   cout << "s1.length(): " << s1.length() << endl;
// 
//   return 0;
// }

// int main()
// {
//   string s1 = string();
//   size_t old_capacity = s1.capacity();
//   cout << old_capacity << endl;
// 
//   for (int i = 0; i < 500; i++)
//   {
//     s1.push_back('x');
//     if (old_capacity != s1.capacity())
//     {
//       old_capacity = s1.capacity();
//       cout << old_capacity << endl;
//     }
//   }
// 
//   return 0;
// }

int main()
{
  string s1 = "hello world!";

  for (size_t i = 0; i < s1.size(); i++)
  {
    cout << s1[i] << endl;    // 使用 operator[] 访问每个字符
    // cout << s1.operator[i] << endl;
  }
}