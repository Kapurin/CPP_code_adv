#ifndef PRINTER_H
#define PRINTER_H

#include <QDebug>
#include <QTimer>
#include <QString>

#include <QObject>

class Printer : public QObject
{
    Q_OBJECT

public:
    Printer(const QString &msg = "Hello World");
    ~Printer();



    // метод смены сообщения
    void setMsg(QString msg);

    // метод смены интервала
    void setInterval(int interval);

private:
    QString m_msg;
    QTimer *m_timer = nullptr;

    int m_interval = 1000;    // 1000 ms = 1 sec

    int CountMess = 0; // счетчик сообщений

public slots:
    void init();
    void printMsg();

    void startPrinting();
    void endPrinting();

    // функционал смены сообщения
    void sl_PrinterChMess(QString msg_new);

    // функционал смены интервала
    void sl_PrinterChInterval(int interval_new);

signals:
    // функционал смены сообщения
    void sig_PrinterCount15();

    // функционал смены интервала
    void sig_PrinterCount30();
};

#endif // PRINTER_H
