#include <stdio.h>
#include<winsock.h>
#include<string.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"wsock32.lib")

int input_startport()//������ʼ�˿ں�
{
	
	int startport;	
	cout << "��������ʼ�˿ںţ�";
	cin >> startport;
	cout << endl;
	return startport;
}

int input_endport()//��������˿ں�
{
	int endport;
	cout << "����������˿ںţ�";
	cin >> endport;
	cout << endl;
	return endport;
}

char des_ip[30];
char* input_ip()//����Ŀ������IP��ַ
{
	cout << "������Ŀ������IP��ַ��";
	cin >> des_ip;
	cout << endl;
	return des_ip;
}

void scan(char des_ip[],int startport,int endport,sockaddr_in addr)
{//��Ŀ������IP��ַ����ʼ�˿ڿ�ʼɨ��

	cout<<" IP��ַ	  �˿�	״̬"<<endl;
	for (int i = startport; i <= endport; i++)
		{
			//ÿɨ��һ���˿ڴ���һ���µ��׽���
			SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (s == INVALID_SOCKET)
			{
				printf("Failed socket() %d \n", ::WSAGetLastError());
			}
			//����Զ�̵�ַ��Ϣ�еĶ˿ں�Ϊ��Ҫɨ��ĵ�ǰ�˿ں�
			addr.sin_port = htons(i);
			int ret = connect(s, (LPSOCKADDR)&addr, sizeof(addr));//�������ӣ��ɹ�����0
			if (ret ==0)//��ʾ�˿ڿ���
			{
				printf("%s:%d  �˿ڿ���\n", des_ip, i);
			}
			else//��ʾ�˿ڹر�
			{
				printf("%s:%d  �˿ڹر�\n", des_ip, i);
			}
			::closesocket(s);//�ر�
		}
		cout << endl;
}

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup  �޷���ʼ����" << endl;
		return 0;
	}
	// ��дԶ�̵�ַ��Ϣ
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	input_ip();
	//���û�ȡ���û�����IP��ַΪԶ��IP��ַ 
	addr.sin_addr.S_un.S_addr = inet_addr(des_ip);
	int startport=input_startport();
	int endport=input_endport();
	scan(des_ip,startport,endport,addr);
	if (WSACleanup() == SOCKET_ERROR)
		cout << "WSACleanup ����" << endl;
	return 0;
}
