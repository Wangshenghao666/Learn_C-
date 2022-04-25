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
//解决1.
//用一个就得显示实例化一个
template
void F2<int>(const int& n);
template
void F2<double>(const double& n);

//解决2.
//声明和定义不分离（基本采用这种方法）
//那么使用它的地方，头文件展开以后，直接就有模板定义和实例化，呢么直接就可以
//填上函数调用地址，不需要连接去找了