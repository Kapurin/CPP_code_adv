#include "mainwindow.h"
//#include <QCoreApplication>
#include <QApplication>
#include "server.h"


int main(int argc, char *argv[])
{
 //   QCoreApplication a(argc, argv);
    QApplication a(argc, argv);
    //Server server("127.0.0.1", 12345);

    MainWindow w;
    w.show();

    return a.exec();
}
