#include <QMediaDevices>

#include "soundboardplayer.h"

SoundboardPlayer::SoundboardPlayer() :
    audioDevices(QMediaDevices::audioOutputs()),
    primaryPlayer(QMediaPlayer()),
    secondaryPlayer(QMediaPlayer()),
    primaryOutput(QAudioOutput()),
    secondaryOutput(QAudioOutput())
{
    primaryPlayer.setAudioOutput(&primaryOutput);
    secondaryPlayer.setAudioOutput(&secondaryOutput);
    primaryOutput.setVolume(50);
    secondaryOutput.setVolume(50);

    primaryOutput.setDevice(QAudioDevice());
}

void SoundboardPlayer::play()
{
    primaryPlayer.play();
    secondaryPlayer.play();
}

void SoundboardPlayer::setSource(QUrl& url)
{
    primaryPlayer.setSource(url);
    secondaryPlayer.setSource(url);
}

QUrl SoundboardPlayer::getSource()
{
    return primaryPlayer.source();
}

void SoundboardPlayer::setPrimaryOutputDevice(QAudioDevice& device)
{
    primaryOutput.setDevice(device);
}

void SoundboardPlayer::setPrimaryOutputDevice(QString& deviceName)
{
    auto itAudioDevice = std::find_if(
        audioDevices.begin(), audioDevices.end(),
        [deviceName](QAudioDevice& a) { return a.description() == deviceName; }
    );

    if (itAudioDevice != audioDevices.end()) setPrimaryOutputDevice(*itAudioDevice);
}

void SoundboardPlayer::setSecondaryOutputDevice(QAudioDevice& device)
{
    secondaryOutput.setDevice(device);
}

void SoundboardPlayer::setSecondaryOutputDevice(QString& deviceName)
{
    auto itAudioDevice = std::find_if(
        audioDevices.begin(), audioDevices.end(),
        [deviceName](QAudioDevice& a) { return a.description() == deviceName; }
        );

    if (itAudioDevice != audioDevices.end()) setSecondaryOutputDevice(*itAudioDevice);
}
