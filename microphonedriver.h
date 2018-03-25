#ifndef MICROPHONEDRIVER_H
#define MICROPHONEDRIVER_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QFile>
#include    <QDebug>
class MicroPhoneDriver:public QObject
{
    Q_OBJECT

public:
    MicroPhoneDriver();
    virtual ~MicroPhoneDriver();
private slots:
    void handleStateChanged(QAudio::State);
public slots:
    void stopRecording(bool _ignore);
private:
    QAudioInput *m_audio;
    QFile *m_recordingFile;

};

#endif // MICROPHONEDRIVER_H
