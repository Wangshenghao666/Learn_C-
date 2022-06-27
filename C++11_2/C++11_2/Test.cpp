#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<assert.h>
using namespace std;

// ����ȡ��ַ���󣬾�����ֵ
int main()
{
	int a = 10;
	int& r1 = a;
	int* p = &a;
	int& r2 = *p;

	const int b = 10;
	const int& r3 = b;

	return 0;
}

// ����ȡ��ַ���󣬾�����ֵ
int main()
{
	double x = 1.1, y = 2.2;

	// ���¼������ǳ�������ֵ
	//���泣�������ʽ����ֵ����ֵ���غ����ķ���ֵ
	10;
	x + y;
	fmin(x, y);

	//cout << &fmin(x, y) << endl;

	// ���¼������Ƕ���ֵ����ֵ����
	int&& rr1 = 10;
	double&& rr2 = x + y;
	double&& rr3 = fmin(x, y);

	return 0;
}



 //��������
 //��ֵ�����ܷ�������ֵ
 //��ֵ�����ܷ�������ֵ
int main()
{
	// ���¼������ǳ�������ֵ
	double x = 1.1, y = 2.2;
	10;
	x + y;
	fmin(x, y);

	// ���µ�p��b��c��*p������ֵ
	int* p = new int(0);
	int b = 1;
	const int c = 2;

	// ��ֵ�����ܷ�������ֵ -- ����ֱ�����ã�����const ��ֵ���ÿ���������ֵ
	// void push_back(const T& x)
	const int& r1 = 10;
	const double& r2 = x+y;
	const double& r3 = fmin(x, y);

	// ��ֵ�����ܷ�������ֵ -- ����ֱ�����ã����ǿ�����ֵ���ÿ�������move�Ժ���ֵ
	int*&& rr1 = move(p);
	int&& rr2 = move(*p);
	int&& rr3 = move(b);
	const int&& rr4 = move(c);

	return 0;
}



namespace bit
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str)" << endl;

			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		 s1.swap(s2)
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}

		 ��������
		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			cout << "string(const string& s) -- ���" << endl;

			string tmp(s._str);
			swap(tmp);
		}

		 �ƶ�����
		string(string&& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			cout << "string(string&& s) -- ��Դת��" << endl;

			this->swap(s);
		}

		 ��ֵ����
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- ת����Դ" << endl;
			swap(s);

			return *this;
		}
		string& operator=(const string& s)
		{
			cout << "string& operator=(string s) -- ���" << endl;
			string tmp(s);
			swap(tmp);

			return *this;
		}

		~string()
		{
			cout << "~string()" << endl;

			delete[] _str;
			_str = nullptr;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;

				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		string operator+=(char ch)
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string operator+(char ch)
		{
			string tmp(*this);
			push_back(ch);

			return tmp;
		}

		const char* c_str() const
		{
			return _str;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity; // �������������ʶ��\0
	};
}

 //����1
 //��ֵ���������������������Ľ����������
void func1(bit::string s)
{}

void func2(const bit::string& s)
{}

 //����2
 //��ֵ����������ֵ��ֻ�ܽ����������
 //string& operator+=(char ch) �����
 //string operator+(char ch)   û�н��

 //��ֵ���ã���ν��operator+��ֵ���ش��ڿ����������أ�
 //C++11 ����ֵ��Ϊ������ֵ������ֵ
bit::string func3()
{
	bit::string str("hello world");
	cin >> str;

	return str;
}

int main()
{
	bit::string str("hello world");
	//func1(str);
	//func2(str);

	/*str += '!';
	str + '!';*/
	func3();

	return 0;
}



int main()
{
	bit::string s1("hello world");
	bit::string s2("xxxx");
	s1 = s2;
	s1 = move(s2);

	return 0;
}
