#pragma once
#include <deque>

namespace wr
{
  template <class T, class Con = deque<T>>
  class stack
  {
  public:
    void push(const T &x)
    {
      _con.push_back(x);
    }

    void pop()
    {
      _con.pop_back();
    }

    T &top()
    {
      return _con.back();
    }

    T &top() const
    {
      return _con.back();
    }

    size_t size()
    {
      return _con.size();
    }

    bool empty()
    {
      return _con.empty();
    }

  private:
    Con _con;
  };
}