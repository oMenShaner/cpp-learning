#pragma once

#include <deque>
#include <vector>

namespace wr
{
  template <class T, class Con = deque<T>>
  class queue
  {
  public:
    void push(const T &x)
    {
      _con.push_back(x);
    }

    void pop()
    {
      _con.pop_front();
    }

    T &back()
    {
      return _con.back();
    }

    const T &back() const
    {
      return _con.back();
    }

    T &front()
    {
      return _con.front();
    }

    const T &front() const
    {
      return _con.front();
    }

    size_t size() const
    {
      return _con.size();
    }

    bool empty() const
    {
      return _con.empty();
    }

  private:
    Con _con;
  };

  template <class T>
  class greater
  {
  public:
    bool operator()(const T &a, const T &b)
    {
      return a > b;
    }
  };

  template <class T>
  class less
  {
  public:
    bool operator()(const T &a, const T &b)
    {
      return a < b;
    }
  };

  template <class T, class Con = vector<T>, class Compare = less<T>>
  class priority_queue
  {
    void adjust_up(int child)
    {
      int parent = (child - 1) / 2;
      while (parent >= 0)
      {
        // 默认less，大堆，a[child] > a[parent] 交换
        if (_comp(_con[parent], _con[child]))
        {
          swap(_con[parent], _con[child]);
          child = parent;
          parent = (child - 1) / 2;
        }
        else
        {
          break;
        }
      }
    }

    void adjust_down(int parent)
    {
      int child = parent * 2 + 1;
      while (child < _con.size())
      {
        // 默认less, 如果_con[child+1] > _con[child], 更新child
        if (child + 1 < _con.size() && _comp(_con[child], _con[child + 1]))
        {
          child++;
        }

        if (_comp(_con[parent], _con[child]))
        {
          swap(_con[parent], _con[child]);
          parent = child;
          child = parent * 2 + 1;
        }
        else
        {
          break;
        }
      }
    }

  public:
    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last)
    {
      while (first < last)
      {
        push(*first);
        first++;
      }
    }

    bool empty() const
    {
      return _con.empty();
    }

    size_t size() const
    {
      return _con.size();
    }

    const T &top() const
    {
      return _con.front();
    }

    void push(const T &x)
    {
      _con.push_back(x);
      adjust_up(_con.size() - 1);
    }

    void pop()
    {
      _con[0] = _con[_con.size() - 1];
      _con.pop_back();
      adjust_down(0);
    }

  private:
    Con _con;
    Compare _comp;
  };
}