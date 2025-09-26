#pragma once
#include "RBTree.h"

namespace omen
{
    template<class K, class V>
    class map {
        struct MapKeyOfT
        {
            const K& operator()(const pair<K, V> &kv)
            {
                return kv.first;
            }
        };
    public:
        typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::Iterator iterator;

        iterator begin()
        {
            return _m.Begin();
        }

        iterator end()
        {
            return _m.End();
        }

        pair<iterator, bool> insert(const pair<K, V>& kv)
        {
            return _m.Insert(kv);
        }

        V& operator[](const K& key)
        {
            pair<iterator, bool> ret = insert({ key, V() });
            return ret.first->second;
        }
    private:
        RBTree<K, pair<const K, V>, MapKeyOfT> _m;
    };

}
