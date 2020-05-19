#include <QCoreApplication>

#include "general.h"

#include <QVector>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QVector<int> vec;

    General g_class;
    g_class.example_2();

    return app.exec();
}


