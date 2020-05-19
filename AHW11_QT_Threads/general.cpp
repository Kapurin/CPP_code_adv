#include "general.h"
#include "Windows.h"

General::General()
{
    m_printer = new PrintWorker;

    // функционал смены сообщения
    connect(m_printer, &PrintWorker::sig_PrintWToGeneralCount15, this, &General::sl_PrintWToGeneralCount15, Qt::DirectConnection);
    connect(this, &General::sig_GeneralToPrintWChMess, m_printer, &PrintWorker::sig_PrintWToPrinterChMess,Qt::DirectConnection);

    // функционал смены интервала
    connect(m_printer, &PrintWorker::sig_PrintWToGeneralCount30, this, &General::sl_PrintWToGeneralCount30, Qt::DirectConnection);
    connect(this, &General::sig_GeneralToPrintWChInterval, m_printer, &PrintWorker::sig_PrintWToPrinterChInterval,Qt::DirectConnection);
}



void General::example_2()
{
    m_printer->StartPrint();

    Sleep(40000);

    delete m_printer;
}


// функционал смены сообщения
void General::sl_PrintWToGeneralCount15()
{
    qDebug() << "General. Counter reached 15!";
    emit sig_GeneralToPrintWChMess("Message_NEW");
}


// функционал смены интервала
void General::sl_PrintWToGeneralCount30()
{
    qDebug() << "General. Counter reached 30!";
    emit sig_GeneralToPrintWChInterval(500);
}

