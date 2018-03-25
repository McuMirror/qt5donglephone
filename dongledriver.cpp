#include "dongledriver.h"
/**
 * @brief DongleDriver::DongleDriver
 * @param path
 */
DongleDriver::DongleDriver(QString cmdPath, QString audioPath):m_cmdInterface(new QSerialPort(cmdPath)),m_audioInterface(new QSerialPort(audioPath))
{
    if(m_cmdInterface->open(QIODevice::ReadWrite)){
        m_cmdInterface->setBaudRate(QSerialPort::Baud115200);
        m_cmdInterface->setDataBits(QSerialPort::Data8);
        m_cmdInterface->setParity(QSerialPort::NoParity);
        m_cmdInterface->setStopBits(QSerialPort::OneStop);
        m_cmdInterface->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(m_cmdInterface, SIGNAL(readyRead()), this, SLOT(OnCmdDataAvailabeForRead()));
    }else{
        qDebug() << "Error In Initialising Device Command Interface:" << m_cmdInterface->errorString();
    }

    if(m_audioInterface->open(QIODevice::ReadWrite)){
        m_audioInterface->setBaudRate(QSerialPort::Baud115200);
        m_audioInterface->setDataBits(QSerialPort::Data8);
        m_audioInterface->setParity(QSerialPort::NoParity);
        m_audioInterface->setStopBits(QSerialPort::OneStop);
        m_audioInterface->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(m_audioInterface, SIGNAL(readyRead()), this, SLOT(OnAudioDataAvailabeForRead()));
    }else{
        qDebug() << "Error In Initialising Device Audio Interface:" << m_audioInterface->errorString();
    }

    QAudioFormat format;
    // Set up the format, eg.
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }
    m_loudSpeaker = new QAudioOutput(format, this);
    connect(m_loudSpeaker, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleLoudSpeakerStateChanged(QAudio::State)));
    m_loudSpeaker->start(m_audioInterface);
}

DongleDriver::~DongleDriver()
{

}
/**
 * @brief DongleDriver::Initialize
 */
void DongleDriver::Initialize()
{
    if(m_cmdInterface->open(QIODevice::ReadWrite)){
        m_cmdInterface->setBaudRate(QSerialPort::Baud115200);
        m_cmdInterface->setDataBits(QSerialPort::Data8);
        m_cmdInterface->setParity(QSerialPort::NoParity);
        m_cmdInterface->setStopBits(QSerialPort::OneStop);
        m_cmdInterface->setFlowControl(QSerialPort::NoFlowControl);
        m_cmdInterface->write("AT\n\r");
        if(m_cmdInterface->waitForReadyRead(100)){
            QByteArray resp = m_cmdInterface->readAll();
            qDebug() << "Resp : " << resp;
        }
    }else{
        qDebug() << "Error In Initialising Device:" << m_cmdInterface->errorString();
    }

}

void DongleDriver::writeCommand(QString cmd)
{
    if(m_cmdInterface->isWritable()){
        m_cmdInterface->write(cmd.toStdString().c_str());
    }else{
        qDebug() << "Device Not Writeble" ;
    }
}

void DongleDriver::OnCmdDataAvailabeForRead()
{
    QByteArray resp = m_cmdInterface->readAll();
    qDebug() << "Some Command Data availabe: " << resp ;
}


void DongleDriver::OnAudioDataAvailabeForRead()
{
   // QByteArray resp = m_cmdInterface->readAll();
    qDebug() << "Some Audio Data availabe: ";// << resp ;
//    if(m_loudSpeaker->state() != QAudio::StoppedState){
//        qDebug() << "Trying to stream in default device";
//        m_loudSpeaker->start(m_cmdInterface);
//    }
}

void DongleDriver::handleLoudSpeakerStateChanged(QAudio::State newState)
{
    switch (newState) {
            case QAudio::IdleState:
                // Finished playing (no more data)
            qDebug() << "Playing Stopped NO Data";
//                    m_audio->stop();
//                    delete m_audio;
                break;

            case QAudio::StoppedState:
                // Stopped for other reasons
                if (m_loudSpeaker->error() != QAudio::NoError) {
                    // Error handling
                    qDebug() << "Error in Audio Output to Speaker";
                }
                break;

            default:
                // ... other cases as appropriate
                break;
        }
}
