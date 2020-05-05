#pragma once
#include<iostream>


template <class T> class Smart_ptr
{
private:
    T *m_ptr;
public:
    Smart_ptr(T *ptr = nullptr);    // �����������
    ~Smart_ptr();                   // ����������

    Smart_ptr(Smart_ptr &Sptr);    // ����������� ����������� (��������� ��������� �����������)

    // ���������� ��������� ������������= (��������� ��������� �����������)
    Smart_ptr& operator=(Smart_ptr &Sptr);

    // ���������� ��������� *(������������� ���������)
    T& operator*();

    // ���������� ��������� ->(�������� ������ �����)
    T* operator->();
};



//�����������
template <class T> Smart_ptr<T>::Smart_ptr(T *ptr)
{
    std::cout << "Smart_ptr constructor \n";
    m_ptr = ptr;
}


//����������
template <class T> Smart_ptr<T>::~Smart_ptr()
{
    std::cout << "Smart_ptr destructor \n";
    delete m_ptr;       //������������ ������
}


// ����������� ����������� (��������� ��������� �����������)
template <class T> Smart_ptr<T>::Smart_ptr(Smart_ptr &Sptr)
{
    std::cout << "Smart_ptr constructor copy\n";
    m_ptr = Sptr.m_ptr;
    Sptr.m_ptr = nullptr;
}


// ���������� ��������� ������������= (��������� ��������� �����������)
template <class T> Smart_ptr<T>& Smart_ptr<T>::operator=(Smart_ptr &Sptr)
{
    if (&Sptr == this)
        return *this;

    delete m_ptr;
    m_ptr = Sptr.m_ptr;
    Sptr.m_ptr = nullptr;
    return *this;
}


// ���������� ��������� *(������������� ���������)
template <class T> T& Smart_ptr<T>::operator*()
{
    return *m_ptr;
}


// ���������� ��������� ->(�������� ������ �����)
template <class T> T* Smart_ptr<T>::operator->()
{
    return m_ptr;
}
