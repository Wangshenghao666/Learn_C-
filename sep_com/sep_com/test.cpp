#define _CRT_SECURE_NO_WARNINGS 1

#include"sp.h"

int main()
{
	F1(10);
	F2(10);//无法解析的外部符号 "void __cdecl F2<int>(int const &)" (??$F2@H@@YAXABH@Z)，该符号在函数 _main 中被引用
	//没有实例化出对象，所以不能调用
	F2(1.11);
	return 0;
}