#pragma once
#include<iostream>
using namespace std;

class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1);
	int GetMonthDay(int year, int month);//�ж�ĳ��ĳ���Ƕ�������
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

	// ����һ�²���ռλ����ǰ��++,���ɺ�������
	// d1++; ����Ϊ�˸�ǰ��++����������
	Date operator++(int);

	// d1 -= 10
	Date& operator-=(int day);

	// d1 - 10
	Date operator-(int day);

	// --d1;
	Date& operator--();

	//d1--
	Date operator--(int);

	int operator-(const Date& d);//����-����

	void PrintWeekDay();//������
private:
	int _year;
	int _month;
	int _day;
};
