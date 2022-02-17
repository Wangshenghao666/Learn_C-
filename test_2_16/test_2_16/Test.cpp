#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

初始化列表--成员变量定义的地方
class A
{
public:
	A(int a)
	{
		_a = a;
	}
private:
	int _a;
};
class Date
{
public:
	Date(int year, int month, int day,int i)
		:_N(10)
		, _ret(i)
		, _aa(-1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;

	const int _N;//const
	int& _ret;//引用
	A _aa;//没有默认构造函数的自定义类型成员变量
};
int main()
{
	int i = 0;
	Date d1(2022, 1, 19, i);
	Date d2(2021, 1, 19, i);
	return 0;
}


//explicit关键字
class Date
{
public:
	Date(int year)
		:_year(year)
	{
	}
	explicit Date(int year)
		:_year(year)
	{}
private:
	int _year;
	int _month;
	int _day;
};
void TestDate()
{
	Date d1(2018);
	
	//用一个整形变量给日期类型对象赋值
	//实际编译器背后会用2019构造一个无名对象，最后用无名对象给d1对象进行赋值
	d1 = 2019;
}
//用explicit修饰构造函数，将会禁止单参构造函数的隐式转换


//static成员
class A
{
public:
	A(int a = 0)
		:_a(a)
	{
		++_sCount;
	}

	A(const A& aa)
		:_a(aa._a)
	{
		++_sCount;
	}

	// 没有this指针，只能访问静态成员变量和成员函数
	static int GetCount()
	{
		//_a;
		return _sCount;
	}
private:
	int _a;

//public:
	// 静态成员变量属于整个类，所有对象，生命周期在整个程序运行期间
	// 类成员函数中，可以随便访问
	static int _sCount; // 声明
};

int A::_sCount = 0; // 定义初始化

void f(A a)
{

}

int main()
{
	A a1;
	A a2 = 1;
	f(a1);

	// 类外面访问的方式。 ->public
	/*cout << A::_sCount << endl;
	cout << a1._sCount << endl;
	cout << a2._sCount << endl;*/

	cout << a1.GetCount() << endl;
	cout << A::GetCount() << endl;

	return 0;
}


// C++11 -- 打补丁
class B
{
public:
	B(int b = 0)
		:_b(b)
	{}
private:
	int _b;
};
class A
{
public:
	// 如果你再初始化列表阶段，没有对成员变量初始化，它就会使用缺省值初始化
	A()
	{}
private:           // 要注意的是这里不是初始化，因为这里是声明，不能初始化
	int _a1 = 0;  // 这个里是给成员变量缺省值
	B _bb1 = 10;
	B _bb2 = B(20);
	int* p = (int*)malloc(4*10);
	// vs2019支持
	//int arr[10] = { 1, 2, 3, 4, 5 };

	// 静态的不能这样给缺省值，必须在类外面全局位置定义初始化
	// static int _sCount = 0;
};

int main()
{
	A aa;

	return 0;
}


友元函数
友元函数可以直接访问类的私有成员，它是定义在类外部的普通函数，不属于任何类，但需要在类的内部声
明，声明时需要加friend关键字。
class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
	friend istream& operator>>(istream& _cin, Date& d);
public:
	Date(int year, int month, int day)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& _cout, const Date& d) {
	_cout << d._year << "-" << d._month << "-" << d._day;

	return _cout;
}
istream& operator>>(istream& _cin, Date& d) {
	_cin >> d._year;
	_cin >> d._month;
	_cin >> d._day;

	return _cin;
}
int main()
{
	Date d(2022,1,2);
	cin >> d;
	cout << d << endl;
	return 0;
}
友元类的所有成员函数都可以是另一个类的友元函数，都可以访问另一个类中的非公有成员
class Date; // 前置声明
class Time
{
	friend class Date; // 声明日期类为时间类的友元类，则在日期类中就直接访问Time类中的私有成
	//员变量
public:
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{}

private:
	int _hour;
	int _minute;
	int _second;
};
class Date
{
	friend class Time;
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	void SetTimeOfDate(int hour, int minute, int second)
	{
		// 直接访问时间类私有的成员变量
		_t._hour = hour;
		_t._minute = minute;
		_t.second = second;
	}

private:
	int _year;
	int _month;
	int _day;
	Time _t;
};


//内部类
class A
{
private:
	static int k;
	int h;
public:
	// 内部类
	// 1、内部类B和在全局定义是基本一样的，只是他的受外部类A类域限制,定义在A的类域中
	// 2、内部类B天生就是外部类A的友元，也就是B中可以访问A的私有，A不能访问B的私有
	class B
	{
		//friend class A;
	public:
		void foo(const A& a)
		{
			cout << k << endl;//OK
			cout << a.h << endl;//OK
		}

	private:
		int _b;
	};

	void f(B bb)
	{
		// A不是B的友元，不能访问B
		bb._b;
	}
};

int A::k = 1;

int main()
{
	cout << sizeof(A) << endl;
	A aa;
	A::B bb;

	return 0;
}