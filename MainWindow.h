#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QAction>

#include "configmanager.h"
#include "presetsmanager.h"
#include "newsounddialog.h"
#include "configdialog.h"
#include "soundboardplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PresetsManager pm;
    ConfigManager cm;
    SoundboardPlayer player;
    QAction aboutAction;
    QAction configAction;
    NewSoundDialog soundDialog;
    ConfigDialog configDialog;

    void addConfigure();
    void connectWidgets();
    //void addPresetToList(QString);
    void deletePresetFromList();
    void refreshPresetsList();
    void setupSoundDialog();

private slots:
    void onSoundDialogFinished(int);
    void openSoundDialog();
    void deletePreset();
    void deleteSoundFromPreset();
    void exitApp();
    void showConfigure();
    void playSound(QListWidgetItem *item);
    void createNewPreset();
    void selectPreset(QListWidgetItem *item);
    void showPresetContextMenu(const QPoint&);
    void showSoundContextMenu(const QPoint&);
    void updateDevices(int);
    void refreshSoundsList();
};

#endif // MAINWINDOW_H
