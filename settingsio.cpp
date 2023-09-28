#include "settingsio.h"


QVector<Preset> SettingsIO::readPresets()
{
    return settings.value(PRESETS_KEY).value<QVector<Preset>>();
}

void SettingsIO::writePresets(QVector<Preset> presets)
{
    settings.setValue(PRESETS_KEY, QVariant::fromValue(presets));
}
