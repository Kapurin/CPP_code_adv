#ifndef BOXER_H
#define BOXER_H

#include <QObject>
#include <QDebug>


class Boxer : public QObject
{
    Q_OBJECT
public:
    Boxer();
    Boxer(int Health);

    // функции-сеттеры
    void setHealth(int Health);

    // функции-геттеры
    int getHealth() const;


    // функция удара
    int Punch();


private:
    int m_health;	// здоровье

};

#endif // BOXER_H
