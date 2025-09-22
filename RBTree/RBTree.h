#pragma once

// 枚举值表示颜色
enum Colour {
    RED,
    BLACK
};

// 默认用key/value结构实现
template<class K, class V>
struct RBTreeNode 
{
    pair<K, V> _kv; 
    RBTreeNode<K, V> *_left;
    RBTreeNode<K, V> *_right;
    RBTreeNode<K, V>* _parent;
    Colour _col;
    RBTreeNode(const pair<K, V>& kv)
        :_kv(kv)
        ,_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_col(RED)
    {}
};

template<class K, class V>
class RBTree 
{
    typedef RBTreeNode<K, V> Node;
public:
    bool Insert(const pair<K, V> &kv)
    {
        // 1.树为空，直接赋值
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK;

            return true;
        }

        // 2.树非空，根据二叉搜索树规则找到对应插入位置
        Node* cur = _root;
        Node* parent = nullptr;
        while (cur)
        {
            if (kv.first < cur->_kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else if (kv.first > cur->_kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else
            {
                return false;
            }
        }

        // 默认新结点为红，同时更新其parent指针
        cur = new Node(kv);
        cur->_col = RED;
        if (kv.first < parent->_kv.first)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }
        cur->_parent = parent;

        // 新增结点及其父节点都是红色时，红黑树不平衡
        // 此时c(R), p(R), g(B), 根据u颜色情况进行分类
        while (parent && parent->_col == RED)
        {
            Node* grandparent = parent->_parent;    // grandparent必定不为空
            if (grandparent->_left == parent)
            {
                //      g
                //   p     u
                Node* uncle = grandparent->_right;
                
                // u为红色
                if (uncle && uncle->_col == RED)
                {
                    // p，u变为黑，g变为红，此时以g为根节点的子树平衡，继续向上进行更新
                    // 此时c不区分左右孩子
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                    grandparent->_col = RED;

                    cur = grandparent;
                    parent = cur->_parent;
                }
                else // u为黑色或不存在
                {
                    // 旋转+变色 
                    // 此时c区分左右孩子
                    if (cur == parent->_left)
                    {
                        //      g
                        //   p     u
                        // c
                        // 以g为旋转点进行右单旋，p变黑，g变红，黑色结点数量没有变化，p为黑时不会出现连续两个红色结点，不需要向上更新，
                        RotateR(grandparent);
                        parent->_col = BLACK;
                        grandparent->_col = RED;
                    }
                    else
                    {
                        //      g
                        //   p     u
                        //     c
                        // 进行左右双旋，c变黑，g变红
                        RotateL(parent);
                        RotateR(grandparent);
                        cur->_col = BLACK;
                        grandparent->_col = RED;
                    }
                    break;  // 不需要向上更新
                }
            }
            else
            {
                //      g
                //   u     p
                Node* uncle = grandparent->_left;
                if (uncle && uncle->_col == RED)
                {
                    uncle->_col = BLACK;
                    parent->_col = BLACK;
                    grandparent->_col = RED;

                    // 更新c，p，不跳出循环
                    cur = grandparent;
                    parent = cur->_parent;
                }   
                else // u不存在或者为黑
                {
                    if (cur == parent->_right)
                    {
                        //      g
                        //   u     p
                        //            c
                        // 以g为旋转点进行左单旋，g变红，p变黑
                        RotateL(grandparent);
                        grandparent->_col = RED;
                        parent->_col = BLACK;
                    }
                    else
                    {
                        //      g
                        //   u     p
                        //       c
                        // 进行右左旋，g变红，c变黑
                        RotateR(parent);
                        RotateL(grandparent);
                        grandparent->_col = RED;
                        cur->_col = BLACK;
                    }
                    break;
                }
            }
        }

        // 不论如何，保持根节点为黑
        _root->_col = BLACK;
        return true;
    }
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }
    int Size()
    {
        return _Size(_root);
    }
    int Height()
    {
        return _Height(_root);
    }
    Node* Find(const K& key)
    {
        Node* cur = _root;
        while (cur)
        {
            if (key < cur->_kv.first)
            {
                cur = cur->_left;
            }
            else if (key > cur->_kv.first)
            {
                cur = cur->_right;
            }
            else
            {
                return cur;
            }
        }
        return nullptr;
    }
    bool IsBalance()
    {
        if (_root == nullptr)
            return true;
        if (_root->_col == RED)
            return false;

        Node* cur = _root;
        int blackNumRef = 0;
        while (cur)
        {
            if (cur->_col == BLACK)
                ++blackNumRef;
            cur = cur->_left;
        }

        return Check(_root, 0, blackNumRef);
    }
private:
    void _InOrder(Node* root)
    {
        if (root == nullptr)
            return;
        _InOrder(root->_left);
        cout << root->_kv.first << " ";
        _InOrder(root->_right);
    }
    int _Size(Node* root)
    {
        return root == nullptr ? 0 : _Size(root->_left) + _Size(root->_right) + 1;
    }
    int _Height(Node* root)
    {
        if (root == nullptr)
            return 0;
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }
    bool Check(Node* cur, int blackNum, const int blackNumRef)
    {
        if (cur == nullptr)
        {
            if (blackNum != blackNumRef)
            {
                cout << "黑色节点的数量不相等" << endl;
                return false;
            }
            return true;
        }
        if (cur->_col == RED && cur->_parent->_col == RED)
        {
            cout << cur->_kv.first << "->" << "连续的红色节点" << endl;
            return false;
        }
        if (cur->_col == BLACK)
            ++blackNum;
        return Check(cur->_left, blackNum, blackNumRef)
            && Check(cur->_right, blackNum, blackNumRef);
    }
    void RotateR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;
        if (subLR)
            subLR->_parent = parent;

        Node* parentParent = parent->_parent;

        subL->_right = parent;
        parent->_parent = subL;

        if (parent == _root)
        {
            _root = subL;
            subL -> _parent = nullptr;
        }
        else
        {
            if (parentParent->_left == parent)
            {
                parentParent->_left = subL;
            }
            else
            {
                parentParent->_right = subL;
            }
        }

        subL->_parent = parentParent;
    }
    void RotateL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        parent->_right = subRL;
        if (subRL)
            subRL->_parent = parent;

        Node* parentParent = parent->_parent;
        subR->_left = parent;
        parent->_parent = subR;

        if (parent == _root)
        {
            _root = subR;
            subR->_parent = nullptr;
        }
        else
        {
            if (parentParent->_left == parent)
            {
                parentParent->_left = subR;
            }
            else
            {
                parentParent->_right = subR;
            }
        }

        subR->_parent = parentParent;
    }
private:
    Node* _root = nullptr;
};