#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "mai piao - quanjiang" << endl;
	}
};
class Student :public Person
{
public:
	//������������ͬ��������������������ֵ�����麯����������д�����ǣ�
	virtual void BuyTicket()
	{
		cout << "mai piao - banjiang" << endl;
	}
};
void Func(Person& p)
{
	p.BuyTicket();
}
int main()
{
	Person ps;
	Student st;

	Func(ps);
	Func(st);
	return 0;
}
//���ɶ�̬�������ĸ����͵Ķ��󣬵��õľ���������͵��麯��--�������й�
//�����ɶ�̬�����þ���p���͵ĺ���---�������й�





//��дҪ�󷵻�ֵ��ͬ��һ�����⣺Э��---Ҫ�󷵻�ֵ�Ǹ��ӹ�ϵ��ָ�������
class A
{

};
class B :public A
{

};
class Person
{
public:
	virtual Person* BuyTicket()//������  virtual A* BuyTicket()
	{
		cout << "mai piao -- quanjiang" << endl;
		return nullptr;
	}
};
class Student :public Person
{
public:
	virtual Student* BuyTicket()//������  virtual B* BuyTicket()
	{
		cout << "maipiao -- banjiang" << endl;
		return nullptr;
	}
};






//�����������麯����������д          ���������������⴦���ˣ������destructor
class Person
{
public:
	virtual ~Person()
	{
		cout << "~Person()" << endl;
	}
};
class Student :public Person
{
public:
	virtual ~Student()
	{
		cout << "~Student()" << endl;
	}
};
int main()
{
	/*Person p;
	Student s;*/
	//��ͨ�������������Ƿ��麯�����Ƿ������д��������ȷ����

	Person* p1 = new Person;//operator new + ����
	Person* p2 = new Person;
	delete p1;   
	// ���� + operator delete
	//p1->destructor();
	delete p2;
	//p2->destructor();
	return 0;
}
//��ǰ��û�м����麯����û�й�����д������������ǰ���÷�
//�����麯������̬����Ķ���������˸���ָ�������ô��Ҫ�����������麯��





class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "mei piao -- quanjiang" << endl;
	}
	virtual ~Person()
	{
		cout << "~Person()" << endl;
	}
};
class Student:public Person
{
	//��Ȼ����ûдvirtual�����������ȼ̳��˸�����麯�����ԣ��������д����ô��Ҳ�����麯��
public:
	void BuyTicket()
	{
		cout << "mai piao -- banjiang" << endl;
	}
	virtual ~Student()
	{
		cout << "~Student()" << endl;
	}
};





//C++ final override
//  final
//  ���һ�����ܱ��̳е��ࣿ  C++98��

class A
{
private:
	A(int a = 0)
		:_a(a)
	{

	}
	//���
public:
	static A GreateObj(int a = 0)
	{
		return A(a);
	}
protected:
	int _a;
};
//������ƣ����๹�캯���޷����ø��๹�캯����ʼ����Ա��û�취ʵ��������
class B :public A
{

};
int main()
{
	A aa = A::GreateObj(10);
	return 0;
}

//C++11�� �ֱ�ֱ������
class A final
{
protected:
	int _a;
};
//zhi jie xian zhi
class B :public A
{

};
int main()
{
	return 0;
}
//������������д
class c
{
public:
	virtual void f() final
	{
		cout << "C::f()" << endl;
	}
};
class d :public c
{
public:
	virtual void f()
	{
		cout << "D::f()" << endl;
	}
};
int main()
{
	return 0;
}





//override����������д�麯���ĺ��棬����Ƿ������д��û����д�ͻᱨ��
class Car
{
public:
	virtual void Drive()
	{

	}
};
class Benz :public Car
{
public:
	virtual void Drive() override//���������д
	{
		cout << "Benz - shushi" << endl;
	}
};
int main()
{
	return 0;
}