#pragma once
#include <iostream>
using namespace std;

// ��������� �������


// ��������� ��� ��������� �� �������
typedef int (*arithmeticFcn) (int, int);


// ������� ����������������� ����� �����
int UserInputNumber();

// ������� ����������������� ����� ���.��������
char UserInputOperation();

// ������� ��������
int add(int Num1, int Num2);

// ������� ���������
int subtract(int Num1, int Num2);

// ������� ���������
int multiply(int Num1, int Num2);

// ������� �������
int divide(int Num1, int Num2);

// ������� ������ ������� �������������� ��������
arithmeticFcn getArithmeticFcn(char Oper);

