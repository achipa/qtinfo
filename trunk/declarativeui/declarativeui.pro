######################################################################
# Automatically generated by qmake (2.01a) to 24. maalis 09:24:08 2011
######################################################################

TEMPLATE = lib
#TARGET =
DEPENDPATH += .
INCLUDEPATH += .

QT += core gui declarative

# Input
HEADERS += declarativeui.h
SOURCES += declarativeui.cpp

symbian {
    DESTDIR=test1

    #Build STDDLL
    CONFIG += stdbinary

    TARGET = declarativeui

    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN

    TARGET.EPOCALLOWDLLDATA = 1

    addFiles.sources = $${TARGET}.dll
    addFiles.path = !:/sys/bin

    # Add more folders to ship with the application, here
    folder_01.source = qml_symbian
    folder_01.target = .
    DEPLOYMENTFOLDERS = folder_01

    DEPLOYMENT += addFiles
}

exists($$QMAKE_INCDIR_QT"/../qmsystem2/qmkeys.h"):!contains(MEEGO_EDITION,harmattan): {
  MEEGO_VERSION_MAJOR     = 1
  MEEGO_VERSION_MINOR     = 2
  MEEGO_VERSION_PATCH     = 0
  MEEGO_EDITION           = harmattan
  DEFINES += MEEGO_EDITION_HARMATTAN
}

load(sailfishsilicabackground)

unix:!symbian: {
    contains(MEEGO_EDITION,harmattan): {
	    # Add more folders to ship with the application, here
        folder_01.files = qml_meegoharmattan/*
    }
    contains(LIBS,-lsailfishsilicabackground): {
        folder_01.files = qml_sailfish/*
    }

    folder_01.path = /opt/qtinfo/qml
    target.path = /opt/qtinfo/bin
    INSTALLS += target folder_01
}

OTHER_FILES += \
    main.qml \
    qml_symbian/main.qml \
    qml_symbian/MainPage.qml \
    qml_symbian/InfoView.qml \
    qml_meegoharmattan/main.qml \
    qml_meegoharmattan/MainPage.qml \
    qml_meegoharmattan/InfoView.qml \
    qml_sailfish/main.qml \
    qml_sailfish/MainPage.qml \
    qml_sailfish/InfoView.qml \
    qml_desktop/main.qml \
    qml_meegoux/main.qml

RESOURCES += \
    qtquickqmls.qrc

for(deploymentfolder, DEPLOYMENTFOLDERS) {
    item = item$${deploymentfolder}
    itemsources = $${item}.sources
    $$itemsources = $$eval($${deploymentfolder}.source)
    itempath = $${item}.path
    $$itempath= $$eval($${deploymentfolder}.target)
    export($$itemsources)
    export($$itempath)
    DEPLOYMENT += $$item
}

include(../qtinfo_symbianplatsec.pri)
