#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;

//�쳣
double Division(int a, int b) 
{
	 //��b == 0ʱ�׳��쳣
	if (b == 0)
		throw "Division by zero condition!";
	else
		return ((double)a / (double)b);
}
void Func1()
{
	int len, time;
	cin >> len >> time;
	cout << Division(len, time) << endl;
}
void Func2()
{
	int len, time;
	cin >> len >> time;
	if (time != 0)
	{
		throw 1;
	}
	else
	{
		cout << len << " " << time << endl;
	}
}
int main()
{
	try {
		Func1();
		Func2();// �쳣��ͨ���׳�����������ģ��ö�������;�����Ӧ�ü����ĸ�catch�Ĵ�����롣
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	catch (int errid) 
	{
		cout << errid << endl;
	}
	catch (...)
	{
		cout << "unkown exception" << endl;
	}
	return 0;
}



// ��ѡ�еĴ�������ǵ���������ö�������ƥ�������׳��쳣λ���������һ����
double Division(int a, int b)
{
	// ��b == 0ʱ�׳��쳣
	if (b == 0)
		throw "Division by zero condition!";
	else
		return ((double)a / (double)b);
}

void Func1()
{
	try
	{
		int len, time;
		cin >> len >> time;
		cout << Division(len, time) << endl;
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
}

void Func2()
{
	int len, time;
	cin >> len >> time;
	if (time != 0)
	{
		throw 1;
	}
	else
	{
		cout << len << " " << time << endl;
	}
}

int main()
{
	try 
	{
		Func1();
		Func2();
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	catch (int errid) 
	{
		cout << errid << endl;
	}
	catch (...)
	{
		cout << "unkown exception" << endl;
	}

	return 0;
}




// �׳��쳣����󣬻�����һ���쳣����Ŀ�������Ϊ�׳����쳣���������һ����ʱ�������Ի�����
//һ���������������������ʱ������ڱ�catch�Ժ����١�������Ĵ��������ں����Ĵ�ֵ���أ�
double Division(int a, int b)
{
	// ��b == 0ʱ�׳��쳣
	if (b == 0)
	{
		string str("�������");
		throw str;
	}
	else
	{
		return ((double)a / (double)b);
	}
}

void Func1()
{
	int len, time;
	cin >> len >> time;
	cout << Division(len, time) << endl;
}

int main()
{
	try
	{
		Func1();
	}
	catch (const string& errmsg)
	{
		cout << errmsg << endl;
	}

	return 0;
}


////catch (...)���Բ����������͵��쳣�������ǲ�֪���쳣������ʲô��
//catch (...){
//	cout << "unkown exception" << endl;
//}

//�쳣�������׳�
//�п��ܵ�����catch������ȫ����һ���쳣���ڽ���һЩУ�������Ժ�ϣ���ٽ��������ĵ�������������
//��catch�����ͨ�������׳����쳣���ݸ����ϲ�ĺ������д���
double Division(int a, int b) {
	// ��b == 0ʱ�׳��쳣
	if (b == 0)
	{
		throw "Division by zero condition!";
	}
	return (double)a / (double)b;
}
void Func()
{
	// ������Կ������������0�����׳��쳣�����������arrayû�еõ��ͷš�
	// �������ﲶ���쳣�󲢲������쳣���쳣���ǽ������洦�����ﲶ������
	// �����׳�ȥ��
	int* array = new int[10];
	try {
		int len, time;
		cin >> len >> time;
		cout << Division(len, time) << endl;
	}
	catch (...)
	{
		cout << "delete []" << array << endl;
		delete[] array;
		throw;
	}
	// ...
	cout << "delete []" << array << endl;
	delete[] array;
}
int main()
{
	try
	{
		Func();
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	return 0;
}
//eg:
double Division(int a, int b)
{
	// ��b == 0ʱ�׳��쳣
	if (b == 0)
	{
		throw "Division by zero condition!";
	}
	return (double)a / (double)b;
}

void Func()
{
	// ������Կ������������0�����׳��쳣�����������arrayû�еõ��ͷš�
	// �������ﲶ���쳣�󲢲������쳣���쳣���ǽ������洦�����ﲶ������
	// �����׳�ȥ��
	int* array = new int[10];
	int len, time;
	cin >> len >> time;

	try
	{
		cout << Division(len, time) << endl;
	}
	catch (...)  // �����쳣������Ҫ�����쳣������Ҫ�����ͷ���Դ
	{
		cout << "delete []" << array << endl;
		delete[] array;
		throw;  // ����ʲô����������׳�ʲô����
	}

	cout << "delete []" << array << endl;
	delete[] array;
}

int main()
{
	try
	{
		Func();
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
		// ��¼��־
	}

	return 0;
}





