/* Программа реализует базовый калькулятор v2.0
* (реализация через указатели на функцию)
*
* Примечание: данная версия программы отличается от версии v1.0 тем что 
* логика выбора мат. оператора перемещена из функции getArithmeticFcn в массив arithmeticArray.
*/

#include "service_func.h"


int main()
{
	setlocale(LC_CTYPE, "rus");
	cout << "=== Программа-калькулятор v2.0 (реализация через указатели на функцию) ===\n\n";

	// ввод данных от пользователя
	int Num1 = UserInputNumber();
	char Oper = UserInputOperation();
	int Num2 = UserInputNumber();

	// вывод результата операции
	arithmeticFcn PtrFun = getArithmeticFcn(Oper);			// указатель на функцию
	cout << "Результат: " << PtrFun(Num1, Num2) << endl;

	system("pause");
	return 0;
}




