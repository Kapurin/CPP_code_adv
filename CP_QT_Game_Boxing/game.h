#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "boxer.h"


class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    void processGame();
    void processGameNEW();

    // функция вывода текущего здоровья игрока
    void PrintPlayHealth(Boxer *P, QString Name);

    // функция вывода информации в начале атаки
    void PrintFightStartInfo(QString Num1, QString Num2);

    // функция вывода информации в конце атаки
    void PrintFightEndInfo(Boxer *P2, QString Name1, QString Name2);

    // функция нанесения удара
    void FightPunch(Boxer *P1, Boxer *P2);


    // функции-геттеры
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

    void delayfunc();

    void SrvSetPunchBlock();
    void ClSetPunchBlock();
private:
//    uint16_t m_HPSrvGame;
//    uint16_t m_HPClGame;
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
    void RxText(QString);

    // функции-сеттеры
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
    void TxText(QString);
    void TxHPSrvGame(QString);
    void TxHPClGame(QString);
    void punchTest();
};



#endif // GAME_H
