#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Server *SrvPtr = nullptr;

private slots:
    void on_ButtonStart_clicked();
    void on_ButtonStop_clicked();
    void PrintText(QString Txt);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
