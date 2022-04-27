#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;

//�̳У�������Ʋ�εĸ��ã�

class Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
protected:
	string _name = "peter"; // ����
	int _age = 18; // ����
};
// �̳к����Person�ĳ�Ա����Ա����+��Ա�����������������һ����
class Student : public Person
{
protected:
	int _stuid; // ѧ��
};
class Teacher : public Person
{
protected:
	int _jobid; // ����
};
int main()
{
	Student s;
	Teacher t;
	s.Print();
	t.Print();
	return 0;
}




//��������������ֵת������ֵ���ݹ���
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
	//���� = ���ำֵ����->�и��Ƭ
	p = s;
	Person* ptr = &s;
	Person& ref = s;
	//:ע�������public   ���ﲻ��������ת�������﷨��Ȼ֧����Ϊ


	//���� = ���� �������ԣ�
	//s = p;
	return 0;
}






//�̳��е�������
class Person
{
protected:
	string _name = "С����"; // ����
	int _num = 111; // ���֤��
};
class Student : public Person
{
public:
	void Print()
	{
		cout << " ����:" << _name << endl;
		cout << " ���֤��:" << Person::_num << endl;
		cout << " ѧ��:" << _num << endl;

		//�������ʸ����
		cout << "ѧ��2��" << Person::_num << endl;
	}
protected:
	int _num = 999; // ѧ��
	//����һ��_num���̳�������һ����������߷���_num���Լ��ģ��ͽ�ԭ��
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
	b.fun(10);//ע�⣺���ǲ����ɺ������أ���Ϊ��������Ҫ����ͬһ�����򡣳�Ա����ֻҪ��������ͬ�͹�������

	
	//b.fun()//�޲εı������ˣ�ֻ�ܵ����вεģ�����޲εģ�ָ�������򼴿�
	b.A::fun();
}






//�������Ĭ�ϳ�Ա����
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
	string _name; // ����
	//int* _ptr = new int[10];
};
class Student :public Person
{
public:
	Student(const char* name = "����",int num = 1)
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


	//�����������ֻᱻͳһ�����destructor()
	//�������������������������������������
	~Student()
	{
		//Person::~Person();�������д���������Զ�����
		//delete[] _ptr;
	}
	//����������������ʱ�����Զ����ø�����������������������Լ�ʵ�ֵ��������������ǣ�����Ҫ��ʾ���ø�����������
	//�������ܱ�֤�����������Ա�������������Ա
protected:
	int _num = 1;//ѧ��
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
//�ܽ᣺�����Լ��ĳ�Ա�����Ͱ���ǰ�ķ�ʽ����ͨ�ࣩ�����̳еĳ�Ա�����ø��༸��Ĭ�ϳ�Ա��������






//�̳�����Ԫ����Ԫ��ϵ���ܼ̳У�
class Student;
class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name; // ����
};
class Student : public Person
{
	friend void Display(const Person& p, const Student& s);

protected:

	int _stuNum; // ѧ��
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






//�̳��뾲̬��Ա
class Person
{
public:
	Person() { ++_count; }
protected:
	string _name; // ����
public:
	static int _count; // ͳ���˵ĸ�����
};
int Person::_count = 0;
class Student : public Person
{
protected:
	int _stuNum; // ѧ��
};
class Graduate : public Student
{
protected:
	string _seminarCourse; // �о���Ŀ
};
int main()
{
	Person p;
	Student s;
	Graduate g;

	cout << Person::_count << endl;
	cout << Student::_count << endl;
	cout << Graduate::_count << endl;

	//���ඨ����static��̬��Ա���������̳���ϵ����ֻ��һ�������ĳ�Ա���������������ٸ����࣬��ֻ��һ��static��Աʵ�� ��
	return 0;
}






//���ӵ����μ̳м���������̳�
class Person
{
public:
	string _name; // ����
	int _a[10000];
};
class Student : public Person
{
public:
	int _num; //ѧ��
};
class Teacher : public Person
{
public:
	int _id; // ְ�����
};
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // ���޿γ�
};
int main()
{
	//�����ԡ���������
	Assistant a;
	a._id = 1;
	a._num = 2;
	a.Student::_name = "xiao zhang";
	a.Teacher::_name = "zhang lao shi";

	cout << sizeof(a) << endl;
	//���ӡ80000�࣬���40000�˷�
	return 0;
}


//�Ľ�--����ؼ���virtual
class Person
{
public:
	string _name; // ����
	int _a[10000];
};
class Student : virtual public Person
{
public:
	int _num; //ѧ��
};
class Teacher : virtual public Person
{
public:
	int _id; // ְ�����
};
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // ���޿γ�
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