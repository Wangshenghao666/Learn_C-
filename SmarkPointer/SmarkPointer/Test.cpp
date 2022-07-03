#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>

using namespace std;

int div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw invalid_argument("��0����");

	return a / b;
}

void func()
{
	int* p1 = new int;
	int* p2 = nullptr, *p3 = nullptr;
	try
	{
		p2 = new int;
		p3 = new int;

		cout << div() << endl; // �쳣��ȫ������
	}
	catch (...)
	{

	}

	cout <<"delete:"<<p1 << endl;

	delete p1;
	delete p2;
	delete p3;
}

int main()
{
	try
	{
		func();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	

	return 0;
}




template<class T>
class SmartPtr
{
public:
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{}

	~SmartPtr()
	{
		cout << "delete:" << _ptr << endl;
		delete _ptr;
	}

	// ��ָ��һ��ʹ��
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

int div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw invalid_argument("��0����");

	return a / b;
}

void func()
{
	SmartPtr<int> sp1(new int);
	SmartPtr<int> sp2(new int);
	SmartPtr<int> sp3(new int);

	*sp1 = 10;
	cout << *sp1 << endl;
	(*sp1)++;
	(*sp1)++;
	cout << *sp1 << endl;

	cout << div() << endl;
}

int main()
{
	try
	{
		func();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}




namespace wsh
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}

		auto_ptr(auto_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			// ����Ȩת��
			sp._ptr = nullptr;
		}

		~auto_ptr()
		{
			if (_ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
			}
		}

		// ��ָ��һ��ʹ��
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
}
int main()
{
	std::auto_ptr<int> sp1(new int);
	std::auto_ptr<int> sp2(sp1); // ����Ȩת��

	// sp1����
	*sp2 = 10;
	cout << *sp2 << endl;
	cout << *sp1 << endl;

	return 0;
}
// ���ۣ�auto_ptr��һ��ʧ����ƣ��ܶ๫˾��ȷҪ����ʹ��auto_ptr





