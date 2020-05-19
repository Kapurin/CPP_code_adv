#include "printworker.h"

PrintWorker::PrintWorker()
{
    qDebug() << "Constructor PrintWorker";

    m_printer = new Printer("Some Message");
    m_threadP = new QThread;

    m_printer->moveToThread(m_threadP);

    connect(m_threadP, &QThread::finished, m_printer, &Printer::deleteLater);
    connect(m_threadP, &QThread::finished, m_threadP, &QThread::deleteLater);

    connect(this, &PrintWorker::s_startPrint, m_printer, &Printer::startPrinting);
    connect(this, &PrintWorker::s_stopPrint,  m_printer, &Printer::endPrinting);

    // функционал смены сообщения
    connect(m_printer, &Printer::sig_PrinterCount15, this, &PrintWorker::sig_PrintWToGeneralCount15, Qt::DirectConnection);
    connect(this, &PrintWorker::sig_PrintWToPrinterChMess, m_printer, &Printer::sl_PrinterChMess, Qt::DirectConnection);

    // функционал смены интервала
    connect(m_printer, &Printer::sig_PrinterCount30, this, &PrintWorker::sig_PrintWToGeneralCount30, Qt::DirectConnection);
    connect(this, &PrintWorker::sig_PrintWToPrinterChInterval, m_printer, &Printer::sl_PrinterChInterval, Qt::DirectConnection);

    connect(m_threadP, &QThread::started, m_printer, &Printer::init);

    m_threadP->start();
}

PrintWorker::~PrintWorker()
{
    qDebug() << "Destructor PrintWorker";

    m_threadP->quit();
    m_threadP->wait();
}

void PrintWorker::StartPrint()
{
    emit s_startPrint();
}

void PrintWorker::StopPrint()
{
    emit s_stopPrint();
}


