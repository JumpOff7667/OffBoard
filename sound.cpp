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

QDataStream& operator<<(QDataStream& out, const Sound& sound) {
    out << sound.name << sound.path;
    return out;
}

QDataStream& operator>>(QDataStream& in, Sound& sound) {
    in >> sound.name;
    in >> sound.path;
    return in;
}
