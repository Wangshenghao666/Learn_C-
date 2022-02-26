#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
string
常见的构造string();string (const char* s);string (const string& str);
           无参       构造对象                拷贝构造
#include<string>
int main()
{
	string s1;//构造空的string类对象s1
	string s2("hello world");
	string s3(s2);

	cin >> s1;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;

	string (const string& str, size_t pos, size_t len = npos);用某一部分去初始化
	string s4(s2, 2, 6);
	cout << s4 << endl;
	
	string s5(s2, 2);
	cout << s5 << endl;
	
	string s6(s2, 2, 100);
	cout << s6 << endl;

	string (const char* s, size_t n);取前n个值
	string s7("hello world", 5);
	cout << s7 << endl;

	string (size_t n, char c);n个数来填充字符
	string s8(10, '!');
	cout << s8 << endl;

	return 0;
}


int main()
{
	string s1;
	cin >> s1;
	 不包含最后作为结尾标识符的\0 , 有效字符的长度
	cout << s1.size() << endl;
	cout << s1.length() << endl;

	cout << s1.max_size() << endl;//zui da shu
	cout << s1 << endl;

	cout << s1.capacity() << endl;//容量
	s1.clear();//清空有效数据
	cout << s1 << endl;
	cout << s1.capacity() << endl;


	return 0;
}


char& operator[] (size_t pos)//这里的引用支持修改返回对象
{
  assert(pos < _size);
	return _str[pos];
}
opreator[]:可以向数组一样访问元素、修改
int main()
{
	string s1("hello world");
	cout << s1 << endl;
	for (size_t i = 0; i < s1.size(); ++i)
	{
		cout << s1.operator[](i) << " ";
		cout << s1[i] << " ";
	}
	cout << endl;

	for (size_t i = 0; i < s1.size(); ++i)
	{
		s1[i] += 1;
	}
	cout << endl;

	cout << s1 << endl;
	for (size_t i = 0; i < s1.size(); ++i)
	{
		s1.at(i) -= 1;
	}
	cout << endl;
	cout << s1 << endl;
	return 0;
}


int main()
{
	string s1;
	s1.push_back('a');
	s1.append("bcde");
	cout << s1 << endl;

	s1 += ':';
	s1 += "hello world";
	cout << s1 << endl;


	return 0;
}


辩立数组的方式
void test_string1()
{
	string s1("hello world");

	// 遍历+修改
	// 方式1：下标+[]
	for (size_t i = 0; i < s1.size(); ++i)
	{
		s1[i] += 1;
	}

	for (size_t i = 0; i < s1.size(); ++i)
	{
		cout << s1[i] << " ";
	}
	cout << endl;

	// 方式2：迭代器
	string::iterator it = s1.begin();
	while (it != s1.end())
	{
		*it -= 1;
		++it;
	}
	cout << endl;

	it = s1.begin();
	while (it != s1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	// 方式3：范围for,自动往后迭代，自动判断结束
	// C++11
	//for (char& e : s1)
	for (auto& e : s1)
	{
		e -= 1;
	}

	for (auto e : s1)
	{
		cout << e << " ";
	}
	cout << endl;
}
//反向迭代器（逆置）
void test_string2()
{
	string s1("hello world");
	//string::reverse_iterator rit = s1.rbegin();
	//上面代码也可以写成：
	auto rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

//reserve(申请空间)
void TestPushBack()
{
	string s;
	s.reserve(1000); // 申请至少能存储1000个字符的空间
	size_t sz = s.capacity();
	cout << "capacity changed: " << sz << '\n';
	cout << "making s grow:\n";
	for (int i = 0; i < 1000; ++i)
	{
		//s.push_back('c');
		s += 'c';
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

//reserve 和resize区别
void test_string3()
{
	string s1;
	s1.reserve(100);

	string s2;
	s2.resize(100, 'x');

	string s3("hello world");
	s3.reserve(100);

	string s4("hello world");
	s4.resize(100, 'x');

	string s5("hello world");
	s5.resize(5);
}

//查
void test_string4()
{
	string s("hello world");
	cout << s << endl;
	cout << s.c_str() << endl;

	//string file("test.txt");
	//FILE* fout = fopen(file.c_str(), "w");

	//// 要求你取出文件的后缀名
	//size_t pos = file.find('.');
	//if (pos != string::npos)
	//{
	//	//string suffix = file.substr(pos, file.size() - pos);
	//	string suffix = file.substr(pos);
	//	cout << suffix << endl;
	//}

	string file("test.txt.zip");
	FILE* fout = fopen(file.c_str(), "w");

	// 要求你取出文件的后缀名
	size_t pos = file.rfind('.');
	if (pos != string::npos)
	{
		//string suffix = file.substr(pos, file.size() - pos);
		string suffix = file.substr(pos);
		cout << suffix << endl;
	}

	//打印协议，域名，目录
	// http://www.cplusplus.com/reference/string/string/
	// https://translate.google.cn/?sl=zh-CN&tl=en&text=%E5%90%8E%E7%BC%80&op=translate
	string url("http://www.cplusplus.com/reference/string/string/find/");
	size_t pos1 = url.find(':');
	string protocol = url.substr(0, pos1 - 0);
	cout << protocol << endl;

	size_t pos2 = url.find('/', pos1 + 3);
	string domain = url.substr(pos1 + 3, pos2 - (pos1 + 3));
	cout << domain << endl;

	string uri = url.substr(pos2 + 1);
	cout << uri << endl;
}

插
void test_string5()
{
	string s("hello world");
	s += ' ';
	s += "!!!!";
	cout << endl;

	 头插  效率，O(N),尽量少用
	s.insert(0, 1, 'x');
	s.insert(s.begin(), 'y');
	s.insert(0, "test");
	cout << s << endl;

	 中间位置插入
	s.insert(4, "&&&&&");
	cout << s << endl;
}

删
void test_string6()
{
	string s("hello world");
	 尽量少用头部和中间删除，因为要挪动数据，效率低
	s.erase(0, 1);
	s.erase(s.size() - 1, 1);
	cout << s << endl;

	s.erase(3);
	cout << s << endl;
}
int main()
{
	test_string1();
	test_string2();
	TestPushBack();
	test_string3();
	test_string4();
	test_string5();
	test_string6();

	getline用法：
	string s1, s2;
	cin >> s1;
	cin >> s2;
	char ch = getchar();
	char ch;
	cin >> ch;
	char ch = cin.get();
	while (ch != '\n')
	{
		s1 += ch;
		ch = getchar();
		cin >> ch;
	}
	cout << s1 << endl;
	return 0;
}