#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    this->setModal(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowTitle("Configuration");

    addDevicesToLists();
    connect();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::addDevicesToLists()
{
    QList<QAudioDevice> devices = QMediaDevices::audioOutputs();

    for (QAudioDevice &d : devices) {
        ui->primaryDevicesList->addItem(d.description());
        ui->secondaryDevicesList->addItem(d.description());
    }
}

void ConfigDialog::setSelectedPrimaryDeviceName()
{
    this->selectedPrimaryDeviceName = ui->primaryDevicesList->currentItem()->text();
}

void ConfigDialog::setSelectedSecondaryDeviceName()
{
    this->selectedSecondaryDeviceName = ui->secondaryDevicesList->currentItem()->text();
}

void ConfigDialog::acceptDialog()
{
    setSelectedPrimaryDeviceName();
    setSelectedSecondaryDeviceName();
    accept();
}

QString& ConfigDialog::getSelectedPrimaryDeviceName()
{
    return this->selectedPrimaryDeviceName;
}

QString& ConfigDialog::getSelectedSecondaryDeviceName()
{
    return this->selectedSecondaryDeviceName;
}

void ConfigDialog::connect()
{
    QAbstractButton::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptDialog()));
    QAbstractButton::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}
