#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
using namespace std;

void test_vector1()
{
	vector<int> v1;
	vector<int> v2(10, 8);//10���ռ�,��ʼ����8
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
	//����
	//1.
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] += 1;//�����޸�ֵ
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

	//eg:ԭ��ָ�������Ȼ�ĵ�����������֧�ַ�Χfor,�ᱻ�滻��ָ��
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

	cout << v.max_size() << endl;//ÿһ�����ε����ֵ

	v.reserve(100);//���ݣ���Ӱ�����ݸ���
	v.resize(100);//�����������100
	v.resize(2);//�������ɾ��2

	//v[3];//���ö��Լ��Խ��
	//at[3];//�����쳣

	v.assign(10, 5);//���ԭ�������ݸ��ǵ�������д���µ�����

}
//��
#include<algorithm>
void test_vector5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//findʹ��Ҫ�õ���������ʽ
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

	//ɾ��ͬ�ϣ�
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