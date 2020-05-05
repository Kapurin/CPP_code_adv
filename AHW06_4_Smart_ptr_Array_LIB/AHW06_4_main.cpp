/* Подключение шаблонных классов "Smart_ptr" и "Array"
*  через статические библиотеки (*.lib) данных классов. 
*/

#include "Smart_ptr_lib.h"
#include "Array_lib.h"


using namespace std;


int main()
{
    setlocale(LC_CTYPE, "rus");
    int n;

    cout << "Введите размер массива: ";
    cin >> n;

    Smart_ptr <Array<int>> SPtr1(new Array<int>(n));
    Smart_ptr <Array<int>> SPtr2(SPtr1);

    cout << "Массив: " << endl;
    (*SPtr2).Print();
    SPtr1 = SPtr2;
    cout << "Массив: " << endl;
    (*SPtr1).Print();



    system("pause");
    return 0;
}