#ifndef SETTINGSIO_H
#define SETTINGSIO_H

#include <QSettings>
#include <QStandardPaths>
#include "preset.h"

class SettingsIO
{
public:
    static SettingsIO& getInstance()
    {
        static SettingsIO instance;
        return instance;
    }

    SettingsIO(SettingsIO const&)     = delete;
    void operator=(SettingsIO const&) = delete;

    QVector<Preset> readPresets();
    void writePresets(QVector<Preset>);

private:
    SettingsIO() {}

    const static inline QString PRESETS_KEY = "soundboard/presets";
    QSettings settings;
};

#endif // SETTINGSIO_H
