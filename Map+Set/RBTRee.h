#pragma once

// ö��ֵ��ʾ��ɫ
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

template<class K, class T, class KeyOfT>
class RBTree
{
    typedef RBTreeNode<T> Node;
public:
    bool Insert(const T& data)
    {
        KeyOfT kot;
        // 1.��Ϊ�գ�ֱ�Ӹ�ֵ
        if (_root == nullptr)
        {
            _root = new Node(data);
            _root->_col = BLACK;

            return true;
        }

        // 2.���ǿգ����ݶ��������������ҵ���Ӧ����λ��
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
                return false;
            }
        }

        // Ĭ���½��Ϊ�죬ͬʱ������parentָ��
        cur = new Node(data);
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

        // ������㼰�丸�ڵ㶼�Ǻ�ɫʱ���������ƽ��
        // ��ʱc(R), p(R), g(B), ����u��ɫ������з���
        while (parent && parent->_col == RED)
        {
            Node* grandparent = parent->_parent;    // grandparent�ض���Ϊ��
            if (grandparent->_left == parent)
            {
                //      g
                //   p     u
                Node* uncle = grandparent->_right;

                // uΪ��ɫ
                if (uncle && uncle->_col == RED)
                {
                    // p��u��Ϊ�ڣ�g��Ϊ�죬��ʱ��gΪ���ڵ������ƽ�⣬�������Ͻ��и���
                    // ��ʱc���������Һ���
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                    grandparent->_col = RED;

                    cur = grandparent;
                    parent = cur->_parent;
                }
                else // uΪ��ɫ�򲻴���
                {
                    // ��ת+��ɫ 
                    // ��ʱc�������Һ���
                    if (cur == parent->_left)
                    {
                        //      g
                        //   p     u
                        // c
                        // ��gΪ��ת������ҵ�����p��ڣ�g��죬��ɫ�������û�б仯��pΪ��ʱ�����������������ɫ��㣬����Ҫ���ϸ��£�
                        RotateR(grandparent);
                        parent->_col = BLACK;
                        grandparent->_col = RED;
                    }
                    else
                    {
                        //      g
                        //   p     u
                        //     c
                        // ��������˫����c��ڣ�g���
                        RotateL(parent);
                        RotateR(grandparent);
                        cur->_col = BLACK;
                        grandparent->_col = RED;
                    }
                    break;  // ����Ҫ���ϸ���
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

                    // ����c��p��������ѭ��
                    cur = grandparent;
                    parent = cur->_parent;
                }
                else // u�����ڻ���Ϊ��
                {
                    if (cur == parent->_right)
                    {
                        //      g
                        //   u     p
                        //            c
                        // ��gΪ��ת�����������g��죬p���
                        RotateL(grandparent);
                        grandparent->_col = RED;
                        parent->_col = BLACK;
                    }
                    else
                    {
                        //      g
                        //   u     p
                        //       c
                        // ������������g��죬c���
                        RotateR(parent);
                        RotateL(grandparent);
                        grandparent->_col = RED;
                        cur->_col = BLACK;
                    }
                    break;
                }
            }
        }

        // ������Σ����ָ��ڵ�Ϊ��
        _root->_col = BLACK;
        return true;
    }
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    Node* Find(const K& key)
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
                return cur;
            }
        }
        return nullptr;
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