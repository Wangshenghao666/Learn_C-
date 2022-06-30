#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<vector>
#include<condition_variable>
using namespace std;

template <class ...Args>
void ShowList(Args... args)
{
	cout << sizeof...(Args) << endl;
	cout << sizeof...(args) << endl << endl; 

	//for (size_t i = 0; i < sizeof...(Args); ++i)
	//{
	//	// 无法编译，编译器无法解析
	//	cout << args[i] << "-";
	//}
	//cout << endl;

}
int main()
{
	ShowList(1);
	ShowList(1, 'A');
	ShowList(1, 'A', std::string("sort"));

	return 0;
}




 递归终止函数
template <class T>
void ShowList(const T& t)
{
	cout << t << endl << endl;
}

// 解析并打印参数包中每个参数的类型及值
template <class T, class ...Args>
void ShowList(T val, Args... args)
{
	cout << typeid(val).name() << ":" << val << endl;
	ShowList(args...);
}




template <class T>
void PrintArg(T val)
{
	T copy(val);
	cout << typeid(T).name() << ":" << val << endl;
}

//展开函数
template <class ...Args>
void ShowList(Args... args)
{
	int arr[] = { (PrintArg(args), 0)... };
	cout << endl;
}



template <class T>
int PrintArg(T val)
{
	T copy(val);
	cout << typeid(T).name() << ":" << val << endl;

	return 0;
}

//展开函数
template <class ...Args>
void ShowList(Args... args)
{
	int arr[] = { PrintArg(args)... };
	cout << endl;
}

int main()
{
	ShowList(1);
	ShowList(1, 'A');
	ShowList(1, 'A', std::string("sort"));

	return 0;
}





//////////////////////////////////////////////////////////////////////
//两个线程对同一个变量x++
int x = 0;
mutex mtx;

void Func(int n)
{
	// 加锁，加再循环里面还是循环外面？为什么？
	// 2
	mtx.lock();
	for (int i = 0; i < n; ++i)
	{
		// 1
		//cout << std::this_thread::get_id() <<"->"<< x << endl;
		++x;
	}
	mtx.unlock();
}
int main()
{
	thread t1(Func, 5000000);
	thread t2(Func, 5000000);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}




// 原子操作的++
atomic<int> x = 0;
void Func(int n)
{
	for (int i = 0; i < n; ++i)
	{
		++x;
	}
}

int main()
{
	thread t1(Func, 5000000);
	thread t2(Func, 5000000);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}



//验证
int main()
{
	//atomic<int> x = 0;
	int x = 0;
	mutex mtx;
	int N = 10000000;
	atomic<int> costTime1 = 0;

	thread t1([&]{
		int begin1 = clock();
		mtx.lock();
		for (int i = 0; i < N; ++i)
		{
			++x;
		}
		mtx.unlock();
		int end1 = clock();

		costTime1 += (end1 - begin1);
	});

	thread t2([&]{
		int begin2 = clock();
		mtx.lock();
		for (int i = 0; i < N; ++i)
		{
			++x;
		}
		mtx.unlock();

		int end2 = clock();

		costTime1 += (end2 - begin2);
	});

	t1.join();
	t2.join();

	cout << x <<":"<<costTime1 <<endl;


	return 0;
}



void func(int& x)
{
	cout << "x:" << &x << endl;
	x += 10;
}
int main()
{
	int n = 0;
	cout << "n:" << &n << endl;
	// 严格来说thread可执行函数参数不能是左值引用
	// 可以13支持C++11的bug
	thread t1(func, n);
	t1.join();

	cout << n << endl;
	return 0;
}
//改成传地址可以，也可以：
void func(int& x)
{
	cout <<"x:"<<&x << endl;
	x += 10;
}

int main()
{
	int n = 0;
	cout <<"n:"<<&n << endl;
	
	thread t1(func, std::ref(n));
	t1.join();

	cout << n << endl;

	return 0;
}




