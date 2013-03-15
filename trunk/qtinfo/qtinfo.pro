#-------------------------------------------------
#
# Project created by QtCreator 2011-03-17T15:58:35
#
#-------------------------------------------------

QT       += core gui

contains (QT_MAJOR_VERSION,5): QT += widgets

TARGET = qtinfo
TEMPLATE = app

SOURCES += main.cpp  \
    mainwindow.cpp \
    infoloader.cpp

HEADERS  += mainwindow.h \
    infoloader.h

FORMS    += mainwindow.ui

qnx {
# Cant switch UIs on BB10 so have to start with cascades upfront
    SOURCES -= main.cpp mainwindow.cpp
    HEADERS -= mainwindow.h
    SOURCES += maincascades.cpp maincascadeswindow.cpp
    HEADERS += maincascadeswindow.hpp
    CONFIG += cascades
    LIBS   += -lbbdata

}

symbian {
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x1000000
    ICON=qtinfo.svg

    # Hide the icon from the menu while maintaining the application registered
    # this allows the laucher icon to be the only one visible
    # while the laucher can still find the GUI app in the list of installed apps.
    # comment out when the launcher is not used
    RSS_RULES += "hidden = KAppIsHidden;"
}

contains(QMAKE_HOST.os, Linux): {
    GITREV=$$system(git rev-parse HEAD)
    message(Git rev $$GITREV)
}

exists($$QMAKE_INCDIR_QT"/../qmsystem2/qmkeys.h"):!contains(MEEGO_EDITION,harmattan): {
  MEEGO_VERSION_MAJOR     = 1
  MEEGO_VERSION_MINOR     = 2
  MEEGO_VERSION_PATCH     = 0
  MEEGO_EDITION           = harmattan
  DEFINES += MEEGO_EDITION_HARMATTAN
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
#    INSTALLS += desktopfile icon target
}


load(sailfishsilicabackground)
contains(LIBS,-lsailfishsilicabackground): {
    message(SailfishOS build)
    # QML files and folders
    qml.files = *.qml pages cover main.qml

    # The .desktop file
    desktop.files = qtinfo_sailfish.desktop

    # Please do not modify the following line.
    include(../sailfishapplication/sailfishapplication.pri)

    OTHER_FILES = qtinfo.yaml

}

qnx {
    !contains($${PWD}, $${OUT_PWD}) { # copy files in case of shadow building (packaging duh)
        unix: COPY = cp -r
        win32: COPY = copy /y
        QMAKE_POST_LINK +=    $$COPY $${PWD}/bb10icon.png $${OUT_PWD}/icon.png
        QMAKE_POST_LINK += && $$COPY $${PWD}/../cascadesui/assets $${OUT_PWD}/../cascadesui
    }
    OTHER_FILES += \
        bb10icon.png \
        bar-descriptor.xml
}

symbian: include(../qtinfo_symbianplatsec.pri)

