######################################################################
# Automatically generated by qmake (2.01a) to 24. maalis 09:24:08 2011
######################################################################

TEMPLATE = lib
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

QT += core gui
maemo5 {
#    CONFIG += mobility
    CONFIG += mobility11
#    CONFIG += mobility12
} else {
    CONFIG += mobility
}
MOBILITY += systeminfo sensors # serviceframework

# Input
HEADERS += mobilityinfo.h
SOURCES += mobilityinfo.cpp

maemo5 {
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}
