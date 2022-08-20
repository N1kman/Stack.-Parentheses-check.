#include "header.h"

//������� ���������� ��������
void push_front(stack** point, char item, int pos)
{
	if (!*point)
	{
		(*point) = (stack*)malloc(sizeof(stack));     //��������� ������
		if ((*point))
		{
			(*point)->pointer = nullptr;              //��������� ��������� �� ���������� �������
			(*point)->item = item;                    //��������� ��������
			(*point)->position = pos;                 //��������� �������
		}
		else error(); 
		
	}
	else
	{
		stack* buff = (stack*)malloc(sizeof(stack));  //��������� ������
		if (buff)
		{
			buff->pointer = (*point);                 //��������� �� ���������� �������
			(*point) = buff;                          //������ ������� �����
			(*point)->item = item;                    //��������� ��������
			(*point)->position = pos;                 //��������� �������
		}
		else error();
	}
}

//������� �������� ��������
void pop_back(stack** point)
{
	if (!*point)return;
	if (!((*point)->pointer))
	{
		free(*point);                                 //������������ ������
		*point = nullptr;                             //��������� ���������
	}
	else
	{
		stack* buff = (*point);                       //���������� ������� �����
		(*point) = (*point)->pointer;                 //�������� ������� �����
		free(buff);                                   //������������ ������
	}
}

//������� ��������� �����������
void show(stack* point)
{
	if (!point)puts("���� ����");
	else
	{
		for (; ; point = (point->pointer))
		{
			printf("%d - %c\n", point->position + 1, point->item); //����� ���������
			if (!(point->pointer))break;                           //������ �� ������ �����
		}
	}
}

//������ ������� �����
void clear(stack** point)
{
	while (*point)pop_back(point);
}

//������� �������� ������ 
int checking_correct(stack** point1, stack** point2, char* str)
{
	for (int i = 0; *(str + i) != '\n' and *(str + i) != '\0'; ++i)
	{
		if (*(str + i) == '(' or *(str + i) == '{' or *(str + i) == '[')push_front(point1, *(str + i), i);    //���������� �������� � ���� 
		
		if ((*(str + i) == ')' and (*point1)->item == '(') or (*(str + i) == '}' and (*point1)->item == '{')
			or (*(str + i) == ']' and (*point1)->item == '['))pop_back(point1);                               //�������� �� �����
		else if (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']')return 0;
	}

	if (*point1) return 0;
	else return 1;
}

////������� �������� ������ 
//int checking_correct(stack** point1, stack** point2, char* str)
//{
//	for (int i = 0; *(str + i) != '\n' and *(str + i) != '\0'; ++i)
//	{
//		if (*(str + i) == '(' or *(str + i) == '{' or *(str + i) == '[')push_front(point1, *(str + i), i);    //���������� �������� � ���� 
//
//		if (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']')push_front(point2, *(str + i), i);    //���������� �������� � ���� 
//			
//		if (*point1)
//		{
//			if ((*(str + i) == ')' and (*point1)->item == '(') or (*(str + i) == '}' and (*point1)->item == '{') 
//				or (*(str + i) == ']' and (*point1)->item == '['))
//			{
//				pop_back(point1);           //�������� �� �����
//				pop_back(point2);           //�������� �� �����
//			}		
//		}
//
//	}
//
//	if ((*point1) or (*point2))return 0;
//	else return 1;
//}

