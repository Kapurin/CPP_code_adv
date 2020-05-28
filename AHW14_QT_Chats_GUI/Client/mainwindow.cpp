#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ButtonDiscon->setEnabled(false);
    ui->ButtonSend->setEnabled(false);
    ui->label_StsOut->setText("Disconnected!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonCon_clicked()
{
    if (((ui->lineEdit_IP->text().isEmpty()) == false) && ((ui->lineEdit_Port->text().isEmpty()) == false))
    {
        m_client = new Client(ui->lineEdit_IP->text(), ui->lineEdit_Port->text().toUInt());
        senderThread = new QThread;
        m_client->moveToThread(senderThread);

        QObject::connect(this, &MainWindow::sendText, m_client, &Client::sendMsg);
        QObject::connect(m_client, &Client::connected, this, &MainWindow::PrintText);
        QObject::connect(m_client, &Client::disconnected, this, &MainWindow::PrintText);
        QObject::connect(m_client, &Client::sendError, this, &MainWindow::PrintTextWin);

        QObject::connect(this, &MainWindow::disconnect, m_client, &Client::deleteLater);
        QObject::connect(m_client, &Client::destroyed, this, [=](){ senderThread->quit(); senderThread->wait();});
        QObject::connect(senderThread, &QThread::finished, senderThread, &QThread::deleteLater);

        senderThread->start();

        ui->ButtonCon->setEnabled(false);
        ui->ButtonDiscon->setEnabled(true);
        ui->ButtonSend->setEnabled(true);
        ui->textEdit_InWin->clear();
    }
    else
    {
        qDebug () << "Areas IP or Port is empty!";
        PrintTextWin("Areas IP or Port is empty!");
    }
}

void MainWindow::on_ButtonDiscon_clicked()
{
    emit disconnect();
    ui->ButtonCon->setEnabled(true);
    ui->ButtonDiscon->setEnabled(false);
    ui->ButtonSend->setEnabled(false);
}

void MainWindow::on_ButtonSend_clicked()
{
    emit sendText(ui->textEdit_InWin->toPlainText());
    ui->textEdit_InWin->clear();
}

void MainWindow::PrintText(QString Txt)
{
    ui->label_StsOut->setText(Txt);
    if (Txt == "Disconnected!")
    {
        ui->ButtonCon->setEnabled(true);
        ui->ButtonDiscon->setEnabled(false);
    }
}
void MainWindow::PrintTextWin(QString Txt)
{
    ui->textEdit_InWin->setText(Txt);
    ui->ButtonCon->setEnabled(true);
    ui->ButtonDiscon->setEnabled(false);
}
