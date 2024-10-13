#pragma once

template <class K, class V>
struct AVLTreeNode
{
  typedef AVLTreeNode<K, V> Node;

  Node *_left, *_right, *_parent;
  int _bf; // 左子树高度-右子树高度
  pair<K, V> _kv;

  AVLTreeNode(const pair<K, V> &kv)
      : _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0), _kv(kv)
  {
  }
};

template <class K, class V>
class AVLTree
{
  typedef AVLTreeNode<K, V> Node;

public:
  void InOrder()
  {
    _InOrder(_root);
    cout << endl;
  }

  bool Insert(const pair<K, V> &kv)
  {
    if (_root == nullptr)
    {
      _root = new Node(kv);
      return true;
    }

    Node *cur = _root, *parent = nullptr;
    // 找到新结点的插入位置
    while (cur)
    {
      if (cur->_kv.first < kv.first)
      {
        parent = cur;
        cur = cur->_right;
      }
      else if (cur->_kv.first > kv.first)
      {
        parent = cur;
        cur = cur->_left;
      }
      else
      {
        return false;
      }
    }

    // 链接上新结点
    cur = new Node(kv);
    if (parent->_kv.first < kv.first)
      parent->_right = cur;
    else
      parent->_left = cur;

    cur->_parent = parent;

    // 更新平衡因子
    // 插入结点cur可能会影响其祖先的平衡因子
    while (parent)
    {
      // 插入的是左树，bf++
      // 插入的是右树，bf--
      if (parent->_left == cur)
        parent->_bf++;
      else
        parent->_bf--;

      // 更新平衡因子判断是否要继续更新，p代指当前循环中的被更新结点，即cur的双亲
      // 1. 若p->bf == 0, 代表其是由-1(插入到p的左)/1(插入到p的右)改变而来的，以p为根的树高度未变，不会影响p的双亲
      // 2. 若p->bf == 1/-1, 代表其是由0改变而来的，1(插入到p的左)/-1(插入到p的右)，以p为根的高度改变，会影响p的双亲
      // 3. 若p->bf == 2/-2, 代表其实由1(插入到p的左)/-1(插入到p的右)改变而来的，此时违反AVL树平衡规则，进行旋转，旋转后高度不变，不会影响p的双亲
      if (parent->_bf == 0)
      {
        break;
      }
      else if (parent->_bf == 1 || parent->_bf == -1)
      {
        cur = cur->_parent;
        parent = parent->_parent;
      }
      else if (parent->_bf == 2 || parent->_bf == -2)
      {
        // 旋转
        if (parent->_bf == -2 && cur->_bf == -1)
        {
          // RR型左单旋
          RotateL(parent);
          cout << "插入" << kv.first << "发生RoatateL" << endl;
        }
        else if (parent->_bf == 2 && cur->_bf == 1)
        {
          // LL型右单旋
          RotateR(parent);
          cout << "插入" << kv.first << "发生RoatateR" << endl;
        }
        else if (parent->_bf == 2 && cur->_bf == -1)
        {
          // LR型左右双旋
          RotateLR(parent);
          cout << "插入" << kv.first << "发生RoatateLR" << endl;
        }
        else
        {
          // RL型右左双旋
          RotateRL(parent);
          cout << "插入" << kv.first << "发生RoatateRL" << endl;
        }
        break;
      }
      else
      {
        // 插入到AVL树之前就有问题
        assert(false);
      }
    }

    return true;
  }

  // 旋转目的
  // 1. 保持搜索树规则
  // 2. 当前树从不平衡状态旋转为平衡
  // 3. 降低当前树的高度，从而不会影响当前树双亲结点的平衡因子

  // RR型左单旋
  void RotateL(Node *parent)
  {
    // parent 的右指向 subRL
    // subR 的左指向parent
    // 注意
    // 1. subRL为空的情况
    // 2. 链接双亲结点
    // 3. 讨论 parent 是否为根节点
    Node *subR = parent->_right;
    Node *subRL = subR->_left;

    parent->_right = subRL;
    if (subRL)
      subRL->_parent = parent;

    subR->_left = parent;
    Node *ppnode = parent->_parent;
    parent->_parent = subR;

    // 如果旋转前parent是根结点，需要subR直接替换_root
    // 如果不是，分左右链接上双亲结点
    if (parent == _root)
      _root = subR;
    else if (ppnode->_left == parent)
      ppnode->_left = subR;
    else
      ppnode->_right = subR;

    subR->_parent = ppnode;

    // 更新平衡因子，左单旋只会修改parent和subR的平衡因子
    // 修改前p:-2, subR:-1 修改后均为0
    parent->_bf = subR->_bf = 0;
  }

