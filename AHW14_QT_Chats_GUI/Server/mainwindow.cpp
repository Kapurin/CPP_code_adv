#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ButtonStop->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonStart_clicked()
{
    SrvPtr = new Server("127.0.0.1", 12345);
    connect(SrvPtr, &Server::PrintText, this, &MainWindow::PrintText);
    PrintText("Server running...");

    ui->ButtonStart->setEnabled(false);
    ui->ButtonStop->setEnabled(true);
}

void MainWindow::on_ButtonStop_clicked()
{
    delete SrvPtr;
    SrvPtr = nullptr;
    PrintText("Server stopped!");

    ui->ButtonStart->setEnabled(true);
    ui->ButtonStop->setEnabled(false);
}

void MainWindow::PrintText(QString Txt)
{
   ui->textEdit->append(Txt);
}
