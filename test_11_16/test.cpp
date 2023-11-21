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

int main()
{
  string s1 = "1234567890";
  cout << "begin\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl << endl;

  // n > capacity
  // s1.resize(40);
  // cout << "after s1.resize(40)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;

  // n <= capacity && n >= size
  // s1.resize(13);
  // cout << "after s1.resize(13)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;

  // n < size
  s1.resize(5);
  cout << "after s1.resize(5)\nsize: " << s1.size() << "\ncapacity: " << s1.capacity() << endl;

}