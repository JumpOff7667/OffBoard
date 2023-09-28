#ifndef PRESET_H
#define PRESET_H

#include "sound.h"

#include <QUrl>
#include <QString>
#include <QVector>
#include <QDataStream>
#include <QMetaType>

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

    friend QDataStream& operator<<(QDataStream& out, const Preset& preset);
    friend QDataStream& operator>>(QDataStream& in, Preset& preset);
};

Q_DECLARE_METATYPE(Preset);
Q_DECLARE_METATYPE(QList<Preset>);

#endif // PRESET_H
