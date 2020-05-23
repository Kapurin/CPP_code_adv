#ifndef SENDER_H
#define SENDER_H

#include <QObject>

class Sender : public QObject
{
    Q_OBJECT

public slots:
    void enterMsg();

signals:
    void sendMsg(QString);
};

#endif // SENDER_H
