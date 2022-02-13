#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
////命名防止冲突
//namespace bit
//{
//	int rand = 0;
//}
//int a = 20;
//int main()
//{
//	printf("hello world\n");
//	printf("%d\n", bit::rand);
//	int a = 1;
//	printf("%d\n", a);
//	printf("%d\n", ::a);
//	return 0;
//}

////命名空间可以定义变量、函数、类型
//namespace bit
//{
//	int rand = 10;
//	int Add(int left, int right)
//	{
//		return left + right + 10;
//	}
//	struct Node
//	{
//		struct Node* next;
//		int val;
//	};
//}
//namespace wsh
//{
//	int Add(int left, int right)
//	{
//		return left + right;
//	}
//	struct Node
//	{
//		struct Node* next;
//		int val;
//	};
//}
//int main()
//{
//	bit::rand = 10;
//	struct bit::Node node;
//	bit::Add(1, 2);
//	wsh::Add(1, 2);
//	return 0;
//	
//}

////命名空间可以嵌套
//namespace wsh
//{
//	int a;
//	int b;
//	int Add(int left, int right)
//	{
//		return left + right;
//	}
//	namespace zj
//	{
//		int c;
//		int d;
//		int Sub(int left, int right)
//		{
//			return left - right;
//		}
//	}
//}
//int main()
//{	
//	printf("%d\n", wsh::Add(1, 2));
//	printf("%d\n", wsh::zj::Sub(3, 4));
//	return 0;
//}


#include<iostream>
using namespace std;
int main()
{
	cout << "hello world" << endl;
	cout << "hello world\n";
	printf("hello world\n");

	int i = 10;
	double d = 1.11;
	//自动识别类型
	cout << i << " " << d << endl;
	cin >> i >> d;
	cout << i << " " << d << endl;
	return 0;
}