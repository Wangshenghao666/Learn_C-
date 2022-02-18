#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//动态内存开辟
int main()
{
	//动态申请int和5个int数组
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = (int*)malloc(sizeof(int)* 5);

	int* p3 = new int;
	int* p4 = new int[5];

	free(p1);
	free(p2);
	delete p3;
	delete p4;

	p1 = nullptr;
	p2 = nullptr;
	p3 = nullptr;
	p4 = nullptr;
	return 0;
}
//总结malloc/free 和 new/delete 对于内置类型没有本质的区别，只有用法的区别

class A
{
public:
	A(int a = 0)
		: _a(a)
	{
		cout << "A():" << this << endl;
	}

	~A()
	{
		cout << "~A():" << this << endl;
	}

private:
	int _a;
};
int main()
{
	 动态申请单个A对象 和 5个A对象数组
	A* p1 = (A*)malloc(sizeof(A));
	A* p2 = (A*)malloc(sizeof(A)*5);

	 new 在堆上申请对象空间+调用构造函数初始化对象
	A* p3 = new A;
	A* p4 = new A[5];

	A* p3 = new A(10);
	A* p4 = new A[5]{10,20,30,40,50};

	free(p1);
	free(p2);

	 delete 先调用指针类型析构函数 + 释放空间给堆上
	delete p3;
	delete[] p4;

	 一定要malloc free 和new /delete  new[] / delete []匹配使用，否则可能会崩溃
	free(p3);
	free(p4);
	delete p4;

	return 0;
}


void BuyMemory()
{
	char* p2 = new char[1024u * 1024u * 1024u * 2u - 1];
	//p2 = new char[1024u * 1024u * 1024u * 1u];
	printf("%p\n", p2);
}

int main()
{
	// 面向对象的语言，处理错误的方式一般是抛异常，C++中也要求出错抛异常 -- try catch
	// 面向过程的语言，处理错误的方式是什么-》返回值+错误码解决
	/*char* p1 = (char*)malloc(1024u*1024u*1024u*2u);
	if (p1 == nullptr)
	{
	printf("%d\n", errno);
	perror("malloc fail");
	exit(-1);
	}
	else
	{
	printf("%p\n", p1);
	}*/

	try
	{
		BuyMemory();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
