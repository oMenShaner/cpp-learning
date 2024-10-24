#pragma once
namespace openaddress
{
  enum State
  {
    EMPTY,
    EXIST,
    DELETE
  };

  template <class K, class V>
  struct HashNode
  {
    pair<K, V> _kv;
    State _state = EMPTY; // 状态
  };

  // 若key不为int，则使用仿函数得到其哈希值
  template <class K>
  struct HashFunc
  {
    size_t operator()(const K &key)
    {
      return (size_t)key;
    }
  };

  // 特化
  template <>
  struct HashFunc<string>
  {
    size_t hashi = 0;
    size_t operator()(const string &s)
    {
      for (auto e : s)
      {
        hashi += e;
        hashi *= 131; // 乘上一个值
      }

      return (size_t)hashi;
    }
  };

  // 开放定址法（闭散列法）
  template <class K, class V, class Hash = HashFunc<K>>
  class HashTable
  {
  public:
    HashTable(size_t size = 10)
    {
      _tables.resize(size);
    }

    HashNode<K, V> *Find(const K &key)
    {
      Hash hs;
      // 根据哈希函数得到下标
      // 如果该位置为EMPTY, 直接返回false;
      // 如果该位置不为EMPTY, 在下一EMPTY之前寻找key相等并且为EXIST
      size_t hashi = hs(key) % _tables.size();
      while (_tables[hashi]._state != EMPTY)
      {
        if (_tables[hashi]._kv.first == key && _tables[hashi]._state == EXIST)
        {
          return &_tables[hashi];
        }
        else
        {
          hashi++;
          hashi = hashi % _tables.size();
        }
      }

      return nullptr;
    }
    bool Insert(const pair<K, V> &kv)
    {
      if (Find(kv.first))
        return false;

      // 如果负载因子大于等于0.7，进行双倍扩容
      if ((double)_n / _tables.size() >= 0.7)
      {
        // 创建一个新的HashTable, 遍历旧的哈希表递归调用Insert
        HashTable<K, V> newHT(_tables.size() * 2);
        for (auto &e : _tables)
        {
          newHT.Insert(e._kv);
        }

        // 现代规则，直接交换两者
        _tables.swap(newHT._tables);
      }

      // 根据哈希函数得到下标
      // 如果该位置不为EXITS，插入；否则线性探测至下一位置（EMPYT|DELETE)
      Hash hs;
      size_t hashi = hs(kv.first) % _tables.size(); // 哈希函数，使用除留余数法：哈希值%表长
      while (_tables[hashi]._state == EXIST)
      {
        hashi++;
        hashi = hashi % _tables.size();
      }

      // 插入元素
      _tables[hashi]._kv = kv;
      _tables[hashi]._state = EXIST;
      _n++;

      return true;
    }

    bool Erase(const K &key)
    {
      // 通过Find找到要删除的位置，如果为空返回false；否则，只要将状态进行修改即可
      HashNode<K, V> *ret = Find(key);
      if (ret == nullptr)
      {
        return false;
      }
      else
      {
        ret->_state = DELETE;
        _n--;
        return true;
      }
    }

  private:
    vector<HashNode<K, V>> _tables;
    size_t _n = 0; // 已存元素个数
  };
}

namespace hashbucket
{
  template <class K, class V>
  struct HashNode
  {
    pair<K, V> _kv;
    struct HashNode *_next;

    HashNode(const pair<K, V> &kv)
        : _kv(kv), _next(nullptr)
    {
    }
  };

  template <class K>
  struct HashFunc
  {
    size_t operator()(const K &key)
    {
      return (size_t)key;
    }
  };

  // 特化
  template <>
  struct HashFunc<string>
  {
    size_t operator()(const string &key)
    {
      size_t hashi = 0;
      for (auto e : key)
      {
        hashi += e;
        hashi *= 131;
      }

      return (size_t)hashi;
    }
  };
  template <class K, class V, class Hash = HashFunc<K>>
  class HashTable
  {
    typedef struct HashNode<K, V> Node;

