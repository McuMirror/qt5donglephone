#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dongle(new DongleDriver("/dev/ttyUSB2", "/dev/ttyUSB1"))
{
    ui->setupUi(this);
    m_dongle->writeCommand("AT\r\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dialButton_clicked()
{
    m_dongle->writeCommand("ATA\r\n");
}

void MainWindow::on_poundButton_clicked()
{
    m_dongle->writeCommand("AT^DDSETEX=2\r\n");
}
