#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;

//继承（是类设计层次的复用）

class Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
protected:
	string _name = "peter"; // 姓名
	int _age = 18; // 年龄
};
// 继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分
class Student : public Person
{
protected:
	int _stuid; // 学号
};
class Teacher : public Person
{
protected:
	int _jobid; // 工号
};
int main()
{
	Student s;
	Teacher t;
	s.Print();
	t.Print();
	return 0;
}




//基类和派生类对象赋值转换（赋值兼容规则）
class Person
{
protected:
	string _name;
	string _sex;
	int _age;
};
class Student :public Person
{
public:
	int _No;
};
int main()
{
	Person p;
	Student s;
	//父类 = 子类赋值兼容->切割、切片
	p = s;
	Person* ptr = &s;
	Person& ref = s;
	//:注意必须是public   这里不存在类型转换，是语法天然支持行为


	//子类 = 父类 （不可以）
	//s = p;
	return 0;
}






//继承中的作用域
class Person
{
protected:
	string _name = "小李子"; // 姓名
	int _num = 111; // 身份证号
};
class Student : public Person
{
public:
	void Print()
	{
		cout << " 姓名:" << _name << endl;
		cout << " 身份证号:" << Person::_num << endl;
		cout << " 学号:" << _num << endl;

		//如果想访问父类的
		cout << "学号2：" << Person::_num << endl;
	}
protected:
	int _num = 999; // 学号
	//还有一个_num被继承下来，一共两个。这边访问_num是自己的（就近原则）
};
int main()
{
	Student s1;
	s1.Print();

	return 0;
};






class A
{
public:
	void fun()
	{
		cout << "fun()" << endl;
	}
};
class B :public A
{
public:
	void fun(int i)
	{
		cout << "fun(int i)->" << i << endl;
	}
};
int main()
{
	B b;
	b.fun(10);//注意：他们不构成函数重载，因为函数重载要求在同一作用域。成员函数只要函数名相同就构成隐藏

	
	//b.fun()//无参的被隐藏了，只能调用有参的，想调无参的，指明作用域即可
	b.A::fun();
}






//派生类的默认成员函数
class Person
{
public:
	Person(const char* name)
		: _name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;

		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
		//delete[] _ptr;
	}
protected:
	string _name; // 姓名
	//int* _ptr = new int[10];
};
class Student :public Person
{
public:
	Student(const char* name = "张三",int num = 1)
		:Person(name)
		, _num(num)
	{}
	//s2(s1)
	Student(const Student& s)
		:Person(s)
		, _num(s._num)
	{}
	//s2 = s1
	Student& operator=(const Student& s)
	{
		if (this != &s)
		{
			Person::operator=(s);
			_num = s._num;
		}
		return *this;
	}


	//析构函数名字会被统一处理成destructor()
	//子类的析构函数会跟父类的析构函数构成隐藏
	~Student()
	{
		//Person::~Person();这个不用写，结束会自动调用
		//delete[] _ptr;
	}
	//子类析构函数结束时，会自动调用父类的析构函数，所以我们自己实现的子类析构函数是，不需要显示调用父类析构函数
	//这样才能保证先析构子类成员，在析构父类成员
protected:
	int _num = 1;//学号
	//string _s = "hello wsh!!!!!!!!!!!!!!!!!!!!";
	//int* _ptr = new int[10];
};
int main()
{
	Student s1;
	Student s2;
	Student s3("jack", 18);
	s1 = s3;
	return 0;
}
//总结：子类自己的成员函数就按以前的方式（普通类）处理，继承的成员，调用父类几个默认成员函数处理






//继承与友元（友元关系不能继承）
class Student;
class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name; // 姓名
};
class Student : public Person
{
	friend void Display(const Person& p, const Student& s);

protected:

	int _stuNum; // 学号
};
void Display(const Person& p, const Student& s) {
	cout << p._name << endl;
	cout << s._stuNum << endl;
}
int main()
{
	Person p;
	Student s;
	Display(p, s);
}






//继承与静态成员
class Person
{
public:
	Person() { ++_count; }
protected:
	string _name; // 姓名
public:
	static int _count; // 统计人的个数。
};
int Person::_count = 0;
class Student : public Person
{
protected:
	int _stuNum; // 学号
};
class Graduate : public Student
{
protected:
	string _seminarCourse; // 研究科目
};
int main()
{
	Person p;
	Student s;
	Graduate g;

	cout << Person::_count << endl;
	cout << Student::_count << endl;
	cout << Graduate::_count << endl;

	//基类定义了static静态成员，则整个继承体系里面只有一个这样的成员。无论派生出多少个子类，都只有一个static成员实例 。
	return 0;
}






//复杂的菱形继承及菱形虚拟继承
class Person
{
public:
	string _name; // 姓名
	int _a[10000];
};
class Student : public Person
{
public:
	int _num; //学号
};
class Teacher : public Person
{
public:
	int _id; // 职工编号
};
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // 主修课程
};
int main()
{
	//二义性、数据冗余
	Assistant a;
	a._id = 1;
	a._num = 2;
	a.Student::_name = "xiao zhang";
	a.Teacher::_name = "zhang lao shi";

	cout << sizeof(a) << endl;
	//会打印80000多，造成40000浪费
	return 0;
}


//改进--解决关键字virtual
class Person
{
public:
	string _name; // 姓名
	int _a[10000];
};
class Student : virtual public Person
{
public:
	int _num; //学号
};
class Teacher : virtual public Person
{
public:
	int _id; // 职工编号
};
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // 主修课程
};
int main()
{
	Assistant a;
	a._id = 1;
	a._num = 2;
	a.Student::_name = "xiao zhang";
	a.Teacher::_name = "zhang lao shi";

	cout << sizeof(a) << endl;
	return 0;
}