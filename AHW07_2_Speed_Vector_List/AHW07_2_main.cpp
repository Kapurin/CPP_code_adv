/* Сравнение скорости удаления одного элемента в разных контейнерах STL
* (контейнер типа "vector" и контейнер типа "list")
*/

#include <iostream>
#include <conio.h>
#include <list>
#include <chrono>
#include <vector>


using namespace std;
using namespace std::chrono;

int main()
{

  std::list<int> m_list;
  std::vector<int> m_vec;

  for (int i = 0; i < 1000000; i++)
    m_list.push_back(i + 1);

  for (int i = 0; i < 1000000; i++)
      m_vec.push_back(i + 1);


  /* Перебор по итераторам */
  std::list<int>::iterator it_read;
  std::vector<int>::iterator it_read_vec;


  // LIST
  it_read = m_list.begin();
  while (it_read != m_list.end())
  {
    if (*it_read == 5) {
      auto start = high_resolution_clock::now();
      it_read = m_list.erase(it_read);
      cout << "Time erase list: " << duration_cast<microseconds>(high_resolution_clock::now() - start).count() << endl;
    }
    else {
     // std::cout << *it_read << " ";
      ++it_read;
    }
  }
  cout << endl;



  // VECTOR
  it_read_vec = m_vec.begin();
  while (it_read_vec != m_vec.end())
  {
      if (*it_read_vec == 5) {
          auto start = high_resolution_clock::now();
          it_read_vec = m_vec.erase(it_read_vec);
          cout << "Time erase vector: " << duration_cast<microseconds>(high_resolution_clock::now() - start).count() << endl;
      }
      else {
          // std::cout << *it_read_vec << " ";
          ++it_read_vec;
      }
  }

  cout << endl;

  _getch();
  return 0;
}