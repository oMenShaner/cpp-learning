#pragma once

// ö��ֵ��ʾ��ɫ
enum Colour {
    RED,
    BLACK
};

// Ĭ����key/value�ṹʵ��
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
        // 1.��Ϊ�գ�ֱ�Ӹ�ֵ
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK;

            return true;
        }

        // 2.���ǿգ����ݶ��������������ҵ���Ӧ����λ��
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

        // Ĭ���½��Ϊ�죬ͬʱ������parentָ��
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
                cout << "��ɫ�ڵ�����������" << endl;
                return false;
            }
            return true;
        }
        if (cur->_col == RED && cur->_parent->_col == RED)
        {
            cout << cur->_kv.first << "->" << "�����ĺ�ɫ�ڵ�" << endl;
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