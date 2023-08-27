#include "preset.h"

Preset::Preset(QString name) : name(name) {}

Preset::~Preset()
{
    this->sounds.clear();
}

void Preset::addSound(Sound sound)
{
    this->sounds.append(sound);
}

QString& Preset::getName()
{
    return this->name;
}

QVector<Sound>& Preset::getSounds() {
    return this->sounds;
}

Sound* Preset::getSound(QString& name) {
    for (Sound& s : this->sounds)
    {
        if (s.getName() == name) return &s;
    }

    return nullptr;
}

void Preset::deleteSound(QString& name) {
    this->sounds.erase(std::remove_if(this->sounds.begin(), this->sounds.end(), [name](Sound s) { return s.getName() == name; }),
              this->sounds.end());
}
