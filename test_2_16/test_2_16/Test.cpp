#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

��ʼ���б�--��Ա��������ĵط�
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
	int& _ret;//����
	A _aa;//û��Ĭ�Ϲ��캯�����Զ������ͳ�Ա����
};
int main()
{
	int i = 0;
	Date d1(2022, 1, 19, i);
	Date d2(2021, 1, 19, i);
	return 0;
}


//explicit�ؼ���
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
	
	//��һ�����α������������Ͷ���ֵ
	//ʵ�ʱ������������2019����һ������������������������d1������и�ֵ
	d1 = 2019;
}
//��explicit���ι��캯���������ֹ���ι��캯������ʽת��


//static��Ա
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

	// û��thisָ�룬ֻ�ܷ��ʾ�̬��Ա�����ͳ�Ա����
	static int GetCount()
	{
		//_a;
		return _sCount;
	}
private:
	int _a;

//public:
	// ��̬��Ա�������������࣬���ж��������������������������ڼ�
	// ���Ա�����У�����������
	static int _sCount; // ����
};

int A::_sCount = 0; // �����ʼ��

void f(A a)
{

}

int main()
{
	A a1;
	A a2 = 1;
	f(a1);

	// ��������ʵķ�ʽ�� ->public
	/*cout << A::_sCount << endl;
	cout << a1._sCount << endl;
	cout << a2._sCount << endl;*/

	cout << a1.GetCount() << endl;
	cout << A::GetCount() << endl;

	return 0;
}


// C++11 -- �򲹶�
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
	// ������ٳ�ʼ���б�׶Σ�û�жԳ�Ա������ʼ�������ͻ�ʹ��ȱʡֵ��ʼ��
	A()
	{}
private:           // Ҫע��������ﲻ�ǳ�ʼ������Ϊ���������������ܳ�ʼ��
	int _a1 = 0;  // ������Ǹ���Ա����ȱʡֵ
	B _bb1 = 10;
	B _bb2 = B(20);
	int* p = (int*)malloc(4*10);
	// vs2019֧��
	//int arr[10] = { 1, 2, 3, 4, 5 };

	// ��̬�Ĳ���������ȱʡֵ��������������ȫ��λ�ö����ʼ��
	// static int _sCount = 0;
};

int main()
{
	A aa;

	return 0;
}


��Ԫ����
��Ԫ��������ֱ�ӷ������˽�г�Ա�����Ƕ��������ⲿ����ͨ�������������κ��࣬����Ҫ������ڲ���
��������ʱ��Ҫ��friend�ؼ��֡�
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
��Ԫ������г�Ա��������������һ�������Ԫ�����������Է�����һ�����еķǹ��г�Ա
class Date; // ǰ������
class Time
{
	friend class Date; // ����������Ϊʱ�������Ԫ�࣬�����������о�ֱ�ӷ���Time���е�˽�г�
	//Ա����
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
		// ֱ�ӷ���ʱ����˽�еĳ�Ա����
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


//�ڲ���
class A
{
private:
	static int k;
	int h;
public:
	// �ڲ���
	// 1���ڲ���B����ȫ�ֶ����ǻ���һ���ģ�ֻ���������ⲿ��A��������,������A��������
	// 2���ڲ���B���������ⲿ��A����Ԫ��Ҳ����B�п��Է���A��˽�У�A���ܷ���B��˽��
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
		// A����B����Ԫ�����ܷ���B
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