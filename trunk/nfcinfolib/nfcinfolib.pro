######################################################################
# Automatically generated by qmake (2.01a) to 24. maalis 09:24:08 2011
######################################################################

TEMPLATE = lib
#TARGET =
DEPENDPATH += .
INCLUDEPATH += .

QT += core gui nfc

# Input
HEADERS += nfcinfo.h
SOURCES += nfcinfo.cpp

symbian {
    #Build STDDLL
    CONFIG += stdbinary

    TARGET = nfcinfolib

    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.EPOCALLOWDLLDATA = 1

    addFiles.sources = $${TARGET}.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian: {
    target.path = /opt/qtinfo/bin
    INSTALLS += target

    include(../sailfish.pri)

}

android: include(../android.pri)

include(../qtinfo_symbianplatsec.pri)
