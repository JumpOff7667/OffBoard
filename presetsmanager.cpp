#include "presetsmanager.h"

PresetsManager::PresetsManager()
{
    loadStoredPresets();
}

void PresetsManager::addPreset(Preset preset)
{
    presets.append(preset);

//    QSettings settings;
//    settings.setValue("presetsManager/presets", QVariant::fromValue(*(presets)));
//    settings.sync();
}

void PresetsManager::addSoundToPreset(QString presetName, QString soundName, QUrl soundPath)
{
    if (soundName.isEmpty() || soundPath.isEmpty()) return;

    getPreset(presetName)->addSound(Sound(soundName, soundPath));
}

void PresetsManager::deletePreset(QString name)
{
    presets.erase(std::remove_if(presets.begin(), presets.end(), [&name](Preset& p) { return p.getName() == name; }),
              presets.end());
}

bool PresetsManager::presetExists(QString name)
{
    for (Preset& p : presets)
    {
        if (p.getName() == name) return true;
    }

    return false;
}

Preset* PresetsManager::getPreset(QString name)
{
    for (Preset& p : presets)
    {
        if (p.getName() == name) return &p;
    }

    return nullptr;
}

QVector<Preset>& PresetsManager::getPresets()
{
    return presets;
}

void PresetsManager::loadStoredPresets()
{
//    QSettings settings;
//    QVector<Preset> presets = settings.value("presetsManager/presets").value<QVector<Preset>>();

//    if (!presets.isEmpty()) {
//        *(presets) = presets;
//    }
}
