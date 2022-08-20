#pragma once
#include <windows.h>
#include <stdio.h>
#include <iso646.h>

#define length 160  //длина выражения

//структура для списка в формате стека
struct stack
{
	char item;      //элемент
	int position;   //позиция
	stack* pointer; //указатель на предыдущий элемент
};

void ending();            //функция окончания программы
void error();             //экстренное завершение в случае ошибки
int input(int);           //функция ввода типа инт с дополнительной проверкой
char* give_memory(int);   //функция выделения памяти

void show(stack*);                   //функция просмотра содержимого
void push_front(stack**, char, int); //функция добовления элемента
void pop_back(stack**);              //функция удаления элемента	
void clear(stack**);                 //полная очистка стека

int checking(stack**, char*);                  //функция проверки на правильность скобок
int checking_correct(stack**, stack**, char*); //функция проверки скобок с указанием позиций
void menu(stack**, stack**, char*);            //функция меню для проверки и исправления ошибок в выражении
void correct_after(stack**, char*, int);       //функция добовления нужных скобок в выражение
void correct_before(char*, int);               //функция добовления нужных скобок в выражение в начало
