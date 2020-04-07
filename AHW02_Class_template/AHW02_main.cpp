/* ��������� ����� "Array"
*/

#include "Array.hpp"
using namespace std;


/*
* HOMEWORK (07.04.2020)
* ��������:
* 1 - ������ (������ ������ ����)
* 2 - ������� ���������� �������� (���������� ��������, � �� ������)
* 3 - ������� ���������� ��������� (���������� ��������, � �� ������)
* 4 - ����� �����������
* 5 - begin() - ���������� ������ ������� (���������� ��������, � �� ������)
* 6 - end() - ���������� ��������� ������� (���������� ��������, � �� ������)
* 7 - ������� ���������� (�� �����������)
* 8 - ������ ������ find(start, end, ��� ������) - ���������� ������ (���� ������� ����), ���� ������� �� ������ - -1
*/



int main()
{
    setlocale(LC_CTYPE, "rus");
    int n;
    int StartRange = 0, EndRange = 0, FindIndex = 0;
    
    cout << "������� ������ �������: ";
    cin >> n;

    Array<double> Arr(n);
    Array<double> FindEl;

    cout << "������: " << endl;
    Arr.Print();

    cout << "\n�������: " << Arr.getMin() << endl;
    cout << "\n��������: " << Arr.getMax() << endl;
    cout << "\n������ �������: " << Arr.getSize() << endl;
    cout << "\n������ �������: " << Arr.getBegin() << endl;
    cout << "\n��������� �������: " << Arr.getEnd() << endl;

    Arr.Sort();
    Arr.Print();

    cout << "\n������� ������ �������� ������: ";
    cin >> StartRange;
    cout << "\n������� ����� �������� ������: ";
    cin >> EndRange;
    cout << "\n������� ������� �������: ";
    cin >> FindEl[0];
    FindIndex = (Arr.Find(StartRange, EndRange, FindEl));

    if (FindIndex != (-1))
        cout << "\n������ �������� ��������: " << FindIndex << endl;
    else
        cout << "\n������� ������� �� ������! ������ " << FindIndex << endl;

    system("pause");
    return 0;
}