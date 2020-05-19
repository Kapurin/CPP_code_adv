#ifndef PRINTWORKER_H
#define PRINTWORKER_H

#include <QThread>
#include "printer.h"

class PrintWorker : public QObject
{
    Q_OBJECT

public:
    PrintWorker();
    ~PrintWorker();

    void StartPrint();
    void StopPrint();

private:
    Printer *m_printer = nullptr;
    QThread *m_threadP = nullptr;



signals:
    void s_startPrint();
    void s_stopPrint();

    // функционал смены сообщения
    void sig_PrintWToGeneralCount15();
    void sig_PrintWToPrinterChMess(QString msg_new);

    // функционал смены интервала
    void sig_PrintWToGeneralCount30();
    void sig_PrintWToPrinterChInterval(int interval_new);

};

#endif // PRINTWORKER_H
