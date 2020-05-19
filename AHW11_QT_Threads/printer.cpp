#include "printer.h"

Printer::Printer(const QString &msg) : m_msg(msg)
{
    qDebug() << "Constructor Printer";
}

Printer::~Printer()
{
    qDebug() << "Destructor Printer";

    if (m_timer->isActive()) {
        m_timer->stop();
    }

    delete m_timer;
}

void Printer::init()
{
    m_timer = new QTimer;

    connect(m_timer, &QTimer::timeout, this, &Printer::printMsg);
}


// метод смены сообщения
void Printer::setMsg(QString msg)
{
    m_msg = msg;
}

// метод смены интервала
void Printer::setInterval(int interval)
{
    m_interval = interval;
}



void Printer::printMsg()
{
    CountMess++;
    qDebug() << m_msg << CountMess;


    if (CountMess == 15)
    {
       emit sig_PrinterCount15();
      // CountMess = 0;
    }

    if (CountMess == 30)
    {
       emit sig_PrinterCount30();
      // CountMess = 0;
    }
}

void Printer::startPrinting()
{
    m_timer->start(m_interval);
}

void Printer::endPrinting()
{
    m_timer->stop();
}


// функционал смены сообщения
void Printer::sl_PrinterChMess(QString msg_new)
{
    qDebug() << "Printer. Message Changed.";
    setMsg(msg_new);
}

// функционал смены интервала
void Printer::sl_PrinterChInterval(int interval_new)
{
    qDebug() << "Printer. Interval Changed.";
    setInterval(interval_new);
    m_timer->stop();
    m_timer->start(m_interval);
}
