#include "header.h"

//функция добовления элемента
void push_front(stack** point, char item, int pos)
{
	if (!*point)
	{
		(*point) = (stack*)malloc(sizeof(stack));     //выделение памяти
		if ((*point))
		{
			(*point)->pointer = nullptr;              //зануления указателя на предыдущий элемент
			(*point)->item = item;                    //занесение элемента
			(*point)->position = pos;                 //занесение позиции
		}
		else error(); 
		
	}
	else
	{
		stack* buff = (stack*)malloc(sizeof(stack));  //выделение памяти
		if (buff)
		{
			buff->pointer = (*point);                 //указываем на предыдущий элемент
			(*point) = buff;                          //меняем вершину стека
			(*point)->item = item;                    //занесение элемента
			(*point)->position = pos;                 //занесение позиции
		}
		else error();
	}
}

//функция удаления элемента
void pop_back(stack** point)
{
	if (!*point)return;
	if (!((*point)->pointer))
	{
		free(*point);                                 //освобождение памяти
		*point = nullptr;                             //зануление указателя
	}
	else
	{
		stack* buff = (*point);                       //запоминаем вершину стека
		(*point) = (*point)->pointer;                 //сдвигаем вершину стека
		free(buff);                                   //освобождение памяти
	}
}

//функция просмотра содержимого
void show(stack* point)
{
	if (!point)puts("СТЕК ПУСТ");
	else
	{
		for (; ; point = (point->pointer))
		{
			printf("%d - %c\n", point->position + 1, point->item); //вывод элементов
			if (!(point->pointer))break;                           //проход до начала стэка
		}
	}
}

//полная очистка стека
void clear(stack** point)
{
	while (*point)pop_back(point);
}

//функция проверки скобок 
int checking_correct(stack** point1, stack** point2, char* str)
{
	for (int i = 0; *(str + i) != '\n' and *(str + i) != '\0'; ++i)
	{
		if (*(str + i) == '(' or *(str + i) == '{' or *(str + i) == '[')push_front(point1, *(str + i), i);    //добовление элемента в стек 
		
		if ((*(str + i) == ')' and (*point1)->item == '(') or (*(str + i) == '}' and (*point1)->item == '{')
			or (*(str + i) == ']' and (*point1)->item == '['))pop_back(point1);                               //удаление из стека
		else if (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']')return 0;
	}

	if (*point1) return 0;
	else return 1;
}

////функция проверки скобок 
//int checking_correct(stack** point1, stack** point2, char* str)
//{
//	for (int i = 0; *(str + i) != '\n' and *(str + i) != '\0'; ++i)
//	{
//		if (*(str + i) == '(' or *(str + i) == '{' or *(str + i) == '[')push_front(point1, *(str + i), i);    //добовление элемента в стек 
//
//		if (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']')push_front(point2, *(str + i), i);    //добовление элемента в стек 
//			
//		if (*point1)
//		{
//			if ((*(str + i) == ')' and (*point1)->item == '(') or (*(str + i) == '}' and (*point1)->item == '{') 
//				or (*(str + i) == ']' and (*point1)->item == '['))
//			{
//				pop_back(point1);           //удаление из стека
//				pop_back(point2);           //удаление из стека
//			}		
//		}
//
//	}
//
//	if ((*point1) or (*point2))return 0;
//	else return 1;
//}

//функция проверки на правильность скобок
int checking(stack** point, char* str)
{
	int flag = 1;//флаг для сохранения была ли ошибка
	int i = 0;   //счетчик

	for (; *(str + i) != '\n' and *(str + i) != '\0'; ++i)
	{
		//встреча открывающих скобок
		if (*(str + i) == '(' or *(str + i) == '{' or *(str + i) == '[')push_front(point, *(str + i), i);  //добовление элемента в стек                                  
		else if (!(*point) and (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']'))              //если встретилась закрывающая,а открывающих нет
		{
			correct_before(str, i);        //функция добовления нужных скобок в выражение в начало
			++i;
			flag = 0;                      //установления флага на ошибку

		}                                  //если встретилась закрывающая,и открывающая есть
		else if (*point and (*(str + i) == ')' or *(str + i) == '}' or *(str + i) == ']'))
		{
			if ((*(str + i) == ')' and (*point)->item == '(') or (*(str + i) == '}' and (*point)->item == '{')
				or (*(str + i) == ']' and (*point)->item == '['))pop_back(point);    //удаление из стека
			else
			{
				//установление скобки того же типа чтои открывающая
				if ((*point)->item == '(')*(str + i) = ')';
				else if ((*point)->item == '{')*(str + i) = '}';
				else *(str + i) = ']';
				pop_back(point);           //удаление из стека
				flag = 0;                  //установления флага на ошибку
			}
		}
	}

	//если в стеке что-то осталось
	if (*point)
	{
		flag = 0;                      //установления флага на ошибку
		correct_after(point, str, i);  //функция добовления нужных скобок в выражение
	}
	
	return flag;
}

