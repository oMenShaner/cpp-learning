#pragma once

namespace wr
{
  template <class Iterator, class Ref, class Ptr>
  struct Reverse_iterator
  {
    typedef Reverse_iterator<Iterator, Ref, Ptr> Self;
    Iterator _it;

    Reverse_iterator(Iterator it)
        : _it(it)
    {
    }

    Self operator++(int)
    {
      Self tmp = *this;
      _it--;
      return tmp;
    }

    Self operator++()
    {
      _it--;
      return *this;
    }

    Self operator--(int)
    {
      Self tmp = *this;
      _it++;
      return tmp;
    }

    Self operator--()
    {
      _it++;
      return *this;
    }

    Ref operator*()
    {
      Iterator tmp = this->_it;
      tmp--;
      return *tmp;
    }

    Ptr operator->()
    {
      return &(operator*());
    }

    bool operator!=(const Self &s)
    {
      return _it != s._it;
    }

    bool operator==(const Self &s)
    {
      return _it == s._it;
    }
  };
}