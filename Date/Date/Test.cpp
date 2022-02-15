#define _CRT_SECURE_NO_WARNINGS 1
#include"Date.h"


void TestDate1()
{
	Date d1;
	Date d2(2022, 1, 16);
	d1.Print();
	d2.Print();

	Date d3(2022, 13, 15);
	d3.Print();

	Date d4(2022, 2, 29);
	d4.Print();

	Date d5(2020, 2, 29);
	d5.Print();

	Date d6(2000, 2, 29);
	d6.Print();
}
void TestDate2()
{
	Date d1(2022, 1, 16);
	Date ret = d1 + 100;
	ret.Print();

	d1 += 100;
	d1.Print();
	++d1;
	d1.Print();
}
void TestDate3()
{
	Date d1(2022, 1, 17);

	Date ret1 = d1 - 10;
	ret1.Print();

	Date ret2 = d1 - 17;
	ret2.Print();

	Date ret3 = d1 - 30;
	ret3.Print();

	Date ret4 = d1 - 400;
	ret4.Print();

	Date ret5 = d1 - 1500;
	ret5.Print();

	Date ret6 = d1 - -100;
	ret6.Print();
}
void TestDate4()
{
	/*Date today(2022, 1, 17);
	Date offerDay(2022, 9, 1);

	cout << (offerDay - today) << endl;
	cout << (today - offerDay) << endl;*/

	Date today(2022, 1, 17);
	today.PrintWeekDay();

	Date(2022, 1, 17).PrintWeekDay();
}
int main()
{
	//TestDate1();
	//TestDate2();
	//TestDate3();
	TestDate4();
	return 0;
}