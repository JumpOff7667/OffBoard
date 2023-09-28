#ifndef PRESETSMANAGER_H
#define PRESETSMANAGER_H

#include "preset.h"
#include <QSettings>

class PresetsManager
{
private:
    QVector<Preset> presets;
    void setPresets(QVector<Preset>& presets);
    void setPresets(QVector<Preset>&& presets);
    void loadPresets();

public:
    PresetsManager();
    void addPreset(Preset preset);
    void addSoundToPreset(QString presetName, QString soundName, QUrl soundPath);
    void deletePreset(QString presetName);
    void savePresets();
    bool presetExists(QString presetName);
    Preset* getPreset(QString presetName);
    QVector<Preset>& getPresets();
};

#endif // PRESETSMANAGER_H
