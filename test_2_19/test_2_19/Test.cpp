#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

// Type
// ����ģ��
//template<class T1, class T2> // template<typename T> // ģ������б� -- ��������
template<class T>
void Swap(T& x1, T& x2) // ���������б� -- ��������
{
	T x = x1;
	x1 = x2;
	x2 = x;
}

int main()
{
	int a = 0, b = 1;
	double c = 1.1, d = 2.22;
	Swap(a, b);
	Swap(c, d);

	char e = 'A', f = 'B';
	Swap(e, f);

	//auto x = 1;

	return 0;
}
ģ�����ʵ������Ϊ����ʽʵ��������ʾʵ����
��ʽ��
template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}
int main()
{
	int a1 = 10;
	int a2 = 20;
	double a3 = 10.1;
	double a4 = 20.2;
	cout << Add(a1, a2) << endl;
	cout << Add(a3, a4) << endl;
	//cout << Add(a1, a3) << endl;//��ʽ����ͬ������ǿת����
	cout << Add((double)a1, a3) << endl;
	cout << Add<int>(a1, a3) << endl;

}
//��ʾ��
   // cout << Add<int>(a1, a3) << endl;��ʾ�ں�������<>ָ������


//ר�Ŵ���int�ӷ��ĺ���
int Add(int left, int right)
{
	return left + right;
}
//ͨ�üӷ�����
template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}
int main()
{
	int a1 = 10;
	int a2 = 20;
	double a3 = 10.1;
	double a4 = 20.2;
	cout << Add(a1, a2) << endl;//���ȵ���ͨ����
	cout << Add(a3, a4) << endl;
	cout << Add((double)a1, a3) << endl;
	cout << Add<int>(a1, a3) << endl;

}



typedef int STDataType;
//typedef double STDataType;

class StackInt
{
public:
	StackInt(int capacity = 4)
		:_top(0)
		, _capacity(capacity)
	{
		_a = new STDataType[capacity];
	}

	~StackInt()
	{
		delete[] _a;
		_a = nullptr;
		_capacity = _top = 0;
	}

private:
	int* _a;
	int _top;
	int _capacity;
};
class StackDouble
{
public:
	StackDouble(int capacity = 4)
		:_top(0)
		, _capacity(capacity)
	{
		_a = new STDataType[capacity];
	}

	~StackDouble()
	{
		delete[] _a;
		_a = nullptr;
		_capacity = _top = 0;
	}

private:
	doub* _a;
	int _top;
	int _capacity;
};
int main()
{
	Stack s1;
	Stack s2;
	return 0;
}
����дջ��һ������дһ���е��鷳
������ģ��

// ��ģ��
// Stack ����
// Stack<T> ����
template<class T>
class Stack
{
public:
	Stack(int capacity = 4)
		:_top(0)
		, _capacity(capacity)
	{
		_a = new T[capacity];
	}

	~Stack()
	{
		delete[] _a;
		_a = nullptr;
		_capacity = _top = 0;
	}

	void Push(const T& x);

private:
	T* _a;
	int _top;
	int _capacity;
};

template<class T>
void Stack<T>::Push(const T& x)
{
	// ...
}

int main()
{
	Stack<int> st1;     // �洢int
	Stack<double> st2;  // �洢double
	Stack<char> st3;
	Stack<int*> st4;

	st1.Push(1);
	st1.Push(2);
	st1.Push(3);

	return 0;
}


