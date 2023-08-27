#ifndef NEWSOUNDDIALOG_H
#define NEWSOUNDDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QPushButton>
#include <QStandardPaths>

namespace Ui {
class NewSoundDialog;
}

class NewSoundDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSoundDialog(QWidget *parent = nullptr);
    ~NewSoundDialog();

    QString& getSoundName();
    QUrl& getSoundPath();

private slots:
    void browseSoundFile();
    void confirmSoundDialog();

private:
    Ui::NewSoundDialog *ui;
    QString soundName;
    QUrl soundPath;

    void connect();
};

#endif // NEWSOUNDDIALOG_H
