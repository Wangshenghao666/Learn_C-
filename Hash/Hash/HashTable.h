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
	Status _status = EMPTY;//���״̬
};


template<class K>
struct Hash
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
// �ػ�
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
//���ַ���׼��
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
	size_t _n = 0;//��Ч���ݸ���

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
		// ����̽�� or ����̽��
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
		//�� ����    û��  ����
		HashData<K, V>* ret = Find(kv.first);
		if (ret)
		{
			return false;
		}


		//����
		//�������ӵ�0.7������---ԽС��ͻ���ʾ�Խ�ͣ�Ч�ʾ�Խ�ߣ��ռ��˷Ѿ�Խ�࣬��֮�෴��
		if (_tables.size() == 0 || _n * 10 / _tables.size() >= 7)
		{
			//����
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
		//����̽��
		while (_tables[index]._status == EXIST)
		{
			++i;
			index = start + i;
			//index = start + i*i;//��������̽��
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
	ht.Insert(make_pair("sort", "����"));
	ht.Insert(make_pair("string", "�ַ���"));
}
