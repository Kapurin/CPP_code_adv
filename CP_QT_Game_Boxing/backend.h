#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include "server.h"
#include "client.h"
#include "game.h"

class Backend : public QObject
{
    Q_OBJECT

public:
    Backend();
    Server *SrvPtr = nullptr;
    Client *m_client = nullptr;
    QThread *senderThread = nullptr;
    Game *G1 = nullptr;

private:
    QString m_IpGame = "0";
    QString Ch_num1 = "0";
    QString Ch_num2 = "0";

public slots:
    // функция-геттер IP адреса игрока-"сервер"
    QString getIpGame();

    // функция-сеттер IP адреса игрока-"сервер"
    void setIpGame(QString ip_add);

    // == Кнопки (GUI QML) ==
    // выбор ударов/блоков для игрока-"сервер"
    void buttSrvPunchHead();
    void buttSrvPunchBody();
    void buttSrvBlockHead();
    void buttSrvBlockBody();

    // выбор ударов/блоков для игрока-"клиент"
    void buttClPunchHead();
    void buttClPunchBody();
    void buttClBlockHead();
    void buttClBlockBody();

    // Кнопки основных действий с игрой
    // функция создания игры
    void buttCreateGame();

    // функция завершения игры
    void buttDestroyGame();

    // функция подключения к игре
    void buttJoinGame();

    // функция отключения от игры
    void buttDisconGame();

    // функция запуска игры
    void startGame();

    // функция продолжения игры
    void funcContinueGame(QString);

private slots:
    // функция приема данных для игрока-"сервер"
    void PrintText(QString);

    // функция приема данных для игрока-"клиент"
    void PrintTextCl(QString);

signals:
    // передача данных для игрока-"сервер"
    void sendText(QString);

    // передача данных для игрока-"клиент"
    void sendTextCl(QString);

    // сигнал отключения от игры
    void disconnectGame();

    // передача текущих уровней НР игроков
    void updHPSrv(QString);
    void updHPCl(QString);

    // передача имен игроков
    void updUserNameSrv(QString);
    void updUserNameCl(QString);

    // === Сигналы для отправки в класс "Game" ===
    // сигналы от кнопок
    // выбор ударов/блоков для игрока-"сервер"
    void sigSrvPunchHead(QString);
    void sigSrvPunchBody(QString);
    void sigSrvBlockHead(QString);
    void sigSrvBlockBody(QString);

    // выбор ударов/блоков для игрока-"клиент"
    void sigClPunchHead(QString);
    void sigClPunchBody(QString);
    void sigClBlockHead(QString);
    void sigClBlockBody(QString);

    // сигнал продолжения игры
    void sigContinueGame();

    // === Сигналы для отправки в класс "Guiworker" ===
    // прием данных для игрока-"сервер"
    void sigPrintText(QString);

    // прием данных для игрока-"клиент"
    void sigPrintTextCl(QString);

    // инициализация данных
    void sigInitData();

    // остановка воспроизведения фонового саундтрека
    void sigStopMusic();
};

#endif // BACKEND_H
