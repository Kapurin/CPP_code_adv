/* ��������� ����� "Smart_ptr" ("�����" ���������)
*/

#include "Smart_ptr.hpp"
#include "Array.hpp"


using namespace std;


int main()
{
    setlocale(LC_CTYPE, "rus");
    int n;

    cout << "������� ������ �������: ";
    cin >> n;

    Smart_ptr <Array<int>> SPtr1(new Array<int> (n));
    Smart_ptr <Array<int>> SPtr2(SPtr1);

    cout << "������: " << endl;
    (*SPtr2).Print();
    SPtr1 = SPtr2;
    cout << "������: " << endl;
    (*SPtr1).Print();



    system("pause");
    return 0;
}