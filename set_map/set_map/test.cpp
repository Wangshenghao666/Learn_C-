#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<set>
using namespace std;



//void test_set1()
//{
//	//����+ȥ��
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
//	//������ֵһ��������
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
//	//find��val�ж��ֵʱ�����������һ��valֵ���ڽڵ�ĵ�����
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
//	//Ҳ����
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
//	test_multiset();//�������޸ģ��ᱨ��
//	//test_set1();
//	return 0;
//}





#include<map>
#include<string>


void test_map1()
{
	//1.
	map<string, string> dict;
	pair<string, string> kvl("sort", "����");
	dict.insert(kvl);
	//2.
	dict.insert(pair<string, string>("sort", "����"));
	//3.
	dict.insert(make_pair("test", "����"));//�Զ��Ƶ�����

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		//cout << (*it).first << ":" << (*it).second << endl;
		cout << it->first << ":" << it->second << endl;

		//�������ֶ���
		++it;
	}

}

void test_map2()
{
	string arr[] = { "ƻ��", "ƻ��", "�㽶", "ƻ��", "�㽶", "ƻ��", "ӣ��" };
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

	//�����Ż�
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
	dict.insert(make_pair("sort", "����"));
	dict.insert(make_pair("left", "���"));
	dict.insert(make_pair("left", "ʣ��"));

	dict["left"] = "ʣ��"; // �޸�
	dict["test"];          // ����
	cout << dict["sort"] << endl; // ����

	dict["string"] = "�ַ���"; // ����+�޸�
}


void test_map4()
{
	multimap<string, string> dict;
	dict.insert(make_pair("sort", "����"));
	dict.insert(make_pair("left", "���"));
	dict.insert(make_pair("left", "ʣ��"));
	dict.insert(make_pair("left", "ʣ��"));

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