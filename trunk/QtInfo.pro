#-------------------------------------------------
#
# Project created by QtCreator 2011-03-17T15:58:35
#
#-------------------------------------------------

QT       += core gui webkit opengl

contains(QT_VERSION, ^4\\.[0-6]\\..*) symbian: QT -= opengl

TARGET = QtInfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = systeminfo

symbian {

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog
    TARGET.UID3 = 0xe4b20d40
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

maemo5 {
    target.path = /opt/QtInfo/bin
    INSTALLS += target
}
