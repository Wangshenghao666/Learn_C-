#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
using namespace std;

void test_vector1()
{
	vector<int> v1;
	vector<int> v2(10, 8);//10个空间,初始化成8
	vector<int> v3(++v2.begin(), --v2.end());
	vector<int> v4(v3);

	string s("zhangjin");
	vector<int> v5(s.begin(), s.end());
}
void test_vector2()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//遍历
	//1.
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] += 1;//可以修改值
		cout << v[i] << " ";
	}
	cout << endl;
	//2.
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		*it -= 1;
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//3.
	for (auto e : v)
	{
		cout << e << " ";
	}

	cout << endl;

	//eg:原生指针就是天然的迭代器，数组支持范围for,会被替换成指针
	int a[] = { 1, 2, 3 };
	for (int* p = a; p < a + sizeof(a) / sizeof(int); ++p)
	{
		//...
	}
}
void test_vector3()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	cout << v.max_size() << endl;//每一个整形的最大值

	v.reserve(100);//扩容，不影响数据个数
	v.resize(100);//会把数据扩到100
	v.resize(2);//会把数据删到2

	//v[3];//会用断言检查越界
	//at[3];//会抛异常

	v.assign(10, 5);//会把原来的数据覆盖掉，重新写入新的数据

}
//查
#include<algorithm>
void test_vector5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//find使用要用迭代器的形式
	vector<int>::iterator ret = find(v.begin(), v.end(),3);
	if (ret != v.end())
	{
		cout << "zhaodaoli" << endl;
		v.insert(ret, 30);
	}
	v.insert(v.begin(), -1);
	for (auto e : v)
	{
		cout << e << endl;
	}

	//删（同上）
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	if (pos != v.end())
	{
		v.erase(pos);
	}
	for (auto e : v)
	{
		cout << e << endl;
	}
}
int main()
{
	test_vector3();
	return 0;
}