#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QSettings>
#include <QInputDialog>
#include <QListWidget>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pm(PresetsManager())
    , cm(ConfigManager())
    , player(SoundboardPlayer())
    , configAction(QAction(this))
    , soundDialog(NewSoundDialog(this))
    , configDialog(ConfigDialog(this))
{
    ui->setupUi(this);
    ui->presetsList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->soundsList->setContextMenuPolicy(Qt::CustomContextMenu);

    addConfigure();
    connectWidgets();

    refreshPresetsList();
    refreshSoundsList();

    for (Preset& preset : pm.getPresets()) {
        qDebug().nospace() << "Preset name: " << qUtf8Printable(preset.getName());
        qDebug("Sounds :");
        for (Sound& s : preset.getSounds()) {
            qDebug().nospace() << "Name: " << qUtf8Printable(s.getName()) << ", Path: " << qUtf8Printable(s.getPath().toString());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSoundDialog()
{
    soundDialog.exec();
}

void MainWindow::onSoundDialogFinished(int result)
{
    if (result != QDialog::Accepted) return;

    QString currentPresetName = ui->presetsList->currentItem()->text();
    QString soundName = soundDialog.getSoundName();
    QUrl    soundPath = soundDialog.getSoundPath();

    if (soundName.isEmpty() || soundPath.isEmpty()) return;

    if (!ui->soundsList->findItems(soundName, Qt::MatchExactly).empty()) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Sound already exists!."));
        return;
    }

    pm.addSoundToPreset(currentPresetName, soundName, soundPath);
    refreshSoundsList();
}

void MainWindow::refreshSoundsList()
{
    ui->soundsList->clear();
    QListWidgetItem *currentPreset = ui->presetsList->currentItem();

    if (!currentPreset) return;

    QString currentPresetName = currentPreset->text();
    QVector<Sound>& currentPresetSounds = pm.getPreset(currentPresetName)->getSounds();

    for (Sound &s : currentPresetSounds) {
        ui->soundsList->addItem(s.getName());
    }

    pm.savePresets();
}

void MainWindow::refreshPresetsList()
{
    ui->presetsList->clear();

    for (Preset &p : pm.getPresets()) {
        ui->presetsList->addItem(p.getName());
    }

    pm.savePresets();
}

void MainWindow::deletePreset()
{
    QString currentPresetName = ui->presetsList->currentItem()->text();

    pm.deletePreset(currentPresetName);
    deletePresetFromList();
    refreshPresetsList();
    refreshSoundsList();
}

void MainWindow::deleteSoundFromPreset()
{
    QString currentSoundName = ui->soundsList->currentItem()->text();
    QString currentPresetName = ui->presetsList->currentItem()->text();
    Preset* currentPreset = pm.getPreset(currentPresetName);

    currentPreset->deleteSound(currentSoundName);
    refreshSoundsList();
}

void MainWindow::showPresetContextMenu(const QPoint &pos)
{
    if (!ui->presetsList->currentItem()) return;

    // Handle global position
    QPoint globalPos = ui->presetsList->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu presetContextMenu;
    presetContextMenu.addAction(tr("Add Sound"), this, SLOT(openSoundDialog()));
    presetContextMenu.addAction(tr("Delete"),    this, SLOT(deletePreset()));

    // Show context menu at handling position
    presetContextMenu.exec(globalPos);
}

void MainWindow::showSoundContextMenu(const QPoint &pos)
{
    if (!ui->soundsList->currentItem()) return;

    // Handle global position
    QPoint globalPos = ui->soundsList->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu soundContextMenu;
    soundContextMenu.addAction(tr("Delete"),    this, SLOT(deleteSoundFromPreset()));

    // Show context menu at handling position
    soundContextMenu.exec(globalPos);
}

void MainWindow::addConfigure()
{
    configAction.setText(QString(tr("Configure")));
    ui->menubar->addAction(&configAction);
}

void MainWindow::connectWidgets()
{
    connect(ui->actionExit,      SIGNAL(triggered()),                                            this, SLOT(exitApp()));
    connect(ui->presetsList,     SIGNAL(customContextMenuRequested(QPoint)),                     this, SLOT(showPresetContextMenu(QPoint)));
    connect(ui->presetsList,     SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),  this, SLOT(refreshSoundsList()));
    connect(ui->actionNewPreset, SIGNAL(triggered()),                                            this, SLOT(createNewPreset()));
    connect(&configAction,       SIGNAL(triggered()),                                            this, SLOT(showConfigure()));
    connect(ui->soundsList,      SIGNAL(itemDoubleClicked(QListWidgetItem*)),                    this, SLOT(playSound(QListWidgetItem*)));
    connect(ui->soundsList,      SIGNAL(customContextMenuRequested(QPoint)),                     this, SLOT(showSoundContextMenu(QPoint)));
    connect(&soundDialog,        SIGNAL(finished(int)),                                          this, SLOT(onSoundDialogFinished(int)));
    connect(&configDialog,       SIGNAL(finished(int)),                                          this, SLOT(updateDevices(int)));
}

void MainWindow::exitApp()
{
    QCoreApplication::quit();
}

void MainWindow::showConfigure()
{
    configDialog.exec();
}

void MainWindow::updateDevices(int result)
{
    if (result != QDialog::Accepted) return;
    
    cm.setPrimaryOutputDeviceName(configDialog.getSelectedPrimaryDeviceName());
    cm.setSecondaryOutputDeviceName(configDialog.getSelectedSecondaryDeviceName());

    player.setPrimaryOutputDevice(cm.getPrimaryOutputDeviceName());
    player.setSecondaryOutputDevice(cm.getSecondaryOutputDeviceName());
}

void MainWindow::playSound(QListWidgetItem* item)
{
    if (cm.getPrimaryOutputDeviceName().isNull()) {
        return;
    }

    QString selectedSoundName = item->text();
    QString selectedPresetName = ui->presetsList->currentItem()->text();
    Sound* selectedSound = pm.getPreset(selectedPresetName)->getSound(selectedSoundName);

    player.setSource(selectedSound->getPath());
    player.play();
}

void MainWindow::deletePresetFromList()
{
    QList<QListWidgetItem*> items = ui->presetsList->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->presetsList->takeItem(ui->presetsList->row(item));
    }
}

void MainWindow::createNewPreset()
{
    bool ok;
    QString presetName = QInputDialog::getText(this, tr("New Preset"), tr("Enter preset name:"), QLineEdit::Normal, "Preset1", &ok);

    if (ok && !presetName.isEmpty()) {
        if (pm.presetExists(presetName)) {;
            QMessageBox::warning(this, tr("Failed"), tr("Preset already exists!"));
            return;
        }

        Preset newPreset = Preset(presetName);

        pm.addPreset(newPreset);
        refreshPresetsList();
    }
}

void MainWindow::selectPreset(QListWidgetItem *item)
{
    QString presetName = item->text();
    Preset* preset = pm.getPreset(presetName);

    QVector<Sound> presetSounds = preset->getSounds();

    for (Sound sound : presetSounds)
    {
        new QListWidgetItem(sound.getName(), ui->soundsList);
    }
}
