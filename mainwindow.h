#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dongledriver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dialButton_clicked();

    void on_poundButton_clicked();

private:
    Ui::MainWindow *ui;
    DongleDriver *m_dongle;
};

#endif // MAINWINDOW_H
