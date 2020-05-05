#include "service_func.h"


// служебные функции


// функция пользовательского ввода числа
int UserInputNumber()
{
	int Num = 0;
	cout << "Введите целое число: ";
	cin >> Num;
	return Num;
}


// функция пользовательского ввода мат.операции
char UserInputOperation()
{
	char Oper = ' ';
	do
	{
		cout << "Введите математическую операцию (+, -, *, /): ";
		cin >> Oper;

		// проверка введенной операции
		if ((Oper != '+') && (Oper != '-') && (Oper != '*') && (Oper != '/'))
			cout << "\n\nНеверная математическая операция! Повторите попытку.\n\n";

	} while ((Oper != '+') && (Oper != '-') && (Oper != '*') && (Oper != '/'));
	return Oper;
}


// функция сложения
int add(int Num1, int Num2)
{
	return (Num1 + Num2);
}


// функция вычитания
int subtract(int Num1, int Num2)
{
	return (Num1 - Num2);
}


// функция умножения
int multiply(int Num1, int Num2)
{
	return (Num1 * Num2);
}


// функция деления
int divide(int Num1, int Num2)
{
	if (Num2 != 0)
		return (Num1 / Num2);
	else
	{
		cout << "\n\nОшибка! Деление на ноль!\n\n";
		return -1;
	}
}


// функция выбора функции математической операции
arithmeticFcn getArithmeticFcn(char Oper)
{
	switch (Oper)
	{
	case '+':
		return add;
	case '-':
		return subtract;
	case '*':
		return multiply;
	case '/':
		return divide;
	}
}