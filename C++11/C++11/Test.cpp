#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<array>
using namespace std;

//在C++98中，标准允许使用大括号{}对数组或者结构体元素进行统一的列表初始值设定。
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

	//C++11扩大了用大括号括起的列表(初始化列表)的使用范围，使其可用于所有的内置类型和用户自
	//定义的类型，使用初始化列表时，可添加等号(= )，也可不添加。
	int c{ 3 };
	int array1[] {1, 2, 3, 4, 5};
	int array2[5] {0};
	Point pp{ 1, 2 };

	int* ptr1 = new int[5]{1, 2, 3};
	Point* ptr2 = new Point[2]{{ 1, 1 }, { 2, 2 }};
	 
	return 0;
}


//单参数
class A
{
public:
	////加个关键字explicit就不能转换了(A aa2 = 2 不能用了）
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

	// 多参数构造函数，支持隐式类型转换
	Point p2 = { 1, 2 };
	Point p3{ 1, 2 };
	return 0;
}



//创建对象时也可以使用列表初始化方式调用构造函数初始化
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
	// C++11支持的列表初始化，这里会调用构造函数初始化
	Date d2{ 2022, 1, 2 };
	Date d3 = { 2022, 1, 3 };
	return 0;
}





//std::initializer_list
//一般是作为构造函数的参数，C++11对STL中的不少容器就增加
//std::initializer_list作为参数的构造函数，这样初始化容器对象就更方便了。
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
	pair<string, string> kv("left", "左边");
	map<string, string> dict = { { "insert", "插入" }, {"sort", "排序"}, kv, make_pair("list", "列表")};
	v2 = { 10, 20, 30 };

	initializer_list<int> ilt = { 1, 2, 3, 4, 5, 6, 7, 8 };

	return 0;
}



//c++11提供了多种简化声明的方式，尤其是在使用模板时。
//1 auto               C++11中废弃auto原来的用法，将其用于实现自动类型腿断。
//这样要求必须进行显示初始化，让编译器将定义对象的类型设置为初始化值的类型。
int main()
{
	int i = 10;
	auto p = &i;
	
	cout << typeid(p).name() << endl;
	map<string, string> dict = { { "sort", "排序" }, { "insert", "插入" } };
	//map<string, string>::iterator it = dict.begin();
	auto it = dict.begin();
	return 0;
}



//关键字decltype将变量的类型声明为表达式指定的类型。
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

	decltype(x * y) ret; // ret的类型是double
	decltype(&x) p;      // p的类型是int*

	int(*pfunc1)(int) = func;
	auto pfunc2 = func;
	decltype(pfunc2) pfunc3 = func;
	decltype(&func) pfunc4 = func;

	map<string, string> dict = { { "sort", "排序" }, { "insert", "插入" } };
	auto it = dict.begin();
	// decltype的一个使用场景
	//decltype(it) copyIt = it;
	auto copyIt = it;
	vector<decltype(it)> v;
	v.push_back(it);

	return 0;
}




鸡肋语法
int main()
{
	int a1[10];
	array<int, 10> a2;
	cout << sizeof(a2) << endl;

	 1、支持迭代器，更好兼容STL容器玩法
	 2、对于越界的检查
	a1[14] = 0; // *(a1+14) = 0;  抽查
	a2[14] = 0; // a2.operator[](14) = 0; // 必检


	return 0;
}