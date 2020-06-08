#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>

#include "server.h"
#include "client.h"
#include "game.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString userNameSrv READ getUserNameSrv WRITE setUserNameSrv NOTIFY updUserNameSrv)
    Q_PROPERTY(QString userNameCl READ getUserNameCl WRITE setUserNameCl NOTIFY updUserNameCl)

    // уровень НР игроков
    Q_PROPERTY(QString userHPSrv READ getHPSrv WRITE setHPSrv NOTIFY updHPSrv)
    Q_PROPERTY(QString userHPCl READ getHPCl WRITE setHPCl NOTIFY updHPCl)

    Q_PROPERTY(QString ipAddress READ getIpGame WRITE setIpGame)
    Q_PROPERTY(QString statusGame READ getStatusGame WRITE setStatusGame NOTIFY updStatusGame)
    Q_PROPERTY(QString txTextToQML READ getTxTextToQML WRITE setTxTextToQML NOTIFY upTxTextToQML)

public:
    Backend();
    Server *SrvPtr = nullptr;
    Client *m_client = nullptr;
    QThread *senderThread = nullptr;
    Game *G1 = nullptr;


    QString getUserNameSrv();
    void setUserNameSrv(QString name);

    QString getUserNameCl();
    void setUserNameCl(QString name);

    QString getIpGame();
    void setIpGame(QString ip_add);

    QString getTxTextToQML();
    void setTxTextToQML(QString TxText);

    QString getRxTextFromQML();
    void setRxTextFromQML(QString RxText);

    QString getHPSrv();
    QString getHPCl();

    QString getStatusGame();
    void setStatusGame(QString status);

private:
    QString m_UserNameSrv = "Player Server";
    QString m_UserNameCl = "Player Client";
    QString m_IpGame = "0";
    QString m_TxTextToQML;
    QString m_RxTextFromQML;

    QString m_HPSrv = "100";
    QString m_HPCl = "100";

    QString m_StatusGame = "[пусто]";


public slots:
    void buttCreateGame();
    void buttDestroyGame();

    void buttJoinGame();
    void buttDisconGame();

    void printTester();
    void setHPSrv(QString);
    void setHPCl(QString);

    void sendText2();
    void initData();

    // кнопки
    // для игрока-"сервер"
    void buttSrvPunchHead();
    void buttSrvPunchBody();
    void buttSrvBlockHead();
    void buttSrvBlockBody();

    // для игрока-"клиент"
    void buttClPunchHead();
    void buttClPunchBody();
    void buttClBlockHead();
    void buttClBlockBody();


private slots:
    void PrintText(QString);
    void PrintTextCl(QString);

signals:
    void sendText(QString);
    void sendTextCl(QString);

    void disconnect();

    void upTxTextToQML(QString);
    void updHPSrv(QString);
    void updHPCl(QString);
    void updUserNameSrv(QString);
    void updUserNameCl(QString);
    void updStatusGame(QString);

    void punchTestBack();

    // сигналы от кнопок для передачи в класс "Game"
    // для игрока-"сервер"
    void sigSrvPunchHead(QString);
    void sigSrvPunchBody(QString);
    void sigSrvBlockHead(QString);
    void sigSrvBlockBody(QString);

    // для игрока-"клиент"
    void sigClPunchHead(QString);
    void sigClPunchBody(QString);
    void sigClBlockHead(QString);
    void sigClBlockBody(QString);

};

#endif // BACKEND_H
