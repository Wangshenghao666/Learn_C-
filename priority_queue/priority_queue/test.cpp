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


	//Less<int> less;//Less->�º������͡�less�ͽк�������
	//cout << less(1, 2) << endl;//�൱��������cout << less.operator()(1,2) << endl;
	//cout << Less<int>()(1, 2) << endl;
	//cout << Less<double>()(1.1, 2.2) << endl;
	zj::test_priority_queue();

	return 0;
}