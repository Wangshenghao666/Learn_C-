#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>

using namespace std;

//1. �����һ���ֻ࣬���ڶ��ϴ�������
class HeapOnly
{
public:
	static HeapOnly* CreateObj()
	{
		return new HeapOnly;
	}

	HeapOnly(const HeapOnly& ho) = delete;//������
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




//2. �����һ���ֻ࣬����ջ�ϴ�������
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





//3. �����һ���࣬���ܱ�����
//C++98
//���������캯���븳ֵ���������ֻ���������壬���ҽ������Ȩ������Ϊ˽�м��ɡ�
//ԭ��
//1. ���ó�˽�У����ֻ����û�����ó�private���û��Լ���������ⶨ���ˣ��Ϳ��Բ��ܽ�ֹ����
//��
//2. ֻ���������壺����������Ϊ�ú�������������ã���������ʵҲû��ʲô���壬��д��������
//����������������˾Ͳ����ֹ��Ա�����ڲ������ˡ�
//C++11
class CopyBan
{
	// ...

private:
	CopyBan(const CopyBan&);
	CopyBan& operator=(const CopyBan&);
	//...
};
//C++11��չdelete���÷���delete�����ͷ�new�������Դ�⣬�����Ĭ�ϳ�Ա��������� = delete����
//ʾ�ñ�����ɾ������Ĭ�ϳ�Ա������
class CopyBan
{
	// ...
	CopyBan(const CopyBan&) = delete;
	CopyBan& operator=(const CopyBan&) = delete;
	//...
};




//4. �����һ���࣬���ܱ��̳�
//C++98��ʽ
// C++98�й��캯��˽�л����������е���������Ĺ��캯�������޷��̳�
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
//C++11����
//final�ؼ��֣�final�����࣬��ʾ���಻�ܱ��̳С�
class A final
{
	// ....
};




//5. �����һ���ֻ࣬�ܴ���һ������(����ģʽ)
//һ����ֻ�ܴ���һ�����󣬼�����ģʽ����ģʽ���Ա�֤ϵͳ�и���ֻ��һ��ʵ�������ṩһ����������ȫ
//�ַ��ʵ㣬��ʵ�������г���ģ�鹲��
//
//����ģʽ
//����˵�����㽫���ò��ã���������ʱ�ʹ���һ��Ψһ��ʵ������
//���������������ڶ��̸߲߳���������Ƶ��ʹ�ã�����Ҫ��ϸߣ���ô��Ȼʹ�ö���ģʽ��������Դ��
//���������Ӧ�ٶȸ��á�

// ����ģʽ
// �ŵ㣺��
// ȱ�㣺���ܻᵼ�½�����������������ж�����������ʵ������˳��ȷ����
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}

private:
	// ���캯��˽��
	Singleton(){};

	// C++98 ������
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);

	// or

	// C++11
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

	static Singleton m_instance;
};

Singleton Singleton::m_instance; // �ڳ������֮ǰ����ɵ�������ĳ�ʼ��




//����ģʽ
//�������������ʮ�ֺ�ʱ����ռ�úܶ���Դ��������ز������ ��ʼ���������Ӱ�����ȡ�ļ�����
//�ȣ����п��ܸö����������ʱ�����õ�����ôҲҪ�ڳ���һ��ʼ�ͽ��г�ʼ�����ͻᵼ�³�������ʱ
//�ǳ��Ļ����� �����������ʹ������ģʽ���ӳټ��أ����á�
// ����
// �ŵ㣺��һ��ʹ��ʵ������ʱ���������󡣽��������޸��ء��������ʵ������˳�����ɿ��ơ�
// ȱ�㣺����



#include <mutex>
#include <thread>
using namespace std;
class Singleton
{
public:
	static Singleton* GetInstance() {
		// ע������һ��Ҫʹ��Double-Check�ķ�ʽ���������ܱ�֤Ч�ʺ��̰߳�ȫ
		if (nullptr == m_pInstance) {
			m_mtx.lock();
			if (nullptr == m_pInstance) {
				m_pInstance = new Singleton();
			}
			m_mtx.unlock();
		}
		return m_pInstance;
	}
	// ʵ��һ����Ƕ���������� 
	class CGarbo {
	public:
		~CGarbo(){
			if (Singleton::m_pInstance)
				delete Singleton::m_pInstance;
		}
	};
	// ����һ����̬��Ա�������������ʱ��ϵͳ���Զ������������������Ӷ��ͷŵ�������
	static CGarbo Garbo;
private:
	// ���캯��˽��
	Singleton(){};
	// ������
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
	static Singleton* m_pInstance; // ��������ָ��
	static mutex m_mtx; //������
};
Singleton* Singleton::m_pInstance = nullptr;
Singleton::CGarbo Garbo;
mutex Singleton::m_mtx;
void func(int n) {
	cout << Singleton::GetInstance() << endl;
}
// ���̻߳�������ʾ����GetInstance()�����Ͳ�����������
int main()
{
	thread t1(func, 10);
	thread t2(func, 10);
	t1.join();
	t2.join();
	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;
}