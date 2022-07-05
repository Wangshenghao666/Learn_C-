#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

 //boost->scoped_ptr/shared_ptr/weak_ptr

 //C++11库才更新智能指针实现
 //C++11将boost库中智能指针精华部分吸收了过来
 //C++11->unique_ptr/shared_ptr/weak_ptr

 //unique_ptr/scoped_ptr
 //原理：简单粗暴 -- 防拷贝
namespace wsh
{
	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
			}
		}

		// 像指针一样使用
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		unique_ptr(const unique_ptr<T>& sp) = delete;

	private:
		T* _ptr;
	};
}

//int main()
//{
//	/*wsh::unique_ptr<int> sp1(new int);
//	wsh::unique_ptr<int> sp2(sp1);*/
//
//	std::unique_ptr<int> sp1(new int);
//	//std::unique_ptr<int> sp2(sp1);
//
//	return 0;
//}


//---------------------------------------------------------------------------------------------------------

 //需要拷贝场景怎么办？
namespace wsh
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr)
		{
			_refCount = 1;
		}

		shared_ptr(shared_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			++_refCount;
		}

		~shared_ptr()
		{
			if (--_refCount == 0 && _ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
			}
		}

		// 像指针一样使用
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
		static int _refCount;
	};

	template<class T>
	int shared_ptr<T>::_refCount = 0;
}


int main()
{
	wsh::shared_ptr<int> sp1(new int);
	wsh::shared_ptr<int> sp2(sp1);
	wsh::shared_ptr<int> sp3(sp1);

	wsh::shared_ptr<int> sp4(new int);

	//std::unique_ptr<int> sp1(new int);
	//std::unique_ptr<int> sp2(sp1);

	return 0;
}
//解决如下：

namespace wsh
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr)
			, _pRefCount(new int(1))
		{}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pRefCount(sp._pRefCount)
		{
			++(*_pRefCount);
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp);

		~shared_ptr()
		{
			if (--(*_pRefCount) == 0 && _ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
				delete _pRefCount;

				_ptr = nullptr;
				_pRefCount = nullptr;
			}
		}

		 像指针一样使用
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
		int* _pRefCount;
	};
}


int main()
{
	wsh::shared_ptr<int> sp1(new int);
	wsh::shared_ptr<int> sp2(sp1);
	wsh::shared_ptr<int> sp3(sp1);

	wsh::shared_ptr<int> sp4(new int);

	return 0;
}
//---------------------------------------------------------------------------------------------------------
//解决：
// 引用计数支持多个拷贝管理同一个资源，最后一个析构对象释放资源

// shared_ptr智能指针是线程安全的吗？
// 是的，引用计数的加减是加锁保护的。但是指向资源不是线程安全的

// 指向堆上资源的线程安全问题是访问的人处理的，智能指针不管，也管不了
// 引用计数的线程安全问题，是智能指针要处理的
namespace wsh
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _pRefCount(new int(1))
			, _pmtx(new mutex)
		{}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pRefCount(sp._pRefCount)
			, _pmtx(sp._pmtx)
		{
			AddRef();
		}

		void Release()
		{
			_pmtx->lock();

			bool flag = false;
			if (--(*_pRefCount) == 0 && _ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
				delete _pRefCount;

				flag = true;
			}

			_pmtx->unlock();

			if (flag == true)
			{
				delete _pmtx;
			}
		}

		void AddRef()
		{
			_pmtx->lock();

			++(*_pRefCount);

			_pmtx->unlock();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			//if (this != &sp)
			if (_ptr != sp._ptr)
			{
				Release();

				_ptr = sp._ptr;
				_pRefCount = sp._pRefCount;
				_pmtx = sp._pmtx;
				AddRef();
			}

			return *this;
		}

		int use_count()
		{
			return *_pRefCount;
		}

		~shared_ptr()
		{
			Release();
		}

		// 像指针一样使用
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T* get() const
		{
			return _ptr;
		}
	private:
		T* _ptr;
		int* _pRefCount;
		mutex* _pmtx;
	};

	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()
			:_ptr(nullptr)
		{}

		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get())
		{}

		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();

			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}


	private:
		T* _ptr;
	};




	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()
			:_ptr(nullptr)
		{}

		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get())
		{}

		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();

			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}


	private:
		T* _ptr;
	};
}


//int main()
//{
//	wsh::shared_ptr<int> sp1(new int);
// 	wsh::shared_ptr<int> sp2(sp1);
//	wsh::shared_ptr<int> sp3(sp1);
//
//	wsh::shared_ptr<int> sp4(new int);
//	wsh::shared_ptr<int> sp5(sp4);
//
//	//sp1 = sp1;
//	//sp1 = sp2;
//
//	//sp1 = sp4;
//	//sp2 = sp4;
//	//sp3 = sp4;
//
//	*sp1 = 2;
//	*sp2 = 3;
//
//	return 0;
//}
struct Date
{
	int _year = 0;
	int _month = 0;
	int _day = 0;
};

void SharePtrFunc(wsh::shared_ptr<Date>& sp, size_t n, mutex& mtx)
{
	cout << sp.get() << endl;

	for (size_t i = 0; i < n; ++i)
	{
		// 这里智能指针拷贝会++计数，智能指针析构会--计数，这里是线程安全的。
		wsh::shared_ptr<Date> copy(sp);

		// 这里智能指针访问管理的资源，不是线程安全的。所以我们看看这些值两个线程++了2n次，但是最终看到的结果，并一定是加了2n

		{
			unique_lock<mutex> lk(mtx);
			copy->_year++;
			copy->_month++;
			copy->_day++;
		}

		//...
		//cout<<"hello"<<endl;
	}
}
int main()
{
	wsh::shared_ptr<Date> p(new Date);
	cout << p.get() << endl;
	const size_t n = 100000;
	mutex mtx;
	thread t1(SharePtrFunc, std::ref(p), n, std::ref(mtx));
	thread t2(SharePtrFunc, std::ref(p), n, std::ref(mtx));

	t1.join();
	t2.join();

	cout << p->_year << endl;
	cout << p->_month << endl;
	cout << p->_day << endl;

	cout << p.use_count() << endl;

	return 0;
}




