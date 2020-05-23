#include "sender.h"

#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>

void Sender::enterMsg()
{
    while(true) {
        qDebug() << "Enter message: (\"quit\" - exit )";

        QTextStream qtin(stdin);
        QString msg = qtin.readLine();  // This is how you read the entire line

        if (msg == "quit") {
            qApp->exit();
            return;
        }
        else
            emit sendMsg(msg);

        qDebug() << "";
    }
}
