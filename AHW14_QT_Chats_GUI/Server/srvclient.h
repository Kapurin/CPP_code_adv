#ifndef SRVCLIENT_H
#define SRVCLIENT_H

#include <QTcpSocket>
#include <QTcpServer>


class Srvclient : public QObject
{
    Q_OBJECT
public:
    Srvclient(QTcpSocket *client, uint16_t m_numclient);
    ~Srvclient();

private:
    QTcpSocket *m_client = nullptr;
    uint16_t m_numclient = 0;

signals:
    void PrintText(QString Txt);

public slots:
    void slotReadClient();
    void slotClientDisconnected();

};

#endif // SRVCLIENT_H
