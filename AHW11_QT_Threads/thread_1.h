#ifndef THREAD_1_H
#define THREAD_1_H

#include <QThread>
#include <QDebug>
#include <QObject>

class MyThread_1 : public QThread
{
protected:
    void run() {
        for (int i = 0; i < 100; i++)
            qDebug() << i;
    }
};

#endif // THREAD_1_H
