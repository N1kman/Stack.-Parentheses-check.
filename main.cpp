#include "header.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	stack* pointer1 = nullptr;                     //указатель на вершину стека для открывающих скобок
	stack* pointer2 = nullptr;                     //дополнительный указатель на вершину стека для вывода позиций ошибок
	char* string = nullptr;                        //указатель на выражение
	char* string_new = nullptr;                    //указатель на новое выражение 

	for (;;)
	{ 
		system("CLS");                             //очистка экрана

		string = give_memory(length);              //выделение памяти
		string_new = give_memory(length);          //выделение памяти

		puts("---ВВЕДИТЕ ВЫРАЖЕНИЕ--(до 80 символов)");
		rewind(stdin);                             //очистка буффера
		fgets(string, length - 80, stdin);         //ввод выражения
		strcpy_s(string_new, length, string);      //копирование строки

		menu(&pointer1, &pointer2, string_new);    //функция меню для проверки и исправления ошибок в выражении

		printf("\033[32m");
		puts("\n-->ИСХОДНОЕ ВЫРАЖЕНИЕ<--");
		printf("\033[0m");
		printf("%s", string);                      //вывод выражения

		clear(&pointer1);                          //полная очистка стека
		clear(&pointer2);                          //полная очистка стека

		free(string);                              //освобождение памяти
		free(string_new);                          //освобождение памяти

		printf("\n");                              //перевод на новую строку

		ending();                                  //завершение работы
	}
}