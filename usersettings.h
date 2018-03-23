#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QWidget>

namespace Ui {
class UserSettings;
}

class UserSettings : public QWidget
{
    Q_OBJECT

public:
    explicit UserSettings(QWidget *parent = 0);
    ~UserSettings();

private slots:
    void on_startButton_clicked();

private:
    Ui::UserSettings *ui;
};

#endif // USERSETTINGS_H
