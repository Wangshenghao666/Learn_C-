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
	//�����������ɺ�������
	cout << i << d;//����operator<<�������ã��÷���ֵ������
	cin >> i >> d;
	return 0;
}
�����������ǿ���ֱ����cout << cin >>������ʵ����
�Զ������;���Ҫ�����Լ����أ��ſ�����

scanf/printf��ȱ����ֻ��֧����������
cout cin ���������ǣ��Լ������Ժ��Զ������Ͷ���Ҳ�Ǽ�ʵ��






//����IO�㷨��һ�㶼��Ҫѭ�����룺
//������
while (cin >> a)
{
	//...
}
//���:
while (cin >> a >> b >> c)
{
	//...
}
//���н��գ�
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
	while (b)//�ȼ���while(b.operator bool())
	{
		cin >> b._a;
	}
	return 0;
}






�����ƶ�д��fwrite/fread   �ı���д��fprintf/fscanf
struct ServerInfo
{
	char _ip[32];//ip
	int _port;//�ӿ�
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
	�����ƶ�д
	Test_C_W_Bin();
	Test_C_R_Bin();


	�ı���д
	Test_C_W_Txt();
	Test_C_R_Txt();
	return 0;
}