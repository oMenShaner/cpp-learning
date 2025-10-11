#pragma once
#include "Hash.h"

namespace omen {
    template<class K, class Hash = HashFunc<K>>
    class unordered_set {
        struct SetKeyOfT {
            const K& operator()(const K& key)
            {
                return key;
            }
        };

	public:
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::Iterator iterator;
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::ConstIterator const_iterator;

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

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
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
        hash_bucket::HashTable<K, const K, SetKeyOfT, Hash> _ht;
    };

	void Func(const unordered_set<int>& s)
	{
		auto it1 = s.begin();
		while (it1 != s.end())
		{
			// *it1 = 1;

			cout << *it1 << " ";
			++it1;
		}
		cout << endl;
	}

	void test_uset()
	{
		unordered_set<int> s1;
		s1.insert(45);
		s1.insert(5);
		s1.insert(13);
		s1.insert(45);
		s1.insert(452);
		s1.insert(4513);
		s1.insert(333);
		s1.insert(123);

		Func(s1);


		auto it1 = s1.begin();
		while (it1 != s1.end())
		{
			cout << *it1 << " ";
			++it1;
		}
		cout << endl;
	}
}