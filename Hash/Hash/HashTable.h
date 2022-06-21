#pragma once
#include<vector>

enum Status
{
	EXIST,
	EMPTY,
	DELETE
};
template<class K,class V>
struct HashData
{
	pair<K, V> _kv;
	Status _status = EMPTY;//标记状态
};


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
//给字符串准备
//struct HashStr
//{
//	size_t operator()(const string& s)
//	{
//		// BKDR
//		size_t value = 0;
//		for (auto ch : s)
//		{
//			value *= 31;
//			value += ch;
//		}
//		return value;
//	}
//};

template<class K,class V,class HashFunc = Hash<K>>
class HashTable
{
private:
	vector<HashData<K, V>> _tables;
	size_t _n = 0;//有效数据个数

public:
	bool Erase(const K& key)
	{
		HashData<K, V>* ret = Find(key);
		if (ret == nullptr)
		{
			return false;
		}
		else
		{
			--_n;
			ret->_status = DELETE;
			return true;
		}
	}

	HashData<K, V>* Find(const K& key)
	{
		if (_tables.size() == 0)
		{
			return nullptr;
		}
		HashFunc hf;
		size_t start = hf(key) % _tables.size();
		size_t i = 0;
		size_t index = start;
		// 线性探测 or 二次探测
		while (_tables[index]._status != EMPTY)
		{
			if (_tables[index]._kv.first == key && _tables[index]._status == EXIST)
			{
				return &_tables[index];
			}

			++i;
			//index = start + i*i;
			index = start + i;

			index %= _tables.size();
		}
		return nullptr;
	}

	bool Insert(const pair<K, V>& kv)
	{
		//有 返回    没有  插入
		HashData<K, V>* ret = Find(kv.first);
		if (ret)
		{
			return false;
		}


		//扩容
		//负载因子到0.7就扩容---越小冲突概率就越低，效率就越高，空间浪费就越多，反之相反。
		if (_tables.size() == 0 || _n * 10 / _tables.size() >= 7)
		{
			//扩容
			size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

			HashTable<K, V,HashFunc> newHT;
			newHT._tables.resize(newSize);
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i]._status == EXIST)
				{
					newHT.Insert(_tables[i]._kv);
				}
			}
			_tables.swap(newHT._tables);
		}
		HashFunc hf;
		size_t start = hf(kv.first) % _tables.size();
		size_t i = 0;
		size_t index = start + i;
		//线性探测
		while (_tables[index]._status == EXIST)
		{
			++i;
			index = start + i;
			//index = start + i*i;//二次线性探测
			index %= _tables.size();
		}
		_tables[index]._kv = kv;
		_tables[index]._status = EXIST;
		++_n;

		return true;
	}
};




void TestHashTable1()
{
	//HashTable<int, int, Hash<int>> ht;
	HashTable<int, int> ht;
	int a[] = { 2, 12, 22, 32, 42, 52, 62 };
	for (auto& e : a)
	{
		ht.Insert(make_pair(e, e));
	}
	ht.Insert(make_pair(72, 72));
	ht.Insert(make_pair(32, 32));

	Hash<int> hs;
	cout << hs(9) << endl;
	cout << hs(-9) << endl;

	cout << ht.Find(12) << endl;
	ht.Erase(12);
	cout << ht.Find(12) << endl;
}

void TestHashTable2()
{
	HashTable<string, string> ht;
	ht.Insert(make_pair("sort", "排序"));
	ht.Insert(make_pair("string", "字符串"));
}
