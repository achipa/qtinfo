######################################################################
# Automatically generated by qmake (2.01a) to 24. maalis 09:24:08 2011
######################################################################

TEMPLATE = lib
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

QT += core gui
maemo5 {
    CONFIG += mobility11
} else {
    CONFIG += mobility
}
MOBILITY += multimedia

# Input
HEADERS += multimediainfo.h
SOURCES += multimediainfo.cpp

maemo5 {
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}