  // LL型右单旋
  void RotateR(Node *parent)
  {
    Node *subL = parent->_left;
    Node *subLR = subL->_right;

    parent->_left = subLR;
    if (subLR)
      subLR->_parent = parent;

    subL->_right = parent;
    Node *ppnode = parent->_parent;
    parent->_parent = subL;

    if (parent == _root)
      _root = subL;
    else if (ppnode->_left == parent)
      ppnode->_left = subL;
    else
      ppnode->_right = subL;

    subL->_parent = ppnode;

    subL->_bf = parent->_bf = 0;
  }

  // LR型左右双旋
  void RotateLR(Node *parent)
  {
    // 1. 取出因插入结点导致高度为h+1的树的根结点，分成 subLR->_left 和 subLR->_right，对 subL 进行左单旋
    //    subL 右为 subLR->_left, subLR 左为 subL
    // 2. 左单旋后此时 parent:2, subLR:1, 对 parent 进行右单旋
    //    parent 左为 subLR->_right, subLR 右为 parent
    Node *subL = parent->_left;
    Node *subLR = subL->_right;
    int bf = subLR->_bf;
    RotateL(subL);
    RotateR(parent);

    // 左单旋和右单旋将相关结点的平衡因子改为1，但是双旋并不是这样，需要另外修改平衡因子，分为三种情况
    // 1. 旋转前subLR->_bf == 0: h == 0, 修改为 p:0, subL:0, subLR:0
    // 2. 旋转前subLR->_bf == 1: h > 0, 插入的为subLR左子树，修改为 p:-1, subL:0, subLR:0
    // 3. 旋转前subLR->_bf == -1: h > 0, 插入的为subLR右子树，修改为 p:0, subL:1, subLR:0
    if (bf == 0)
    {
      parent->_bf = 0;
      subL->_bf = 0;
      subLR->_bf = 0;
    }
    else if (bf == 1)
    {
      parent->_bf = -1;
      subL->_bf = 0;
      subLR->_bf = 0;
    }
    else if (bf == -1)
    {
      parent->_bf = 0;
      subL->_bf = 1;
      subLR->_bf = 0;
    }
    else
    {
      assert(false);
    }
  }

  // RL型右左双旋
  void RotateRL(Node *parent)
  {
    Node *subR = parent->_right;
    Node *subRL = subR->_left;
    int bf = subRL->_bf;

    RotateR(subR);
    RotateL(parent);

    if (bf == 0)
    {
      parent->_bf = 0;
      subR->_bf = 0;
      subRL->_bf = 0;
    }
    else if (bf == 1)
    {
      parent->_bf = 0;
      subR->_bf = -1;
      subRL->_bf = 0;
    }
    else if (bf == -1)
    {
      parent->_bf = 1;
      subR->_bf = 0;
      subRL->_bf = 0;
    }
    else
    {
      assert(false);
    }
  }

  bool IsBalance()
  {
    int height = 0;
    return _IsBalance(_root, height);
  }

private:
  void _InOrder(Node *root)
  {
    if (root == nullptr)
      return;

    _InOrder(root->_left);
    cout << root->_kv.first << " ";
    _InOrder(root->_right);
  }

  bool _IsBalance(Node *root, int &height)
  {
    if (root == nullptr)
    {
      height = 0;
      return true;
    }

    int leftHeight = 0, rightHeight = 0;
    if (!_IsBalance(root->_left, leftHeight) || !_IsBalance(root->_right, rightHeight))
    {
      return false;
    }

    if (abs(leftHeight - rightHeight) >= 2)
    {
      cout << "不平衡" << endl;
      return false;
    }

    if (leftHeight - rightHeight != root->_bf)
    {
      cout << "平衡因子失效" << endl;
      return false;
    }

    height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

    return true;
  }
  Node *_root = nullptr;
};

void TestAVLTree1()
{
  // int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
  int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
  AVLTree<int, int> t;
  for (auto e : a)
  {
    if (e == 14)
    {
      int x = 0;
    }

    t.Insert(make_pair(e, e));

    // 1、先看是插入谁导致出现的问题
    // 2、打条件断点，画出插入前的树
    // 3、单步跟踪，对比图一一分析细节原因
    cout << e << "->" << t.IsBalance() << endl;
  }

  t.InOrder();
  cout << t.IsBalance() << endl;
}