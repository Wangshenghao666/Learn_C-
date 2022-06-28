#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
#include"string.h"

using namespace std;

//ģ���е�&& ��������
void Fun(int &x)
{ cout << "��ֵ����" << endl; }
void Fun(const int &x)
{ cout << "const ��ֵ����" << endl; }
void Fun(int &&x)
{ cout << "��ֵ����" << endl; }
void Fun(const int &&x)
{ cout << "const ��ֵ����" << endl; }
// ģ���е�&&��������ֵ���ã������������ã�����ܽ�����ֵ���ܽ�����ֵ��
// ģ�����������ֻ���ṩ���ܹ�����ͬʱ������ֵ���ú���ֵ���õ�������
// �����������͵�Ψһ���þ��������˽��յ����ͣ�����ʹ���ж��˻�������ֵ��
// ����ϣ���ܹ��ڴ��ݹ����б���������ֵ������ֵ������, ����Ҫ����������ѧϰ������ת��
template<typename T>
void PerfectForward(T&& t) {
	Fun(t);
}
int main()
{
	PerfectForward(10);// ��ֵ

	int a;
	PerfectForward(a);// ��ֵ
	PerfectForward(std::move(a)); // ��ֵ

	const int b = 8;
	PerfectForward(b);// const ��ֵ
	PerfectForward(std::move(b)); // const ��ֵ

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
	PerfectForward(10);           // ��ֵ

	int a;
	PerfectForward(a);            // ��ֵ
	//PerfectForward(std::move(a)); // ��ֵ

	//const int b = 8;
	//PerfectForward(b);		      // const ��ֵ
	//PerfectForward(std::move(b)); // const ��ֵ

	return 0;
}




//std::forward ����ת���ڴ��εĹ����б�������ԭ����������
void Fun(int &x)
{ 
	cout << "��ֵ����" << endl; 
}
void Fun(const int &x)
{ 
	cout << "const ��ֵ����" << endl; 
}
void Fun(int &&x)
{ 
	cout << "��ֵ����" << endl; 
}
void Fun(const int &&x)
{ 
	cout << "const ��ֵ����" << endl; 
}
// std::forward<T>(t)�ڴ��εĹ����б�����t��ԭ���������ԡ�
template<typename T>
void PerfectForward(T&& t)
{
	Fun(std::forward<T>(t));
}
int main()
{
	PerfectForward(10);// ��ֵ
	int a;
	PerfectForward(a); // ��ֵ
	PerfectForward(std::move(a)); // ��ֵ
	const int b = 8;
	PerfectForward(b);// const ��ֵ
	PerfectForward(std::move(b)); // const ��ֵ
	return 0;
}



//����ת��ʵ���е�ʹ�ó�����
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
		 ֻҪ��ֵ���ã��ٴ��������������ã�Ҫ������ֵ���ԣ�����������ת��
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
		newnode->_data = std::forward<T>(x); // �ؼ�λ��

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
		newnode->_data = x; // �ؼ�λ��

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