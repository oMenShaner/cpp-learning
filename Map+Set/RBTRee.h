#pragma once
#include <iostream>
using namespace std;

// 枚举值表示颜色
enum Colour {
    RED,
    BLACK
};

template<class T>
struct RBTreeNode
{
    T _data;
    RBTreeNode<T>* _left;
    RBTreeNode<T>* _right;
    RBTreeNode<T>* _parent;
    Colour _col;
    RBTreeNode(const T& data)
        : _data(data)
        , _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
        , _col(RED)
    {
    }
};

template<class T,class Ref, class Ptr>
class TreeIterator {
    typedef RBTreeNode<T> Node;
    typedef TreeIterator<T, Ref, Ptr> Self;
    Node* _node;
    Node* _root;
public:
    TreeIterator(Node *node, Node *root)
        :_node(node)
        ,_root(root)
    { }

    Ref operator*()
    {
        return _node->_data;
    }

    Ptr operator->()
    {
        return &(_node->_data);
    }

    bool operator!=(const Self& s)const
    {
        return _node != s._node;
    }

    bool operator==(const Self& s)const
    {
        return _node == s._node;
    } 

    Self& operator--()
    {
        // 当前节点为空
        // 当前结点左不为空,下一个是其左子树的最大结点
        // 当前结点左为空,下一个是为右孩子的祖先结点
        if (_node == nullptr)
        {
            // --end(),走到中序的最后一个结点
            Node* rightMost = _root;
            while (rightMost && rightMost->_right)
            {
                rightMost = rightMost->_right;
            }
            _node = rightMost;
        }
        else if (_node->_left)
        {
            Node* cur = _node->_left;
            while (cur->_right)
            {
                cur = cur->_right;
            }
            _node = cur;
        }
        else
        {
            Node* cur = _node;
            Node* parent = cur->_parent;
            while (parent && cur == parent->_left)
            {
                cur = parent;
                parent = parent->_parent;
            }
            _node = parent;
        }
        return *this;
    }
    Self& operator++()
    {
        // 当前结点右不为空,下一个是当前结点右子树的最小结点
        // 当前结点右为空,下一个是为左孩子的祖先节点
        if (_node->_right)
        {
            Node* cur = _node->_right;
            while (cur->_left)
            {
                cur = cur->_left;
            }
            _node = cur;
        }
        else
        {
            Node* cur = _node;
            Node* parent = cur->_parent;
            while (parent && cur == parent->_right)
            {
                cur = parent;
                parent = parent->_parent;
            }
            _node = parent;
        }
        return *this;
    }
};

template<class K, class T, class KeyOfT>
class RBTree
{
public:
    typedef typename RBTreeNode<T> Node;
    typedef typename TreeIterator<T, T&, T*> Iterator;
public:
    Iterator Begin()
    {
        Node* min = _root;
        while (min && min->_left)
        {
            min = min->_left;
        }
        return Iterator(min, _root);
    }

    Iterator End()
    {
        return Iterator(nullptr, _root);
    }

    pair<Iterator, bool>Insert(const T& data)
    {
        KeyOfT kot;
        // 1.树为空，直接赋值
        if (_root == nullptr)
        {
            _root = new Node(data);
            _root->_col = BLACK;

            return {Iterator(_root, _root), true};
        }

        // 2.树非空，根据二叉搜索树规则找到对应插入位置
        Node* cur = _root;
        Node* parent = nullptr;
        while (cur)
        {
            if (kot(data) < kot(cur->_data))
            {
                parent = cur;
                cur = cur->_left;
            }
            else if (kot(data) > kot(cur->_data))
            {
                parent = cur;
                cur = cur->_right;
            }
            else
            {
                return { Iterator(cur, _root), false };
            }
        }

        // 默认新结点为红，同时更新其parent指针
        cur = new Node(data);
        Node* newNode = cur;
        cur->_col = RED;
        if (kot(data) < kot(parent->_data))
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
        return { Iterator(newNode, _root), true };
    }

    Iterator Find(const K& key)
    {
        KeyOfT kot;
        Node* cur = _root;
        while (cur)
        {
            if (key < kot(cur->_data))
            {
                cur = cur->_left;
            }
            else if (key > kot(cur->_data))
            {
                cur = cur->_right;
            }
            else
            {
                return Iterator(cur, _root);
            }
        }
        return Iteraotr(nullptr, _root);
    }
    
private:
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
            subL->_parent = nullptr;
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