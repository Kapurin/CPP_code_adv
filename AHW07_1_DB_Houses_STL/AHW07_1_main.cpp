/* ��������� ��������� �� ����� � �������� � ���.
* (���������� ����� ��������� STL)
*/

// ������:
//������������ ������ ���-�� ����� �� ����� � ���-�� ������� ��� ������� ����.
//����� ����������� ���� ����������� ��:
//-������ �0�, ����� ������ ����� ���� � �����, ���� �� ����� �� �����.���� �� � ������� ��� �������.
//- ������ �1� - ����� ������ ���
//- ������ �2� - ������ ��� � �������� ���� �������.


#include <iostream>
#include <map>


using namespace std;


int main()
{
	setlocale(LC_CTYPE, "rus");
	cout << "=== ��������� ��������� �� ����� � �������� � ��� (���������� � ������� STL) ===\n\n";

	int Num_H = 0;      // ���-�� ����� �� �����
	int Num_P = 0;      // ���-�� �������
	int Choice = 0;		// ���������� ������ �������� � ����

	map <int, int> DB_Houses;						// �������� ������� ���� "map"
	map <int, int>::iterator it_map;				// �������� ��� ���������� "map"
	pair<map <int, int>::iterator, bool> ResBuild;	// ���� ��� ����������� ���������� ������� ������ �������� � "map"

	cout << "������� �-�� ����� �� �����: ";
	cin >> Num_H;
	cout << endl;

	for (int i = 1; i <= Num_H; i++)
	{
		cout << "������� �-�� ������� � ���� � " << i << " :";
		cin >> Num_P;
		DB_Houses.insert(pair <int, int>(i, Num_P));
	}

	cout << "\n�� ���������.\n";
	system("pause");
	system("cls");
	do
	{
		// ���� ���������
		cout << "�������� ������ �������� ��� ��: \n\n";
		cout << "1 - ����� ���� � �������� �������;\n";
		cout << "2 - ���� ����;\n";
		cout << "3 - ��������� ������ ����; \n";
		cout << "4 - ����� ���������� �� ���� �����; \n";
		cout << "0 - ���������� ������ ���������\n";
		cin >> Choice;


		switch (Choice)
		{
		case 0: // ���������� ������ ���������
			break;
		case 1: // ����� ���� � �������� �������
			cout << "������� ����� �������� ����: ";
			cin >> Num_H;

			it_map = DB_Houses.find(Num_H);
			if (it_map != DB_Houses.end())
				cout << "\n��� ������. �-�� ������� � ����: " << it_map->second << ".\n";
			else
				cout << "\n��� � ������� ������� �� ������! \n";
			break;
		case 2:	// ���� ����
			int NumDestroy;
			NumDestroy = 0;
			cout << "������� ����� ���� ��� ����: ";
			cin >> Num_H;

			NumDestroy = DB_Houses.erase(Num_H);
			if (NumDestroy != 0)
				cout << "\n��������� ��� ������!\n";
			else
				cout << "\n��� � ��������� ������� �� ������! \n";
			break;
		case 3: // ��������� ������ ����
			cout << "������� ����� ������ ����:";
			cin >> Num_H;
			cout << "������� �-�� ������� � ����:";
			cin >> Num_P;
			ResBuild = DB_Houses.insert(pair <int, int>(Num_H, Num_P));
			if (ResBuild.second)
				cout << "\n��� ��������!\n";
			else
				cout << "\n��� � ��������� ������� ��� ����������! \n";
			break;
		case 4: // ����� ���������� �� ���� �����
			if (DB_Houses.empty() == false) // �������� �� ������� ��������� � �������
			{
				it_map = DB_Houses.begin();
				while (it_map != DB_Houses.end())
				{
					cout << "��� � " << it_map->first << " - " << "�������: " << it_map->second << endl;
					++it_map;
				}
			}
			else 
				cout << "����� ���. �� �����." << endl;
			break;
		default:
			cout << "\n\n������������ ����! ��������� �������.\n\n";
		}

		if (Choice != 0)
		{
			system("pause");
			system("cls");
		}

	} while (Choice != 0);



	system("pause");
	return 0;
}