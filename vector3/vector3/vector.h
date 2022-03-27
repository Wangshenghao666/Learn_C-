#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
#include<string>
using namespace std;

//vector��ģ��ʵ��
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
		{}
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}
		/*���
		v2(v1) ��ͳд��
		vector(const vector<int>& v)
		{
			_start = new T[v.capacity()];
			_finish = _start + v.size();
			_endofstorage = _start + v.capacity();

			memcpy(_start, v._start, sizeof(T)*size());
		}*/
		//�ִ�д��������Ĺ��캯����û�в���������һ���������汾�Ĺ��캯��
		//һ��ģ��ĳ�Ա�������ֿ�����һ����Ա����
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		//��װswap
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		//v2(v1)
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			vector<T> tmp(v.begin(), v.end());
			/*swap(_start, tmp._start);
			swap(_finish, tmp._finish);
			swap(_endofstorage, tmp._endofstorage);*/
			swap(tmp);//this->swap(tmp)
		}
		//v1 = v3
		vector<T>& operator=(vector<T> v)
		{
			/*swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endofstorage, v._endofstorage);*/
			swap(v);//tish->swap(v)
			return *this;
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

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					//memcpy(tmp, _start, sizeof(T)*size());
					for (size_t i = 0; i < sz; ++i)
					{
						// T ��int��һ��һ������û����
						// T ��string�� һ��һ������������T�������ֵ��Ҳû����
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}
		void resize(size_t n, const T& val = T())//const T& val = T() ����ȱʡֵ �� �������� const���ӳ���������
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}
				while (_finish != _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}
		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish = x;
			++_finish;
		}
		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
		}





		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			//���˻�����
			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;

			return pos;
		}



		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			iterator begin = pos + 1;

			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;
			return pos;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
	void test_vector1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);

		for (size_t i = 0; i < v.size(); ++i)
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
	void test_vector3()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int> v2(v1);
		for (auto e : v2)
		{
			cout << e << " ";
		}
		cout << endl;
		vector<int> v3;
		v3.push_back(5);
		v3.push_back(6);
		v3.push_back(7);
		v3.push_back(8);
		v1 = v3;
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void test_vector4()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		//123��û����ģ�����1234�ͻ�������⣺
		//�����ǵ�����ʧЧ�����˻����ݣ��Ѿɵ����ݿ������µĿռ䣬�ɿռ�ᱻ�ͷţ�*pos����Ұָ��
		//���Կ���ʹ�÷���ֵ�ķ�ʽ  ���ݻᵼ��posʧЧ������һ��posֵ
		v1.push_back(4);
		vector<int>::iterator it = find(v1.begin(), v1.end(), 2);
		if (it != v1.end())
		{
			v1.insert(it, 20);
		}
		for (auto& e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void test_vector5()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);

		vector<int>::iterator it = find(v1.begin(), v1.end(), 2);
		if (it != v1.end())
		{
			v1.erase(it);
		}
		for (auto& e : v1)
		{
			cout << e << " ";
		}
		cout << endl;


		//eraseҲ���е�����ʧЧ��ʱ��
		//Ҫ��ɾ��n���е�ż��
	/*	vector<int>::iterator it = v1.begin();
		while (it != v1.end())
		{
			if (*it % 2 == 0)
			{
				v1.erase(it);
			}
			++it;
		}*/
		//�������⣺�����12345 ǡ������
		//����ǣ�1234   �����
		//����ǣ�1245   �������ȷ


		//������
		//
		vector<int>::iterator it = v1.begin();
		while (it != v1.end())
		{
			if (*it % 2 == 0)
			{
				it = v1.erase(it);//erase�Ժ�ITʧЧ��������һ������λ�õĵ�����
			}
			else
			{
				++it;
			}
		}
	}
	void test_vector6()
	{
		vector<string> v;
		v.push_back("11111111111");
		v.push_back("11111111111");
		v.push_back("11111111111");
		v.push_back("11111111111");
		v.push_back("11111111111");

		for (auto& e : v)
		{
			cout << e << " ";
		}
		cout << endl;
		//�����ӡ��5�λ��������Ϊ������������
		//memcpy�У�string����������ǳ������

		//������治ʹ��memcpy
	}
}