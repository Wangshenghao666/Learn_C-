#define _CRT_SECURE_NO_WARNINGS 1

#include"sp.h"

int main()
{
	F1(10);
	F2(10);//�޷��������ⲿ���� "void __cdecl F2<int>(int const &)" (??$F2@H@@YAXABH@Z)���÷����ں��� _main �б�����
	//û��ʵ�������������Բ��ܵ���
	F2(1.11);
	return 0;
}