#ifndef SOUND_H
#define SOUND_Hcpp copy constructor

#include <QString>
#include <QUrl>

class Sound
{
private:
    QString name;
    QUrl path;

public:
    Sound(QString&, QUrl&);
    QString& getName();
    QUrl& getPath();
};

#endif // SOUND_H
