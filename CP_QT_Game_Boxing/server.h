#ifndef SERVER_H
#define SERVER_H

#include <QTcpSocket>
#include <QTcpServer>
#include "srvclient.h"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QString host, uint16_t port);
    ~Server();

private:
    QTcpServer *m_serverSocket = nullptr;


    QString  m_host;
    uint16_t m_port;
    uint16_t m_numclient = 0;

signals:
    void PrintText(QString Txt);
    void sendMsgSrv(QString);
    void sigNewConnection();

private slots:
    void slotNewConnection();
    void slotErrorFromClient(QAbstractSocket::SocketError);
    void slotErrorServer(QAbstractSocket::SocketError);


};

#endif // SERVER_H
