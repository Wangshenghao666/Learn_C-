#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

// Type
// 函数模板
//template<class T1, class T2> // template<typename T> // 模板参数列表 -- 参数类型
template<class T>
void Swap(T& x1, T& x2) // 函数参数列表 -- 参数对象
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
模板参数实例化分为：隐式实例化和显示实例化
隐式：
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
	//cout << Add(a1, a3) << endl;//隐式将不同的类型强转过来
	cout << Add((double)a1, a3) << endl;
	cout << Add<int>(a1, a3) << endl;

}
//显示：
   // cout << Add<int>(a1, a3) << endl;显示在函数名加<>指定类型


//专门处理int加法的函数
int Add(int left, int right)
{
	return left + right;
}
//通用加法函数
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
	cout << Add(a1, a2) << endl;//优先调普通函数
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
这样写栈会一个类型写一个有点麻烦
引出类模板

// 类模板
// Stack 类名
// Stack<T> 类型
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
	Stack<int> st1;     // 存储int
	Stack<double> st2;  // 存储double
	Stack<char> st3;
	Stack<int*> st4;

	st1.Push(1);
	st1.Push(2);
	st1.Push(3);

	return 0;
}


