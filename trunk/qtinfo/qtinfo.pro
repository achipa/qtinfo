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

unix:!symbian { # not funny
    desktopfile.files = $${TARGET}.desktop
    maemo5 {
        icon.files = $${TARGET}.png
        icon.path = /usr/share/icons/hicolor/64x64/apps
        desktopfile.path = /usr/share/applications/hildon
    } else {
        icon.files = $${TARGET}.svg
        icon.path = /usr/share/themes/base/meegotouch/icons
        desktopfile.path = /usr/share/applications
    }
    target.path = /opt/qtinfo/bin
    INSTALLS += desktopfile icon target  
}
