/* ��������� ��������� ������� ����������� v2.0
* (���������� ����� ��������� �� �������)
*
* ����������: ������ ������ ��������� ���������� �� ������ v1.0 ��� ��� 
* ������ ������ ���. ��������� ���������� �� ������� getArithmeticFcn � ������ arithmeticArray.
*/

#include "service_func.h"


int main()
{
	setlocale(LC_CTYPE, "rus");
	cout << "=== ���������-����������� v2.0 (���������� ����� ��������� �� �������) ===\n\n";

	// ���� ������ �� ������������
	int Num1 = UserInputNumber();
	char Oper = UserInputOperation();
	int Num2 = UserInputNumber();

	// ����� ���������� ��������
	arithmeticFcn PtrFun = getArithmeticFcn(Oper);			// ��������� �� �������
	cout << "���������: " << PtrFun(Num1, Num2) << endl;

	system("pause");
	return 0;
}




