#include "mainwindow.h"
#include <QApplication>
#include "dongledriver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    DongleDriver myDongle("/dev/ttyUSB0", "/dev/ttyUSB1");
//    myDongle.writeCommand("AT\r\n");
    return a.exec();
}
