#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T19:54:21
#
#-------------------------------------------------

QT       += core gui
QT      += serialport
QT      += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DongleDialer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dongledriver.cpp \
    usersettings.cpp \
    microphonedriver.cpp \
    loudspeakerdriver.cpp

HEADERS  += mainwindow.h \
    dongledriver.h \
    usersettings.h \
    microphonedriver.h \
    loudspeakerdriver.h

FORMS    += mainwindow.ui \
    usersettings.ui
