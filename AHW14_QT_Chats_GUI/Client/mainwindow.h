#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>

#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Client *m_client = nullptr;
    QThread *senderThread = nullptr;

private slots:
    void on_ButtonCon_clicked();
    void on_ButtonDiscon_clicked();
    void on_ButtonSend_clicked();
    void PrintText(QString);
    void PrintTextWin(QString);

signals:
    void sendText(QString);
    void disconnect();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
