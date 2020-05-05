/* Программа реализует БД домов с жителями в них.
* (реализация через контейнер STL)
*/

// ЗАДАЧА:
//Пользователь вводит кол-во домов на улице и кол-во жителей для каждого дома.
//Далее запускается меню модификации БД:
//-вводит «0», далее вводит номер дома и узнаёт, если ли такой на улице.Если да – сколько там жителей.
//- вводит «1» - может снести дом
//- вводит «2» - строит дом и заселяет туда жильцов.


#include <iostream>
#include <map>


using namespace std;


int main()
{
	setlocale(LC_CTYPE, "rus");
	cout << "=== Программа реализует БД домов с жителями в них (реализация с помощью STL) ===\n\n";

	int Num_H = 0;      // кол-во домов на улице
	int Num_P = 0;      // кол-во жителей
	int Choice = 0;		// переменная выбора действия в меню

	map <int, int> DB_Houses;						// создание объекта типа "map"
	map <int, int>::iterator it_map;				// итератор для контейнера "map"
	pair<map <int, int>::iterator, bool> ResBuild;	// пара для определения результата вставки нового элемента в "map"

	cout << "Введите к-во домов на улице: ";
	cin >> Num_H;
	cout << endl;

	for (int i = 1; i <= Num_H; i++)
	{
		cout << "Введите к-во жителей в доме № " << i << " :";
		cin >> Num_P;
		DB_Houses.insert(pair <int, int>(i, Num_P));
	}

	cout << "\nБД заполнена.\n";
	system("pause");
	system("cls");
	do
	{
		// меню программы
		cout << "Выберите нужное действие для БД: \n\n";
		cout << "1 - поиск дома с заданным номером;\n";
		cout << "2 - снос дома;\n";
		cout << "3 - постройка нового дома; \n";
		cout << "4 - вывод информации по всем домам; \n";
		cout << "0 - завершение работы программы\n";
		cin >> Choice;


		switch (Choice)
		{
		case 0: // завершение работы программы
			break;
		case 1: // поиск дома с заданным номером
			cout << "Введите номер искомого дома: ";
			cin >> Num_H;

			it_map = DB_Houses.find(Num_H);
			if (it_map != DB_Houses.end())
				cout << "\nДом найден. К-во жильцов в доме: " << it_map->second << ".\n";
			else
				cout << "\nДом с искомым номером не найден! \n";
			break;
		case 2:	// снос дома
			int NumDestroy;
			NumDestroy = 0;
			cout << "Введите номер дома под снос: ";
			cin >> Num_H;

			NumDestroy = DB_Houses.erase(Num_H);
			if (NumDestroy != 0)
				cout << "\nУказанный дом снесен!\n";
			else
				cout << "\nДом с указанным номером не найден! \n";
			break;
		case 3: // постройка нового дома
			cout << "Введите номер нового дома:";
			cin >> Num_H;
			cout << "Введите к-во жителей в доме:";
			cin >> Num_P;
			ResBuild = DB_Houses.insert(pair <int, int>(Num_H, Num_P));
			if (ResBuild.second)
				cout << "\nДом построен!\n";
			else
				cout << "\nДом с указанным номером уже существует! \n";
			break;
		case 4: // вывод информации по всем домам
			if (DB_Houses.empty() == false) // проверка на наличие элементов в массиве
			{
				it_map = DB_Houses.begin();
				while (it_map != DB_Houses.end())
				{
					cout << "Дом № " << it_map->first << " - " << "Жильцов: " << it_map->second << endl;
					++it_map;
				}
			}
			else 
				cout << "Домов нет. БД пуста." << endl;
			break;
		default:
			cout << "\n\nНеправильный ввод! Повторите попытку.\n\n";
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