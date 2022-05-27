#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<set>
using namespace std;



//void test_set1()
//{
//	//排序+去重
//	set<int> s;
//	s.insert(3);
//	s.insert(1);
//	s.insert(5);
//	s.insert(2);
//	s.insert(6);
//	
//	set<int>::iterator it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	auto pos = s.find(3);
//	if (pos != s.end())
//	{
//		s.erase(pos);
//	}
//	it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//}
//void test_multiset()
//{
//	//允许数值一样，排序
//	multiset<int> s;
//	s.insert(3);
//	s.insert(1);
//	s.insert(5);
//	s.insert(2);
//	s.insert(8);
//	s.insert(1);
//	s.insert(8);
//
//	multiset<int>::iterator it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	multiset<int>::iterator pos = s.find(1);
//	//while (pos != s.end())
//	//{
//	//	cout << *pos << " ";
//	//	++pos;
//	//}
//	//cout << endl;
//	//find的val有多个值时，返回中序第一个val值所在节点的迭代器
//
//	//pos = s.find(1);
//	while (pos != s.end() && *pos == 1)
//	{
//		auto next = pos;
//		++next;
//		s.erase(pos);
//		pos = next;
//	}
//	it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	//也可以
//	cout << s.erase(8) << endl;
//	for (auto e : s)
//	{
//		cout << e << " ";
//
//	}
//	cout << endl;
//}
//int main()
//{
//	test_multiset();//不允许修改，会报错。
//	//test_set1();
//	return 0;
//}





#include<map>
#include<string>


void test_map1()
{
	//1.
	map<string, string> dict;
	pair<string, string> kvl("sort", "排序");
	dict.insert(kvl);
	//2.
	dict.insert(pair<string, string>("sort", "排序"));
	//3.
	dict.insert(make_pair("test", "测试"));//自动推导类型

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		//cout << (*it).first << ":" << (*it).second << endl;
		cout << it->first << ":" << it->second << endl;

		//以上两种都可
		++it;
	}

}

void test_map2()
{
	string arr[] = { "苹果", "苹果", "香蕉", "苹果", "香蕉", "苹果", "樱桃" };
	map<string, int> countMap;
	/*for (auto& str : arr)
	{
		auto ret = countMap.find(str);
		if (ret == countMap.end())
		{
			countMap.insert(make_pair(str, 1));
		}
		else
		{
			ret->second++;
		}
	}*/

	//上面优化
	for (auto& str : arr)
	{
		auto kv = countMap.insert(make_pair(str, 1));
		if (kv.second == false)
		{
			kv.first->second++;
		}
	}
	for (auto& kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
	cout << endl;
}


void test_map3()
{
	map<string, string> dict;
	dict.insert(make_pair("sort", "排序"));
	dict.insert(make_pair("left", "左边"));
	dict.insert(make_pair("left", "剩余"));

	dict["left"] = "剩余"; // 修改
	dict["test"];          // 插入
	cout << dict["sort"] << endl; // 查找

	dict["string"] = "字符串"; // 插入+修改
}


void test_map4()
{
	multimap<string, string> dict;
	dict.insert(make_pair("sort", "排序"));
	dict.insert(make_pair("left", "左边"));
	dict.insert(make_pair("left", "剩余"));
	dict.insert(make_pair("left", "剩余"));

	cout << dict.count("left") << endl;
}
int main()
{
	//test_map1();
	//test_map2();
	//test_map3();
	test_map4();
	return 0;
}