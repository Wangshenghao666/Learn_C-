#pragma once
#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;
//框架的基本实现
namespace wsh
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef T* const_iterator;
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{

		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endofstorage - _start;
		}
		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				//kuorong
				size_t newcpacity = capacity() == 0 ? 4 : capacity() * 2;
				size_t sz = size();
				T* tmp = new T[newcpacity];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T)*size());
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + newcpacity;
			}
			*_finish = x;
			++_finish;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
	void test()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		for (size_t i = 0; i < v.size(); i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	
}