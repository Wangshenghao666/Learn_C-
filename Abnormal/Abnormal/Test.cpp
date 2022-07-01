#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;

//异常
double Division(int a, int b) 
{
	 //当b == 0时抛出异常
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
		Func2();// 异常是通过抛出对象而引发的，该对象的类型决定了应该激活哪个catch的处理代码。
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



// 被选中的处理代码是调用链中与该对象类型匹配且离抛出异常位置最近的那一个。
double Division(int a, int b)
{
	// 当b == 0时抛出异常
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




// 抛出异常对象后，会生成一个异常对象的拷贝，因为抛出的异常对象可能是一个临时对象，所以会生成
//一个拷贝对象，这个拷贝的临时对象会在被catch以后销毁。（这里的处理类似于函数的传值返回）
double Division(int a, int b)
{
	// 当b == 0时抛出异常
	if (b == 0)
	{
		string str("除零错误");
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


////catch (...)可以捕获任意类型的异常，问题是不知道异常错误是什么。
//catch (...){
//	cout << "unkown exception" << endl;
//}

//异常的重新抛出
//有可能单个的catch不能完全处理一个异常，在进行一些校正处理以后，希望再交给更外层的调用链函数来处
//理，catch则可以通过重新抛出将异常传递给更上层的函数进行处理。
double Division(int a, int b) {
	// 当b == 0时抛出异常
	if (b == 0)
	{
		throw "Division by zero condition!";
	}
	return (double)a / (double)b;
}
void Func()
{
	// 这里可以看到如果发生除0错误抛出异常，另外下面的array没有得到释放。
	// 所以这里捕获异常后并不处理异常，异常还是交给外面处理，这里捕获了再
	// 重新抛出去。
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
	// 当b == 0时抛出异常
	if (b == 0)
	{
		throw "Division by zero condition!";
	}
	return (double)a / (double)b;
}

void Func()
{
	// 这里可以看到如果发生除0错误抛出异常，另外下面的array没有得到释放。
	// 所以这里捕获异常后并不处理异常，异常还是交给外面处理，这里捕获了再
	// 重新抛出去。
	int* array = new int[10];
	int len, time;
	cin >> len >> time;

	try
	{
		cout << Division(len, time) << endl;
	}
	catch (...)  // 拦截异常，不是要处理异常，而是要正常释放资源
	{
		cout << "delete []" << array << endl;
		delete[] array;
		throw;  // 捕获到什么对象就重新抛出什么对象
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
		// 记录日志
	}

	return 0;
}





