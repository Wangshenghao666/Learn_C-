#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
//C++���������
using namespace std;
struct Student
{
	char name[20];
	int age;
	//...
};
int main()
{
	//������<<
	cout << "hello world" << endl;
	const char* str = "hello Linux";
	cout << str << endl;
	int i = 0;
	double d = 1.11;
	cout << i << " " << d << endl;
	printf("%d %.2lf\n", i, d);

	struct Student s = { "wangshenghao", 18 };
	
	cout << "����:" << s.name << endl;
	cout << "����:" << s.age << endl << endl;
	printf("������%s\n���䣺%d\n", s.name, s.age);

	//>> ��������ȡ��
	cin >> s.name >> s.age;
	scanf("%s%d", s.name, &s.age);
	return 0;
}


//ȱʡ����
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
//ȫȱʡ
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
//��ȱʡ--ȱʡ���ֲ���-�����������ȱʡ-��������ȱʡ
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


����
int main()
{
	int a = 10;
	int& b = a;
    return 0;
}//�������﷨�㣬����Ҫ�������û�п����µĿռ䣬���Ƕ�ԭ����ȡ��һ�������ƽ���b
����������
void swap(int* p1, int* p2)//����ַ
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void swap(int& r1, int& r2)//������
{
	int tmp = r1;
	r1 = r2;
	r2 = tmp;
}
void swap(int r1, int r2)//��ֵ
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
//�����������ɺ������أ�����swap(x,y);����ʱ�������壬��֪�����ô�ֵ��������
