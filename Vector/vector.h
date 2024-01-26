#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstring>
#include <assert.h>
#include <utility>

namespace wr
{
  template <typename T>
  class vector
  {
  public:
    // 重命名迭代器，vector迭代器是原生指针
    typedef T *iterator;  
    typedef const T *const_iterator;
    iterator begin() { return _start; }
    iterator end() { return _finish; }
    const_iterator begin() const { return _start; }
    const_iterator end() const { return _finish; }

    //////////construct and destroy//////////
    vector () {}
    vector(int n, const T &value = T())
    {
      assert(n >= 0);

      reserve(n);
      while (_finish != _start + n)
      {
        push_back(value);
      }
    }
    template<typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
      assert(last >= first);

      reserve(last - first);
      while (first < last)
      {
        push_back(*first);
        ++first;
      }
    }
    vector(const vector<T>& v)
    {
      // reserve(v.capacity());
      // memcpy(_start, v._start, sizeof(T) * v.size());
      // _finish = _start + v.size();

      reserve(v.capacity());
      for (const auto &e :v)
      {
        push_back(e);
      }
    }
    vector<T>& operator=(vector<T> v)
    {
      if (this != &v)
        swap(v);

      return *this;
    }
    ~vector()
    {
      delete[] (_start);
      _start = _finish = _endofstorage = nullptr;
    }
    
    //////////capacity//////////
    size_t size() const { return _finish - _start; }
    size_t capacity() const { return _endofstorage - _start; }
    void reserve(size_t n)
    {
      // 只有 n > 当前capacity，才真正会发生扩容
      if (n > capacity())
      {
        size_t old_size = size();
        iterator tmp = new T[n]; 
        // memcpy(tmp, _start, sizeof(T) * old_size);
        // memcpy 只是浅拷贝，由于已经申请并且初始化该空间，需要另外进行赋值
        if(_start) {
          for (size_t i = 0; i < old_size; ++i)
          {
            tmp[i] = _start[i];
          }
          delete[] (_start);
        }

        _start = tmp;
        _finish = _start + old_size;
        _endofstorage = _start + n;
      }
    }
    void resize(size_t n, const T & value = T())
    {
      assert(n >= 0);

      reserve(n); // 先申请空间，避免下面push_back频繁new消耗内存
      if (n < size()) // 直接改变_finish
      {
        _finish = _start + n;
      }
      else if (n >size())  // 直接尾插
      {
        while (_finish != _start+n)
        {
          push_back(value);
        }
      }
    }

    //////////access//////////
    T& operator[](size_t pos) 
    {
      assert(pos >= 0);
      assert(pos < size());

      return *(_start + pos);
    }
    const T &operator[](size_t pos) const
    {
      assert(pos >= 0);
      assert(pos < size());

      return *(_start + pos);
    }
    
    //////////modify//////////
    void push_back(const T &x)
    {
      // 如果容量不够，先扩容
      if (_finish == _endofstorage)
      {
        reserve(capacity() == 0 ? 4 : 2 * capacity());
      }
      *_finish = x;
      ++_finish;
    }
    void pop_back()
    {
      assert(_finish > _start);

      --_finish;
    }
    iterator insert(iterator pos, const T& x)
    {
      // pos 之前插入数据
      assert(pos >= _start);
      assert(pos <= _finish);

      // 先记录pos相对_start的位置，扩容会更改pos指向元素的位置
      size_t old_pos = pos - _start;
      // 容量不够先扩容
      if (_finish == _endofstorage)
      {
        reserve(capacity() == 0 ? 4 : capacity() * 2);
      }
      
      // 更新pos，移动数据后插入数据
      pos = _start + old_pos;
      // memmove(pos + 1, pos, sizeof(T) * (_finish - pos));
      iterator end = _finish;
      while (end >= pos)
      {
        *(end + 1) = *end;
        --end;
      }
      ++_finish;
      *pos = x;

      return pos;
    }
    iterator erase(iterator pos)
    {
      assert(pos >= _start);
      assert(pos < _finish);

      //memmove(pos, pos + 1, sizeof(T) * (_finish - pos - 1));
      iterator it = pos + 1;
      while (it < _finish)
      {
        *(it - 1) = *it;
        ++it;
      }
      --_finish;

      return pos;
    }
    void swap(vector<T>& v)
    {
      std::swap(_start, v._start);
      std::swap(_finish, v._finish);
      std::swap(_endofstorage, v._endofstorage);
    }

  private:
    iterator _start = nullptr;  // 指向数据块的开始
    iterator _finish = nullptr; // 指向有效数据的尾
    iterator _endofstorage = nullptr; // 指向存储容量的尾
  };
} // namespace wr

#endif // vector.h