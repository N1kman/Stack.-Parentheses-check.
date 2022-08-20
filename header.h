#pragma once
#include <windows.h>
#include <stdio.h>
#include <iso646.h>

#define length 160  //����� ���������

//��������� ��� ������ � ������� �����
struct stack
{
	char item;      //�������
	int position;   //�������
	stack* pointer; //��������� �� ���������� �������
};

void ending();            //������� ��������� ���������
void error();             //���������� ���������� � ������ ������
int input(int);           //������� ����� ���� ��� � �������������� ���������
char* give_memory(int);   //������� ��������� ������

void show(stack*);                   //������� ��������� �����������
void push_front(stack**, char, int); //������� ���������� ��������
void pop_back(stack**);              //������� �������� ��������	
void clear(stack**);                 //������ ������� �����

int checking(stack**, char*);                  //������� �������� �� ������������ ������
int checking_correct(stack**, stack**, char*); //������� �������� ������ � ��������� �������
void menu(stack**, stack**, char*);            //������� ���� ��� �������� � ����������� ������ � ���������
void correct_after(stack**, char*, int);       //������� ���������� ������ ������ � ���������
void correct_before(char*, int);               //������� ���������� ������ ������ � ��������� � ������
