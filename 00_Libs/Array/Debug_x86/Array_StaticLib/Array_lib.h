/* Шаблонный класс "Array" (*.lib)
*/

#pragma once
#include<iostream>
#include <ctime>

template <class T> class Array
{
private:
    T* m_arr;		// указатель типа Т на массив
    int m_N;		// размерность массива
public:
    Array();			// конструктор без параметров
    Array(int n);		// конструктор с одним параметром
    ~Array();   		// деструктор

    // перегрузка оператора []
    T& operator[](int n);

    // перегрузка оператора >>
    //friend std::istream& operator>> (std::istream &in, Array<T> &Element);

    // служебные функции
    int getSize();		        // возвращение размера массива
    void Print();		        // показать массив
    void Set();			    	// ввод случайных элементов массива

    T& getMin();	        	// функция нахождения минимума
    T& getMax();		    	// функция нахождения максимума
    T& getBegin();		        // функция возвращает первый элемент
    T& getEnd();                // функция возвращает последний элемент
    void Sort();                // функция сортировки (по возрастанию)

    int Find(int Start, int End, Array<T>& FindElement);  // функция поиска заданного элемента

};


// явное инстанцирование шаблона
template class Array <int>;
template class Array <double>;