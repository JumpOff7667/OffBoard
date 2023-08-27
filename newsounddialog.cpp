#include "newsounddialog.h"
#include "ui_newsounddialog.h"

NewSoundDialog::NewSoundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSoundDialog)
{
    ui->setupUi(this);

    this->setModal(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowTitle("New Sound");

    connect();

}

NewSoundDialog::~NewSoundDialog()
{
    delete ui;
}

void NewSoundDialog::browseSoundFile()
{
    QString musicDir = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Select Sound"), musicDir, tr("Audio Files (*.m4a *.mp3 *.wav)"));

    ui->soundPath->setText(fileName);
}

void NewSoundDialog::confirmSoundDialog()
{
    soundName = ui->soundName->text();
    soundPath = QUrl(ui->soundPath->text());

    accept();
}

void NewSoundDialog::connect()
{
    QAbstractButton::connect(ui->browse,    SIGNAL(clicked()),  this, SLOT(browseSoundFile()));
    QAbstractButton::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(confirmSoundDialog()));
    QAbstractButton::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QString& NewSoundDialog::getSoundName()
{
    return soundName;
}

QUrl& NewSoundDialog::getSoundPath()
{
    return soundPath;
}
