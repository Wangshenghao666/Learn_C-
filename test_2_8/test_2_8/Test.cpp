#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

��Ͷ���
C++����C����ṹ����÷���ͬʱstruct��C++��Ҳ��������

struct Student
{
	char name[10];
	int age;
	int id;
};
int main()
{
	struct Student s1;//����c
	Student s2;//��������
	strcpy(s1.name, "zhangsan");
	s1.age = 18;
	s1.id = 1;

	strcpy(s2.name, "lisi");
	s2.age = 19;
	s2.id = 2;

	return 0;
}


C++��ͽṹ�岻ͬ���ǳ��˿��Զ�������������Զ��巽��������
struct Student
{
	//��Ա����
	char _name[10];
	int _age;
	int _id;
	//��Ա��������Ա����
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
	//����ֱ�ӵ���ʹ��
	Student s1;
	s1.Init("zhangshan", 18, 1);
	s1.Print();
	return 0;
}


��������������ԣ���װ���̳У���̬
��װ��1 ���ݺͷ����ŵ���һ���������档2 �����޶���
һ���ڶ������ʱ�򣬽�����ȷ������ʷ�����Ҫ��class/structĬ���޶�
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



//thisָ������
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

		// һ����������Ƕ�����������������ʾд
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


���캯��
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
	//���Խ����������ϲ���һ������ȱʡ
	//�Ƽ�ʹ��ȱʡ
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
C++��������ͷ�Ϊ���ࣺ���ú��Զ���
���ǲ�д����������Ĭ�����ɹ��캯�����������ò�����ʼ�����������Զ����Ա�������ͻ�ȥ����
�����޲�Ĭ�Ϲ��캯������û�оͻᱨ��
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



//��������
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
		//Date��û����Դ��Ҫ�������Բ�ʵ����������Ҳ�ǿ��Ե�
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

// ����ջʵ��һ������
class MyQueue {
public:
	// Ĭ�����ɹ��캯����������������Զ������ͳ�Ա�������Ĺ��������
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


��������
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
	Date d2(d1);//��������
	return 0;
}