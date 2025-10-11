#pragma once
#include "Hash.h"

namespace omen {
    template<class K, class V, class Hash = HashFunc<K>>
    class unordered_map {
        struct MapKeyOfT {
            const K& operator()(const pair<K, V>& kv)
            {
                return kv.first;
            }
        };
    public:
        typedef typename hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash>::Iterator iterator;
		typedef typename hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash>::ConstIterator const_iterator;

		iterator begin() 
		{
			return _ht.Begin();
		}

		iterator end() 
		{
			return _ht.End();
		}

		const_iterator begin() const
		{
			return _ht.Begin();
		}

		const_iterator end() const
		{
			return _ht.End();
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert({ key, V() });
			return ret.first->second;
		}

		pair<iterator, bool> insert(const pair<K, V> kv)
		{
			return _ht.Insert(kv);
		}

		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

		iterator Find(const K& key)
		{
			return _ht.Find(key);
		}
    private:
        hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash> _ht;
    };

	void test_umap()
	{
		unordered_map<string, string> dict;
		dict.insert({ "insert", "≤Â»Î" });
		dict.insert({ "sort", "≈≈–Ú" });
		dict.insert({ "test", "≤‚ ‘" });

		for (auto& [k, v] : dict)
		{
			// k += 'x';

			cout << k << ":" << v << endl;
		}

		dict["string"] = "◊÷∑˚¥Æ";
		dict["key"];
		dict["key"] = "πÿº¸◊÷";
		dict["for"];


		for (auto& [k, v] : dict)
		{
			cout << k << ":" << v << endl;
		}
	}
}