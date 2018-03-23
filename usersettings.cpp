#include "usersettings.h"
#include "ui_usersettings.h"

UserSettings::UserSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSettings)
{
    ui->setupUi(this);
}

UserSettings::~UserSettings()
{
    delete ui;
}

void UserSettings::on_startButton_clicked()
{

}
