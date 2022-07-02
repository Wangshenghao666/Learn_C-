#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<time.h>
#include<thread>
using namespace std;

// 服务器开发中通常使用的异常继承体系
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{}

	virtual string what() const
	{
		return _errmsg;
	}
protected:
	string _errmsg;
	int _id;
};

class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{}

	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;

		return str;
	}

private:
	const string _sql;
};

class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{}

	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};

class HttpServerException : public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		, _type(type)
	{}

	virtual string what() const
	{
		string str = "HttpServerException:";
		str += _type;
		str += ":";
		str += _errmsg;

		return str;
	}

private:
	const string _type;
};

void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不足", 100, "select * from name = '张三'");
	}

	//throw "xxxxxx";
}

void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不足", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}

	SQLMgr();
}

void HttpServer()
{
	// ...
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("请求资源不存在", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("权限不足", 101, "post");
	}

	CacheMgr();
}

void ServerStart()
{
	while (1)
	{
		this_thread::sleep_for(chrono::seconds(1));

		try{
			HttpServer();
		}
		catch (const Exception& e) // 这里捕获父类对象就可以
		{
			// 多态
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
}

int main()
{
	ServerStart();

	return 0;
}

//int main()
//{
//	try{
//		vector<int> v(10, 5);
//		// 这里如果系统内存不够也会抛异常
//		//v.reserve(1000000000);
//
//		// 这里越界会抛异常
//		v.at(10) = 100;
//	}
//	catch (const exception& e) // 这里捕获父类对象就可以
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "Unkown Exception" << endl;
//	}
//
//	return 0;
//}