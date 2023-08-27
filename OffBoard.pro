QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configdialog.cpp \
    configmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    newsounddialog.cpp \
    preset.cpp \
    presetsmanager.cpp \
    settingsio.cpp \
    sound.cpp \
    soundboardplayer.cpp

HEADERS += \
    configdialog.h \
    configmanager.h \
    mainwindow.h \
    newsounddialog.h \
    preset.h \
    presetsmanager.h \
    settingsio.h \
    sound.h \
    soundboardplayer.h

FORMS += \
    configdialog.ui \
    mainwindow.ui \
    newsounddialog.ui

TRANSLATIONS += \
    OffBoard_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
