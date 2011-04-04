#-------------------------------------------------
#
# Project created by QtCreator 2011-03-17T15:58:35
#
#-------------------------------------------------

QT       += core gui


TARGET = qtinfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

#CONFIG += mobility
#MOBILITY = systeminfo

symbian {
    TARGET.UID3 = 0xe4b20d40
    TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData # WriteDeviceData ReadDeviceData ?
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

contains(QMAKE_HOST.os, Linux): {
    GITREV=$$system(git rev-parse HEAD)
    message(Git rev $$GITREV)
}

CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT

RESOURCES += \
    qtinfo.qrc

maemo5 {
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}
