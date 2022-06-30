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
	//	// �޷����룬�������޷�����
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




 �ݹ���ֹ����
template <class T>
void ShowList(const T& t)
{
	cout << t << endl << endl;
}

// ��������ӡ��������ÿ�����������ͼ�ֵ
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

//չ������
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

//չ������
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
//�����̶߳�ͬһ������x++
int x = 0;
mutex mtx;

void Func(int n)
{
	// ����������ѭ�����滹��ѭ�����棿Ϊʲô��
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




// ԭ�Ӳ�����++
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



//��֤
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
	// �ϸ���˵thread��ִ�к���������������ֵ����
	// ����13֧��C++11��bug
	thread t1(func, n);
	t1.join();

	cout << n << endl;
	return 0;
}
//�ĳɴ���ַ���ԣ�Ҳ���ԣ�
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
		// ����
		for (int i = 0; i < n; ++i)
		{
			mtx.lock();
			cout << this_thread::get_id() << ":" << base + i << endl;

			// ʧ���� ���쳣 -- �쳣��ȫ������
			v.push_back(base+i);
			// ģ��push_backʧ�����쳣
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
class LockGuard // ��������
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
		// ����
		for (int i = 0; i < n; ++i)
		{
			//mtx.lock();
			//LockGuard<mutex> lock(mtx);
			//lock_guard<mutex> lock(mtx);
			unique_lock<mutex> lock(mtx);

			cout << this_thread::get_id() << ":" << base + i << endl;

			// ʧ���� ���쳣 -- �쳣��ȫ������
			v.push_back(base + i);

			// ģ��push_backʧ�����쳣
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





//�����߳̽����ӡ��һ����ӡ���� һ����ӡż��
int main()
{
	int n = 100;
	int i = 0;
	mutex mtx;

	// ż��-�ȴ�ӡ
	thread t1([n, &i, &mtx]{
		while (i < n)
		{
			unique_lock<mutex> lock(mtx);

			cout <<this_thread::get_id()<<":"<<i << endl;
			++i;
		}
	});

	// ����-���ӡ
	thread t2([n, &i, &mtx]{
		while (i < n)
		{
			// ģ���м�ĳ��t2ʱ��Ƭ�����ˣ��������ŶӺܣ���������һ��
			if (i == 50)
				this_thread::sleep_for(chrono::nanoseconds(100));

			unique_lock<mutex> lock(mtx);

			cout << this_thread::get_id() << ":" << i << endl;
			++i;
		}
	});

	// ������

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

	// ����-���ӡ
	thread t2([n, &i, &mtx, &cv, &flag]{
		while (i < n)
		{
			// ģ���м�ĳ��t2ʱ��Ƭ�����ˣ��������ŶӺܣ���������һ��
			/*if (i == 50)
			{
			cout << this_thread::get_id() << "����3s" << endl;
			this_thread::sleep_for(chrono::seconds(3));
			}*/

			unique_lock<mutex> lock(mtx);
			// flag��false��ʱ�������һֱ������֪��flag���true
			cv.wait(lock, [&flag](){return flag; });

			cout << this_thread::get_id() << ":->" << i << endl;
			++i;

			flag = false;

			cv.notify_one();
		}
	});

	// ż��-�ȴ�ӡ
	thread t1([n, &i, &mtx, &cv, &flag]{
		while (i < n)
		{
			unique_lock<mutex> lock(mtx);
			// !flag��true,��ô�����ȡ�������������������
			cv.wait(lock, [&flag](){return !flag; });

			cout << this_thread::get_id() << "->:" << i << endl;
			++i;

			// ��֤��һ����ӡ����һ����t1��Ҳ���Է�ֹt1������ӡ����
			flag = true;

			cv.notify_one();
		}
	});

	// ������

	t1.join();
	t2.join();

	return 0;
}


