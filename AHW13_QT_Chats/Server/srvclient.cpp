#include "srvclient.h"

#include <QDebug>
#include <QDataStream>

Srvclient::Srvclient(QTcpSocket *client, uint16_t numclient) :
    m_client(client),
    m_numclient(numclient)
{
    //qDebug() << "Constructor Srvclient! #" << m_numclient;
    connect(m_client, &QTcpSocket::readyRead, this, &Srvclient::slotReadClient);
}


Srvclient::~Srvclient()
{
    //qDebug() << "Destructor Srvclient! #" << m_numclient;
    //delete m_client;
}



void Srvclient::slotReadClient()
{
    int msgSize = 0;
    QString msg;
    for (;;)
    {
        /* По протоколу стыковки первые 10 байт - это размер сообщения
        * если доступных байт меньше 10ти, выходим.. подождём пока придут
        * */
        if (!msgSize)
        {
            if (m_client->bytesAvailable() < 10) return;
            msgSize = m_client->read(10).toInt();
        }

        /* Если мы прочитали размер посылки, крутимся в вайле пока не вычитаем все сообщение
         *
         * ВОПРОС!!!!!
         * что я не предусмотрел в реализации ниже????
         *
         * ОТВЕТ: не предусмотрена ситуация, когда высланные данные клиентом
         * могут прийти не сразу, а с некоторой задержкой (для этого используем "вечный" цикл for).
         * */

        // Если доступных байт меньше чем размер посылки выходим, ждем пока прийдет посылка полностью
        if (m_client->bytesAvailable() < msgSize) return;

        while (msgSize > 0) {
            QByteArray buf = m_client->read(512);
            msg.append(buf);
            msgSize -= buf.size();
        }

        qDebug() << "Client #" << m_numclient << ":" << msg;
        msgSize = 0;
    }
}

void Srvclient::slotClientDisconnected()
{
    qDebug() << "Client #" << m_numclient << "disconnected!";
}
