#ifndef PRESET_H
#define PRESET_H

#include "sound.h"

#include <QUrl>
#include <QString>
#include <QVector>
#include <QDataStream>

class Preset
{
private:
    QString name;
    QVector<Sound> sounds;

public:
    Preset(QString);
    Preset() = default;
    ~Preset();
    void addSound(Sound);
    QString& getName();
    QVector<Sound>& getSounds();
    Sound* getSound(QString& name);
    void deleteSound(QString& name);
};

#endif // PRESET_H
