#ifndef DONGLEDRIVER_H
#define DONGLEDRIVER_H

#include <QString>
#include <QSerialPort>
#include <QDebug>
/**
 * @brief The DongleDriver class
 *  we can use readReady signal for implementating our Framer.
 *
 */
class DongleDriver : public QObject
{
    Q_OBJECT

public:
    DongleDriver(QString path);
    virtual ~DongleDriver();
    void Initialize(void);
    void writeCommand(QString cmd);
private:
    QSerialPort *m_device;
protected slots:
    void OnDataAvailabeForRead();
};

#endif // DONGLEDRIVER_H
