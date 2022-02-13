#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
//C++的输入输出
using namespace std;
struct Student
{
	char name[20];
	int age;
	//...
};
int main()
{
	//流插入<<
	cout << "hello world" << endl;
	const char* str = "hello Linux";
	cout << str << endl;
	int i = 0;
	double d = 1.11;
	cout << i << " " << d << endl;
	printf("%d %.2lf\n", i, d);

	struct Student s = { "wangshenghao", 18 };
	
	cout << "姓名:" << s.name << endl;
	cout << "年龄:" << s.age << endl << endl;
	printf("姓名：%s\n年龄：%d\n", s.name, s.age);

	//>> 流运算提取福
	cin >> s.name >> s.age;
	scanf("%s%d", s.name, &s.age);
	return 0;
}


//缺省参数
void func(int i = 0)
{
	cout << i << endl;
}
int main()
{
	func();
	func(1);
	return 0;
}
//全缺省
void Func(int a = 10, int b = 20, int c = 30)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl << endl;
}
int main()
{
	Func();
	Func(1);
	Func(1,2);
	Func(1,2,3);
	return 0;
}
//半缺省--缺省部分参数-必须从右往左缺省-必须连续缺省
void Func(int a, int b, int c = 30)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl << endl;
}
int main()
{ 
	
	Func(1,2);
	Func(1,2,3);
	return 0;
}


引用
int main()
{
	int a = 10;
	int& b = a;
    return 0;
}//引用在语法层，我们要理解这里没有开辟新的空间，就是对原来的取了一个新名称叫做b
引用做参数
void swap(int* p1, int* p2)//传地址
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void swap(int& r1, int& r2)//传引用
{
	int tmp = r1;
	r1 = r2;
	r2 = tmp;
}
void swap(int r1, int r2)//传值
{
	int tmp = r1;
	r1 = r2;
	r2 = tmp;
}
int main()
{
	int x = 0, y = 1;
	swap(&x, &y);
	//swap(x, y);
	return 0;
}
//他们三个构成函数重载，但是swap(x,y);调用时存在歧义，不知道调用传值还是引用
