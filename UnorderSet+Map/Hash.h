#pragma once
#include<vector>

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

template<>
struct HashFunc<string>
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto ch : str)
		{
			hash += ch;
			hash *= 131;
		}

		return hash;
	}
};

inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] =
	{
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

namespace hash_bucket
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{
		}
	};

	// 声明
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
	struct HTIterator {
		typedef HashNode<T> Node;
		typedef HTIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		Node* _node;
		const HashTable<K, T, KeyOfT, Hash>* _pht;

		HTIterator(Node* node, const HashTable<K, T, KeyOfT, Hash>* pht)
			:_node(node)
			,_pht(pht)
		{ }

		Ref operator*()
		{
			return _node->_data;
		}
		
		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s) const
		{
			return s._node != _node;
		}
		
		bool operator==(const Self& s) const
		{
			return s._node == _node;
		}

		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfT kot;
				Hash hs;
				size_t hashi = hs(kot(_node->_data)) % _pht->_tables.size();
				++hashi;
				while (hashi < _pht->_tables.size())
				{
					if (_pht->_tables[hashi])
					{
						break;
					}
					++hashi;
				}

				if (hashi == _pht->_tables.size())
				{
					_node = nullptr;
				}
				else
				{
					_node = _pht->_tables[hashi];
				}
			}

			return *this;
		}
	};

	template<class K, class T, class KeyOfT, class Hash>
	class HashTable
	{
		typedef HashNode<T> Node;
		// 友元声明,迭代器才能取到HashTable的私有对象
		template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
		friend struct HTIterator;

	public:
		typedef HTIterator<K, T, T&, T*, KeyOfT, Hash> Iterator;
		typedef HTIterator<K, T, const T&, const T*, KeyOfT, Hash> ConstIterator;

		Iterator Begin() 
		{
			if (_n == 0)
			{
				return End();
			}
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return Iterator(cur, this);
				}
			}
			return End();
		}

		Iterator End() 
		{
			return Iterator(nullptr, this);
		}

		ConstIterator Begin() const
		{
			if (_n == 0)
			{
				return End();
			}
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return ConstIterator(cur, this);
				}
			}
			return End();
		}

		ConstIterator End() const
		{
			return ConstIterator(nullptr, this);
		}

		HashTable()
			:_tables(__stl_next_prime(1), nullptr)
			, _n(0)
		{
		}

		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				// 当前桶的节点重新映射挂到新表
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}

				_tables[i] = nullptr;
			}
		}

		pair<Iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;
			auto it = Find(kot(data));
			if (it != End())
				return { it, false };

			Hash hs;
			// 负载因子==1扩容
			if (_n == _tables.size())
			{
				vector<Node*> newtables(__stl_next_prime(_tables.size() + 1));
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					// 当前桶的节点重新映射挂到新表
					while (cur)
					{
						Node* next = cur->_next;

						// 插入到新表
						size_t hashi = hs(kot(cur->_data)) % newtables.size();
						cur->_next = newtables[hashi];
						newtables[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;
				}

				_tables.swap(newtables);
			}

			size_t hashi = hs(kot(data)) % _tables.size();
			// 头插
			Node* newNode = new Node(data);
			newNode->_next = _tables[hashi];
			_tables[hashi] = newNode;

			++_n;
			return { Iterator(newNode, this), true};
		}

		Iterator Find(const K& key)
		{
			KeyOfT kot;
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
					return { cur, this };

				cur = cur->_next;
			}

			return { nullptr, this };
		}

		bool Erase(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;

					return true;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n = 0;  // 实际存储的数据个数
	};
}