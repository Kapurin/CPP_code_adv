#include "client.h"
#include <QDebug>
#include <QCoreApplication>
#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>



Client::Client(QString host, uint16_t port) :
    m_host(host),
    m_port(port)
{
    qDebug() << "Constructor Client!";
    m_socketConnection = new QTcpSocket(this);

    m_socketConnection->connectToHost(m_host, m_port);

    connect(m_socketConnection, &QTcpSocket::connected, this, &Client::slotConnected);

    connect(m_socketConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));

    connect(m_socketConnection, &QTcpSocket::disconnected, this, [=]()
    { qDebug() << "Disconnected!"; emit disconnected("Disconnected!");} );

    connect(m_socketConnection, &QTcpSocket::readyRead, this, &Client::slotReadClientCl);
}


Client::~Client()
{
    qDebug() << "Destructor Client!";
    delete m_socketConnection;
}


void Client::sendMsg(QString msg)
{
    // Hello World!         // 12 символов -> 0000000012
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

    if (m_socketConnection->state() == QTcpSocket::ConnectedState)
        m_socketConnection->write(block);
}


void Client::slotReadClientCl()
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
                if (m_socketConnection->bytesAvailable() < 10) return;
                msgSize = m_socketConnection->read(10).toInt();
            }

         /* Если мы прочитали размер посылки, крутимся в вайле пока не вычитаем все сообщение
         *
         * ВОПРОС!!!!!
         * что я не предусмотрел в реализации ниже????
         *
         * ОТВЕТ: не предусмотрена ситуация, когда высланные данные клиентом
         * могут прийти не сразу, а с некоторой задержкой (для этого используем "вечный" цикл for).
         * */
            while (msgSize > 0) {
                if (msgSize < 512)
                    buf = m_socketConnection->read(msgSize);
                else
                    buf = m_socketConnection->read(512);
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
    } while (m_socketConnection->bytesAvailable());
}


void Client::slotConnected()
{
    qDebug() << "Connected!";
    emit connected("Connected!");
}


void Client::slotError(QAbstractSocket::SocketError error)
{
    if (error == QAbstractSocket::ConnectionRefusedError ||
            error == QAbstractSocket::HostNotFoundError)
    {
        qDebug() << "Connection failed!";
        sendError("Connection failed!");
    }

    if (error == QAbstractSocket::RemoteHostClosedError)
    {
        qDebug() << "HostClosedError!";
        sendError("HostClosedError!");
    }
}
