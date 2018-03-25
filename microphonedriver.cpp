#include "microphonedriver.h"

MicroPhoneDriver::MicroPhoneDriver()
{
    m_recordingFile = new QFile();
    m_recordingFile->setFileName("/tmp/testrec.wav");
    m_recordingFile->open( QIODevice::WriteOnly | QIODevice::Truncate );
    QAudioFormat format;
    // Set up the desired format, for example:
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
          qWarning() << "Default format not supported, trying to use the nearest.";
          format = info.nearestFormat(format);
    }
    m_audio = new QAudioInput(format, this);
    connect(m_audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    m_audio->start(m_recordingFile);
}

MicroPhoneDriver::~MicroPhoneDriver()
{
    m_recordingFile->close();
}

void MicroPhoneDriver::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
      case QAudio::StoppedState:
          if (m_audio->error() != QAudio::NoError) {
              // Error handling
              qDebug() << "Error In Audio Recording" ;
          } else {
              // Finished recording
              qDebug() << "Recording Finished";
          }
          break;

      case QAudio::ActiveState:
          // Started recording - read from IO device
//            m_audio->start(m_recordingFile);
            qDebug() << "Recording Started";
          break;

      default:
          // ... other cases as appropriate
          break;
    }
}

void MicroPhoneDriver::stopRecording(bool _ignore)
{
    m_audio->stop();
    m_recordingFile->close();
    delete m_audio;
    m_audio = NULL;
}
