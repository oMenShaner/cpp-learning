#ifndef __LIST_H__
#define __LIST_H__
#include <assert.h>

namespace wr
{
  // ListNode
  template <typename T>
  struct ListNode
  {
    ListNode<T> *_next; // 指向后继结点的指针
    ListNode<T> *_prev; // 指向前驱结点的指针
    T _data;            // 存放结点的数据

    ListNode(const T &val = T()) // 全缺省构造
        : _next(nullptr), _prev(nullptr), _data(val)
    {
    }
  };

  // __list_iterator
  template <typename T, typename Ref, typename Ptr>
  struct __list_iterator
  {
    typedef ListNode<T> Node;
    typedef __list_iterator<T, Ref, Ptr> self; // 重命名为self

    Node *_node; // 迭代器指向的结点指针

    __list_iterator(Node *node = nullptr)
        : _node(node)
    {
    }
    __list_iterator(const self &s)
        : _node(s._node)
    {
    }

    self &operator++()
    {
      _node = _node->_next;
      return *this;
    }
    self operator++(int)
    {
      self tmp(*this);
      _node = _node->_next;
      return tmp;
    }
    self &operator--()
    {
      _node = _node->_prev;
      return *this;
    }
    self operator--(int)
    {
      self tmp(*this);
      _node = _node->_prev;
      return tmp;
    }
    Ref operator*()
    {
      return _node->_data;
    }
    Ptr operator->()
    {
      return &(operator*());
    }

    bool operator!=(const self &s)
    {
      return _node != s._node;
    }
    bool operator==(const self &s)
    {
      return _node == s._node;
    }
  };

  // Reverse_iterator
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
      --_it;
      return *this;
    }

    Self operator++()
    {
      Self tmp(*this);
      --_it;
      return tmp;
    }

    Self operator--(int)
    {
      ++_it;
      return *this;
    }

    Self operator--()
    {
      Self tmp(*this);
      ++_it;
      return tmp;
    }

    Ref operator*()
    {
      return *_it;
    }

    Ptr operator->()
    {
      return &(*_it);
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

  // list
  template <typename T>
  class list
  {
    typedef ListNode<T> Node;

  public:
    typedef __list_iterator<T, T &, T *> iterator;
    typedef __list_iterator<T, const T &, const T *> const_iterator;

    typedef Reverse_iterator<iterator, T &, T *> reverse_iterator;
    typedef Reverse_iterator<const_iterator, const T &, const T *> const_reverse_iterator;

    list()
    {
      empty_init();
    }
    list(int n, const T &val = T())
    {
      empty_init();
      for (int i = 0; i < n; ++i)
      {
        push_back(val);
      }
    }
    template <typename InputIterator>
    list(InputIterator first, InputIterator last)
    {
      empty_init();
      while (first != last)
      {
        push_back(*first);
        ++first;
      }
    }
    list(const list<T> &l)
    {
      empty_init();
      for (const auto &e : l)
      {
        push_back(e);
      }
    }
    list<T> &operator=(const list<T> l)
    {
      swap(l);
      return *this;
    }
    ~list()
    {
      clear();
      delete _head;
      _head = nullptr;
    }

    ////////////////////////////////////////////////////////////
    // List Iterator
    iterator begin()
    {
      return _head->_next;
    }
    iterator end()
    {
      return _head;
    }
    const_iterator begin() const
    {
      return _head->_next;
    }
    const_iterator end() const
    {
      return _head;
    }

    reverse_iterator rbegin()
    {
      return reverse_iterator(--end());
    }

    reverse_iterator rend()
    {
      return reverse_iterator(--begin());
    }

    const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(--end());
    }

    const_reverse_iterator rend() const
    {
      return const_reverse_iterator(--begin());
    }

    ////////////////////////////////////////////////////////////
    // List Capacity
    size_t size() const
    {
      size_t size = 0;
      const_iterator it = begin();
      while (it != end())
      {
        ++size;
        ++it;
      }
      return size;
    }
    bool empty() const
    {
      return !size();
    }

    ////////////////////////////////////////////////////////////
    // List Access
    T &front()
    {
      return *(begin());
    }
    const T &front() const
    {
      return *(begin());
    }
    T &back()
    {
      return *(--end());
    }
    const T &back() const
    {
      return *(--end());
    }

    ////////////////////////////////////////////////////////////
    // List Modify
    void push_back(const T &val = T())
    {
      // Node *newNode = new Node(val);
      // Node *tail = _head->_prev;

      // tail->_next = newNode;
      // newNode->_prev = tail;
      // newNode->_next = _head;
      // _head->_prev = newNode;
      insert(end(), val);
    }
    void pop_back()
    {
      erase(--end());
    }
    void push_front(const T &val = T())
    {
      insert(begin(), val);
    }
    void pop_front()
    {
      erase(begin());
    }
    iterator insert(iterator pos, const T &val)
    { // 在pos位置前插入值为val的节点
      Node *cur = pos._node;
      Node *prev = cur->_prev;
      Node *newNode = new Node(val);

      prev->_next = newNode;
      newNode->_prev = prev;
      newNode->_next = cur;
      cur->_prev = newNode;

      return newNode;
    }
    iterator erase(iterator pos)
    { // 删除pos位置的节点，返回该节点的下一个位置
      assert(pos != end());

      Node *cur = pos._node;
      Node *prev = cur->_prev;
      Node *next = cur->_next;
      prev->_next = next;
      next->_prev = prev;

      delete cur;

      return next;
    }
    void clear()
    {
      iterator it = begin();
      while (it != end())
      {
        it = erase(it);
      }
    }
    void swap(list<T> &l)
    {
      std::swap(_head, l._head);
    }

  private:
    void empty_init()
    {
      _head = new Node;
      _head->_next = _head;
      _head->_prev = _head;
    }
    Node *_head;
  };
}

#endif // __LIST_H__