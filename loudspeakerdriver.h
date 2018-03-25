#ifndef LOUDSPEAKERDRIVER_H
#define LOUDSPEAKERDRIVER_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QFile>
#include <QDebug>

class LoudSpeakerDriver : public QObject
{
    Q_OBJECT
public:
    explicit LoudSpeakerDriver(QObject *parent = 0);
    virtual ~LoudSpeakerDriver();

signals:

public slots:

private slots:
    void handleStateChanged(QAudio::State);
private:
    QAudioOutput *m_audio;
    QFile *m_sourceFile;
};

#endif // LOUDSPEAKERDRIVER_H
