######################################################################
# Automatically generated by qmake (2.01a) to 24. maalis 09:24:08 2011
######################################################################

TEMPLATE = lib
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

QT += core gui declarative

CONFIG += qt cascades

LIBS   += -lbbdata

# Input
HEADERS += cascadesui.h
SOURCES += cascadesui.cpp

unix:!symbian: {
    !maemo5: {
	    # Add more folders to ship with the application, here
        folder_01.files = qml_meegoharmattan/*
        folder_01.path = /opt/qtinfo/qml
    }
    target.path = /opt/qtinfo/bin
    INSTALLS += target folder_01
}

OTHER_FILES += \
    main.qml \
    qml_cascades/main.qml 

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

