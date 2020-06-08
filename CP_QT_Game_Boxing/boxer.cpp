#include "boxer.h"

// конструктор
Boxer::Boxer() {}
Boxer::Boxer(int Health)
{
    m_health = Health;
}


// функции-сеттеры
void Boxer::setHealth(int Health)
{
    m_health = Health;
}



// функции-геттеры
int Boxer::getHealth() const
{
    return m_health;
}

// функция удара
int Boxer::Punch()
{
    // случайное число (от 5 до 33)
    return (rand() % 29 + 5);
}