//������� �������� �� ������������ ������
int checking(stack** point, char* str)
{
	int flag = 1;//���� ��� ���������� ���� �� ������
	int i = 0;   //�������

	for (; *(str + i) != '\n' and *(str + i) != '\0'; ++i)
	{
		//������� ����������� ������
		if (*(str + i) == '(' or *(str + i) == '{' or *(str + i) == '[')push_front(point, *(str + i), i);  //���������� �������� � ����                                  
		else if (!(*point) and (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']'))              //���� ����������� �����������,� ����������� ���
		{
			correct_before(str, i);        //������� ���������� ������ ������ � ��������� � ������
			++i;
			flag = 0;                      //������������ ����� �� ������

		}                                  //���� ����������� �����������,� ����������� ����
		else if (*point and (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']'))
		{
			if ((*(str + i) == ')' and (*point)->item == '(') or (*(str + i) == '}' and (*point)->item == '{')
				or (*(str + i) == ']' and (*point)->item == '['))pop_back(point);    //�������� �� �����
			else
			{
				//������������ ������ ���� �� ���� ���� �����������
				if ((*point)->item == '(')*(str + i) = ')';
				else if ((*point)->item == '{')*(str + i) = '}';
				else *(str + i) = ']';
				pop_back(point);           //�������� �� �����
				flag = 0;                  //������������ ����� �� ������
			}
		}
	}

	//���� � ����� ���-�� ��������
	if (*point)
	{
		flag = 0;                      //������������ ����� �� ������
		correct_after(point, str, i);  //������� ���������� ������ ������ � ���������
	}
	
	return flag;
}

//������� ���������� ������ ������ � ��������� � �����
void correct_after(stack** point, char* str, int pos)
{
	while (*point)
	{
		if ((*point)->item == '(')*(str + pos) = ')';
		else if ((*point)->item == '{')*(str + pos) = '}';
		else *(str + pos) = ']';
		++pos;
		pop_back(point);             //�������� �� �����
	}
	*(str + pos) = '\0';             //���������� ������
}

//������� ���������� ������ ������ � ��������� � ������
void correct_before(char* str,int pos)
{
	int i = 0; //�������
	char buff; //������

	if (*(str + pos) == ')')
	{
		buff = *(str + i); //����������� �������� ���� ���������
		*(str + i) = '(';  //������� ������
		++i;               //����������� �� ������
	}
	else if (*(str + pos) == '}')
	{
		buff = *(str + i); //����������� �������� ���� ���������
		*(str + i) = '{';  //������� ������
		++i;               //����������� �� ������
	}
	else
	{
		buff = *(str + i); //����������� �������� ���� ���������
		*(str + i) = '[';  //������� ������
		++i;               //����������� �� ������
	}
	
	while (buff != '\0')
	{
		char buff2 = buff;  //�������������� �������
		buff = *(str + i);  //����������� ������������ ��������
		*(str + i) = buff2; //������� ��������
		++i;                //����������� �� ������
	}

	*(str + i) = buff;      //������� ��������

}

//������� ���� ��� �������� � ����������� ������ � ���������
void menu(stack** point1, stack** point2, char* str)
{
	for (;;)
	{
		puts("����� ������ � ����������� ������������?");
		rewind(stdin);            //������� �������
		char choice1 = getchar(); //���� ������� ������

		if (choice1 == 'Y' or choice1 == 'y')
		{
			system("CLS");        //������� ������
			int check = checking(point1, str); //�������� ������

			if (check)
			{
				printf("\033[32m");
				puts("-->������ � ��������� �� �������<--");
				printf("\033[0m");
				printf("%s", str);//����� ���������
			}
			else
			{
				printf("\033[31m");
				puts("-->������ � ��������� �������<--");
				printf("\033[0m");
				printf("\033[32m");
				puts("-->����������� ���������<--");
				printf("\033[0m");
				printf("%s", str);//����� ���������
			}
			break;
		}
		else if (choice1 == 'N' or choice1 == 'n')
		{
			system("CLS");                                     //������� ������
			int check = checking_correct(point1, point2, str); //�������� ������

			if (check)
			{
				printf("\033[32m");
				puts("-->������ � ��������� �� �������<--");
				printf("\033[0m");
				printf("%s", str);//����� ���������
			}
			else
			{
				printf("\033[31m");
				puts("-->������ � ��������� �������<--");
				printf("\033[0m");
				puts("����� ������� ��������� ������");
				show(*point1);//����� �����
				show(*point2);//����� �����
			}
			break;
		}
		else puts("������");
	}
}
