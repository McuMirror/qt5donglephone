#ifndef DONGLEDRIVER_H
#define DONGLEDRIVER_H

#include <QString>
#include <QSerialPort>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QAudioInput>
#include <QDebug>
#include <QFile>
/**
 * @brief The DongleDriver class
 *  we can use readReady signal for implementating our Framer.
 *
 */
class DongleDriver : public QObject
{
    Q_OBJECT

public:
    DongleDriver(QString cmdPath, QString audioPath);
    virtual ~DongleDriver();
    void Initialize(void);
    void writeCommand(QString cmd);
private:
    QSerialPort *m_cmdInterface;
    QSerialPort *m_audioInterface;
    QAudioOutput *m_loudSpeaker;
    QAudioInput *m_microPhone;
protected slots:
    void OnCmdDataAvailabeForRead();
    void OnAudioDataAvailabeForRead();
    void handleLoudSpeakerStateChanged(QAudio::State);
    void handleMicroPhoneStateChanged(QAudio::State);
};

#endif // DONGLEDRIVER_H
