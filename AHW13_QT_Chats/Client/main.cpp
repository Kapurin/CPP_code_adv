#include <QCoreApplication>
#include <QThread>

#include "client.h"
#include "sender.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client m_client("127.0.0.1", 12345);

    Sender *sender = new Sender;
    QThread *senderThread = new QThread;

    sender->moveToThread(senderThread);

    QObject::connect(senderThread, &QThread::started, sender, &Sender::enterMsg);
    QObject::connect(sender, &Sender::sendMsg, &m_client, &Client::sendMsg);

    senderThread->start();

    return a.exec();
}
