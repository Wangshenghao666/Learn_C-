#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

 //boost->scoped_ptr/shared_ptr/weak_ptr

 //C++11��Ÿ�������ָ��ʵ��
 //C++11��boost��������ָ�뾫�����������˹���
 //C++11->unique_ptr/shared_ptr/weak_ptr

 //unique_ptr/scoped_ptr
 //ԭ���򵥴ֱ� -- ������
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

		// ��ָ��һ��ʹ��
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

 //��Ҫ����������ô�죿
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

		// ��ָ��һ��ʹ��
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
//������£�

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

		 ��ָ��һ��ʹ��
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
//�����
// ���ü���֧�ֶ����������ͬһ����Դ�����һ�����������ͷ���Դ

// shared_ptr����ָ�����̰߳�ȫ����
// �ǵģ����ü����ļӼ��Ǽ��������ġ�����ָ����Դ�����̰߳�ȫ��

// ָ�������Դ���̰߳�ȫ�����Ƿ��ʵ��˴���ģ�����ָ�벻�ܣ�Ҳ�ܲ���
// ���ü������̰߳�ȫ���⣬������ָ��Ҫ�����
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

		// ��ָ��һ��ʹ��
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
		// ��������ָ�뿽����++����������ָ��������--�������������̰߳�ȫ�ġ�
		wsh::shared_ptr<Date> copy(sp);

		// ��������ָ����ʹ������Դ�������̰߳�ȫ�ġ��������ǿ�����Щֵ�����߳�++��2n�Σ��������տ����Ľ������һ���Ǽ���2n

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




