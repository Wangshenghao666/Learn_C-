#pragma once


template<class K>
struct Hash
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

// 特化
template<>
struct Hash < string >
{
	size_t operator()(const string& s)
	{
		// BKDR
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};
template<class K, class V>
struct HashNode
{
	pair<K, V> _kv;
	HashNode<K, V>* _next;

	HashNode(const pair<K, V>& kv)
		:_kv(kv)
		, _next(nullptr)
	{}
};

template<class K, class V, class HashFunc = Hash<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	bool Erase(const K& key)
	{
		if (_tables.empty())
		{
			return false;
		}

		HashFunc hf;
		size_t index = hf(key) % _tables.size();
		Node* prev = nullptr;
		Node* cur = _tables[index];
		while (cur)
		{
			if (cur->_kv.first == key)
			{
				if (prev == nullptr) // 头删
				{
					_tables[index] = cur->_next;
				}
				else // 中间删除
				{
					prev->_next = cur->_next;
				}

				--_n;

				delete cur;

				return true;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}

		return false;
	}

	Node* Find(const K& key)
	{
		if (_tables.empty())
		{
			return nullptr;
		}

		HashFunc hf;
		size_t index = hf(key) % _tables.size();
		Node* cur = _tables[index];
		while (cur)
		{
			if (cur->_kv.first == key)
			{
				return cur;
			}
			else
			{
				cur = cur->_next;
			}
		}

		return nullptr;
	}

	bool Insert(const pair<K, V>& kv)
	{
		Node* ret = Find(kv.first);
		if (ret)
			return false;

		HashFunc hf;
		// 负载因子 == 1时扩容
		if (_n == _tables.size())
		{
			size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			vector<Node*> newTables;
			newTables.resize(newSize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;

					size_t index = hf(cur->_kv.first) % newTables.size();
					// 头插
					cur->_next = newTables[index];
					newTables[index] = cur;

					cur = next;
				}

				_tables[i] = nullptr;
			}

			_tables.swap(newTables);
		}

		size_t index = hf(kv.first) % _tables.size();
		Node* newnode = new Node(kv);
		// 头插
		newnode->_next = _tables[index];
		_tables[index] = newnode;

		++_n;
		return true;
	}

private:
	/*struct Data
	{
	forward_list<T> _list;
	set<T> _rbtree;
	size_t _len;
	};
	vector<Data> _tables;*/
	vector<Node*> _tables;

	size_t _n = 0;  // 有效数据的个数
};

void TestHashTable()
{
	int a[] = { 4, 24, 14, 7, 37, 27, 57, 67, 34, 14, 54 };
	HashTable<int, int> ht;
	for (auto e : a)
	{
		ht.Insert(make_pair(e, e));
	}

	ht.Insert(make_pair(84, 84));
}
