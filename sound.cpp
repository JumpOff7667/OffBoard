#include "sound.h"

Sound::Sound(QString& name, QUrl& path) : name(name), path(path){}

QString& Sound::getName()
{
    return name;
}

QUrl& Sound::getPath()
{
    return path;
}
