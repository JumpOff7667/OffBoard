#ifndef SOUNDBOARDPLAYER_H
#define SOUNDBOARDPLAYER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioDevice>

class SoundboardPlayer
{
public:
    SoundboardPlayer();

    void setPrimaryOutputDevice(QAudioDevice& device);
    void setPrimaryOutputDevice(QString& deviceName);
    void setSecondaryOutputDevice(QAudioDevice& device);
    void setSecondaryOutputDevice(QString& deviceName);
    void setSource(QUrl& url);
    QUrl getSource();
    void play();

private:
    QList<QAudioDevice> audioDevices;
    QMediaPlayer primaryPlayer;
    QMediaPlayer secondaryPlayer;
    QAudioOutput primaryOutput;
    QAudioOutput secondaryOutput;
};

#endif // SOUNDBOARDPLAYER_H