void func(vector<int>& v, int n, int base, mutex& mtx)
{
	try
	{
		// 死锁
		for (int i = 0; i < n; ++i)
		{
			mtx.lock();
			cout << this_thread::get_id() << ":" << base + i << endl;

			// 失败了 抛异常 -- 异常安全的问题
			v.push_back(base+i);
			// 模拟push_back失败抛异常
			if (base == 1000 && i == 888)
				throw bad_alloc();

			mtx.unlock();
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		mtx.unlock();
	}
}

int main()
{
	thread t1, t2;
	vector<int> vec;
	mutex mtx;

	try
	{	
		t1 = thread(func, std::ref(vec), 1000, 1000, std::ref(mtx));
		t2 = thread(func, std::ref(vec), 1000, 2000, std::ref(mtx));
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	t1.join();
	t2.join();

	for (auto e : vec)
	{
		cout << e << " ";
	}
	cout << endl << endl;
	cout << vec.size() << endl;


	return 0;
}





template<class Lock>
class LockGuard // 锁的守卫
{
public:
	LockGuard(Lock& lock)
		:_lock(lock)
	{
		_lock.lock();
	}

	~LockGuard()
	{
		_lock.unlock();
	}
private:
	Lock& _lock;
};


void func(vector<int>& v, int n, int base, mutex& mtx)
{
	try
	{
		// 死锁
		for (int i = 0; i < n; ++i)
		{
			//mtx.lock();
			//LockGuard<mutex> lock(mtx);
			//lock_guard<mutex> lock(mtx);
			unique_lock<mutex> lock(mtx);

			cout << this_thread::get_id() << ":" << base + i << endl;

			// 失败了 抛异常 -- 异常安全的问题
			v.push_back(base + i);

			// 模拟push_back失败抛异常
			if (base == 1000 && i == 888)
				throw bad_alloc();


			// mtx.unlock();
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

int main()
{
	thread t1, t2;
	vector<int> vec;
	mutex mtx;

	try
	{
		t1 = thread(func, std::ref(vec), 1000, 1000, std::ref(mtx));
		t2 = thread(func, std::ref(vec), 1000, 2000, std::ref(mtx));
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	t1.join();
	t2.join();

	for (auto e : vec)
	{
		cout << e << " ";
	}
	cout << endl << endl;
	cout << vec.size() << endl;


	return 0;
}





//两个线程交替打印，一个打印奇数 一个打印偶数
int main()
{
	int n = 100;
	int i = 0;
	mutex mtx;

	// 偶数-先打印
	thread t1([n, &i, &mtx]{
		while (i < n)
		{
			unique_lock<mutex> lock(mtx);

			cout <<this_thread::get_id()<<":"<<i << endl;
			++i;
		}
	});

	// 奇数-后打印
	thread t2([n, &i, &mtx]{
		while (i < n)
		{
			// 模拟中间某次t2时间片用完了，竞争大，排队很，多休眠了一会
			if (i == 50)
				this_thread::sleep_for(chrono::nanoseconds(100));

			unique_lock<mutex> lock(mtx);

			cout << this_thread::get_id() << ":" << i << endl;
			++i;
		}
	});

	// 交替走

	t1.join();
	t2.join();

	return 0;
}




int main()
{
	int n = 100;
	int i = 0;
	mutex mtx;
	condition_variable cv;
	bool flag = false;

	// 奇数-后打印
	thread t2([n, &i, &mtx, &cv, &flag]{
		while (i < n)
		{
			// 模拟中间某次t2时间片用完了，竞争大，排队很，多休眠了一会
			/*if (i == 50)
			{
			cout << this_thread::get_id() << "休眠3s" << endl;
			this_thread::sleep_for(chrono::seconds(3));
			}*/

			unique_lock<mutex> lock(mtx);
			// flag是false的时候，这里会一直阻塞，知道flag变成true
			cv.wait(lock, [&flag](){return flag; });

			cout << this_thread::get_id() << ":->" << i << endl;
			++i;

			flag = false;

			cv.notify_one();
		}
	});

	// 偶数-先打印
	thread t1([n, &i, &mtx, &cv, &flag]{
		while (i < n)
		{
			unique_lock<mutex> lock(mtx);
			// !flag是true,那么这里获取侯不会阻塞，优先运行了
			cv.wait(lock, [&flag](){return !flag; });

			cout << this_thread::get_id() << "->:" << i << endl;
			++i;

			// 保证下一个打印运行一定是t1，也可以防止t1连续打印运行
			flag = true;

			cv.notify_one();
		}
	});

	// 交替走

	t1.join();
	t2.join();

	return 0;
}


