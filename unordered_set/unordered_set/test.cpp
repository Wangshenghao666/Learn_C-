#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_set>
#include<set>
#include<time.h>
using namespace std;



void test_unordered_set()
{
	//set 排序+去重
	//unordered_set 去重
	unordered_set<int> us;
	us.insert(5);
	us.insert(1);
	us.insert(5);
	us.insert(3);
	us.insert(7);
	us.insert(2);

	unordered_set<int>::iterator it = us.begin();
	while (it != us.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (auto& e : us)
	{
		cout << e << " ";
	}
	cout << endl;



	//不去重
	unordered_multiset<int> ums;
	ums.insert(5);
	ums.insert(1);
	ums.insert(5);
	ums.insert(3);
	ums.insert(7);
	ums.insert(2);

	for (auto& e : ums)
	{
		cout << e << " ";
	}cout << endl;
}


void test_op()
{
	int n = 1000000;
	vector<int> v;
	v.reserve(n);
	srand(time(0));
	for (int i = 0; i < n; ++i)
	{
		//v.push_back(i);//有序测试
		v.push_back(rand());//无序测试
	}

	size_t begin1 = clock();
	set<int> s;
	for (auto e : v)
	{
		s.insert(e);
	}
	size_t end1 = clock();

	size_t begin2 = clock();
	unordered_set<int> us;
	for (auto e : v)
	{
		us.insert(e);
	}
	size_t end2 = clock();

	cout << s.size() << endl;

	cout << "set insert:" << end1 - begin1 << endl;
	cout << "unordered_set insert:" << end2 - begin2 << endl;


	size_t begin3 = clock();
	for (auto e : v)
	{
		s.find(e);
	}
	size_t end3 = clock();

	size_t begin4 = clock();
	for (auto e : v)
	{
		us.find(e);
	}
	size_t end4 = clock();
	cout << "set find:" << end3 - begin3 << endl;
	cout << "unordered_set find:" << end4 - begin4 << endl;

	size_t begin5 = clock();
	for (auto e : v)
	{
		s.erase(e);
	}
	size_t end5 = clock();

	size_t begin6 = clock();
	for (auto e : v)
	{
		us.erase(e);
	}
	size_t end6 = clock();
	cout << "set erase:" << end5 - begin5 << endl;
	cout << "unordered_set erase:" << end6 - begin6 << endl;
}
int main()
{
	test_unordered_set();//1.遍历不按Key排序，命令体现了
	                     //2.unordered_set是单向迭代器

	test_op();//unordered_set综合效率略胜set
	return 0;
}