// Работа с потоками

#include <iostream> // потоки воода-вывода
#include <chrono> // работа со временем
#include <thread> // потоки выполнения
#include <mutex> // мьютексы
#include <string> // строки
#include <map>

#include <Windows.h>

int GenVar = 0;
std::map <std::thread::id, int> MapTred;    // список потоков

// мьютекс
std::mutex mtx;

long a = 0;

// функция, которая будет запущена в два потока
void thread_function()
{
	mtx.lock();
	GenVar++;
	MapTred.insert(std::pair<std::thread::id, int>(std::this_thread::get_id(), GenVar));
	std::cout << "Процесс запущен №" << GenVar << std::endl;

	for (int i = 0; i < 100000000; i++)
		a = a + 1;

	std::cout << "Процесс остановлен №" << GenVar << std::endl;
	MapTred.erase(std::this_thread::get_id());
	mtx.unlock();
}

int main()
{
    setlocale(LC_ALL, "");

    // Инициализируем потоки
    std::thread t1(thread_function);
    std::thread t2(thread_function);
    std::thread t3(thread_function);
    std::thread t4(thread_function);
    std::thread t5(thread_function);
    std::thread t6(thread_function);
    std::thread t7(thread_function);
    std::thread t8(thread_function);
    std::thread t9(thread_function);
    std::thread t10(thread_function);
 

    // Запускаем потоки
    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();
    t5.detach();
    t6.detach();
    t7.detach();
    t8.detach();
    t9.detach();
    t10.detach();

    //while (MapTred.size() > 0)
        std::cout << "Кол-во работающих процессов:" << MapTred.size() << std::endl;
    Sleep(4500);
    std::cout << "Кол-во работающих процессов:" << MapTred.size() << std::endl;

    std::cout << a << std::endl;

    GenVar = 0;
    system("pause");
    return 0;
}
