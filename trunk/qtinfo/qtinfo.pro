#-------------------------------------------------
#
# Project created by QtCreator 2011-03-17T15:58:35
#
#-------------------------------------------------

QT       += core gui opengl


TARGET = qtinfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = systeminfo

symbian {
    contains(QT_VERSION, ^4\\.[0-6]\\..*): QT -= opengl
    TARGET.UID3 = 0xe4b20d40
    TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

contains(QMAKE_HOST.os, Linux): GITREV=$$system(git rev-parse HEAD)
message($$GITREV)

RESOURCES += \
    qtinfo.qrc

maemo5 {
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}
