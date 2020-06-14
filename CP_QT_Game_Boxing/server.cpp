#include "server.h"
#include <QDebug>
#include <QDataStream>
#include <QThread>


Server::Server(QString host, uint16_t port) :
    m_host(host),
    m_port(port)
{
    qDebug() << "Constructor Server!";

    m_serverSocket = new QTcpServer(this);

    if (!m_serverSocket->listen(QHostAddress(m_host), m_port)) {
        qDebug() << "Unable to start the server: " << m_serverSocket->errorString();
        PrintText("Unable to start the server: " + (m_serverSocket->errorString()));
        return;
    }

    connect(m_serverSocket, &QTcpServer::newConnection, this, &Server::slotNewConnection);
    connect(m_serverSocket, &QTcpServer::newConnection, this, &Server::sigNewConnection);
}


Server::~Server()
{
    qDebug() << "Destructor Server!";
    delete m_serverSocket;
}


void Server::slotNewConnection()
{

    // порядковый номер подключаемого клиента
    m_numclient++;

    qDebug() << "New client connected! #" << m_numclient;
    PrintText("New client connected! #" + QString::number(m_numclient));

    QThread *m_threadP = new QThread;
    QTcpSocket *socket_client = m_serverSocket->nextPendingConnection();
    Srvclient *srv_client = new Srvclient(socket_client, m_numclient);

    /* Вот здесь мы создаем отдельные потоки (на каждого клиента свой поток) */
    srv_client->moveToThread(m_threadP);

    connect(socket_client, &QTcpSocket::disconnected, srv_client, &Srvclient::slotClientDisconnected);
    connect(socket_client, &QTcpSocket::disconnected, srv_client, &Srvclient::deleteLater);
    connect(srv_client, &Srvclient::destroyed, this, [=](){m_threadP->quit();m_threadP->wait();});

    connect(m_threadP, &QThread::finished, m_threadP, &QThread::deleteLater);
    connect(m_threadP, &QThread::finished, socket_client, &QTcpSocket::deleteLater);

    // передача сообщения от клиента с потока для отображения в GUI
    connect(srv_client, &Srvclient::PrintText, this, &Server::PrintText);

    connect(this, &Server::sendMsgSrv, srv_client, &Srvclient::sendMsgSrv,Qt::DirectConnection);
    m_threadP->start();
}


void Server::slotErrorFromClient(QAbstractSocket::SocketError error)
{
    qDebug() << error;
}


void Server::slotErrorServer(QAbstractSocket::SocketError error)
{
    qDebug() << error;
}
