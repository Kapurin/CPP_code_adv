#ifndef GAME_H
#define GAME_H

#include <QObject>
#include<QEventLoop>
#include "boxer.h"


class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    // функция основной логики игры
    void processGame();

    // функция вывода информации в начале атаки
    void PrintFightStartInfo(QString Num1, QString Num2);

    // функция вывода информации в конце атаки
    void PrintFightEndInfo(Boxer *P2, QString Name1, QString Name2);

    // функция нанесения удара
    void FightPunch(Boxer *P1, Boxer *P2);

    // функция ожидания пользовательского ввода
    void delayfunc();

    // функция установки ударов/блоков для игрока-"сервер"
    void SrvSetPunchBlock();

    // функция установки ударов/блоков для игрока-"клиент"
    void ClSetPunchBlock();

    // == Функции-геттеры ==
    // для игрока-"сервер"
    QString getSrvPunchHead();
    QString getSrvPunchBody();
    QString getSrvBlockHead();
    QString getSrvBlockBody();
    QString getUserNameSrvGame();

    // для игрока-"клиент"
    QString getClPunchHead();
    QString getClPunchBody();
    QString getClBlockHead();
    QString getClBlockBody();
    QString getUserNameClGame();


private:
    QString m_UserNameSrvGame;
    QString m_UserNameClGame;

    // для игрока-"сервер"
    // удары
    QString m_SrvPunchHead = "0";     // удар в голову
    QString m_SrvPunchBody = "0";     // удар в корпус

    // блоки защиты от ударов
    QString m_SrvBlockHead = "0";     // блок удара в голову
    QString m_SrvBlockBody = "0";     // блок удара в корпус

    // для игрока-"клиент"
    // удары
    QString m_ClPunchHead = "0";     // удар в голову
    QString m_ClPunchBody = "0";     // удар в корпус

    // блоки защиты от ударов
    QString m_ClBlockHead = "0";     // блок удара в голову
    QString m_ClBlockBody = "0";     // блок удара в корпус


    QString m_SrvPunch =  "0";
    QString m_SrvBlock =  "0";
    QString m_ClPunch =  "0";
    QString m_ClBlock =  "0";

public slots:
    // == Функции-сеттеры ==
    // для игрока-"сервер"
    void setSrvPunchHead(QString);
    void setSrvPunchBody(QString);
    void setSrvBlockHead(QString);
    void setSrvBlockBody(QString);
    void setUserNameSrvGame(QString);

    // для игрока-"клиент"
    void setClPunchHead(QString);
    void setClPunchBody(QString);
    void setClBlockHead(QString);
    void setClBlockBody(QString);
    void setUserNameClGame(QString);

signals:
    // передача информационных сообщений из игры
    void TxText(QString);

    // передача текущих уровней НР игроков
    void TxHPSrvGame(QString);
    void TxHPClGame(QString);

    // сигнал продолжения игры
    void sigContinueGame();
};



#endif // GAME_H
