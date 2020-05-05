/* ��������� ����� "Array" (*.lib)
*/

#pragma once
#include<iostream>
#include <ctime>

template <class T> class Array
{
private:
    T* m_arr;		// ��������� ���� � �� ������
    int m_N;		// ����������� �������
public:
    Array();			// ����������� ��� ����������
    Array(int n);		// ����������� � ����� ����������
    ~Array();   		// ����������

    // ���������� ��������� []
    T& operator[](int n);

    // ���������� ��������� >>
    //friend std::istream& operator>> (std::istream &in, Array<T> &Element);

    // ��������� �������
    int getSize();		        // ����������� ������� �������
    void Print();		        // �������� ������
    void Set();			    	// ���� ��������� ��������� �������

    T& getMin();	        	// ������� ���������� ��������
    T& getMax();		    	// ������� ���������� ���������
    T& getBegin();		        // ������� ���������� ������ �������
    T& getEnd();                // ������� ���������� ��������� �������
    void Sort();                // ������� ���������� (�� �����������)

    int Find(int Start, int End, Array<T>& FindElement);  // ������� ������ ��������� ��������

};


// ����� ��������������� �������
template class Array <int>;
template class Array <double>;