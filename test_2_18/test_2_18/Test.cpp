#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//��̬�ڴ濪��
int main()
{
	//��̬����int��5��int����
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
//�ܽ�malloc/free �� new/delete ������������û�б��ʵ�����ֻ���÷�������

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
	 ��̬���뵥��A���� �� 5��A��������
	A* p1 = (A*)malloc(sizeof(A));
	A* p2 = (A*)malloc(sizeof(A)*5);

	 new �ڶ����������ռ�+���ù��캯����ʼ������
	A* p3 = new A;
	A* p4 = new A[5];

	A* p3 = new A(10);
	A* p4 = new A[5]{10,20,30,40,50};

	free(p1);
	free(p2);

	 delete �ȵ���ָ�������������� + �ͷſռ������
	delete p3;
	delete[] p4;

	 һ��Ҫmalloc free ��new /delete  new[] / delete []ƥ��ʹ�ã�������ܻ����
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
	// �����������ԣ��������ķ�ʽһ�������쳣��C++��ҲҪ��������쳣 -- try catch
	// ������̵����ԣ��������ķ�ʽ��ʲô-������ֵ+��������
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
