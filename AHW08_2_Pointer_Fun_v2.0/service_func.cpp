#include "service_func.h"


// ��������� �������


// ��������� arithmeticStruct
struct arithmeticStruct
{
	char Oper;
	arithmeticFcn PtrF;
};

// ���������� ������ arithmeticArray
static arithmeticStruct arithmeticArray[4] = { {'+', add}, {'-', subtract}, {'*', multiply}, {'/', divide} };


// ������� ����������������� ����� �����
int UserInputNumber()
{
	int Num = 0;
	cout << "������� ����� �����: ";
	cin >> Num;
	return Num;
}


// ������� ����������������� ����� ���.��������
char UserInputOperation()
{
	char Oper = ' ';
	do
	{
		cout << "������� �������������� �������� (+, -, *, /): ";
		cin >> Oper;

		// �������� ��������� ��������
		if ((Oper != '+') && (Oper != '-') && (Oper != '*') && (Oper != '/'))
			cout << "\n\n�������� �������������� ��������! ��������� �������.\n\n";

	} while ((Oper != '+') && (Oper != '-') && (Oper != '*') && (Oper != '/'));
	return Oper;
}


// ������� ��������
int add(int Num1, int Num2)
{
	return (Num1 + Num2);
}


// ������� ���������
int subtract(int Num1, int Num2)
{
	return (Num1 - Num2);
}


// ������� ���������
int multiply(int Num1, int Num2)
{
	return (Num1 * Num2);
}


// ������� �������
int divide(int Num1, int Num2)
{
	if (Num2 != 0)
		return (Num1 / Num2);
	else
	{
		cout << "\n\n������! ������� �� ����!\n\n";
		return -1;
	}
}


// ������� ������ ������� �������������� ��������
arithmeticFcn getArithmeticFcn(char Oper)
{
	for (auto Elem : arithmeticArray)
	{
		if (Elem.Oper == Oper)
			return Elem.PtrF;
	}
}