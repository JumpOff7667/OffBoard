#include "presetsmanager.h"
#include "settingsio.h"

PresetsManager::PresetsManager()
{
    loadPresets();
}

void PresetsManager::addPreset(Preset preset)
{
    presets.append(preset);
}

void PresetsManager::setPresets(QVector<Preset>& presets)
{
    this->presets = presets;
}

void PresetsManager::setPresets(QVector<Preset>&& presets)
{
    this->presets = presets;
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

void PresetsManager::loadPresets()
{
    setPresets(SettingsIO::getInstance().readPresets());
}

void PresetsManager::savePresets()
{
    SettingsIO::getInstance().writePresets(presets);
}
