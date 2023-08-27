#include "configmanager.h"

QString& ConfigManager::getPrimaryOutputDeviceName()
{
    return this->primaryOutputDeviceName;
}

QString& ConfigManager::getSecondaryOutputDeviceName()
{
    return this->SecondaryOutputDeviceName;
}

void ConfigManager::setPrimaryOutputDeviceName(QString& deviceName)
{
    this->primaryOutputDeviceName = deviceName;
}

void ConfigManager::setSecondaryOutputDeviceName(QString& deviceName)
{
    this->SecondaryOutputDeviceName = deviceName;
}
