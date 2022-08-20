#include "header.h"

//������� ��������� ���������
void ending()
{
	puts("������ ����������?(Y/N)");
	for (;;)
	{
		rewind(stdin);                                   //������� �������
		char choice = getchar();                         //���� 
		if (choice == 'N' or choice == 'n')exit(0);      //����� �� ���������
		else if (choice == 'Y' or choice == 'y') return; //����� �� �������
		else puts("--->������<---");
	}
}

//���������� ���������� � ������ ������
void error()
{
	puts("ERROR"); //��������� �� ������
	Sleep(3000);   //�������� �� 3 �������
	exit(-1);      //���������� ����������
}

//������� ����� ���� ��� � �������������� ���������
int input(int test)
{
	int number;

	for (;;)
	{
		rewind(stdin);                                                      //������� �������
		int check = scanf_s("%d", &number);                                 //���� �����
		if (check and number > 0 and number <= test) return number;         //����������� ���������
		else puts("--->������<---");
	}
}

//������� ��������� ������
char* give_memory(int size)
{
	char* pointer = nullptr;
	for (int i = 0; i < 3; i++)
	{
		pointer = (char*)malloc(size * sizeof(char)); //��������� ������
		if (!pointer) puts("-->������<--");           //��������
		else break;
	}
	return pointer;
}