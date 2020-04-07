#include<iostream>
#include <ctime>

template <class T> class Array
{
private:
    T *m_arr;		// ��������� ���� � �� ������
    int m_N;		// ����������� �������
public:
    Array();			// ����������� ��� ����������
    Array(int n);		// ����������� � ����� ����������
    ~Array();			// ����������

    // ���������� ��������� []
    T& operator[](int n);

    // ���������� ��������� >>
    friend std::istream& operator>> (std::istream &in, Array<T> &Element);

    // ��������� �������
    int getSize();		        // ����������� ������� �������
    void Print();		        // �������� ������
    void Set();			    	// ���� ��������� ��������� �������

    T& getMin();		    	// ������� ���������� ��������
    T& getMax();		    	// ������� ���������� ���������
    T& getBegin();		        // ������� ���������� ������ �������
    T& getEnd();                // ������� ���������� ��������� �������
    void Sort();                // ������� ���������� (�� �����������)

    int Find(int Start, int End, Array<T> &FindElement);   // ������� ������ ��������� ��������

};



//����������� ��� ����������
template <class T> Array<T>::Array()    
{
    m_N = 1;
    m_arr = new T [m_N];
    for (int i = 0; i < m_N; i++)
        m_arr[i] = 0;
}


//����������� � ����� ����������
template <class T> Array<T>::Array(int n)
{
    m_N = n;
    m_arr = new T [m_N];
    Array<T>::Set();
}


//����������
template <class T> Array<T>::~Array()
{
    delete [] m_arr; //������������ ������
}

 
// ���������� ��������� []
template <class T> T &Array<T>::operator[](int n)
{
    if (n < 0 || n > m_N)
    {
        std::cout << "\n������! �������� ������� ";
        std::cout << n << " ������� �� ������� ����������� ���������!";
        system("pause");
        exit(1);
    }
    return m_arr[n];
}


// ���������� ��������� >>
template <class T> std::istream& operator>>(std::istream &in, Array<T> &Element)
{
    in >> Element[0];
    return in;
}



// ��������� �������

// ����������� ������� �������
template <class T> int Array<T>::getSize()
{
    return m_N;
}


// �������� ������
template <class T> void Array<T>::Print()
{
    for (int i = 0; i < m_N; i++)
        std::cout << m_arr[i] << "  ";
    std::cout << std::endl;
}


// ���� ��������� ��������� �������
template <class T> void Array<T>::Set()
{
    srand(time(NULL));
    for (int i = 0; i < m_N; i++)
        m_arr[i] = rand() % 100;
}

// ������� ���������� ��������
template <class T> T& Array<T>::getMin()
{
    int TempMin = 0;
    for (int i = 0; i < m_N; i++)
    {
        if (m_arr[i] < m_arr[TempMin])
            TempMin = i;
    }
    return m_arr[TempMin];
}


// ������� ���������� ���������
template <class T> T& Array<T>::getMax()
{
    int TempMax = 0;
    for (int i = 0; i < m_N; i++)
    {
        if (m_arr[i] > m_arr[TempMax])
            TempMax = i;
    }
    return m_arr[TempMax];
}


// ������� ���������� ������ �������
template <class T> T& Array<T>::getBegin()
{
    return m_arr[0];
}


// ������� ���������� ��������� �������
template <class T> T& Array<T>::getEnd()
{
    return m_arr[m_N-1];
}


// ������� ���������� (�� �����������)
template <class T> void Array<T>::Sort()
{
	for (int i = 0; i < m_N - 1; i++)
	{
		for (int j = 0; j < m_N - 1; j++)
		{
			if (m_arr[j + 1] < m_arr[j])
			{
				T temp;
				temp = m_arr[j];
                m_arr[j] = m_arr[j + 1];
                m_arr[j + 1] = temp;
			}
		}
	}
}

// ������� ������ ��������� ��������
template <class T> int Array<T>::Find(int Start, int End, Array<T> &FindElement)
{
    // �������� ���������� ���������
    if ((Start - 1)  >= 0 && ((End - 1) <= (m_N - 1)) && (Start <= End))
    {
        int FindIndex = 0;
        for (int i = (Start - 1); i <= (End - 1); i++)
        {
            if (m_arr[i] == FindElement[0])
                FindIndex = i;
        }
        if (m_arr[FindIndex] == FindElement[0])
            return FindIndex;
        else
        {
            return -1;
        }
    }
    else
    {
        std::cout << "\n������! ��������� ������� ������ �������!";
        return -1;
    }
}








