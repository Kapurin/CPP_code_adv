#ifndef GENERAL_H
#define GENERAL_H



#include "printworker.h"

class General : public QObject
{
    Q_OBJECT


public:
    General();

    void example_2();


public slots:

    // функционал смены сообщения
    void sl_PrintWToGeneralCount15();

    // функционал смены интервала
    void sl_PrintWToGeneralCount30();

signals:
    // функционал смены сообщения
    void sig_GeneralToPrintWChMess(QString msg_new);

    // функционал смены интервала
    void sig_GeneralToPrintWChInterval(int interval_new);

private:

    PrintWorker *m_printer = nullptr;
};

#endif // GENERAL_H
