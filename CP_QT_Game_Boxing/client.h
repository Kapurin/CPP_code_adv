#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QString host, uint16_t port);
    ~Client();

private:
    QTcpSocket *m_socketConnection = nullptr;

    QString  m_host;
    uint16_t m_port;

public slots:
    void sendMsg(QString);
    void slotReadClientCl();

private slots:
    void slotConnected();
    void slotError(QAbstractSocket::SocketError);

signals:
    void connected(QString);
    void disconnected(QString);
    void sendError(QString);
    void PrintText(QString Txt);
};

#endif // CLIENT_H
