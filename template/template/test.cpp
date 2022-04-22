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
};//һ����̬ջ
int main()
{
	Mystack<int> st1;
	Mystack<int> st2;
	//���ﲻ�ܿ���һ��100��һ��200
	return 0;
}



�����������ģ�����--����->���������ͳ�����int��char��long long��

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

��������Ҳ����,Ҳ���Ը�ȱʡ����



//����ģ��--����ƥ��
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
}//����ģ�����棬�����ػ��ܼ���
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
//ȫ�ػ�
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
//ƫ�ػ�
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




//���������ػ���
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
//�����ػ�




