#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
#include"string.h"

using namespace std;

//模板中的&& 万能引用
void Fun(int &x)
{ cout << "左值引用" << endl; }
void Fun(const int &x)
{ cout << "const 左值引用" << endl; }
void Fun(int &&x)
{ cout << "右值引用" << endl; }
void Fun(const int &&x)
{ cout << "const 右值引用" << endl; }
// 模板中的&&不代表右值引用，而是万能引用，其既能接收左值又能接收右值。
// 模板的万能引用只是提供了能够接收同时接收左值引用和右值引用的能力，
// 但是引用类型的唯一作用就是限制了接收的类型，后续使用中都退化成了左值，
// 我们希望能够在传递过程中保持它的左值或者右值的属性, 就需要用我们下面学习的完美转发
template<typename T>
void PerfectForward(T&& t) {
	Fun(t);
}
int main()
{
	PerfectForward(10);// 右值

	int a;
	PerfectForward(a);// 左值
	PerfectForward(std::move(a)); // 右值

	const int b = 8;
	PerfectForward(b);// const 左值
	PerfectForward(std::move(b)); // const 右值

	return 0;
}




void PerfectForward(int&& t)
{
	cout << &t << endl;
	Fun(t);
}

void PerfectForward(const int& t)
{
	Fun(t);
}

int main()
{
	PerfectForward(10);           // 右值

	int a;
	PerfectForward(a);            // 左值
	//PerfectForward(std::move(a)); // 右值

	//const int b = 8;
	//PerfectForward(b);		      // const 左值
	//PerfectForward(std::move(b)); // const 右值

	return 0;
}




//std::forward 完美转发在传参的过程中保留对象原生类型属性
void Fun(int &x)
{ 
	cout << "左值引用" << endl; 
}
void Fun(const int &x)
{ 
	cout << "const 左值引用" << endl; 
}
void Fun(int &&x)
{ 
	cout << "右值引用" << endl; 
}
void Fun(const int &&x)
{ 
	cout << "const 右值引用" << endl; 
}
// std::forward<T>(t)在传参的过程中保持了t的原生类型属性。
template<typename T>
void PerfectForward(T&& t)
{
	Fun(std::forward<T>(t));
}
int main()
{
	PerfectForward(10);// 右值
	int a;
	PerfectForward(a); // 左值
	PerfectForward(std::move(a)); // 右值
	const int b = 8;
	PerfectForward(b);// const 左值
	PerfectForward(std::move(b)); // const 右值
	return 0;
}



//完美转发实际中的使用场景：
template<class T>
struct ListNode
{
	ListNode* _next = nullptr;
	ListNode* _prev = nullptr;
	T _data;
};

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	List()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}

	void PushBack(T&& x)
	{
		 只要右值引用，再传递其他函数调用，要保持右值属性，必须用完美转发
		Insert(_head, x);
		Insert(_head, std::forward<T>(x));
	}

	void PushFront(T&& x)
	{
		Insert(_head->_next, x);
		Insert(_head->_next, std::forward<T>(x));
	}

	void Insert(Node* pos, T&& x)
	{
		Node* prev = pos->_prev;

		Node* newnode = new Node;
		newnode->_data = std::forward<T>(x); // 关键位置

		Node* newnode = (Node*)malloc(sizeof(Node));
		new(&newnode->_data)T(x);
		new(&newnode->_data)T(std::forward<T>(x));

		 prev newnode pos
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = pos;
		pos->_prev = newnode;
	}

	void Insert(Node* pos, const T& x)
	{
		Node* prev = pos->_prev;
		Node* newnode = new Node;
		newnode->_data = x; // 关键位置

		 prev newnode pos
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = pos;
		pos->_prev = newnode;
	}
private:
	Node* _head;
};

int main()
{
	List<wsh::string> lt;
	lt.PushBack("1111");
	lt.PushFront("2222");

	return 0;
}