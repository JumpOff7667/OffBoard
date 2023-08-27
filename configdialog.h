#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QMediaDevices>
#include <QAudioDevice>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = nullptr);
    ~ConfigDialog();

    QString& getSelectedPrimaryDeviceName();
    QString& getSelectedSecondaryDeviceName();

private:
    Ui::ConfigDialog *ui;
    QString selectedPrimaryDeviceName;
    QString selectedSecondaryDeviceName;

    void addDevicesToLists();
    void connect();
    void setSelectedPrimaryDeviceName();
    void setSelectedSecondaryDeviceName();

private slots:
    void acceptDialog();
};

#endif // CONFIGDIALOG_H
