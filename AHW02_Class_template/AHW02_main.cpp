/* Шаблонный класс "Array"
*/

#include "Array.hpp"
using namespace std;


/*
* HOMEWORK (07.04.2020)
* Добавить:
* 1 - шаблон (массив любого типа)
* 2 - функция нахождения минимума (возвращает значение, а не индекс)
* 3 - функция нахождения максимума (возвращает значение, а не индекс)
* 4 - вывод размерности
* 5 - begin() - возвращает первый элемент (возвращает значение, а не индекс)
* 6 - end() - возвращает последний элемент (возвращает значение, а не индекс)
* 7 - функция сортировки (по возрастанию)
* 8 - фунция поиска find(start, end, что искать) - возвращает индекс (если элемент есть), если элемент не найден - -1
*/



int main()
{
    setlocale(LC_CTYPE, "rus");
    int n;
    int StartRange = 0, EndRange = 0, FindIndex = 0;
    
    cout << "Введите размер массива: ";
    cin >> n;

    Array<double> Arr(n);
    Array<double> FindEl;

    cout << "Массив: " << endl;
    Arr.Print();

    cout << "\nМинимум: " << Arr.getMin() << endl;
    cout << "\nМаксимум: " << Arr.getMax() << endl;
    cout << "\nРазмер массива: " << Arr.getSize() << endl;
    cout << "\nПервый элемент: " << Arr.getBegin() << endl;
    cout << "\nПоследний элемент: " << Arr.getEnd() << endl;

    Arr.Sort();
    Arr.Print();

    cout << "\nВведите начало дипазона поиска: ";
    cin >> StartRange;
    cout << "\nВведите конец дипазона поиска: ";
    cin >> EndRange;
    cout << "\nВведите искомый элемент: ";
    cin >> FindEl[0];
    FindIndex = (Arr.Find(StartRange, EndRange, FindEl));

    if (FindIndex != (-1))
        cout << "\nИндекс искомого элемента: " << FindIndex << endl;
    else
        cout << "\nИскомый элемент не найден! Ошибка " << FindIndex << endl;

    system("pause");
    return 0;
}