  public:
    HashTable(size_t size = 10)
    {
      _tables.resize(size, nullptr);
      _n = 0;
    }

    ~HashTable()
    {
      // 把每个下标链接的链表delete掉
      for (int i = 0; i < _tables.size(); i++)
      {
        Node *cur = _tables[i];
        while (cur)
        {
          Node *next = cur->_next;
          delete cur;
          cur = next;
        }
        _tables[i] = nullptr;
      }
    }

    Node *Find(const K &key)
    {
      Hash hs;
      // 根据哈希函数得到下标
      size_t hashi = hs(key) % _tables.size();
      Node *cur = _tables[hashi];

      // 进行链表查找
      while (cur != nullptr)
      {
        if (cur->_kv.first == key)
        {
          return cur;
        }
        else
        {
          cur = cur->_next;
        }
      }
      return nullptr;
    }

    bool Insert(const pair<K, V> &kv)
    {
      Hash hs;
      if (Find(kv.first))
        return false;

      // 如果负载因子等于1，扩容两倍
      // 创建一个新的tables，直接进行插入，不需要重新创建结点
      if (_n == _tables.size())
      {
        vector<Node *> newTables(_tables.size() * 2);
        // 遍历旧table
        for (int i = 0; i < _tables.size(); i++)
        {
          Node *cur = _tables[i];
          Node *next = nullptr;
          // 遍历每个下标链接的链表
          while (cur)
          {
            next = cur->_next;
            // 计算每个结点的哈希值在新表对应的下标，直接在新表进行头插
            size_t hashi = hs(cur->_kv.first) % newTables.size();
            cur->_next = newTables[hashi];
            newTables[hashi] = cur;

            cur = next;
          }
        }
        _tables.swap(newTables);
      }

      // 根据哈希函数得到下标
      size_t hashi = hs(kv.first) % _tables.size();

      // 头插
      Node *newNode = new Node(kv);
      newNode->_next = _tables[hashi];
      _tables[hashi] = newNode;

      ++_n;
      return true;
    }

    bool Erase(const K &key)
    {
      Hash hs;
      // 直接计算下标，遍历链表的同时，如果有该关键字进行删除；如果没有返回false
      size_t hashi = hs(key) % _tables.size();
      Node *cur = _tables[hashi];
      Node *prev = nullptr;
      while (cur)
      {
        // 如果当前结点是要找的关键字，将该结点进行删除
        if (cur->_kv.first == key)
        {
          // 如果此时prev为空，说明链表第一个结点就是要删除的结点，直接替换；否则将prev与被删除的结点的下一个进行连接
          if (prev)
          {
            prev->_next = cur->_next;
          }
          else
          {
            _tables[hashi] = cur->_next;
          }
          delete cur;
          --_n;
          return true;
        }

        prev = cur;
        cur = cur->_next;
      }

      return false;
    }
    void Some()
    {
      size_t bucketSize = 0;
      size_t maxBucketLen = 0;
      size_t sum = 0;
      double averageBucketLen = 0;

      for (size_t i = 0; i < _tables.size(); i++)
      {
        Node *cur = _tables[i];
        if (cur)
        {
          ++bucketSize;
        }

        size_t bucketLen = 0;
        while (cur)
        {
          ++bucketLen;
          cur = cur->_next;
        }

        sum += bucketLen;

        if (bucketLen > maxBucketLen)
        {
          maxBucketLen = bucketLen;
        }
      }

      averageBucketLen = (double)sum / (double)bucketSize;

      printf("load factor:%lf\n", (double)_n / _tables.size());
      printf("all bucketSize:%d\n", _tables.size());
      printf("bucketSize:%d\n", bucketSize);
      printf("maxBucketLen:%d\n", maxBucketLen);
      printf("averageBucketLen:%lf\n\n", averageBucketLen);
    }

  private:
    vector<Node *> _tables; // 指针数组
    size_t _n = 0;          // 元素个数
  };
}