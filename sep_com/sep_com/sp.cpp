#define _CRT_SECURE_NO_WARNINGS 1

#include"sp.h"

void F1(int n)
{
	cout << "void F1(int n)" << endl;
}


template<class T>
void F2(const T& n)
{
	cout << "void F2(const T& n)" << endl;
}
//���1.
//��һ���͵���ʾʵ����һ��
template
void F2<int>(const int& n);
template
void F2<double>(const double& n);

//���2.
//�����Ͷ��岻���루�����������ַ�����
//��ôʹ�����ĵط���ͷ�ļ�չ���Ժ�ֱ�Ӿ���ģ�嶨���ʵ��������ôֱ�ӾͿ���
//���Ϻ������õ�ַ������Ҫ����ȥ����