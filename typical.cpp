#include "header.h"

//функция окончания программы
void ending()
{
	puts("Хотите продолжить?(Y/N)");
	for (;;)
	{
		rewind(stdin);                                   //очистка буффера
		char choice = getchar();                         //ввод 
		if (choice == 'N' or choice == 'n')exit(0);      //выход из программы
		else if (choice == 'Y' or choice == 'y') return; //выход из функции
		else puts("--->ОШИБКА<---");
	}
}

//экстренное завершение в случае ошибки
void error()
{
	puts("ERROR"); //сообщение об ошибке
	Sleep(3000);   //задержка на 3 секунды
	exit(-1);      //экстренное завершение
}

//функция ввода типа инт с дополнительной проверкой
int input(int test)
{
	int number;

	for (;;)
	{
		rewind(stdin);                                                      //очистка буффера
		int check = scanf_s("%d", &number);                                 //ввод числа
		if (check and number > 0 and number <= test) return number;         //возвращение аргумента
		else puts("--->ОШИБКА<---");
	}
}

//функция выделения памяти
char* give_memory(int size)
{
	char* pointer = nullptr;
	for (int i = 0; i < 3; i++)
	{
		pointer = (char*)malloc(size * sizeof(char)); //выделение памяти
		if (!pointer) puts("-->ОШИБКА<--");           //проверка
		else break;
	}
	return pointer;
}