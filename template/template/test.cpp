#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

#define N 100
template<class T>
class Mystack
{
public:
	void Push(const T& x)
	{
		//...
	}
private:
	T _a[N];
	size_t _top;
};//一个静态栈
int main()
{
	Mystack<int> st1;
	Mystack<int> st2;
	//这里不能控制一个100，一个200
	return 0;
}



解决：非类型模板参数--常量->必须是整型常量（int、char、long long）

template<class T,size_t N>
class Mystack
{
public:
	void Push(const T& x)
	{
		//...
	}
private:
	T _a[N];
	size_t _top;
};
int main()
{
	Mystack<int, 100> st1;
	Mystack<int, 200> st2;
	return 0;
}

不带类型也可以,也可以给缺省参数



//函数模板--参数匹配
template<class T>
bool objLess(const T& left, const T& right)
{
	return left < right;
}
bool objLess(const Data*& left, const Data*& right)
{
	return *left < *right;
}
bool objLess<Data*>(const Data* left, const Data* right)
{
	return *left < *right;
}//函数模板里面，这种特化很鸡肋
int main()
{
	cout << objLess(1, 2) << endl;
	Data* p1 = new Data(2022, 3, 26);
	Data* p2 = new Data(2022, 4, 26);
	cout << objLess(p1, p2) << endl;
	return 0;
}



template<class T1,class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2>" << endl;
	}
private:
	T1 _d1;
	T2 _d2;
};
//全特化
template<>
class Data<int, char>
{
public:
	Data()
	{
		cout << "Data<int.char>" << endl;
	}
private:
};
//偏特化
template<class T1>
class Data<T1, char>
{
public:
	Data()
	{
		cout << "Data<T1,char>" << endl;
	}
private:
};
template<class T1,class T2>
class Data<T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*,T2*>" << endl;
	}
private:
};
template<class T1, class T2>
class Data<T1&, T2&>
{
public:
	Data()
	{
		cout << "Data<T1&,T2&>" << endl;
	}
private:
};
int main()
{
	Data<int, int> d1;
	Data<int, char> d2;
	Data<char, char> d3;
	Data<double, char> d4;
	Data<double*, char*> d5;
	Data<char*, char*> d6;
	Data<char&, char&> d7;
	return 0;
}




//非类型能特化吗？
//eg:
template<size_t N>
class A
{
public:
	A()
	{
		cout << "A<N>" << endl;
	}
};
template<>
class A<10>
{
public:
	A()
	{
		cout << "A<10>" << endl;
	}
};
int main()
{
	A<100> aa1;
	A<10> aa2;
	return 0;
}
//可以特化




