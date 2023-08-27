#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

class ConfigManager
{
public:
    ConfigManager() = default;
    QString& getPrimaryOutputDeviceName();
    QString& getSecondaryOutputDeviceName();
    void setPrimaryOutputDeviceName(QString& deviceName);
    void setSecondaryOutputDeviceName(QString& deviceName);

private:
    QString primaryOutputDeviceName;
    QString SecondaryOutputDeviceName;
};

#endif // CONFIGMANAGER_H
