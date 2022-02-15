#pragma once
#include<iostream>
using namespace std;

class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1);
	int GetMonthDay(int year, int month);//判断某年某月是多少天数
	void Print();

	bool operator>(const Date& d);

	bool operator<(const Date& d);
	bool operator>=(const Date& d);
	bool operator<=(const Date& d);
	bool operator==(const Date& d);
	bool operator!=(const Date& d);

	// d1 += 100
	Date& operator+=(int day);

	// d1 + 100
	Date operator+(int day);


	// ++d1;
	Date& operator++();

	// 增加一下参数占位，跟前置++,构成函数重载
	// d1++; 后置为了跟前置++，进行区分
	Date operator++(int);

	// d1 -= 10
	Date& operator-=(int day);

	// d1 - 10
	Date operator-(int day);

	// --d1;
	Date& operator--();

	//d1--
	Date operator--(int);

	int operator-(const Date& d);//日期-日期

	void PrintWeekDay();//算星期
private:
	int _year;
	int _month;
	int _day;
};
