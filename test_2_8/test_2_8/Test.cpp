#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

类和对象
C++兼容C里面结构体的用法，同时struct在C++中也升级到类

struct Student
{
	char name[10];
	int age;
	int id;
};
int main()
{
	struct Student s1;//兼容c
	Student s2;//升级到类
	strcpy(s1.name, "zhangsan");
	s1.age = 18;
	s1.id = 1;

	strcpy(s2.name, "lisi");
	s2.age = 19;
	s2.id = 2;

	return 0;
}


C++类和结构体不同，是除了可以定义变量，还可以定义方法、函数
struct Student
{
	//成员变量
	char _name[10];
	int _age;
	int _id;
	//成员方法，成员函数
	void Init(const char* name, int age, int id)
	{
		strcpy(_name, name);
		_age = age;
		_id = id;
	}
	void Print()
	{
		cout << _name << endl;
		cout << _age << endl;
		cout << _id << endl;
	}
};
int main()
{
	//可以直接调用使用
	Student s1;
	s1.Init("zhangshan", 18, 1);
	s1.Print();
	return 0;
}


面向对象三大特性：封装，继承，多态
封装：1 数据和方法放到了一起在类里面。2 访问限定符
一般在定义类的时候，建议明确定义访问符，不要用class/struct默认限定
class Student
{
private:
	char _name[10];
	int _age;
	int _id;
public:
	void Init(const char* name, int age, int id)
	{
		strcpy(_name, name);
		_age = age;
		_id = id;
	}
	void Print()
	{
		cout << _name << endl;
		cout << _age << endl;
		cout << _id << endl;
	}
};



//this指针引出
class Date
{
public:
	//void Init(Date* const this, int year, int month, int day)
	void Init(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;


		/*this->_year = year;
		this->_month = month;
		this->_day = day;*/
	}
	//void Print(Date* const this)
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;

		// 一般情况，我们都不会像下面这样显示写
		//		cout << this->_year << "-" << this->_month << "-" << this->_day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1;
	d1.Init(2022, 1, 15);// d1.Init(&d1, 2022, 1, 15);
	d1.Print();// d1.Print(&d1);

	Date d2;
	d2.Init(2022, 1, 16);// d2.Init(&d2, 2022, 1, 16);
	d2.Print();// d2.Print(&d2);
	return 0;
}


构造函数
class Date
{
public:
	/*Date()
	{
		_year = 1;
		_month = 0;
		_age = 0;
	}
	Date(int year, int month, int age)
	{
		_year = year;
		_month = month;
		_age = age;
	}*/
	//可以将上面两个合并成一个，用缺省
	//推荐使用缺省
	Date(int year = 1, int month = 0, int age = 0)
	{
		_year = year;
		_month = month;
		_age = age;
	}
private:
	int _year;
	int _month;
	int _age;
};
int main()
{
	//Date d1;
	Date d2(2022, 1, 11);
	return 0;
}
C++里面把类型分为两类：内置和自定义
我们不写，编译器会默认生成构造函数，对于内置不做初始化处理，对于自定义成员变量类型回去调用
他的无参默认构造函数，如没有就会报错
class A
{
public:
	/*A()
	{
		cout << "A()" << endl;
		_a = 0;
	}*/
	A(int a = 0 )
	{
		cout << "A()" << endl;
		_a = 0;
	}
private:
	int _a;
};
class Date
{
public:
private:
	int _year;
	int _month;     
	int _age;

	A _aa;
};
int main()
{
	Date d1;

	return 0;
}



//析构函数
class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	~Date()
	{
		//Date类没有资源需要清理，所以不实现析构函数也是可以的
	}
private:
	int _year;
	int _month;
	int _day;
};
class Stack
{
public:
	Stack(int capacity = 4)
	{
		_a = (int*)malloc(sizeof(int)*capacity);
		if (_a == nullptr)
		{
			cout << "malloc fail\n" << endl;
			exit(-1);
		}
		_top = 0;
		_capacity = capacity;
	}
	void Push(int x)
	{
		//.....
	}
	~Stack()
	{
		free(_a);
		_a = nullptr;
		_top = _capacity = 0;
	}
private:
	int* _a;
	size_t _top;
	size_t _capacity;
};
int main()
{
	Date d1;
	Date d2(2022, 1, 15);

	Stack s1;
	Stack s2(20);
	return 0;
}


class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	~Date()
	{

	}
private:
	int _year;
	int _month;
	int _day;
};

class Stack
{
public:
	Stack(int capacity = 4)
	{
		_a = (int*)malloc(sizeof(int)*capacity);
		if (_a == nullptr)
		{
			cout << "malloc fail\n" << endl;
			exit(-1);
		}

		_top = 0;
		_capacity = capacity;
	}
	void Push(int x)
	{

	}
	~Stack()
	{
		free(_a);
		_a = nullptr;
		_top = _capacity = 0;
	}
private:
	int* _a;
	size_t _top;
	size_t _capacity;
};

// 两个栈实现一个队列
class MyQueue {
public:
	// 默认生成构造函数和析构函数会对自定义类型成员调用他的构造和析构
	void push(int x) {

	}
private:
	Stack pushST;
	Stack popST;
};

int main()
{
	Date d1;
	Date d2(2022, 1, 15);

	Stack s1;
	Stack s2(20);

	MyQueue mq;

	return 0;
}


拷贝构造
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
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}*/

private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2022, 1, 15);
	Date d2(d1);//拷贝复制
	return 0;
}