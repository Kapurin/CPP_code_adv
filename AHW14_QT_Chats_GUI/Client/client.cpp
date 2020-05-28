#include "client.h"
#include <QDebug>
#include <QCoreApplication>

#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>

#include <iostream>

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
    QString tempSize = QString::number(msg.size());
    for (int i = 0; i < 10 - tempSize.size(); i++)
        msgSize.append("0");
    msgSize.append(tempSize);

    QByteArray block;
    block.append(msgSize.toUtf8());
    block.append(msg.toUtf8());

    if (m_socketConnection->state() == QTcpSocket::ConnectedState)
        m_socketConnection->write(block);
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
