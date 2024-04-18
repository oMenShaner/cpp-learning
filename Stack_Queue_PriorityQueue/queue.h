#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <deque>
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
#endif