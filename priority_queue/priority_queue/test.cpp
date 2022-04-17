#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<assert.h>
#include<stdbool.h>
#include <functional>
#include<vector>
#include<deque>
using namespace std;

#include"priority_queue.h"


int main()
{
	//wsh::test_priority_queue();


	//Less<int> less;//Less->仿函数类型。less就叫函数对象
	//cout << less(1, 2) << endl;//相当于重载了cout << less.operator()(1,2) << endl;
	//cout << Less<int>()(1, 2) << endl;
	//cout << Less<double>()(1.1, 2.2) << endl;
	zj::test_priority_queue();

	return 0;
}