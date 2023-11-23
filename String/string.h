#ifndef __STRING_H__
#define __STRING_H__
#include <iostream>
#include <assert.h>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

namespace wr
{
  class string
  {
    friend ostream &operator<<(ostream &_cout, const wr::string &s);
    friend istream &operator>>(istream &_cin, const wr::string &s);

  public:
    typedef char *iterator;

  public:
    string(const char *str = "")
    {
      _size = strlen(str);
      _capacity = _size;
      _str = new char[_capacity + 1]; // 多一个空间给 \0
      strcpy(_str, str);
    }

    string(const string &s)
    {

    }

    string &operator=(const string &s)
    {
    
    }

    ~string()
    {
      delete[] (_str);
      _str = nullptr;
      _size = _capacity = 0;
    }

    // iterator
    iterator begin()
    {
      return _str;
    }

    iterator end()
    {
      return _str + _size;
    }

    // modify
    void push_back(char c)
    {
      if (_size == _capacity)
      {
        size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
        this->reserve(newCapacity);
      }
      *(_str + _size) = c;
      ++_size;
      *(_str + _size) = '\0';
    }

    string &operator+=(const char c){
      this->push_back(c);

      return *this;
    }

    void append(const char *str){
      int len = strlen(str);
      if (_size + len > _capacity){
        size_t newCapacity = _size + len;
        this->reserve(newCapacity);
      }

      strcpy(_str + _size, str);
      _size += len;
    }

    string &operator+=(const char *str){
      this->append(str);

      return *this;
    }

    void swap(string &s){

    }

    const char *c_str() const {
      return _str;
    }

    // capacity
    size_t size() const
    {
      return _size;
    }

    size_t capacity() const
    {
      return _capacity;
    }

    bool empty() const
    {
      return !_size;
    }

    void reserve(size_t n)
    {
      assert(n >= 0);

      if (n > _capacity)
      {
        char *tmp = new char[n + 1];
        strcpy(tmp, _str);
        delete[](_str);
        _str = tmp;
        _capacity = n;
      }
    }

    void resize(size_t n, char c = '\0')
    {
      assert(n >= 0);

      if (n > _capacity)
      {
        this->reserve(n);
        for (int i = _size; i < n; ++i)
        {
          this->push_back(c);
        }
      }
      else if (n >= _size)
      {
        for (int i = _size; i < n; ++i)
        {
          this->push_back(c);
        }
      }
      else
      {
        _size = n;
        *(_str + _size) = '\0';
      }
    }

    // access
    char &operator[](size_t index)
    {
      assert(index >= 0 && index <= _size);

      return *(_str + index);
    }

    const char &operator[](size_t index) const
    {
      assert(index >= 0 && index <= _size);

      return _str[index];
    }

    // relational operators
    bool operator<(const string &s){
      int len1 = this->size();
      int len2 = s.size();

      if (len1 != len2){
        return len1 < len2;
      }

      for (int i = 0; i < len1; ++i){
        if (this->_str[i] >= s._str[i]){
          return false;
        }
      }

      return true;
    }

    bool operator==(const string &s){
      int len1 = this->size();
      int len2 = s.size();

      if (len1 != len2){
        return false;
      }

      for (int i = 0; i < len1; ++i){
        if (this->_str[i] != s._str[i]){
          return false;
        }
      }
      
      return true;
    }
  
    bool operator<=(const string &s){
      return *this < s && *this == s;
    }

    bool operator>(const string &s){
      return !(*this <= s);
    }

    bool operator>=(const string &s){
      return *this > s && *this == s;
    }

    bool operator!=(const string &s){
      return !(*this == s);
    }

    // 返回 c 在 string 第一次出现的位置
    size_t find(char c, size_t pos = 0){
      assert(pos >= 0 && pos < this->size());

      for (int i = pos; i < this->size(); ++i)
      {
        if (this->_str[i] == c){
          return i;
        }
      }

      return -1;
    }

    // 返回子串 s 在string 第一次出现的位置
    size_t find(const char *s, size_t pos = 0){
      assert(pos >= 0 && pos < this->size());

      for (int i = pos; i < this->size(); ++i){
        if (this->_str[i] == s[0]){
          for (int j = 1; j < strlen(s); ++j){
            if (this->_str[i+j] != s[j]){
              break;
            }

            if (j == strlen(s) - 1){
              return i;
            }
          }
        }
      }

      return -1;
    }

    // 在 pos 位置插入字符 c /字符串 str, 并返回该字符的位置
    string &insert(size_t pos, char c){
      assert(pos >= 0 && pos <= this->size());

      this->push_back('\0');
      for (int i = this->size()-1; i > pos; --i){
        this->_str[i + 1] = this->_str[i];
      }
      this->_str[pos] = c;

      return *this;
    }

  private:
    char *_str;
    size_t _capacity;
    size_t _size

  };

  ostream &operator<<(ostream &_cout, const wr::string &s)
  {
    _cout << s._str;

    return _cout;
  }

  istream &operator>>(istream &_cin, const wr::string &s)
  {
    _cin >> s._str;

    return _cin;
  }
};

#endif
