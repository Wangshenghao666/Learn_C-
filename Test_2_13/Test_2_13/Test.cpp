#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

运算符重载
class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
//private:
	int _year;
	int _month;
	int _day;
};
//函数名  operator操作符
//返回类型  看操作符运算后返回值是什么
//参数    操作符有几个操作数，它就有几个参数
bool operator>(const Date& d1, const Date& d2)
{
	if (d1._year > d2._year)
	{
		return true;
	}
	else if (d1._year > d2._year && d1._month > d2._month)
	{
		return true;
	}
	else if (d1._year > d2._year && d1._month > d2._month && d1._day > d2._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	Date d1(2022, 1, 16);
	Date d2(2022, 1, 31);
	Date d3(2022, 2, 26);
	//比较日期 默认情况下C++是不支持自定义类型对象使用运算符
	d1 > d2;//也可以写成 operator>(d1,d2);
	cout << (d1 > d2) << endl;//cout << operator>(d1, d2) << endl;
	return 0;
}

加上private

class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	//bool operator>(const Date& d1, const Date& d2)//现在参数不匹配，有隐含的this指针
	//bool operator>(Date* const this,const Date& d)
	bool operator>(const Date& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year && _month > d._month)
		{
			return true;
		}
		else if (_year == d._year && _month == d._month && _day > d._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2022, 1, 16);
	Date d2(2022, 1, 31);
	Date d3(2022, 2, 26);
	d1 > d2;//也可以写成 operator>(d1,d2);
	cout << (d1 > d2) << endl;//cout << operator>(d1, d2) << endl;

	return 0;
}


赋值运算符重载
class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	/*Date(const Date& d)
	{
		cout << "Date(const Date& d)" << endl;
	}
*/
	// d1 = d3;
	// d1 = d1;
	Date& operator=(const Date& d)
	{
		// 极端情况下自己给自己赋值就可以不同处理了，直接判断一下跳过
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
 

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2022, 1, 16);
	Date d2(2022, 1, 31);
	Date d3(2022, 2, 26);

	// 一个已经存在的对象拷贝初始化一个马上创建实例化的对象
	Date d4(d1);  // 拷贝构造
	Date d5 = d1; // 拷贝构造

	// 两个已经存在的对象之间进行赋值拷贝
	d2 = d1 = d3; // d1.operator=(d3)
	//d1 = d3; // d1.operator=(d3)

	//d1 = d1;


	return 0;
}


