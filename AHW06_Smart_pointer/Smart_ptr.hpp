#pragma once
#include<iostream>


template <class T> class Smart_ptr
{
private:
    T *m_ptr;
public:
    Smart_ptr(T *ptr = nullptr);    // конструктор
    ~Smart_ptr();                   // деструктор

    Smart_ptr(Smart_ptr &Sptr);    // конструктор копирования (реализует семантику перемещения)

    // перегрузка оператора присваивания= (реализует семантику перемещения)
    Smart_ptr& operator=(Smart_ptr &Sptr);

    // перегрузка оператора *(разыменование указателя)
    T& operator*();

    // перегрузка оператора ->(оператор выбора члена)
    T* operator->();
};



//конструктор
template <class T> Smart_ptr<T>::Smart_ptr(T *ptr)
{
    std::cout << "Smart_ptr constructor \n";
    m_ptr = ptr;
}


//деструктор
template <class T> Smart_ptr<T>::~Smart_ptr()
{
    std::cout << "Smart_ptr destructor \n";
    delete m_ptr;       //освобождение памяти
}


// конструктор копирования (реализует семантику перемещения)
template <class T> Smart_ptr<T>::Smart_ptr(Smart_ptr &Sptr)
{
    std::cout << "Smart_ptr constructor copy\n";
    m_ptr = Sptr.m_ptr;
    Sptr.m_ptr = nullptr;
}


// перегрузка оператора присваивания= (реализует семантику перемещения)
template <class T> Smart_ptr<T>& Smart_ptr<T>::operator=(Smart_ptr &Sptr)
{
    if (&Sptr == this)
        return *this;

    delete m_ptr;
    m_ptr = Sptr.m_ptr;
    Sptr.m_ptr = nullptr;
    return *this;
}


// перегрузка оператора *(разыменование указателя)
template <class T> T& Smart_ptr<T>::operator*()
{
    return *m_ptr;
}


// перегрузка оператора ->(оператор выбора члена)
template <class T> T* Smart_ptr<T>::operator->()
{
    return m_ptr;
}
