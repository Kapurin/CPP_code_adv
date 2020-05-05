#pragma once
#include <iostream>
using namespace std;

// служебные функции


// псевдоним для указателя на функцию
typedef int (*arithmeticFcn) (int, int);


// функция пользовательского ввода числа
int UserInputNumber();

// функция пользовательского ввода мат.операции
char UserInputOperation();

// функция сложения
int add(int Num1, int Num2);

// функция вычитания
int subtract(int Num1, int Num2);

// функция умножения
int multiply(int Num1, int Num2);

// функция деления
int divide(int Num1, int Num2);

// функция выбора функции математической операции
arithmeticFcn getArithmeticFcn(char Oper);

