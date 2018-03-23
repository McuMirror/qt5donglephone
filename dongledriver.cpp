#include "dongledriver.h"
/**
 * @brief DongleDriver::DongleDriver
 * @param path
 */
DongleDriver::DongleDriver(QString path):m_device(new QSerialPort(path))
{
    if(m_device->open(QIODevice::ReadWrite)){
        m_device->setBaudRate(QSerialPort::Baud115200);
        m_device->setDataBits(QSerialPort::Data8);
        m_device->setParity(QSerialPort::NoParity);
        m_device->setStopBits(QSerialPort::OneStop);
        m_device->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(m_device, SIGNAL(readyRead()), this, SLOT(OnDataAvailabeForRead()));
    }else{
        qDebug() << "Error In Initialising Device:" << m_device->errorString();
    }
}

DongleDriver::~DongleDriver()
{

}
/**
 * @brief DongleDriver::Initialize
 */
void DongleDriver::Initialize()
{
    if(m_device->open(QIODevice::ReadWrite)){
        m_device->setBaudRate(QSerialPort::Baud115200);
        m_device->setDataBits(QSerialPort::Data8);
        m_device->setParity(QSerialPort::NoParity);
        m_device->setStopBits(QSerialPort::OneStop);
        m_device->setFlowControl(QSerialPort::NoFlowControl);
        m_device->write("AT\n\r");
        if(m_device->waitForReadyRead(100)){
            QByteArray resp = m_device->readAll();
            qDebug() << "Resp : " << resp;
        }
    }else{
        qDebug() << "Error In Initialising Device:" << m_device->errorString();
    }

}

void DongleDriver::writeCommand(QString cmd)
{
    if(m_device->isWritable()){
        m_device->write("AT\r\n");
    }else{
        qDebug() << "Device Not Writeble" ;
    }
}

void DongleDriver::OnDataAvailabeForRead()
{
    QByteArray resp = m_device->readAll();
    qDebug() << "Some Data availabe: " << resp ;
}


