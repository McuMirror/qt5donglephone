#include "loudspeakerdriver.h"

LoudSpeakerDriver::LoudSpeakerDriver(QObject *parent) : QObject(parent)
{
    m_sourceFile = new QFile();
    m_sourceFile->setFileName("/home/rajesh/testrec.wav");
    m_sourceFile->open(QIODevice::ReadOnly);
        QAudioFormat format;
        // Set up the format, eg.
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleSize(8);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::UnSignedInt);
        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
        if (!info.isFormatSupported(format)) {
            qWarning() << "Raw audio format not supported by backend, cannot play audio.";
            return;
        }
        m_audio = new QAudioOutput(format, this);
        connect(m_audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
        m_audio->start(m_sourceFile);
}

LoudSpeakerDriver::~LoudSpeakerDriver()
{

}

void LoudSpeakerDriver::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
            case QAudio::IdleState:
                // Finished playing (no more data)
            qDebug() << "Playing Stopped NO Data";
            m_audio->stop();
            m_sourceFile->close();
            delete m_audio;
                break;

            case QAudio::StoppedState:
                // Stopped for other reasons
                if (m_audio->error() != QAudio::NoError) {
                    // Error handling
                    qDebug() << "Error in Audio Output to Speaker";
                }
                break;

            default:
                // ... other cases as appropriate
                break;
        }
}
