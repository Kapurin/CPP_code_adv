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
    do {
        qDebug() << "Start reading...";
        int msgSize = 0;
        QString msg;
        QByteArray buf;
        for (;;)
        {
        /* По протоколу стыковки первые 10 байт - это размер сообщения
         * если доступных байт меньше 10ти, выходим.. подождём пока придут
         */
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
         */
            while (msgSize > 0) {
                if (msgSize < 512)
                    buf = m_client->read(msgSize);
                else
                    buf = m_client->read(512);
                msg.append(buf);
                msgSize -= buf.size();
            }

            if (msgSize == 0)
            {
                qDebug() << "MsgFromSrv #" << msg;
                PrintText(msg);
                buf.clear();
                msg.clear();
            }
        }
    } while (m_client->bytesAvailable());
}


void Srvclient::slotClientDisconnected()
{
    qDebug() << "Client #" << m_numclient << "disconnected!";
    PrintText("Client #" + QString::number(m_numclient) + " disconnected!");
}


void Srvclient::sendMsgSrv(QString msg)
{
    // Hello World!                 // 12 символов -> 0000000012
    // Шаг 1 - считаем кол-во символов (получаем int)
    // int переводим в QString
    // считаем кол-во символов получившейся стройки
    // формируем строчку по маске хххххххххх

    QString msgSize;
    QString tempSize = QString::number(msg.toUtf8().size());
    for (int i = 0; i < 10 - tempSize.size(); i++)
        msgSize.append("0");
    msgSize.append(tempSize);

    QByteArray block;
    block.append(msgSize.toUtf8());
    block.append(msg.toUtf8());

    if (m_client->state() == QTcpSocket::ConnectedState)
        m_client->write(block);
}
