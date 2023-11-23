#ifndef __STRING_H__
#define __STRING_H__
#include <iostream>
#include <assert.h>
#include <string.h>

using std::cout, std::cin, std::endl;
using std::ostream, std::istream;

namespace wr
{
  class string 
  {
    friend ostream &operator<<(ostream &_cout, const wr::string &s);
    friend istream &operator>>(istream &_cin, const wr::string &s);

  public:
    typedef char *iterator;

  public:
    string(const char *str = ""){
      _size = strlen(str);
      _capacity = _size;
      _str = new char[_capacity + 1];  // 多一个空间给 \0
      strcpy(_str, str);
    }

    string(const string &s){
      _capacity = s._capacity;
      _size = s._size;
      _str = new char[_capacity + 1];
      strcpy(_str, s._str);
    }

    string& operator=(const string &s){
      _capacity = s._capacity;
      _size = s._size;
      _str = new char[_capacity + 1];
      strcpy(_str, s._str);

      return *this;
    }

    ~string(){
      delete[] (_str);
      _str = nullptr;
      _size = _capacity = 0;
    }

  /////////////////////////////////////
  // iterator
    iterator begin(){
      return _str;
    }

    iterator end(){
      return _str + _size;
    }

  private:
    char *_str;
    size_t _capacity;
    size_t _size;
  };

  ostream &operator<<(ostream &_cout, const wr::string &s)
  {
    _cout << s._str;

    return _cout;
  }

  istream &operator>>(istream &_cin, const wr::string &s){
    _cin >> s._str;

    return _cin;
  }
};


#endif