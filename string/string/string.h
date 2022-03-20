#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;

//深浅拷贝
1.传统写法
namespace wsh
{
	class string
	{
	public:
		string(const char* str)
			:_str(new char[strlen(str)+1])
		{
			strcpy(_str, str);
		}


		string(const string& s)
			:_str(new char[strlen(s._str)+1])
		{
			strcpy(_str, s._str);
		}

		string& operator=(const string& s)
		{
			/*if (this != &s)
			{
				delete[] _str;
				_str = new char[strlen(s._str) + 1];
				strcpy(_str, s._str);

			}
			return *this;*/
			//改进

			if (this != &s)
			{
				char* tmp = new char[strlen(s._str) + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
			}
			return *this;
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
	private:
		char* _str;
	};



	void test_string1()
	{
		string s1("hello bit");
		string s2(s1);

		string s3("Sort");
		s1 = s3;
	}
}

//2.现代写法
namespace WSH
{
	class string
	{
	public:
		string(const char* str)
			:_str(new char[strlen(str)+1])
		{
			strcpy(_str, str);
		}
		//s2(s1)复用构造
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
		}
		//s1 = s3复用拷贝构造
		//string& operator=(const string& s)
		//{
		//	/*if (this != &s)
		//	{
		//		string tmp(s);
		//		swap(_str, tmp._str);
		//	}
		//	return *this;*/

		//}


		//简化
		string& operator=(string s)
		{
			swap(_str, s._str);
			return *this;
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
	private:
		char* _str;
	};
	void test_string1()
	{
		string s1("wangshenghao");
		string s2(s1);
		string s3("zhangjin");
		s1 = s3;
	}
}