#-------------------------------------------------
#
# Project created by QtCreator 2011-03-17T15:58:35
#
#-------------------------------------------------

QT       += core gui


TARGET = qtinfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    infoloader.cpp

HEADERS  += mainwindow.h \
    infoloader.h

FORMS    += mainwindow.ui

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
    INSTALLS += desktopfile icon target
}

include(../qtinfo_symbianplatsec.pri)
