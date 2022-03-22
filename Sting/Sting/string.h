#pragma once
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string>
#include<iostream>
using namespace std;

namespace zj
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}



		const char* c_str() const
		{
			return _str;
		}
		size_t size() const
		{
			return _size;
		}


		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}



		void swap(string& s)//封装
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		//构造函数
		string(const char* str = "")
			:_size(strlen(str))
			,_capacity(_size)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		~string()
		{
			if (_str)
			{
				delete[] _str;
				_str = nullptr;
			}
		}
		//拷贝构造(复用构造）s2(s1)
		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			string tmp(s._str);
			swap(tmp);//相当于是this->swap(tmp)
		}
		//赋值s1 = s3
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}





		void reserve(size_t n)//扩容
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);//原来的数据拿过来
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			str = nullptr;
			_size += len;
		}
		//+=
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		//resize 没有缩容
		void resize(size_t n, char ch = '\0')
		{
			if (n <= _size)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				memset(_str + _size, ch, n - _size);
				_size = n;
				_str[_size] = '\0';
			}
		}




		//查
		size_t find(char ch)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (ch == _str[i])
				{
					return i;
				}
			}
			return _npos;
		}
		size_t find(const char* s, size_t pos = 0)
		{
			const char* ptr = strstr(_str + pos, s);
			if (ptr == nullptr)
			{
				return _npos;
			}
			else
			{
				return ptr - _str;
			}
		}




		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			if (_size == _capacity)

			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = ch;
			++_size;
			return *this;
		}
		string& insert(size_t pos, const char* s)
		{
			assert(pos <= _size);
			size_t len = strlen(s);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size + len;
			while (end >= pos+len)
			{
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + pos, s, len);
			_size += len;
			return *this;
		}



		//删
		string& erase(size_t pos = 0, size_t len = _npos)
		{
			assert(pos < _size);
			if (len == _npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t _npos;
	};
	const size_t string::_npos = -1;




	bool operator<(const string& s1, const string& s2)
	{
		/*size_t i1 = 0; size_t i2 = 0;
		while (i1 < s1.size() && i2 < s2.size())
		{
			if (s1[i1] < s2[i2])
			{
				return true;
			}
			else if (s1[i1] > s2[i2])
			{
				return false;
			}
			else
			{
				++i1; ++i2;
			}
		}
		return i2 < s2.size() ? true : false;*/
		//简化
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}
	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}
	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;
	}
	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}
	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}
	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}




	//流插入、流提取

	ostream& operator<<(ostream& out, const string& s)
	{
		////1.
		//for (auto ch : s)
		//{
		//	out << ch;
		//}

		//2.
		for (size_t i = 0; i < s.size(); ++i)
		{
			out << s[i];
		}
		return out;
	}
	istream& operator>>(istream& in, string& s)
	{
		char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}
	void test_string1()
	{
		string s1("zhangji");
		string s2(s1);

		string s3("Sort");

	}
	void test_string2()
	{
		string s1("zhangji");
		cout << s1.c_str() << endl;

		for (size_t i = 0; i < s1.size(); ++i)
		{
			cout << s1[i] << " ";
		}
		printf("\n");

		string s2("wangshenghao");
		string::iterator it = s1.begin();
		while (it != s1.end())
		{
			cout << *it << " ";
			++it;
		}
		printf("\n");

		for (auto e : s1)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void test_string3()
	{
		string s1("zhangji");
		s1.push_back(' ');
		s1.push_back('@');
		s1.append("hello bit!!!!!!!!!!!!!!!!!!!!!");
		cout << s1.c_str() << endl;
		printf("------------------------------------\n");
		string s2;
		s2 += 'x';
		s2 += "yz 123";
		cout << s2.c_str() << endl;
	}
	void test_string4()
	{
		string s1("zhangji");
		s1.insert(0, "abc--");
		cout << s1.c_str() << endl;

	}
	void test_string5()
	{
		string s1("hello world");
		s1.erase(5, 2);
		s1.erase(5, 20);
	}
	void test_string6()
	{
		string s1("abcd");
		string s2("abcd");
		cout << (s1 < s2) << endl;
		string s3("abcd");
		string s4("abcde");
		cout << (s3 < s4) << endl;
		string s5("abcde");
		string s6("abcd");
		cout << (s5 < s6) << endl;
	}
	void test_string7()
	{
		string s1;
		cin >> s1;
		cout << s1;
	}
}