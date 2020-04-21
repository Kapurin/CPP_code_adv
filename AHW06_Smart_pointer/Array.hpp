#include<iostream>
#include <ctime>

template <class T> class Array
{
private:
    T *m_arr;		// указатель типа Т на массив
    int m_N;		// размерность массива
public:
    Array();			// конструктор без параметров
    Array(int n);		// конструктор с одним параметром
    ~Array();			// деструктор

    // перегрузка оператора []
    T& operator[](int n);

    // перегрузка оператора >>
    friend std::istream& operator>> (std::istream &in, Array<T> &Element);

    // служебные функции
    int getSize();		        // возвращение размера массива
    void Print();		        // показать массив
    void Set();			    	// ввод случайных элементов массива

    T& getMin();		    	// функция нахождения минимума
    T& getMax();		    	// функция нахождения максимума
    T& getBegin();		        // функция возвращает первый элемент
    T& getEnd();                // функция возвращает последний элемент
    void Sort();                // функция сортировки (по возрастанию)

    int Find(int Start, int End, Array<T> &FindElement);   // функция поиска заданного элемента

};



//конструктор без параметров
template <class T> Array<T>::Array()    
{
    m_N = 1;
    m_arr = new T [m_N];
    for (int i = 0; i < m_N; i++)
        m_arr[i] = 0;
}


//конструктор с одним параметром
template <class T> Array<T>::Array(int n)
{
    m_N = n;
    m_arr = new T [m_N];
    Array<T>::Set();
}


//деструктор
template <class T> Array<T>::~Array()
{
    delete [] m_arr; //освобождение памяти
}

 
// перегрузка оператора []
template <class T> T &Array<T>::operator[](int n)
{
    if (n < 0 || n > m_N)
    {
        std::cout << "\nОшибка! Значение индекса ";
        std::cout << n << " выходит за пределы допустимого диапазона!";
        system("pause");
        exit(1);
    }
    return m_arr[n];
}


// перегрузка оператора >>
template <class T> std::istream& operator>>(std::istream &in, Array<T> &Element)
{
    in >> Element[0];
    return in;
}



// служебные функции

// возвращение размера массива
template <class T> int Array<T>::getSize()
{
    return m_N;
}


// показать массив
template <class T> void Array<T>::Print()
{
    for (int i = 0; i < m_N; i++)
        std::cout << m_arr[i] << "  ";
    std::cout << std::endl;
}


// ввод случайных элементов массива
template <class T> void Array<T>::Set()
{
    srand(time(NULL));
    for (int i = 0; i < m_N; i++)
        m_arr[i] = rand() % 100;
}

// функция нахождения минимума
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


// функция нахождения максимума
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


// функция возвращает первый элемент
template <class T> T& Array<T>::getBegin()
{
    return m_arr[0];
}


// функция возвращает последний элемент
template <class T> T& Array<T>::getEnd()
{
    return m_arr[m_N-1];
}


// функция сортировки (по возрастанию)
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

// функция поиска заданного элемента
template <class T> int Array<T>::Find(int Start, int End, Array<T> &FindElement)
{
    // проверка введенного диапазона
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
        std::cout << "\nОшибка! Введенный дипазон поиска неверен!";
        return -1;
    }
}








