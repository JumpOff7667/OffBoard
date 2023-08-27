#ifndef SETTINGSIO_H
#define SETTINGSIO_H

#include <QSettings>

class SettingsIO
{
public:
    SettingsIO() = default;
    void read();
    void write();

private:
    QSettings settings;
};

#endif // SETTINGSIO_H
