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
	//子类中满足三同（函数名，参数，返回值）的虚函数，叫做重写（覆盖）
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
//构成多态，传的哪个类型的对象，调用的就是这个类型的虚函数--跟对象有关
//不构成多态，调用就是p类型的函数---跟类型有关





//重写要求返回值相同有一个例外：协变---要求返回值是父子关系的指针或引用
class A
{

};
class B :public A
{

};
class Person
{
public:
	virtual Person* BuyTicket()//或者是  virtual A* BuyTicket()
	{
		cout << "mai piao -- quanjiang" << endl;
		return nullptr;
	}
};
class Student :public Person
{
public:
	virtual Student* BuyTicket()//或者是  virtual B* BuyTicket()
	{
		cout << "maipiao -- banjiang" << endl;
		return nullptr;
	}
};






//析构函数是虚函数，构成重写          析构函数名被特殊处理了，处理成destructor
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
	//普通对象析构函数是否虚函数，是否完成重写，都会正确调用

	Person* p1 = new Person;//operator new + 构造
	Person* p2 = new Person;
	delete p1;   
	// 析构 + operator delete
	//p1->destructor();
	delete p2;
	//p2->destructor();
	return 0;
}
//如前面没有加上虚函数，没有构成重写，所以这是以前的用法
//加上虚函数，动态申请的对象，如果给了父类指针管理，呢么需要析构函数是虚函数





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
	//虽然子类没写virtual，但是它是先继承了父类的虚函数属性，在完成重写，呢么它也算是虚函数
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
//  设计一个不能被继承的类？  C++98中

class A
{
private:
	A(int a = 0)
		:_a(a)
	{

	}
	//解决
public:
	static A GreateObj(int a = 0)
	{
		return A(a);
	}
protected:
	int _a;
};
//间接限制，子类构造函数无法调用父类构造函数初始化成员，没办法实例化对象
class B :public A
{

};
int main()
{
	A aa = A::GreateObj(10);
	return 0;
}

//C++11中 粗暴直接限制
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
//还可以限制重写
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





//override放在子类重写虚函数的后面，检查是否完成重写、没有重写就会报错
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
	virtual void Drive() override//帮助检查重写
	{
		cout << "Benz - shushi" << endl;
	}
};
int main()
{
	return 0;
}