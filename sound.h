#ifndef SOUND_H
#define SOUND_Hcpp copy constructor

#include <QString>
#include <QUrl>
#include <QMetaType>

class Sound
{
private:
    QString name;
    QUrl path;

public:
    Sound() = default;
    Sound(QString&, QUrl&);
    QString& getName();
    QUrl& getPath();

    friend QDataStream& operator<<(QDataStream& out, const Sound& sound);
    friend QDataStream& operator>>(QDataStream& in, Sound& sound);
};

Q_DECLARE_METATYPE(Sound);

#endif // SOUND_H
