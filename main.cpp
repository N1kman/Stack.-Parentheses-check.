#include "header.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	stack* pointer1 = nullptr;                     //��������� �� ������� ����� ��� ����������� ������
	stack* pointer2 = nullptr;                     //�������������� ��������� �� ������� ����� ��� ������ ������� ������
	char* string = nullptr;                        //��������� �� ���������
	char* string_new = nullptr;                    //��������� �� ����� ��������� 

	for (;;)
	{ 
		system("CLS");                             //������� ������

		string = give_memory(length);              //��������� ������
		string_new = give_memory(length);          //��������� ������

		puts("---������� ���������--(�� 80 ��������)");
		rewind(stdin);                             //������� �������
		fgets(string, length - 80, stdin);         //���� ���������
		strcpy_s(string_new, length, string);      //����������� ������

		menu(&pointer1, &pointer2, string_new);    //������� ���� ��� �������� � ����������� ������ � ���������

		printf("\033[32m");
		puts("\n-->�������� ���������<--");
		printf("\033[0m");
		printf("%s", string);                      //����� ���������

		clear(&pointer1);                          //������ ������� �����
		clear(&pointer2);                          //������ ������� �����

		free(string);                              //������������ ������
		free(string_new);                          //������������ ������

		printf("\n");                              //������� �� ����� ������

		ending();                                  //���������� ������
	}
}