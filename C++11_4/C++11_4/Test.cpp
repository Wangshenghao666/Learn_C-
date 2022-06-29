#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include <algorithm>
#include<functional>
using namespace std;

 lambda

struct Goods
{
	string _name;  // 名字
	double _price; // 价格
	int _evaluate; // 评价

	Goods(const char* str, double price, int evaluate)
		:_name(str)
		, _price(price)
		, _evaluate(evaluate)
	{}
};


struct ComparePriceLess
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price < gr._price;
	}
};

struct ComparePriceGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price > gr._price;
	}
};

int main()
{
	vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2, 3 }, { "菠萝", 1.5, 4 } };
	sort(v.begin(), v.end(), ComparePriceLess());
	sort(v.begin(), v.end(), ComparePriceGreater());
}
int main()
{
	// 实现一个两个数相加的lambda
	//auto add1 = [](int a, int b)->int{return a + b; };
	// 返回值类型可以省略
	auto add1 = [](int a, int b){return a + b; };

	//auto add2 = add1;
	//decltype(add1) add3 = add1;

	cout << add1(1, 2) << endl; 

	// 没有参数可以省略参数列表
	auto func1 = []{cout << "hello world" << endl; };
	func1();

	return 0;
}


int a = 0, b = 1;
 在全局中不能捕捉对象
auto func5 = [a, b](){};
auto func5 = [](){};

int main()
{
	// 捕捉列表是干嘛的呢？
	int a = 1, b = 2;
	auto swap1 = [](int& x, int& y) {
		int z = x;
		x = y;
		y = z;
	};

	swap1(a, b);

	auto swap2 = [a, b]()mutable {
		int z = a;
		a = b;
		b = z;
	};

	swap2();

	auto swap3 = [&a, &b](){
		int z = a;
		a = b;
		b = z;
	};

	swap3();

	auto func3 = [=, &a](){
	};
	swap3();


	return 0;
}



int main()
{
	vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2, 3 }, { "菠萝", 1.5, 4 } };
	//auto priceLess = [](const Goods& g1, const Goods& g2){return g1._price < g2._price; };
	//sort(v.begin(), v.end(), priceLess);

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2){return g1._price < g2._price; });
	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2){return g1._price > g2._price; });
	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2){return g1._evaluate < g2._evaluate; });
	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2){return g1._evaluate > g2._evaluate; });
}



函数对象，又称为仿函数，即可以想函数一样使用的对象，就是在类中重载了operator()运算符的类对象。
class Rate
{
public:
	Rate(double rate) : _rate(rate)
	{}

	double operator()(double money, int year)
	{
		return money * _rate * year;
	}

private:
	double _rate;
};

int main()
{
	// 函数对象
	double rate = 0.49;
	Rate r1(rate);
	r1(10000, 2);

	// lamber  底层原理，其实是被处理成一个lambda_uuid的一个仿函数类
	auto r2 = [=](double monty, int year)->double{return monty*rate*year; };
	r2(10000, 2);
	return 0;

	// lamber
	auto r3 = [=](double monty, int year)->double{return monty*rate*year; };
	r3(10000, 2);
	return 0;
}




//包装器
template<class F, class T>
T useF(F f, T x) 
{
	static int count = 0;
	cout << "count:" << ++count << endl;
	cout << "count:" << &count << endl;
	return f(x);
}
double f(double i)
{
	return i / 2;
}
struct Functor
{
	double operator()(double d)
	{
		return d / 3;
	}
};
int main()
{
	// 函数名
	cout << useF(f, 11.11) << endl;
	// 函数对象
	cout << useF(Functor(), 11.11) << endl;
	// lamber表达式
	cout << useF([](double d)->double{ return d / 4; }, 11.11) << endl;
	return 0;
}
//通过上面的程序验证，我们会发现useF函数模板实例化了三份。
//包装器可以很好的解决上面的问题:以下



int f(int a, int b)
{
	return a + b;
}

struct Functor
{
public:
	int operator() (int a, int b)
	{
		return a * b;
	}
};

class Plus
{
public:
	static int plusi(int a, int b)
	{
		return a + b + 1;
	}

	double plusd(double a, double b)
	{
		return a + b;
	}
};

int main()
{
	function<int(int, int)> f1 = f;
	cout << f1(1, 2) << endl;

	function<int(int, int)> f2 = Functor();
	cout << f2(1, 2) << endl;

	function<int(int, int)> f3 = &Plus::plusi;
	cout << f3(1, 2) << endl;

	function<double(Plus, double, double)> f4 = &Plus::plusd;
	cout << f4(Plus(), 1.1, 2.2) << endl;

	return 0;
}




//bind
int SubFunc(int a, int b)
{
	return a - b;
}

class Sub
{
public:
	int sub(int a, int b)
	{
		return a - b;
	}
};

int main()
{
	function<int(int, int)> f1 = SubFunc;
	cout << f1(10, 3) << endl;

	function<int(int, int)> f2 = bind(SubFunc, placeholders::_1, placeholders::_2);
	cout << f2(10, 3) << endl;

	// 通过bind调整参数顺序
	function<int(int, int)> f3 = bind(SubFunc, placeholders::_2, placeholders::_1);
	cout << f3(10, 3) << endl;

	// 通过bind调整参数个数
	function<int(Sub, int, int)> f4 = &Sub::sub;
	cout << f4(Sub(), 10, 3) << endl;

	function<int(int, int)> f5 = bind(&Sub::sub, Sub(), placeholders::_1, placeholders::_2);
	cout << f5(10, 3) << endl;
	
	auto f6 = bind(&Sub::sub, Sub(), placeholders::_1, placeholders::_2);
	cout << f6(10, 3) << endl;

	return 0;
}