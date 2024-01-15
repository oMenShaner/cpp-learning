#ifndef __STRING_H__
#define __STRING_H__
#include <assert.h>
#include <string.h>
  

namespace wr
{
  class string
  {
  public:
    typedef char* iterator;
    typedef const char *const_iterator;

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
      // _str = new char[s._capacity + 1];
      // strcpy(_str, s._str);
      // _capacity = s._capacity;
      // _size = s._size;

      // 现代写法，直接构造tmp，调用swap
      string tmp(s._str);
      swap(tmp);

    }

    string &operator=(string &s)
    {
      // if (this != &s)
      // {
      //   delete[] (_str);
      //   char *tmp = new char[s._capacity + 1];
      //   strcpy(tmp, s._str);

      //   _capacity = s._capacity;
      //   _size = s._size;
      //   _str = tmp;
      // }

      // 现代写法，直接调用swap
      swap(s);

      return *this;
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

    const_iterator begin() const
    {
      return _str;
    }

    const_iterator end() const
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

    string &operator+=(const char c)
    {
      this->push_back(c);

      return *this;
    }

    void append(const char *str)
    {
      int len = strlen(str);
      if (_size + len > _capacity)
      {
        size_t newCapacity = _size + len;
        this->reserve(newCapacity);
      }

      strcpy(_str + _size, str);
      _size += len;
    }

    string &operator+=(const char *str)
    {
      this->append(str);

      return *this;
    }

    void swap(string &s)
    {
      std::swap(_str, s._str);
      std::swap(_capacity, s._capacity);
      std::swap(_size, s._size);
    }

    const char *c_str() const
    {
      return _str;
    }

    void clear()
    {
      _str[0] = '\0';
      _size = 0;
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
        delete[] (_str);
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
    bool operator<(const string &s)
    {
      int len1 = this->size();
      int len2 = s.size();

      if (len1 != len2)
      {
        return len1 < len2;
      }

      for (int i = 0; i < len1; ++i)
      {
        if (this->_str[i] >= s._str[i])
        {
          return false;
        }
      }

      return true;
    }

    bool operator==(const string &s)
    {
      int len1 = this->size();
      int len2 = s.size();

      if (len1 != len2)
      {
        return false;
      }

      for (int i = 0; i < len1; ++i)
      {
        if (this->_str[i] != s._str[i])
        {
          return false;
        }
      }

      return true;
    }

    bool operator<=(const string &s)
    {
      return *this < s && *this == s;
    }

    bool operator>(const string &s)
    {
      return !(*this <= s);
    }

    bool operator>=(const string &s)
    {
      return *this > s && *this == s;
    }

    bool operator!=(const string &s)
    {
      return !(*this == s);
    }

    // 返回 c 在 string 第一次出现的位置
    size_t find(char c, size_t pos = 0)
    {
      assert(pos < _size);

      for (int i = pos; i < _size; ++i)
      {
        if (this->_str[i] == c)
        {
          return i;
        }
      }

      return npos;
    }

    // 返回子串 s 在string 第一次出现的位置
    size_t find(const char *str, size_t pos = 0)
    {
      assert(pos < _size);

      const char *ptr = strstr(_str + pos, str);
      if (ptr == nullptr)
      {
        return npos;
      }
      else
      {
        return ptr - _str;
      }
    }

    // 在 pos 位置插入字符 c /字符串 str, 并返回该字符的位置
    string &insert(size_t pos, char c)
    {
      assert(pos <= _size);

      if (_size == _capacity)
      {
        size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
        this->reserve(newCapacity);
      }

      size_t end = _size + 1;
      while (end > pos)
      {
        _str[end] = _str[end - 1];
        --end;
      }
      _str[end] = c;
      ++_size;

      return *this;
    }

    string &insert(size_t pos, const char *str)
    {
      assert(pos <= _size);

      size_t len = strlen(str);
      if (_size + len > _capacity)
      {
        this->reserve(_capacity + len);
      }

      size_t end = _size + len;
      while (end > pos)
      {
        _str[end] = _str[end - len];
        --end;
      }
      strncpy(_str + pos, str, len);
      _size += len;

      return *this;
    }

    string &erase(size_t pos, size_t len = npos)
    {
      assert(pos < _size);

      if (len == npos || pos + len >= _size)
      {
        _str[pos] = '\0';
        _size = pos;
      }
      else 
      {
        strcpy(_str + pos, _str + pos + len);
        _size -= len;
      }

      return *this;
    }

    string substr(size_t pos = 0, size_t len = npos)
    {
      assert(pos < _size);

      size_t end = pos + len;
      if (len == npos || pos + len >= _size)
      {
        end = _size;
      }

      string str;
      str.reserve(end - pos);
      for (int i = pos; i < end; ++i)
      {
        str += _str[i];
      }

      return str;
    }

  private:
    char *_str;
    size_t _capacity;
    size_t _size;
    const static size_t npos = -1;
  };

  // 不一定非要友元，只有访问到私有成员才需要
  ostream &operator<<(ostream &_cout, const wr::string &s)
  {
    for (size_t i = 0; i < s.size(); ++i)
    {
      _cout << s[i];
    }

      return _cout;
  }

  istream &operator>>(istream &_cin, wr::string &s)
  {
    s.clear();
    char buffer[128] = {0, }; // 给一个buffer数组，临时存放输入的内容
    char ch = _cin.get(); // get()可以拿到空格或换行
    int i = 0;
    while (ch != ' ' && ch != '\n')
    {
      buffer[i++] = ch;
      if (i == 127)
      {
        buffer[i] = '\0';
        s += buffer;
        i = 0;
      }
      ch = _cin.get();
    }

    if (i > 0)
    {
      buffer[i] = '\0';
      s += buffer;
    }
    return _cin;
  }
};

#endif