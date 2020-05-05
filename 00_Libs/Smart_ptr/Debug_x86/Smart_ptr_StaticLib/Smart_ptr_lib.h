/* Шаблонный класс "Smart_ptr" ("Умный" указатель) (*.lib)
*/

#pragma once
#include<iostream>
#include "Array_lib.h"

template <class T> class Smart_ptr
{
private:
    T* m_ptr;
public:
    Smart_ptr(T* ptr = nullptr);    // конструктор
    ~Smart_ptr();                   // деструктор

    Smart_ptr(Smart_ptr& Sptr);    // конструктор копирования (реализует семантику перемещения)

    // перегрузка оператора присваивания= (реализует семантику перемещения)
    Smart_ptr& operator=(Smart_ptr& Sptr);

    // перегрузка оператора *(разыменование указателя)
    T& operator*();

    // перегрузка оператора ->(оператор выбора члена)
    T* operator->();
};


// явное инстанцирование шаблона
template class Smart_ptr <int>;
template class Smart_ptr <double>;
template class Smart_ptr <Array<int>>;

