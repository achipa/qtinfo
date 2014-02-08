TEMPLATE = subdirs

CONFIG += ordered

# The actual projects
SUBDIRS = \
          sqlinfolib \
          glinfolib \
          webkitinfolib \
          networkinfolib \
          mobilityinfolib \
          multimediainfolib \
          qtquickinfolib \
          declarativeui \
          qt5declarativeui \
          qtinfo 

qtinfo.depends = qtquickinfolib glinfolib webkitinfolib mobilityinfolib sqlinfolib multimediainfolib qtquickinfolib declarativeui

# Qt prior to 4.7 has no declarative module
contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    SUBDIRS -= qtquickinfolib declarativeui
    qtinfo.depends -= qtquickinfolib declarativeui
}
android {
    SUBDIRS -= webkitinfolib # no webkit on android for now
    qtinfo.depends -= webkitinfolib
}
message(CONFIG: $$CONFIG)
message(QT_MODULES: $$QT_MODULES)
contains(QT_MAJOR_VERSION,5) {
    SUBDIRS += qtquick2infolib
    qtinfo.depends += qtquick2infolib
    SUBDIRS -= mobilityinfolib # multimediainfolib
    qtinfo.depends -= mobilityinfolib # multimediainfolib
}

# Symbian doesn't do the GL module
symbian: {
    SUBDIRS -= glinfolib
    qtinfo.depends -= glinfolibs
}

# BB10 uses cascades, has no webkit, gl or the sysinfo from mobility libs
qnx {
    SUBDIRS += cascadesui bb10infolib
    qtinfo.depends += cascadesui bb10infolib
    SUBDIRS -= webkitinfolib
#glinfolib
    qtinfo.depends -= webkitinfolib
#glinfolib
}

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    qtc_packaging/meego.spec \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

unix:!symbian { # not funny
    target.path = /opt/qtinfo/bin
    INSTALLS += target
}

packagesExist(sailfishapp) {
    target.path = /usr/share/harbour-qtinfo/bin
    INSTALLS += target

# QT_MODULES:
# bluetooth compositor concurrent contacts core dbus declarative docgallery feedback gui location multimedia multimediawidgets network opengl openglextensions
# organizer platformsupport positioning publishsubscribe qml qtmultimediaquicktools quick quickparticles script scripttools sensors serviceframework sql svg
# versit versitorganizer webkit widgets xml xmlpatterns

}

symbian:OTHER_FILES += magic.pkg
