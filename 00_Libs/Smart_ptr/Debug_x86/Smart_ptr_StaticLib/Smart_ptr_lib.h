/* ��������� ����� "Smart_ptr" ("�����" ���������) (*.lib)
*/

#pragma once
#include<iostream>
#include "Array_lib.h"

template <class T> class Smart_ptr
{
private:
    T* m_ptr;
public:
    Smart_ptr(T* ptr = nullptr);    // �����������
    ~Smart_ptr();                   // ����������

    Smart_ptr(Smart_ptr& Sptr);    // ����������� ����������� (��������� ��������� �����������)

    // ���������� ��������� ������������= (��������� ��������� �����������)
    Smart_ptr& operator=(Smart_ptr& Sptr);

    // ���������� ��������� *(������������� ���������)
    T& operator*();

    // ���������� ��������� ->(�������� ������ �����)
    T* operator->();
};


// ����� ��������������� �������
template class Smart_ptr <int>;
template class Smart_ptr <double>;
template class Smart_ptr <Array<int>>;

