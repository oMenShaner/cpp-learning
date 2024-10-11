#pragma once

template <class K>
struct BSTreeNode
{
  typedef BSTreeNode<K> Node;

  Node *_left;
  Node *_right;
  K _key;

  BSTreeNode(const K &key)
      : _left(nullptr), _right(nullptr), _key(key)
  {
  }
};

template <class K>
class BSTree
{
  typedef BSTreeNode<K> Node;

public:
  BSTree() = default;
  BSTree(const BSTree<K> &t)
  {
    _root = Copy(t._root);
  }
  BSTree<K> operator=(BSTree<K> t)
  {
    swap(_root, t._root);
    return *this;
  }
  ~BSTree()
  {
    _Destroy(_root);
  }

  bool Insert(const K &key)
  {
    // 如果树为空，直接创建新结点并作为根
    if (!_root)
    {
      _root = new Node(key);
      return true;
    }
    Node *cur = _root, *parent = nullptr;

    while (cur)
    {
      if (cur->_key < key)
      {
        parent = cur;
        cur = cur->_right;
      }
      else if (cur->_key > key)
      {
        parent = cur;
        cur = cur->_left;
      }
      else
        return false; // 不允许插入重复结点
    }

    cur = new Node(key);
    if (parent->_key < key)
      parent->_right = cur;
    else
      parent->_left = cur;

    return true;
  }
  bool Find(const K &key)
  {
    // 从头开始搜索
    // 如果key比当前结点大，找右子树；
    // 如果key比当前结点小，找左子树；
    // 如果key与当前结点相等，返回true
    Node *cur = _root;
    while (cur)
    {
      if (cur->_key < key)
        cur = cur->_right;
      else if (cur->_key > key)
        cur = cur->_left;
      else
        return true;
    }

    return false; // 如果遍历到这里，说明没有找到
  }
  bool Erase(const K &key)
  {
    Node *cur = _root, *parent = nullptr;
    while (cur)
    {
      if (cur->_key < key)
      {
        parent = cur;
        cur = cur->_right;
      }
      else if (cur->_key > key)
      {
        parent = cur;
        cur = cur->_left;
      }
      else
      {
        // 三种情况
        // 1. 删除结点是叶子结点，直接删除
        // 2. 删除结点只有一个孩子，将其孩子托付给父亲
        // 3. 删除结点有两个孩子，先找到其右子树的最左结点，将其替换被删除结点，随后删除最左结点
        // 1、2情况可以合并成一种
        if (cur->_left == nullptr)
        {
          if (cur == _root)
          {
            _root = _root->_right; // 如果删除的是根结点，直接改变，因为此时parent是nullptr
          }
          else
          {
            if (cur->_key < parent->_key)
              parent->_left = cur->_right;
            else
              parent->_right = cur->_right;
          }

          delete (cur);
          return true;
        }
        else if (cur->_right == nullptr)
        {
          if (cur == _root)
          {
            _root = _root->_left; // 如果删除的是根结点，直接改变，因为此时parent是nullptr
          }
          else
          {
            if (cur->_key < parent->_key)
              parent->_left = cur->_left;
            else
              parent->_right = cur->_left;
          }
          delete (cur);
          return true;
        }
        else
        {
          // 先找到右子树的最左结点，注意该结点可能为右子树的根
          Node *rightMin = cur->_right, *rightMinParent = cur;
          while (rightMin->_left)
          {
            rightMinParent = rightMin;
            rightMin = rightMin->_left;
          }

          // 替换被删除结点的key
          cur->_key = rightMin->_key;

          // 由于最左结点的左肯定是空的，只要把最左结点的右托付给它的双亲即可
          if (rightMinParent->_right == rightMin)
          {
            // 特殊情况，右子树的根即最左结点
            rightMinParent->_right = rightMin->_right;
          }
          else
          {
            rightMinParent->_left = rightMin->_right;
          }

          free(rightMin);
          return true;
        }
      }
    }

    return false; // 如果遍历到这里，说明没有找到
  }
  void InOrder()
  {
    _InOrder(_root);
    cout << endl;
  }

  //////////////////////////////////////////////////////////////////
  bool FindR(const K &key)
  {
    return _FindR(_root, key);
  }

  bool InsertR(const K &key)
  {
    return _InsertR(_root, key);
  }

  bool EraseR(const K &key)
  {
    return _EraseR(_root, key);
  }

private:
  void _InOrder(Node *root)
  {
    if (root == nullptr)
      return;

    _InOrder(root->_left);
    cout << root->_key << " ";
    _InOrder(root->_right);
  }
  void _Destroy(Node *root)
  {
    if (root == nullptr)
      return;

    _Destroy(root->_left);
    _Destroy(root->_right);
    free(root);
  }
  Node *Copy(Node *root)
  {
    if (root == nullptr)
      return nullptr;

    Node *newNode = new Node(root->_key);
    newNode->_left = Copy(root->_left);
    newNode->_right = Copy(root->_right);
    return newNode;
  }
  bool _FindR(Node *root, const K &key)
  {
    if (root == nullptr)
      return false;

    if (root->_key < key)
      return _FindR(root->_right, key);
    else if (root->_key > key)
      return _FindR(root->_left, key);
    else
      return true;
  }
  bool _InsertR(Node *&root, const K &key)
  {
    if (root == nullptr)
    {
      root = new Node(key);
      return true;
    }

    if (root->_key < key)
      return _InsertR(root->_right, key);
    else if (root->_key > key)
      return _InsertR(root->_left, key);
    else
      return false;
  }
  bool _EraseR(Node *&root, const K &key)
  {
    if (root == nullptr)
      return false;

    if (root->_key < key)
      return _EraseR(root->_right, key);
    else if (root->_key > key)
      return _EraseR(root->_left, key);
    else
    {
      Node *del = root;
      if (root->_left == nullptr)
        root = root->_right;
      else if (root->_right == nullptr)
        root = root->_left;
      else
      {
        Node *rightMin = root->_right;
        while (rightMin->_left)
        {
          // 由于可以递归，只要找到最左结点交换值即可，随后进行递归删除
          rightMin = rightMin->_left;
        }

        // del = rightMin;
        // root->_key = rightMin;
        // if (rightMinParent->_right == rightMin)
        //   rightMinParent->_right = rightMin->_right;
        // else
        //   rightMinParent->_left = rightMin->_right;

        swap(root->_key, rightMin->_key);
        return _EraseR(root->_right, key);
      }

      free(del);
      return true;
    }
  }
  Node *_root = nullptr;
};