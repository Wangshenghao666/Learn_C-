#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
using namespace std;




int main()
{
	int i = 1;
	double d = 2.22;
	cout << i;//->cout.operator<<(i)
	cout << d;//->cout.operator<<(d)
	//以上俩个构成函数重载
	cout << i << d;//两个operator<<函数调用，用返回值来接收
	cin >> i >> d;
	return 0;
}
内置类型我们可以直接用cout << cin >>，库里实现了
自定义类型就需要我们自己重载，才可以用

scanf/printf的缺点是只能支持内置类型
cout cin 真正优势是：自己重载以后，自定义类型对象也是简单实用






//对于IO算法，一般都需要循环输入：
//单个：
while (cin >> a)
{
	//...
}
//多个:
while (cin >> a >> b >> c)
{
	//...
}
//整行接收：
while (cin >> str)
{
	//...
}
eg:
class B
{
public:
	operator bool()
	{
		return _a != 0;
	}
	int _a;
};
int main()
{
	B b;
	while (b)//等价于while(b.operator bool())
	{
		cin >> b._a;
	}
	return 0;
}






二进制读写：fwrite/fread   文本读写：fprintf/fscanf
struct ServerInfo
{
	char _ip[32];//ip
	int _port;//接口
};
void Test_C_W_Bin()
{
	ServerInfo info = { "127.0.0.1", 80 };
	FILE* fout = fopen("text.bin", "wb");
	assert(fopen);
	fwrite(&info, sizeof(info), 1, fout);
	fclose(fout);
}
void Test_C_R_Bin()
{
	FILE* fin = fopen("text.bin", "r");
	assert(fin);
	ServerInfo info;
	fread(&info, sizeof(info), 1, fin);
	fclose(fin);
	printf("%s:%d\n", info._ip, info._port);
}
void Test_C_W_Txt()
{
	FILE* fout = fopen("text.txt", "w");
	assert(fopen);
	ServerInfo info = { "127.0.0.2",90 };
	fprintf(fout, "%s %d", info._ip, info._port);
	fclose(fout);
}
void Test_C_R_Txt()
{
	FILE* fin = fopen("text.txt", "r");
	assert(fopen);
	ServerInfo info;
	fscanf(fin,"%s %d", info._ip, &info._port);
	fclose(fin);

	printf("%s:%d\n", info._ip, info._port);
}

int main()
{
	二进制读写
	Test_C_W_Bin();
	Test_C_R_Bin();


	文本读写
	Test_C_W_Txt();
	Test_C_R_Txt();
	return 0;
}