//функция добовления нужных скобок в выражение в конец
void correct_after(stack** point, char* str, int pos)
{
	while (*point)
	{
		if ((*point)->item == '(')*(str + pos) = ')';
		else if ((*point)->item == '{')*(str + pos) = '}';
		else *(str + pos) = ']';
		++pos;
		pop_back(point);             //удаление из стека
	}
	*(str + pos) = '\0';             //завершение строки
}

//функция добовления нужных скобок в выражение в начало
void correct_before(char* str,int pos)
{
	int i = 0; //счетчик
	char buff; //буффер

	if (*(str + pos) == ')')
	{
		buff = *(str + i); //запоминание элемента куда вставляем
		*(str + i) = '(';  //вставка скобки
		++i;               //продвижение по строке
	}
	else if (*(str + pos) == '}')
	{
		buff = *(str + i); //запоминание элемента куда вставляем
		*(str + i) = '{';  //вставка скобки
		++i;               //продвижение по строке
	}
	else
	{
		buff = *(str + i); //запоминание элемента куда вставляем
		*(str + i) = '[';  //вставка скобки
		++i;               //продвижение по строке
	}
	
	while (buff != '\0')
	{
		char buff2 = buff;  //дополнительный буффера
		buff = *(str + i);  //запоминание вставляемого элемента
		*(str + i) = buff2; //вставка элемента
		++i;                //продвижение по строке
	}

	*(str + i) = buff;      //вставка элемента

}

//функция меню для проверки и исправления ошибок в выражении
void menu(stack** point1, stack** point2, char* str)
{
	for (;;)
	{
		puts("ПОИСК ОШИБКИ С ПОСЛЕДУЮЩИМ ИСПРАВЛЕНИЕМ?");
		rewind(stdin);            //очистка буффера
		char choice1 = getchar(); //ввод символа выбора

		if (choice1 == 'Y' or choice1 == 'y')
		{
			system("CLS");        //очистка экрана
			int check = checking(point1, str); //проверка скобок

			if (check)
			{
				printf("\033[32m");
				puts("-->ОШИБОК В ВЫРАЖЕНИИ НЕ НАЙДЕНО<--");
				printf("\033[0m");
				printf("%s", str);//вывод выражения
			}
			else
			{
				printf("\033[31m");
				puts("-->ОШИБКИ В ВЫРАЖЕНИИ НАЙДЕНЫ<--");
				printf("\033[0m");
				printf("\033[32m");
				puts("-->ИСПРАВЛЕНОЕ ВЫРАЖЕНИЕ<--");
				printf("\033[0m");
				printf("%s", str);//вывод выражения
			}
			break;
		}
		else if (choice1 == 'N' or choice1 == 'n')
		{
			system("CLS");                                     //очистка экрана
			int check = checking_correct(point1, point2, str); //проверка скобок

			if (check)
			{
				printf("\033[32m");
				puts("-->ОШИБОК В ВЫРАЖЕНИИ НЕ НАЙДЕНО<--");
				printf("\033[0m");
				printf("%s", str);//вывод выражения
			}
			else
			{
				printf("\033[31m");
				puts("-->ОШИБКИ В ВЫРАЖЕНИИ НАЙДЕНЫ<--");
				printf("\033[0m");
				puts("ВЫВОД ПОЗИЦИЙ ОШИБОЧНЫХ СКОБОК");
				show(*point1);//вывод стека
				show(*point2);//вывод стека
			}
			break;
		}
		else puts("ОШИБКА");
	}
}
