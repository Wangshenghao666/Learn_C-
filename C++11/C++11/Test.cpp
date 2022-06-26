#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<array>
using namespace std;

//��C++98�У���׼����ʹ�ô�����{}��������߽ṹ��Ԫ�ؽ���ͳһ���б��ʼֵ�趨��
struct Point
{
	int _x;
	int _y;

	Point(int x, int y)
		:_x(x)
		, _y(y)
	{}
};
int main()
{
	Point p = { 1, 2 };
	int a = 1;
	int b = { 2 };

	//C++11�������ô�����������б�(��ʼ���б�)��ʹ�÷�Χ��ʹ����������е��������ͺ��û���
	//��������ͣ�ʹ�ó�ʼ���б�ʱ������ӵȺ�(= )��Ҳ�ɲ���ӡ�
	int c{ 3 };
	int array1[] {1, 2, 3, 4, 5};
	int array2[5] {0};
	Point pp{ 1, 2 };

	int* ptr1 = new int[5]{1, 2, 3};
	Point* ptr2 = new Point[2]{{ 1, 1 }, { 2, 2 }};
	 
	return 0;
}


//������
class A
{
public:
	////�Ӹ��ؼ���explicit�Ͳ���ת����(A aa2 = 2 �������ˣ�
	//explicit A(int a)
	//	:_a(a)
	//{}
	A(int a)
		:_a(a)
	{}
private:
	int _a;
};
int main()
{
	A aa1(1);
	A aa2 = 2;

	string s1("hello");
	string s2 = "world";
	vector<string> v;
	v.push_back(s1);
	v.push_back("world");

	// ��������캯����֧����ʽ����ת��
	Point p2 = { 1, 2 };
	Point p3{ 1, 2 };
	return 0;
}



//��������ʱҲ����ʹ���б��ʼ����ʽ���ù��캯����ʼ��
class Date
{
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int year, int month, int day)" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2022, 1, 1); // old style
	// C++11֧�ֵ��б��ʼ�����������ù��캯����ʼ��
	Date d2{ 2022, 1, 2 };
	Date d3 = { 2022, 1, 3 };
	return 0;
}





//std::initializer_list
//һ������Ϊ���캯���Ĳ�����C++11��STL�еĲ�������������
//std::initializer_list��Ϊ�����Ĺ��캯����������ʼ����������͸������ˡ�
int main()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);

	vector<int> v2 = {1, 2, 3, 4};
	vector<int> v3 = { 1, 2, 3, 4, 5, 6, 7, 8};
	list<int> lt1 = { 1, 2, 3, 4, 5 };
	pair<string, string> kv("left", "���");
	map<string, string> dict = { { "insert", "����" }, {"sort", "����"}, kv, make_pair("list", "�б�")};
	v2 = { 10, 20, 30 };

	initializer_list<int> ilt = { 1, 2, 3, 4, 5, 6, 7, 8 };

	return 0;
}



//c++11�ṩ�˶��ּ������ķ�ʽ����������ʹ��ģ��ʱ��
//1 auto               C++11�з���autoԭ�����÷�����������ʵ���Զ������ȶϡ�
//����Ҫ����������ʾ��ʼ�����ñ�����������������������Ϊ��ʼ��ֵ�����͡�
int main()
{
	int i = 10;
	auto p = &i;
	
	cout << typeid(p).name() << endl;
	map<string, string> dict = { { "sort", "����" }, { "insert", "����" } };
	//map<string, string>::iterator it = dict.begin();
	auto it = dict.begin();
	return 0;
}



//�ؼ���decltype����������������Ϊ���ʽָ�������͡�
int func(int a)
{
	cout << "int func(int a)" << endl;
	return a;
}

int main()
{
	const int x = 1;
	double y = 2.2;
	//cout << typeid(x).name() << endl;
	decltype(x) z = 2;

	decltype(x * y) ret; // ret��������double
	decltype(&x) p;      // p��������int*

	int(*pfunc1)(int) = func;
	auto pfunc2 = func;
	decltype(pfunc2) pfunc3 = func;
	decltype(&func) pfunc4 = func;

	map<string, string> dict = { { "sort", "����" }, { "insert", "����" } };
	auto it = dict.begin();
	// decltype��һ��ʹ�ó���
	//decltype(it) copyIt = it;
	auto copyIt = it;
	vector<decltype(it)> v;
	v.push_back(it);

	return 0;
}




�����﷨
int main()
{
	int a1[10];
	array<int, 10> a2;
	cout << sizeof(a2) << endl;

	 1��֧�ֵ����������ü���STL�����淨
	 2������Խ��ļ��
	a1[14] = 0; // *(a1+14) = 0;  ���
	a2[14] = 0; // a2.operator[](14) = 0; // �ؼ�


	return 0;
}