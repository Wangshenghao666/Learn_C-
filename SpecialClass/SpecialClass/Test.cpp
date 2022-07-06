#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>

using namespace std;

//1. 请设计一个类，只能在堆上创建对象
class HeapOnly
{
public:
	static HeapOnly* CreateObj()
	{
		return new HeapOnly;
	}

	HeapOnly(const HeapOnly& ho) = delete;//防拷贝
private:
	HeapOnly()
		:_a(0)
	{}
private:
	int _a;
};
int main()
{
	//HeapOnly ho1;
	//HeapOnly* pho = new HeapOnly;
	HeapOnly* ptr1 = HeapOnly::CreateObj();
	//HeapOnly copy(*ptr);
   return 0;
}




//2. 请设计一个类，只能在栈上创建对象
class StackOnly
{
public:
	static StackOnly CreateObj()
	{
		return StackOnly();
	}

	void* operator new(size_t size) = delete;
	void operator delete(void* p) = delete;
private:
	StackOnly()
		:_a(0)
	{}

private:
	int _a;
};

int main()
{

	//StackOnly* ptr2 = new StackOnly;
	StackOnly obj = StackOnly::CreateObj();
	//StackOnly* ptr3 = new StackOnly(obj);

	return 0;
}





//3. 请设计一个类，不能被拷贝
//C++98
//将拷贝构造函数与赋值运算符重载只声明不定义，并且将其访问权限设置为私有即可。
//原因：
//1. 设置成私有：如果只声明没有设置成private，用户自己如果在类外定义了，就可以不能禁止拷贝
//了
//2. 只声明不定义：不定义是因为该函数根本不会调用，定义了其实也没有什么意义，不写反而还简
//单，而且如果定义了就不会防止成员函数内部拷贝了。
//C++11
class CopyBan
{
	// ...

private:
	CopyBan(const CopyBan&);
	CopyBan& operator=(const CopyBan&);
	//...
};
//C++11扩展delete的用法，delete除了释放new申请的资源外，如果在默认成员函数后跟上 = delete，表
//示让编译器删除掉该默认成员函数。
class CopyBan
{
	// ...
	CopyBan(const CopyBan&) = delete;
	CopyBan& operator=(const CopyBan&) = delete;
	//...
};




//4. 请设计一个类，不能被继承
//C++98方式
// C++98中构造函数私有化，派生类中调不到基类的构造函数。则无法继承
class NonInherit
{
public:
	static NonInherit GetInstance()
	{
		return NonInherit();
	}
private:
	NonInherit()
	{}
};
//C++11方法
//final关键字，final修饰类，表示该类不能被继承。
class A final
{
	// ....
};




//5. 请设计一个类，只能创建一个对象(单例模式)
//一个类只能创建一个对象，即单例模式，该模式可以保证系统中该类只有一个实例，并提供一个访问它的全
//局访问点，该实例被所有程序模块共享。
//
//饿汉模式
//就是说不管你将来用不用，程序启动时就创建一个唯一的实例对象。
//如果这个单例对象在多线程高并发环境下频繁使用，性能要求较高，那么显然使用饿汉模式来避免资源竞
//争，提高响应速度更好。

// 饿汉模式
// 优点：简单
// 缺点：可能会导致进程启动慢，且如果有多个单例类对象实例启动顺序不确定。
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}

private:
	// 构造函数私有
	Singleton(){};

	// C++98 防拷贝
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);

	// or

	// C++11
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

	static Singleton m_instance;
};

Singleton Singleton::m_instance; // 在程序入口之前就完成单例对象的初始化




//懒汉模式
//如果单例对象构造十分耗时或者占用很多资源，比如加载插件啊， 初始化网络连接啊，读取文件啊等
//等，而有可能该对象程序运行时不会用到，那么也要在程序一开始就进行初始化，就会导致程序启动时
//非常的缓慢。 所以这种情况使用懒汉模式（延迟加载）更好。
// 懒汉
// 优点：第一次使用实例对象时，创建对象。进程启动无负载。多个单例实例启动顺序自由控制。
// 缺点：复杂



#include <mutex>
#include <thread>
using namespace std;
class Singleton
{
public:
	static Singleton* GetInstance() {
		// 注意这里一定要使用Double-Check的方式加锁，才能保证效率和线程安全
		if (nullptr == m_pInstance) {
			m_mtx.lock();
			if (nullptr == m_pInstance) {
				m_pInstance = new Singleton();
			}
			m_mtx.unlock();
		}
		return m_pInstance;
	}
	// 实现一个内嵌垃圾回收类 
	class CGarbo {
	public:
		~CGarbo(){
			if (Singleton::m_pInstance)
				delete Singleton::m_pInstance;
		}
	};
	// 定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数从而释放单例对象
	static CGarbo Garbo;
private:
	// 构造函数私有
	Singleton(){};
	// 防拷贝
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
	static Singleton* m_pInstance; // 单例对象指针
	static mutex m_mtx; //互斥锁
};
Singleton* Singleton::m_pInstance = nullptr;
Singleton::CGarbo Garbo;
mutex Singleton::m_mtx;
void func(int n) {
	cout << Singleton::GetInstance() << endl;
}
// 多线程环境下演示上面GetInstance()加锁和不加锁的区别。
int main()
{
	thread t1(func, 10);
	thread t2(func, 10);
	t1.join();
	t2.join();
	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;
}